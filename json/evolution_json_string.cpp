#include "evolution_json_parse_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::UTILITY;



//IUnknown
u32 JsonString::AddRef(){
    return this->m_instance_counter.AddRef();
}

RESULT JsonString::QueryInterface(EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown *>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IJsonValue))
    {
        *ppvObject = static_cast<IJsonValue*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_JsonString))
    {
        *ppvObject = static_cast<JsonString*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }
    return RESULT::S_ok;
}

u32 JsonString::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

JsonString::JsonString(u32 parent_crc, u32 index, JsonSerialize* serialize) : m_parent_crc(parent_crc), m_str(nullptr), m_length(0), m_name(nullptr), mp_serialize(serialize){
    do{
        u64 crc_work = ((u64)parent_crc << 32) | serialize->MakeCRC32((u8*)&index, sizeof(index));
        this->m_crc = serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));
    } while (false);

    const char* str = serialize->GetKeyName();
    m_length = strlen(str);
    m_str = NEW char[m_length + 1];

    const char* s = str;
    char* d = this->m_str;
    //データコピー
    while (*d++ = *s++){}
}

JsonString::JsonString(u32 parent_crc, const char* my_name, JsonSerialize* serialize) : m_parent_crc(parent_crc), m_str(nullptr), m_length(0), mp_serialize(serialize){
    do{
        u32 name_len = strlen(my_name);
        m_name = NEW char[strlen(my_name) + 1];
        const char* s = my_name;
        char* d = m_name;
        while (*d++ = *s++){}
        u64 crc_work = ((u64)parent_crc << 32) | serialize->MakeCRC32((u8*)this->m_name, name_len);;
        this->m_crc = serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));
    } while (false);

    const char* str = serialize->GetKeyName();
    m_length = strlen(str);
    m_str = NEW char[m_length + 1];

    const char* s = str;
    char* d = this->m_str;
    //データコピー
    while (*d++ = *s++){}
}

JsonString::~JsonString(){
    EVOLUTION_DELETE_ARRAY(this->m_str);
    EVOLUTION_DELETE_ARRAY(this->m_name);
}

const char* JsonString::GetString()const{
    return this->m_str;
}

u32 JsonString::GetLength(const char* name)const{
    return this->m_length;
}
u32 JsonString::Crc32()const{
    return this->m_crc;
}
const char* JsonString::GetName()const{
    return this->m_name;
}