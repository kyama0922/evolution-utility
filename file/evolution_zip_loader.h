#ifndef __EVOLUTION_ZIPARCHIVE_H__
#define __EVOLUTION_ZIPARCHIVE_H__


#include <evolution.h>
#include <map>
#include "zlib/zlib.h"
namespace EVOLUTION{

    namespace TEMPLATE{
        template < class _T >class Array;
    }

    namespace UTILITY{

#pragma pack(push , 1)
        //Local file header
        struct LocalFileHeader{
            //u32 local_file_header_signature;//Local file header であることを示す固定値 0x04034B50 = 0x50, 0x4B, 0x03, 0x04
            u16 version_needed_to_extract;//展開に必要なZIPのバージョン
            u16 general_purpose_bit_flag;//オプションフラグ
            u16 compression_method;//ファイル圧縮に用いたアルゴリズム0 (無圧縮ファイル)8 (デフレート形式)
            u16 last_mod_file_time;//タイムスタンプ(時刻)
            u16 last_mod_file_date;//タイムスタンプ(日付)
            u32 crc_32;//ファイルのデータから算出した CRC-32 の値
            u32 compressed_size;//圧縮後のデータ量、File data のサイズ無圧縮なら uncompressed size フィールドと同値
            u32 uncompressed_size;//圧縮前のデータ量
            u16 file_name_length;//file name フィールドのサイズ
            u16  extra_field_length;//extra field フィールドのサイズ
            char* file_name;//ファイル名を格納する領域
            char* extra_field;//拡張データを格納する領域
        };

        //Data descriptor signature
        struct DataDescriptorSignature{
            //u32 data_descriptor_header_signature;//Data descriptor であることを示す固定値 0x08074B50 = 0x50, 0x4B, 0x07, 0x08
            u32 crc_32;//ファイルのデータから算出した CRC-32 の値
            u32 compressed_size;//圧縮後のデータ量、無圧縮なら uncompressed size と同値
            u32 uncompressed_size;//圧縮前のデータ量
        };

        //Central directory header
        struct CentralDirectoryHeader{
            //u32 central_file_header_signature;//Central directory header であることを示す固定値 0x02014B50 = 0x50, 0x4B, 0x01, 0x02
            u8 version_made_lower_byte;//アプリがサポートするZIPのバージョン 10 (ver.1.0) ⇒無圧縮ファイル 20 (ver.2.0) ⇒フォルダ、デフレート、パスワード保護 45 (ver.4.5) ⇒ZIP64
            u8 version_made_upper_byte;//OSの種類00 (MS-DOS) 03 (UNIX) 07 (Macintosh)
            u16 version_needed_to_extract;//展開に必要なZIPのバージョン
            u16 general_purpose_bit_flag;//オプションフラグ
            u16 compression_method;//ファイル圧縮に用いたアルゴリズム
            u16 last_mod_file_time;//タイムスタンプ(時刻)
            u16 last_mod_file_date;//タイムスタンプ(日付)
            u32 crc_32;//ファイルのデータから算出した CRC-32 の値
            u32 compressed_size;//圧縮後のデータ量、File data のサイズ無圧縮なら uncompressed size フィールドと同値
            u32 uncompressed_size;//圧縮前のデータ量
            u16 file_name_length;//file name フィールドのサイズ
            u16 extra_field_length;//extra field フィールドのサイズ
            u16 file_comment_length;//file_commentフィールドのサイズ
            u16 disk_number_start;//対応する Local file header が格納されているディスクの番号
            u16 internal_file_attributes;//データの属性(性質を示す)ビットフラグ0 (バイナリデータ)1 (ASCII、テキストファイル)
            u32 external_file_attributes;//ファイルの属性(読み込み専用とか隠しファイルとか)
            u32 relative_offset_of_local_header;//対応する Local file header までのオフセットZIPファイル先頭から(ディスク分割時はそのディスクの先頭から)のオフセット
            char* file_name;//ファイル名を格納する領域
            char* extra_field;//拡張データを格納する領域
            char* file_comment;//当該ファイルに対してのコメントを格納する領域
        };

        //End of central directory record
        struct EndOfCentralDirectoryRecord{
            u32 end_of_central_dir_signature;//End of central directory record であることを示す固定値 0x06054B50 = 0x50, 0x4B, 0x05, 0x06
            u16 number_of_this_disk;//このディスク(End of central directory record の有る)の番号ディスクの総数
            u16 number_of_the_disk_with_the_start_of_the_central_directory;//最初の Central directory header が有るディスクの番号
            u16 total_number_of_entries_in_the_central_directory_on_this_disk;//ディスク分割において、同じディスクから取得できる Central directory header の数
            u16 total_number_of_entries_in_the_central_directory;//ZIPファイルに格納してある Central directory header の総数
            u32 size_of_the_central_directory;//全ての Central directory header サイズの合計値
            u32 offset_of_start_of_central_directory_with_respect_to_the;//最初の Central directory header までのオフセット.ZIPファイル先頭から(ディスク分割時はそのディスクの先頭から)のオフセット
            u16 _ZIP_file_comment_length;//.ZIP file comment フィールドのサイズ
            u16 _ZIP_file_comment;//ZIPファイルに対してのコメントを格納する領域 (安全性は保証されない)
        };
#pragma pack(pop)
        class ZipLoader{
        private:
            const EVOLUTION::CORE::FILE::IFileRead* cp_fileloader;

            struct ZipFolder{
                u64 file_pos;
                LocalFileHeader* localfileheader;
                CentralDirectoryHeader* centraldirectoryheader;
            };

            std::map<u32, ZipFolder*> mp_file_table;
        public:
            ZipLoader(EVOLUTION::CORE::FILE::IFileRead& fileloader);
            ZipLoader(EVOLUTION::CORE::FILE::IFileRead* fileloader);

            ~ZipLoader();

            //Fileの存在確認
            bool IsFileCheck(const char* file_name);

            //file sizeの取得
            u32 GetFileSize(const char* file_name);

            //データの取得
            s32 GetData(const char* file_name, TEMPLATE::Array<char>& data);
        private:
            void TableLoad();

            void TableLoad_LocalFileHeader();
            void TableLoad_DataDescriptorSignature();

            void TableLoad_CentralDirectoryHeader();
            void TableLoad_EndOfCentralDirectoryRecord();
        };
    }
}
#endif //!__EVOLUTION_ZIPARCHIVE_H__