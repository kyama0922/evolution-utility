#include "evolution_json_parse_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::UTILITY;


//IUnknown
u32 JsonNull::AddRef(){
    return this->m_instance_counter.AddRef();
}

RESULT JsonNull::QueryInterface(EVOLUTION_IID riid, void **ppvObject){
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
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_JsonNull))
    {
        *ppvObject = static_cast<JsonNull*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }
    return _RESULT::S_ok;
}

u32 JsonNull::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}
JsonNull::JsonNull(u32 parent_crc, u32 index, JsonSerialize* serialize) : m_parent_crc(parent_crc), mp_serialize(serialize){
    u64 crc_work = ((u64)parent_crc << 32) | serialize->MakeCRC32((u8*)&index, sizeof(index));
    this->m_crc = serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));
}

JsonNull::JsonNull(u32 parent_crc, const char* my_name, JsonSerialize* serialize) : m_parent_crc(parent_crc), mp_serialize(serialize){
    u32 name_len = strlen(my_name);
    m_name = NEW char[strlen(my_name) + 1];
    const char* s = my_name;
    char* d = m_name;
    while (*d++ = *s++){}
    u64 crc_work = ((u64)parent_crc << 32) | serialize->MakeCRC32((u8*)this->m_name, name_len);
    this->m_crc = serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));
}

JsonNull::~JsonNull(){
    EVOLUTION_DELETE_ARRAY(this->m_name);
}


u32 JsonNull::Crc32()const{
    return this->m_crc;
}
const char* JsonNull::GetName()const{
    return this->m_name;
}
