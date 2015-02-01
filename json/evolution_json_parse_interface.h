#ifndef __EVOLUTION_JSON_PARSE_INTERFACE__
#define __EVOLUTION_JSON_PARSE_INTERFACE__

namespace EVOLUTION{
    namespace UTILITY{

        struct JsonException{
            enum _EXCEPTION{
                CONVERSION, //変換に失敗
                NO_INSTANCE, //インスタンスなし
            };
        };

        class IJsonObject;
        class IJsonValue :public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(IJsonValue);
        public:
            //このオブイェクトのCRC32を取得する
            virtual u32 Crc32()const = 0;
            //このオブイェクト名を取得する
            virtual const char* GetName()const = 0;
        };

        class IJsonArray : public IJsonValue{
            EVOLUTION_NOT_DESTRUCTOR(IJsonArray);
        public:
            //Arrayの要素数を返す
            virtual  u32 GetCount()const = 0;
            //インデックスからJsonObjectを取得参照カウントが1増加する(取得に失敗するとJsonExceptionをthrowする※破棄する場合は必ずReleaseを呼び出してください)
            virtual IJsonObject* GetJsonObject(u32 index) const = 0;
            //インデックスからJsonArrayを取得参照カウントが1増加する(取得に失敗するとJsonExceptionをthrowする※破棄する場合は必ずReleaseを呼び出してください)
            virtual IJsonArray* GetJsonArray(u32 index)const = 0;
            //インデックスから数字を取得する(取得に失敗するとJsonExceptionをthrowする)
            virtual double GetNumber(u32 index)const = 0;
            //インデックスから文字列を取得する(取得に失敗するとJsonExceptionをthrowする)
            virtual const char* GetString(u32 index)const = 0;
            //インデックスから真偽を取得する(取得に失敗するとJsonExceptionをthrowする)
            virtual bool GetBoolean(u32 index)const = 0;
        };

        class IJsonObject : public IJsonValue{
            EVOLUTION_NOT_DESTRUCTOR(IJsonObject);
        public:
            //名前から真偽を取得する(取得に失敗するとJsonExceptionをthrowする)
            virtual const bool GetBoolean(const char* name)const = 0;
            //名前から文字列を取得する(取得に失敗するとJsonExceptionをthrowする)
            virtual const char* GetString(const char* name)const = 0;
            //名前から数字を取得する(取得に失敗するとJsonExceptionをthrowする)
            virtual double GetNumber(const char* name)const = 0;
            //名前からJsonArrayを取得参照カウントが1増加する(取得に失敗するとJsonExceptionをthrowする※破棄する場合は必ずReleaseを呼び出してください)
            virtual IJsonArray* GetJsonArray(const char* name)const = 0;
            //名前からJsonObjectを取得参照カウントが1増加する(取得に失敗するとJsonExceptionをthrowする※破棄する場合は必ずReleaseを呼び出してください)
            virtual IJsonObject* GetJsonObject(const char* name)const = 0;
            //名前からオブジェクトを検索する
            virtual bool FindName(const char *pfind)const = 0;
            //このクラスが持っているオブジェクト数を返す
            virtual u32 GetObjectCount()const = 0;
            //オブジェクトが持っているオブジェクト名を返す
            virtual const char* GetObjectName(u32 index)const = 0;
        };

        class IJsonRoot : public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(IJsonRoot);
        public:
            //JsonObjectを取得参照カウントが1増加する(取得に失敗するとJsonExceptionをthrowする※破棄する場合は必ずReleaseを呼び出してください)
            virtual IJsonObject* GetJsonObject() = 0;
            //JsonArrayを取得参照カウントが1増加する(取得に失敗するとJsonExceptionをthrowする※破棄する場合は必ずReleaseを呼び出してください)
            virtual IJsonArray* GetJsonArray() = 0;
        };

    }

    namespace FUNCTION{
        //バッファからの読み込み
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