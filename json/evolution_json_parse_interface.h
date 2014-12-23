#ifndef __EVOLUTION_JSON_PARSE_INTERFACE__
#define __EVOLUTION_JSON_PARSE_INTERFACE__

namespace EVOLUTION{
    namespace UTILITY{

        struct JsonException{
            enum _EXCEPTION{
                CONVERSION, //�ϊ��Ɏ��s
                NO_INSTANCE, //�C���X�^���X�Ȃ�
            };
        };

        class IJsonObject;
        class IJsonValue :public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(IJsonValue);
        public:
            //���̃I�u�C�F�N�g��CRC32���擾����
            virtual u32 Crc32()const = 0;
            //���̃I�u�C�F�N�g�����擾����
            virtual const char* GetName()const = 0;
        };

        class IJsonArray : public IJsonValue{
            EVOLUTION_NOT_DESTRUCTOR(IJsonArray);
        public:
            //Array�̗v�f����Ԃ�
            virtual  u32 GetCount()const = 0;
            //�C���f�b�N�X����JsonObject���擾�Q�ƃJ�E���g��1��������(�擾�Ɏ��s�����JsonException��throw���遦�j������ꍇ�͕K��Release���Ăяo���Ă�������)
            virtual IJsonObject* GetJsonObject(u32 index) const = 0;
            //�C���f�b�N�X����JsonArray���擾�Q�ƃJ�E���g��1��������(�擾�Ɏ��s�����JsonException��throw���遦�j������ꍇ�͕K��Release���Ăяo���Ă�������)
            virtual IJsonArray* GetJsonArray(u32 index)const = 0;
            //�C���f�b�N�X���琔�����擾����(�擾�Ɏ��s�����JsonException��throw����)
            virtual double GetNumber(u32 index)const = 0;
            //�C���f�b�N�X���當������擾����(�擾�Ɏ��s�����JsonException��throw����)
            virtual const char* GetString(u32 index)const = 0;
            //�C���f�b�N�X����^�U���擾����(�擾�Ɏ��s�����JsonException��throw����)
            virtual bool GetBoolean(u32 index)const = 0;
        };

        class IJsonObject : public IJsonValue{
            EVOLUTION_NOT_DESTRUCTOR(IJsonObject);
        public:
            //���O����^�U���擾����(�擾�Ɏ��s�����JsonException��throw����)
            virtual const bool GetBoolean(const char* name)const = 0;
            //���O���當������擾����(�擾�Ɏ��s�����JsonException��throw����)
            virtual const char* GetString(const char* name)const = 0;
            //���O���琔�����擾����(�擾�Ɏ��s�����JsonException��throw����)
            virtual double GetNumber(const char* name)const = 0;
            //���O����JsonArray���擾�Q�ƃJ�E���g��1��������(�擾�Ɏ��s�����JsonException��throw���遦�j������ꍇ�͕K��Release���Ăяo���Ă�������)
            virtual IJsonArray* GetJsonArray(const char* name)const = 0;
            //���O����JsonObject���擾�Q�ƃJ�E���g��1��������(�擾�Ɏ��s�����JsonException��throw���遦�j������ꍇ�͕K��Release���Ăяo���Ă�������)
            virtual IJsonObject* GetJsonObject(const char* name)const = 0;
            //���O����I�u�W�F�N�g����������
            virtual bool FindName(const char *pfind)const = 0;
            //���̃N���X�������Ă���I�u�W�F�N�g����Ԃ�
            virtual u32 GetObjectCount()const = 0;
            //�I�u�W�F�N�g�������Ă���I�u�W�F�N�g����Ԃ�
            virtual const char* GetObjectName(u32 index)const = 0;
        };

        class IJsonRoot : public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(IJsonRoot);
        public:
            //JsonObject���擾�Q�ƃJ�E���g��1��������(�擾�Ɏ��s�����JsonException��throw���遦�j������ꍇ�͕K��Release���Ăяo���Ă�������)
            virtual IJsonObject* GetJsonObject() = 0;
            //JsonArray���擾�Q�ƃJ�E���g��1��������(�擾�Ɏ��s�����JsonException��throw���遦�j������ꍇ�͕K��Release���Ăяo���Ă�������)
            virtual IJsonArray* GetJsonArray() = 0;
        };

    }

    namespace FUNCTION{
        //�o�b�t�@����̓ǂݍ���
        extern RESULT CreateJsonRoot(UTILITY::IJsonRoot** root, const char* json, u32 work_size = 256);
    }

    namespace EVOLUTION_GUID{
        // {834DFD15-7443-405c-8319-CD9E8A8E5095}
        static const EVOLUTION_IID IID_IJsonValue =
        { 0x834dfd15, 0x7443, 0x405c, { 0x83, 0x19, 0xcd, 0x9e, 0x8a, 0x8e, 0x50, 0x95 } };

        // {3DA759A4-A357-49e7-92EC-B944273034B6}
        static const EVOLUTION_IID IID_IJsonArray =
        { 0x3da759a4, 0xa357, 0x49e7, { 0x92, 0xec, 0xb9, 0x44, 0x27, 0x30, 0x34, 0xb6 } };

        // {F07BF519-36E6-4f7f-99D7-C5D265706EEE}
        static const EVOLUTION_IID IID_IJsonObject =
        { 0xf07bf519, 0x36e6, 0x4f7f, { 0x99, 0xd7, 0xc5, 0xd2, 0x65, 0x70, 0x6e, 0xee } };

        // {03F4CCBB-FF64-4d5c-AB33-E6917CFF7690}
        static const EVOLUTION_IID IID_IJsonRoot =
        { 0x3f4ccbb, 0xff64, 0x4d5c, { 0xab, 0x33, 0xe6, 0x91, 0x7c, 0xff, 0x76, 0x90 } };

    }
}
#endif //__MONOBIT_JSON_PARSE__