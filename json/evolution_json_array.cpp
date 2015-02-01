#include "evolution_json_parse_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::UTILITY;

//IUnknown
u32 JsonArray::AddRef(){
    return this->m_instance_counter.AddRef();
}

RESULT JsonArray::QueryInterface(EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown *>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IJsonArray))
    {
        *ppvObject = static_cast<IJsonArray*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_JsonArray))
    {
        *ppvObject = static_cast<JsonArray*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }
    return _RESULT::S_ok;
}

u32 JsonArray::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

JsonArray::JsonArray(u32 parent_crc, u32 index, JsonSerialize* serialize) : m_parent_crc(parent_crc), m_name(nullptr), mp_serialize(serialize){
    u64 crc_work = ((u64)parent_crc << 32) | serialize->MakeCRC32((u8*)&index, sizeof(index));
    this->m_crc = serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));

    do{
        char c = serialize->Search("[]{}\"1234567890ntf");

        if (c == '['){
            serialize->SetIndex(serialize->GetIndex() + 1);
            IJsonValue* val = NEW JsonArray(this->m_crc, m_array.size() + 1, serialize);
            m_array.push_back(val);
        }
        else if (c == '{'){
            IJsonValue* val = NEW JsonObject(this->m_crc, m_array.size() + 1, serialize);
            m_array.push_back(val);
            serialize->SetIndex(serialize->GetIndex() + 1);
        }
        else if ('0' <= c && c <= '9'){
            IJsonValue* val = NEW JsonNumber(this->m_crc, m_array.size() + 1, serialize);
            m_array.push_back(val);
        }
        else if (c == '\"'){
            IJsonValue* val = NEW JsonString(this->m_crc, m_array.size() + 1, serialize);
            m_array.push_back(val);
        }
        else if (c == 'n'){
            IJsonValue* val = NEW JsonNull(this->m_crc, m_array.size() + 1, serialize);
            m_array.push_back(val);
        }
        else if (c == 'f'){
            IJsonValue* val = NEW JsonBoolean(this->m_crc, m_array.size() + 1, serialize, false);
            m_array.push_back(val);
        }
        else if (c == 't'){
            IJsonValue* val = NEW JsonBoolean(this->m_crc, m_array.size() + 1, serialize, true);
            m_array.push_back(val);
        }

    } while (*serialize->Skip(",]") != ']' && !serialize->IsEnd());
    serialize->SetIndex(serialize->GetIndex() + 1);
}

JsonArray::JsonArray(u32 parent_crc, const char* my_name, JsonSerialize* serialize) : m_parent_crc(parent_crc), mp_serialize(serialize){
    u32 name_len = strlen(my_name);
    m_name = NEW char[strlen(my_name) + 1];
    const char* s = my_name;
    char* d = m_name;
    while (*d++ = *s++){}
    u64 crc_work = ((u64)parent_crc << 32) | serialize->MakeCRC32((u8*)this->m_name, name_len);
    this->m_crc = serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));

    do{
        char c = serialize->Search("[]{}\"1234567890ntf");

        if (c == '['){
            serialize->SetIndex(serialize->GetIndex() + 1);
            IJsonValue* val = NEW JsonArray(this->m_crc, m_array.size() + 1, serialize);
            m_array.push_back(val);
        }
        else if (c == '{'){
            IJsonValue* val = NEW JsonObject(this->m_crc, m_array.size() + 1, serialize);
            m_array.push_back(val);
            serialize->SetIndex(serialize->GetIndex() + 1);
        }
        else if ('0' <= c && c <= '9'){
            IJsonValue* val = NEW JsonNumber(this->m_crc, m_array.size() + 1, serialize);
            m_array.push_back(val);
        }
        else if (c == '\"'){
            IJsonValue* val = NEW JsonString(this->m_crc, m_array.size() + 1, serialize);
            m_array.push_back(val);
        }
        else if (c == 'n'){
            IJsonValue* val = NEW JsonNull(this->m_crc, m_array.size() + 1, serialize);
            m_array.push_back(val);
        }
        else if (c == 'f'){
            IJsonValue* val = NEW JsonBoolean(this->m_crc, m_array.size() + 1, serialize, false);
            m_array.push_back(val);
        }
        else if (c == 't'){
            IJsonValue* val = NEW JsonBoolean(this->m_crc, m_array.size() + 1, serialize, true);
            m_array.push_back(val);
        }

    } while (*serialize->Skip(",]") != ']' && !serialize->IsEnd());
    serialize->SetIndex(serialize->GetIndex() + 1);
}

JsonArray::~JsonArray(){
    EVOLUTION_DELETE_ARRAY(this->m_name);
    for (std::vector<IJsonValue*>::iterator it = this->m_array.begin(); it != this->m_array.end(); it++)
    {
        IUnknown* unknown = (IUnknown*)(*it);
        EVOLUTION_DELETE(unknown);
    }
}


u32 JsonArray::GetCount()const{
    return this->m_array.size();
}

IJsonObject* JsonArray::GetJsonObject(u32 index) const{
    IJsonObject* _object;
    RESULT result = m_array[index]->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_IJsonObject, (void**)&_object);
    if (result != EVOLUTION::_RESULT::S_ok)
    {
        throw JsonException::CONVERSION;
    }
    return _object;
}

IJsonArray* JsonArray::GetJsonArray(u32 index)const{
    IJsonArray* _array;
    RESULT result = m_array[index]->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_IJsonArray, (void**)&_array);
    if (result != EVOLUTION::_RESULT::S_ok)
    {
        throw JsonException::CONVERSION;
    }
    return _array;
}

bool JsonArray::GetBoolean(u32 index)const{
    JsonBoolean* boolean;
    RESULT result = m_array[index]->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_JsonBoolean, (void**)&boolean);
    if (result != EVOLUTION::_RESULT::S_ok)
    {
        throw JsonException::CONVERSION;
    }
    bool ret = boolean->GetBoolean();
    boolean->Release();
    return ret;
}

double JsonArray::GetNumber(u32 index)const{
    JsonNumber* number;
    RESULT result = m_array[index]->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_JsonNumber, (void**)&number);
    if (result != EVOLUTION::_RESULT::S_ok)
    {
        throw JsonException::CONVERSION;
    }
    double ret = number->GetNumber();
    number->Release();
    return ret;
}

const char* JsonArray::GetString(u32 index)const{
    JsonString* str;
    RESULT result = m_array[index]->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_JsonNumber, (void**)&str);
    if (result != EVOLUTION::_RESULT::S_ok)
    {
        throw JsonException::CONVERSION;
    }
    const char* ret = str->GetString();
    str->Release();
    return ret;
}

u32 JsonArray::Crc32()const{
    return this->m_crc;
}
const char* JsonArray::GetName()const{
    return this->m_name;
}
