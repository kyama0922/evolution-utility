#ifndef __EVOLUTION_JSON_PARSE__
#define __EVOLUTION_JSON_PARSE__

#include <evolution_type.h>
#include "evolution_json_parse_interface.h"
#include <map>
#include <vector>

#ifndef NEW
#define NEW new
#endif

namespace EVOLUTION{
    namespace UTILITY{

        class JsonSerialize{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;

            const char* const str_master;
            const char* str_json;
            const u32 m_json_len;
            u32 m_index;
            char* mp_buffer;
            u32 m_buffer_count;
            u32 crc_table[256];
        public:
            JsonSerialize(const char* json, u32 buffer_count);
            ~JsonSerialize();

            char Search(const char* key);

            const char*  SkipIgnore(const char* key);

            const char*  Skip(const char* key);

            const char* GetKeyName();

            double GetNumber();

            bool IsEnd();

            void SetIndex(u32 index);
            u32 GetIndex();

            u32 MakeCRC32(const u8 *buf, u32 len)const;
        };

        //Number
        class JsonNumber : public IJsonValue{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;

            u32 m_crc;
            char* m_name;
            u32 m_parent_crc;
            double m_number;
            const JsonSerialize* mp_serialize;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            JsonNumber(u32 parent_crc, u32 index, JsonSerialize* serialize);
            JsonNumber(u32 parent_crc, const char* my_name, JsonSerialize* serialize);
            ~JsonNumber();

            double GetNumber()const;
            u32 Crc32()const;
            const char* GetName()const;
        };

        //Null
        class JsonNull : public IJsonValue{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;

            u32 m_crc;
            char* m_name;
            u32 m_parent_crc;
            const JsonSerialize* mp_serialize;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            JsonNull(u32 parent_crc, u32 index, JsonSerialize* serialize);
            JsonNull(u32 parent_crc, const char* my_name, JsonSerialize* serialize);
            ~JsonNull();

            u32 Crc32()const;
            const char* GetName()const;
        };

        //Boolean
        class JsonBoolean : public IJsonValue{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;

            u32 m_crc;
            char* m_name;
            u32 m_parent_crc;
            const JsonSerialize* mp_serialize;
            bool m_value;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            JsonBoolean(u32 parent_crc, u32 index, JsonSerialize* serialize, bool val);
            JsonBoolean(u32 parent_crc, const char* my_name, JsonSerialize* serialize, bool val);
            ~JsonBoolean();

            bool GetBoolean()const;
            u32 Crc32()const;
            const char* GetName()const;
        };

        //String
        class JsonString : public IJsonValue{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;

            u32 m_crc;
            char* m_name;
            u32 m_parent_crc;
            const JsonSerialize* mp_serialize;
            char* m_str;
            u32 m_length;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            JsonString(u32 parent_crc, u32 index, JsonSerialize* serialize);
            JsonString(u32 parent_crc, const char* my_name, JsonSerialize* serialize);
            ~JsonString();



            const char* GetString()const;

            u32 GetLength(const char* name)const;
            u32 Crc32()const;
            const char* GetName()const;
        };

        class JsonArray : public IJsonArray{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;

            u32 m_crc;
            char* m_name;
            u32 m_parent_crc;
            const JsonSerialize* mp_serialize;
            std::vector <IJsonValue*> m_array;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            JsonArray(u32 parent_crc, u32 index, JsonSerialize* serialize);
            JsonArray(u32 parent_crc, const char* my_name, JsonSerialize* serialize);
            ~JsonArray();


            u32 GetCount()const;
            IJsonObject* GetJsonObject(u32 index) const;
            IJsonArray* JsonArray::GetJsonArray(u32 index)const;
            double GetNumber(u32 index)const;
            const char* GetString(u32 index)const;
            bool GetBoolean(u32 index)const;

            u32 Crc32()const;
            const char* GetName()const;
        };

        class JsonObject : public IJsonObject{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;

            u32 m_crc;
            char* m_name;
            u32 m_parent_crc;
            const JsonSerialize* mp_serialize;
            std::map<u32, IJsonValue*> m_object;
            std::vector<const char*> m_object_names;
        public:

            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            JsonObject(u32 parent_crc, u32 index, JsonSerialize* serialize);
            JsonObject(u32 parent_crc, const char* my_name, JsonSerialize* serialize);
            ~JsonObject();


            const bool GetBoolean(const char* name)const;

            const char* GetString(const char* name)const;

            double GetNumber(const char* name)const;

            IJsonArray* GetJsonArray(const char* name)const;

            IJsonObject* GetJsonObject(const char* name)const;


            u32 GetObjectCount()const;

            const char* GetObjectName(u32 index)const;

            u32 Crc32()const;

            const char* GetName()const;

            bool FindName(const char *pfind)const;
        };


        class JsonRoot :public IJsonRoot{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;

            JsonSerialize m_json_serialize;
            IJsonValue* mp_value;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            JsonRoot(const char* json, u32 buffer_size);
            ~JsonRoot();

            IJsonObject* GetJsonObject();

            IJsonArray* GetJsonArray();
        };
    }

    namespace EVOLUTION_GUID{

        // {B37963DB-37F4-44cd-AAD0-B6E4A44E8527}
        static const EVOLUTION_IID IID_JsonNumber =
        { 0xb37963db, 0x37f4, 0x44cd, { 0xaa, 0xd0, 0xb6, 0xe4, 0xa4, 0x4e, 0x85, 0x27 } };

        // {B9C4A7A8-E382-4923-919C-7C3718B741F8}
        static const EVOLUTION_IID IID_JsonNull =
        { 0xb9c4a7a8, 0xe382, 0x4923, { 0x91, 0x9c, 0x7c, 0x37, 0x18, 0xb7, 0x41, 0xf8 } };

        // {2BA357BF-7BFB-4cd8-8FA5-CC9614EA89D0}
        static const EVOLUTION_IID IID_JsonBoolean =
        { 0x2ba357bf, 0x7bfb, 0x4cd8, { 0x8f, 0xa5, 0xcc, 0x96, 0x14, 0xea, 0x89, 0xd0 } };

        // {E41F98B0-F538-4acd-B51D-0C40CE34FC34}
        static const EVOLUTION_IID IID_JsonString =
        { 0xe41f98b0, 0xf538, 0x4acd, { 0xb5, 0x1d, 0xc, 0x40, 0xce, 0x34, 0xfc, 0x34 } };

        // {212A4B18-B488-476a-B98B-97A43646925B}
        static const EVOLUTION_IID IID_JsonArray =
        { 0x212a4b18, 0xb488, 0x476a, { 0xb9, 0x8b, 0x97, 0xa4, 0x36, 0x46, 0x92, 0x5b } };

        // {46CD8579-3D48-4901-830E-AA299C721D1C}
        static const EVOLUTION_IID IID_JsonObject =
        { 0x46cd8579, 0x3d48, 0x4901, { 0x83, 0xe, 0xaa, 0x29, 0x9c, 0x72, 0x1d, 0x1c } };

        // {D752D67E-C635-4ec5-B45F-0AB8992738DD}
        static const EVOLUTION_IID IID_JsonRoot =
        { 0xd752d67e, 0xc635, 0x4ec5, { 0xb4, 0x5f, 0xa, 0xb8, 0x99, 0x27, 0x38, 0xdd } };

    }
}

#endif
