#include "../evolution_utility.h"
#include "evolution_zip_loader.h"

#define ZIP_LOCALFILEHEADER 0x04034B50
#define ZIP_DATADESCRIPTORSIGNATURE 0x08074B50
#define ZIP_CENTRALDIRECTORYHEADER 0x02014B50
#define ZIP_ENDOFCENTRALDIRECTORYRECORD 0x06054B50

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::UTILITY;

ZipLoader::ZipLoader(EVOLUTION::CORE::FILE::IFileRead& fileloader) : cp_fileloader(&fileloader) {
    this->TableLoad();
}

ZipLoader::ZipLoader(EVOLUTION::CORE::FILE::IFileRead* fileloader) : cp_fileloader(fileloader) {
    this->TableLoad();
}

ZipLoader::~ZipLoader() {
    for (std::map<u32, ZipFolder*>::iterator it = mp_file_table.begin(); it != mp_file_table.end(); it++) {
        ZipFolder* zipfolder = (*it).second;

        //Central directory headerの開放
        EVOLUTION_DELETE_ARRAY(zipfolder->centraldirectoryheader->file_name);
        EVOLUTION_DELETE_ARRAY(zipfolder->centraldirectoryheader->extra_field);
        EVOLUTION_DELETE_ARRAY(zipfolder->centraldirectoryheader->file_comment);
        EVOLUTION_DELETE(zipfolder->centraldirectoryheader);

        //local fileheaderの開放
        EVOLUTION_DELETE_ARRAY(zipfolder->localfileheader->file_name);
        EVOLUTION_DELETE_ARRAY(zipfolder->localfileheader->extra_field);
        EVOLUTION_DELETE(zipfolder->localfileheader);

        //Zip folderの開放
        EVOLUTION_DELETE(zipfolder);
    }
}

//Fileの存在確認

bool ZipLoader::IsFileCheck(const char* file_name) {
    u32 hash = Hash::GetInstance()->CRC32((u8*) file_name, strlen(file_name));
    return this->mp_file_table.find(hash) != this->mp_file_table.end();
}

//file sizeの取得

u32 ZipLoader::GetFileSize(const char* file_name) {
    u32 hash = Hash::GetInstance()->CRC32((u8*) file_name, strlen(file_name));
    return this->mp_file_table[hash]->localfileheader->compressed_size;
}

//データの取得

s32 ZipLoader::GetData(const char* file_name, TEMPLATE::Array<char>& data) {

    u32 hash = Hash::GetInstance()->CRC32((u8*) file_name, strlen(file_name));
    ZipFolder* zip_folder = this->mp_file_table[hash];

    EVOLUTION_ASSERT_LOG(zip_folder->localfileheader->compressed_size == data.GetMaxCount());

    this->cp_fileloader->SetPos(zip_folder->file_pos);
    this->cp_fileloader->Read(data.GetArray(), zip_folder->localfileheader->compressed_size);
    return 0;
}

void ZipLoader::TableLoad() {
    while (this->cp_fileloader->IsEof()) {
        u32 signature;
        this->cp_fileloader->Read(&signature, sizeof (u32));
        switch (signature) {
            case ZIP_LOCALFILEHEADER:
                this->TableLoad_LocalFileHeader();
                break;
            case ZIP_DATADESCRIPTORSIGNATURE:
                this->TableLoad_DataDescriptorSignature();
                break;
            case ZIP_CENTRALDIRECTORYHEADER:
                this->TableLoad_CentralDirectoryHeader();
                break;
            case ZIP_ENDOFCENTRALDIRECTORYRECORD:
                this->TableLoad_EndOfCentralDirectoryRecord();
                break;
            default:
                EVOLUTION_ASSERT(0);
                break;
        }
    }
}

void ZipLoader::TableLoad_LocalFileHeader() {
    LocalFileHeader* localfileheader = new LocalFileHeader();
    memset(localfileheader, 0, sizeof (LocalFileHeader));

    this->cp_fileloader->Read(localfileheader, sizeof (LocalFileHeader)-(sizeof (void*)* 2));
    //ファイル名の読み込み
    localfileheader->file_name = new char[localfileheader->file_name_length + 1];
    memset(localfileheader->file_name, 0, localfileheader->file_name_length + 1);
    this->cp_fileloader->Read(localfileheader->file_name, localfileheader->file_name_length);

    if (localfileheader->extra_field_length != 0) {
        localfileheader->extra_field = new char[localfileheader->extra_field_length + 1];
        this->cp_fileloader->Read(localfileheader->extra_field, localfileheader->extra_field_length);
    }
    //無圧縮のみサポート
    if (localfileheader->version_needed_to_extract == 0x0A) {
        //ERROR処理
    }
    ZipFolder* zipfolder = new ZipFolder();
    zipfolder->file_pos = this->cp_fileloader->GetPos();
    zipfolder->localfileheader = localfileheader;

    u32 hash = Hash::GetInstance()->CRC32((u8*) localfileheader->file_name, localfileheader->file_name_length);
    this->mp_file_table[hash] = zipfolder;
    this->cp_fileloader->SetPos(this->cp_fileloader->GetPos() + localfileheader->compressed_size);
}

void ZipLoader::TableLoad_DataDescriptorSignature() {

}

void ZipLoader::TableLoad_CentralDirectoryHeader() {
    CentralDirectoryHeader* centraldirectoryheader = new CentralDirectoryHeader();
    memset(centraldirectoryheader, 0, sizeof (CentralDirectoryHeader));
    this->cp_fileloader->Read(centraldirectoryheader, sizeof (CentralDirectoryHeader)-(sizeof (void*)* 3));
    //ファイル名の読み込み
    centraldirectoryheader->file_name = new char[centraldirectoryheader->file_name_length + 1];
    memset(centraldirectoryheader->file_name, 0, centraldirectoryheader->file_name_length + 1);
    this->cp_fileloader->Read(centraldirectoryheader->file_name, centraldirectoryheader->file_name_length);
    //拡張モードの読み込み
    if (centraldirectoryheader->extra_field_length != 0) {
        centraldirectoryheader->extra_field = new char[centraldirectoryheader->extra_field_length + 1];
        this->cp_fileloader->Read(centraldirectoryheader->extra_field, centraldirectoryheader->extra_field_length);
    }
    //ファイルコメントの読み込み
    if (centraldirectoryheader->file_comment_length != 0) {
        centraldirectoryheader->file_comment = new char[centraldirectoryheader->file_comment_length + 1];
        this->cp_fileloader->Read(centraldirectoryheader->file_comment, centraldirectoryheader->file_comment_length);
    }

    u32 hash = Hash::GetInstance()->CRC32((u8*) centraldirectoryheader->file_name, centraldirectoryheader->file_name_length);
    ZipFolder* zipfolder = this->mp_file_table[hash];
    zipfolder->centraldirectoryheader = centraldirectoryheader;
}

void ZipLoader::TableLoad_EndOfCentralDirectoryRecord() {
    EndOfCentralDirectoryRecord endofcentraldirectoryrecord;
    memset(&endofcentraldirectoryrecord, 0, sizeof (endofcentraldirectoryrecord));
    this->cp_fileloader->Read(&endofcentraldirectoryrecord, sizeof (EndOfCentralDirectoryRecord));

}
