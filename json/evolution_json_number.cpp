#include "evolution_json_parse_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::UTILITY;



//IUnknown
u32 JsonNumber::AddRef(){
    return this->m_instance_counter.AddRef();
}

RESULT JsonNumber::QueryInterface(EVOLUTION_IID riid, void **ppvObject){
    if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown *>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IJsonValue))
    {
        *ppvObject = static_cast<IJsonValue*>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_JsonNumber))
    {
        *ppvObject = static_cast<JsonNumber*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }
    return RESULT::S_ok;
}

u32 JsonNumber::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

JsonNumber::JsonNumber(u32 parent_crc, u32 index, JsonSerialize* serialize) : m_parent_crc(parent_crc), m_number(0), m_name(nullptr), mp_serialize(serialize){
    u64 crc_work = ((u64)parent_crc << 32) | serialize->MakeCRC32((u8*)&index, sizeof(index));
    this->m_crc = serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));

    serialize->SetIndex(serialize->GetIndex() - 1);
    m_number = serialize->GetNumber();
}

JsonNumber::JsonNumber(u32 parent_crc, const char* my_name, JsonSerialize* serialize) : m_parent_crc(parent_crc), m_number(0), mp_serialize(serialize){
    u32 name_len = strlen(my_name);
    m_name = NEW char[strlen(my_name) + 1];
    const char* s = my_name;
    char* d = m_name;
    while (*d++ = *s++){}
    u64 crc_work = ((u64)parent_crc << 32) | serialize->MakeCRC32((u8*)this->m_name, name_len);;
    this->m_crc = serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));

    serialize->SetIndex(serialize->GetIndex() - 1);
    m_number = serialize->GetNumber();
}

JsonNumber::~JsonNumber(){
    EVOLUTION_DELETE_ARRAY(this->m_name);
}


double JsonNumber::GetNumber()const{
    return this->m_number;
}
u32 JsonNumber::Crc32()const{
    return this->m_crc;
}
const char* JsonNumber::GetName()const{
    return this->m_name;
}
