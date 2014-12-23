#ifndef __EVOLUTION_ZIPARCHIVE_H__
#define __EVOLUTION_ZIPARCHIVE_H__


#include <evolution.h>
#include <map>
#include "zlib\zlib.h"
namespace EVOLUTION{

    namespace TEMPLATE{
        template < class _T >class Array;
    }

    namespace UTILITY{

#pragma pack(push , 1)
        //Local file header
        struct LocalFileHeader{
            //u32 local_file_header_signature;//Local file header �ł��邱�Ƃ������Œ�l 0x04034B50 = 0x50, 0x4B, 0x03, 0x04
            u16 version_needed_to_extract;//�W�J�ɕK�v��ZIP�̃o�[�W����
            u16 general_purpose_bit_flag;//�I�v�V�����t���O
            u16 compression_method;//�t�@�C�����k�ɗp�����A���S���Y��0 (�����k�t�@�C��)8 (�f�t���[�g�`��)
            u16 last_mod_file_time;//�^�C���X�^���v(����)
            u16 last_mod_file_date;//�^�C���X�^���v(���t)
            u32 crc_32;//�t�@�C���̃f�[�^����Z�o���� CRC-32 �̒l
            u32 compressed_size;//���k��̃f�[�^�ʁAFile data �̃T�C�Y�����k�Ȃ� uncompressed size �t�B�[���h�Ɠ��l
            u32 uncompressed_size;//���k�O�̃f�[�^��
            u16 file_name_length;//file name �t�B�[���h�̃T�C�Y
            u16  extra_field_length;//extra field �t�B�[���h�̃T�C�Y
            char* file_name;//�t�@�C�������i�[����̈�
            char* extra_field;//�g���f�[�^���i�[����̈�
        };

        //Data descriptor signature
        struct DataDescriptorSignature{
            //u32 data_descriptor_header_signature;//Data descriptor �ł��邱�Ƃ������Œ�l 0x08074B50 = 0x50, 0x4B, 0x07, 0x08
            u32 crc_32;//�t�@�C���̃f�[�^����Z�o���� CRC-32 �̒l
            u32 compressed_size;//���k��̃f�[�^�ʁA�����k�Ȃ� uncompressed size �Ɠ��l
            u32 uncompressed_size;//���k�O�̃f�[�^��
        };

        //Central directory header
        struct CentralDirectoryHeader{
            //u32 central_file_header_signature;//Central directory header �ł��邱�Ƃ������Œ�l 0x02014B50 = 0x50, 0x4B, 0x01, 0x02
            u8 version_made_lower_byte;//�A�v�����T�|�[�g����ZIP�̃o�[�W���� 10 (ver.1.0) �˖����k�t�@�C�� 20 (ver.2.0) �˃t�H���_�A�f�t���[�g�A�p�X���[�h�ی� 45 (ver.4.5) ��ZIP64
            u8 version_made_upper_byte;//OS�̎��00 (MS-DOS) 03 (UNIX) 07 (Macintosh)
            u16 version_needed_to_extract;//�W�J�ɕK�v��ZIP�̃o�[�W����
            u16 general_purpose_bit_flag;//�I�v�V�����t���O
            u16 compression_method;//�t�@�C�����k�ɗp�����A���S���Y��
            u16 last_mod_file_time;//�^�C���X�^���v(����)
            u16 last_mod_file_date;//�^�C���X�^���v(���t)
            u32 crc_32;//�t�@�C���̃f�[�^����Z�o���� CRC-32 �̒l
            u32 compressed_size;//���k��̃f�[�^�ʁAFile data �̃T�C�Y�����k�Ȃ� uncompressed size �t�B�[���h�Ɠ��l
            u32 uncompressed_size;//���k�O�̃f�[�^��
            u16 file_name_length;//file name �t�B�[���h�̃T�C�Y
            u16 extra_field_length;//extra field �t�B�[���h�̃T�C�Y
            u16 file_comment_length;//file_comment�t�B�[���h�̃T�C�Y
            u16 disk_number_start;//�Ή����� Local file header ���i�[����Ă���f�B�X�N�̔ԍ�
            u16 internal_file_attributes;//�f�[�^�̑���(����������)�r�b�g�t���O0 (�o�C�i���f�[�^)1 (ASCII�A�e�L�X�g�t�@�C��)
            u32 external_file_attributes;//�t�@�C���̑���(�ǂݍ��ݐ�p�Ƃ��B���t�@�C���Ƃ�)
            u32 relative_offset_of_local_header;//�Ή����� Local file header �܂ł̃I�t�Z�b�gZIP�t�@�C���擪����(�f�B�X�N�������͂��̃f�B�X�N�̐擪����)�̃I�t�Z�b�g
            char* file_name;//�t�@�C�������i�[����̈�
            char* extra_field;//�g���f�[�^���i�[����̈�
            char* file_comment;//���Y�t�@�C���ɑ΂��ẴR�����g���i�[����̈�
        };

        //End of central directory record
        struct EndOfCentralDirectoryRecord{
            u32 end_of_central_dir_signature;//End of central directory record �ł��邱�Ƃ������Œ�l 0x06054B50 = 0x50, 0x4B, 0x05, 0x06
            u16 number_of_this_disk;//���̃f�B�X�N(End of central directory record �̗L��)�̔ԍ��f�B�X�N�̑���
            u16 number_of_the_disk_with_the_start_of_the_central_directory;//�ŏ��� Central directory header ���L��f�B�X�N�̔ԍ�
            u16 total_number_of_entries_in_the_central_directory_on_this_disk;//�f�B�X�N�����ɂ����āA�����f�B�X�N����擾�ł��� Central directory header �̐�
            u16 total_number_of_entries_in_the_central_directory;//ZIP�t�@�C���Ɋi�[���Ă��� Central directory header �̑���
            u32 size_of_the_central_directory;//�S�Ă� Central directory header �T�C�Y�̍��v�l
            u32 offset_of_start_of_central_directory_with_respect_to_the;//�ŏ��� Central directory header �܂ł̃I�t�Z�b�g.ZIP�t�@�C���擪����(�f�B�X�N�������͂��̃f�B�X�N�̐擪����)�̃I�t�Z�b�g
            u16 _ZIP_file_comment_length;//.ZIP file comment �t�B�[���h�̃T�C�Y
            u16 _ZIP_file_comment;//ZIP�t�@�C���ɑ΂��ẴR�����g���i�[����̈� (���S���͕ۏ؂���Ȃ�)
        };
#pragma pack(pop)
        class ZipLoader{
        private:
            const EVOLUTION::CORE::FILE::IFileRead* cp_fileloader;

            struct ZipFolder{
                fpos_t file_pos;
                LocalFileHeader* localfileheader;
                CentralDirectoryHeader* centraldirectoryheader;
            };

            std::map<u32, ZipFolder*> mp_file_table;
        public:
            ZipLoader(EVOLUTION::CORE::FILE::IFileRead& fileloader);
            ZipLoader(EVOLUTION::CORE::FILE::IFileRead* fileloader);

            ~ZipLoader();

            //File�̑��݊m�F
            bool IsFileCheck(const char* file_name);

            //file size�̎擾
            u32 GetFileSize(const char* file_name);

            //�f�[�^�̎擾
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