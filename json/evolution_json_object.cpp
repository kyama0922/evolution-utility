#include "evolution_json_parse_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::UTILITY;

//IUnknown
u32 JsonObject::AddRef(){
    return this->m_instance_counter.AddRef();
}

RESULT JsonObject::QueryInterface(EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown *>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IJsonObject))
    {
        *ppvObject = static_cast<IJsonObject*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_JsonObject))
    {
        *ppvObject = static_cast<JsonObject*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }
    return _RESULT::S_ok;
}

u32 JsonObject::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

JsonObject::JsonObject(u32 parent_crc, u32 index, JsonSerialize* serialize) : m_parent_crc(parent_crc), m_name(nullptr), mp_serialize(serialize){
    u64 crc_work = ((u64)parent_crc << 32) | serialize->MakeCRC32((u8*)&index, sizeof(index));
    this->m_crc = serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));

    do{
        const char* name = serialize->GetKeyName();

        char c = serialize->Search("[]{}\"1234567890ntf");

        if (c == '['){
            serialize->SetIndex(serialize->GetIndex() + 1);
            IJsonValue* val = NEW JsonArray(this->m_crc, name, serialize);
            m_object[val->Crc32()] = val;
        }
        else if (c == '{'){
            IJsonValue* val = NEW JsonObject(this->m_crc, name, serialize);
            m_object[val->Crc32()] = val;
            serialize->SetIndex(serialize->GetIndex() + 1);
        }
        else if ('0' <= c && c <= '9'){
            IJsonValue* val = NEW JsonNumber(this->m_crc, name, serialize);
            m_object[val->Crc32()] = val;
        }
        else if (c == '\"'){
            IJsonValue* val = NEW JsonString(this->m_crc, name, serialize);
            m_object[val->Crc32()] = val;
        }
        else if (c == 'n'){
            IJsonValue* val = NEW JsonNull(this->m_crc, name, serialize);
            m_object[val->Crc32()] = val;
        }
        else if (c == 'f'){
            IJsonValue* val = NEW JsonBoolean(this->m_crc, name, serialize, false);
            m_object[val->Crc32()] = val;
        }
        else if (c == 't'){
            IJsonValue* val = NEW JsonBoolean(this->m_crc, name, serialize, true);
            m_object[val->Crc32()] = val;
        }

    } while (!serialize->IsEnd() && *serialize->Skip(",}") != '}');

    m_object_names.reserve(m_object.size());
    for (std::map<u32, IJsonValue*>::iterator it = m_object.begin(); it != m_object.end(); it++)
    {
        m_object_names.push_back((*it).second->GetName());
    }
}

JsonObject::JsonObject(u32 parent_crc, const char* my_name, JsonSerialize* serialize) : m_parent_crc(parent_crc), m_name(nullptr), mp_serialize(serialize){
    u32 name_len = strlen(my_name);
    m_name = NEW char[strlen(my_name) + 1];
    const char* s = my_name;
    char* d = m_name;
    while (*d++ = *s++){}
    u64 crc_work = ((u64)parent_crc << 32) | serialize->MakeCRC32((u8*)this->m_name, name_len);
    this->m_crc = serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));

    do{
        const char* name = serialize->GetKeyName();

        char c = serialize->Search("[]{}\"1234567890ntf");

        if (c == '['){
            serialize->SetIndex(serialize->GetIndex() + 1);
            IJsonValue* val = NEW JsonArray(this->m_crc, name, serialize);
            m_object[val->Crc32()] = val;
        }
        else if (c == '{'){
            IJsonValue* val = NEW JsonObject(this->m_crc, name, serialize);
            m_object[val->Crc32()] = val;
            serialize->SetIndex(serialize->GetIndex() + 1);
        }
        else if ('0' <= c && c <= '9'){
            IJsonValue* val = NEW JsonNumber(this->m_crc, name, serialize);
            m_object[val->Crc32()] = val;
        }
        else if (c == '\"'){
            IJsonValue* val = NEW JsonString(this->m_crc, name, serialize);
            m_object[val->Crc32()] = val;
        }
        else if (c == 'n'){
            IJsonValue* val = NEW JsonNull(this->m_crc, name, serialize);
            m_object[val->Crc32()] = val;
        }
        else if (c == 'f'){
            IJsonValue* val = NEW JsonBoolean(this->m_crc, name, serialize, false);
            m_object[val->Crc32()] = val;
        }
        else if (c == 't'){
            IJsonValue* val = NEW JsonBoolean(this->m_crc, name, serialize, true);
            m_object[val->Crc32()] = val;
        }

    } while (!serialize->IsEnd() && *serialize->Skip(",}") != '}');

    m_object_names.reserve(m_object.size());
    for (std::map<u32, IJsonValue*>::iterator it = m_object.begin(); it != m_object.end(); it++)
    {
        m_object_names.push_back((*it).second->GetName());
    }
}

JsonObject::~JsonObject(){
    EVOLUTION_DELETE_ARRAY(this->m_name);
    for (std::map<u32, IJsonValue*>::iterator it = this->m_object.begin(); it != this->m_object.end(); it++)
    {
        IJsonValue* val = (*it).second;
        EVOLUTION_RELEASE(val);
    }
}

const bool  JsonObject::GetBoolean(const char* name)const{
    u64 crc_work = ((u64)this->m_crc << 32) | this->mp_serialize->MakeCRC32((u8*)name, strlen(name));
    u32 crc32 = this->mp_serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));

    std::map< u32, IJsonValue*>::const_iterator it = this->m_object.find(crc32);
    if (it != this->m_object.end()){
        JsonBoolean* boolean;
        RESULT result = it->second->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_JsonBoolean, (void**)&boolean);
        if (result != EVOLUTION::_RESULT::S_ok)
        {
            throw JsonException::CONVERSION;
        }
        bool ret = boolean->GetBoolean();
        boolean->Release();
        return ret;
    }
    throw JsonException::NO_INSTANCE;
}

const char*  JsonObject::GetString(const char* name)const{
    u64 crc_work = ((u64)this->m_crc << 32) | this->mp_serialize->MakeCRC32((u8*)name, strlen(name));
    u32 crc32 = this->mp_serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));

    std::map< u32, IJsonValue*>::const_iterator it = this->m_object.find(crc32);
    if (it != this->m_object.end()){
        JsonString* str;
        RESULT result = it->second->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_JsonString, (void**)&str);
        if (result != EVOLUTION::_RESULT::S_ok)
        {
            throw JsonException::CONVERSION;
        }
        const char* ret = str->GetString();
        str->Release();
        return ret;
    }
    throw JsonException::NO_INSTANCE;
}

double  JsonObject::GetNumber(const char* name)const{
    u64 crc_work = ((u64)this->m_crc << 32) | this->mp_serialize->MakeCRC32((u8*)name, strlen(name));
    u32 crc32 = this->mp_serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));

    std::map< u32, IJsonValue*>::const_iterator it = this->m_object.find(crc32);
    if (it != this->m_object.end()){
        JsonNumber* number;
        RESULT result = it->second->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_JsonNumber, (void**)&number);
        if (result != EVOLUTION::_RESULT::S_ok)
        {
            throw JsonException::CONVERSION;
        }
        double ret = number->GetNumber();
        number->Release();
        return ret;
    }
    throw JsonException::NO_INSTANCE;
}

IJsonArray*  JsonObject::GetJsonArray(const char* name)const{
    u64 crc_work = ((u64)this->m_crc << 32) | this->mp_serialize->MakeCRC32((u8*)name, strlen(name));
    u32 crc32 = this->mp_serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));

    std::map< u32, IJsonValue*>::const_iterator it = this->m_object.find(crc32);
    if (it != this->m_object.end()){
        IJsonArray* _array;
        RESULT result = it->second->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_IJsonArray, (void**)&_array);
        if (result != EVOLUTION::_RESULT::S_ok)
        {
            throw JsonException::CONVERSION;
        }
        return _array;
    }
    throw JsonException::NO_INSTANCE;
}

IJsonObject*  JsonObject::GetJsonObject(const char* name)const{
    u64 crc_work = ((u64)this->m_crc << 32) | this->mp_serialize->MakeCRC32((u8*)name, strlen(name));
    u32 crc32 = this->mp_serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));


    std::map< u32, IJsonValue*>::const_iterator it = this->m_object.find(crc32);
    if (it != this->m_object.end()){
        IJsonObject* object;
        RESULT result = it->second->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_IJsonObject, (void**)&object);
        if (result != EVOLUTION::_RESULT::S_ok)
        {
            throw JsonException::CONVERSION;
        }
        return object;
    }
    throw JsonException::NO_INSTANCE;
}

u32  JsonObject::GetObjectCount()const{
    return this->m_object.size();
}

const char*  JsonObject::GetObjectName(u32 index)const{
    if (index > this->m_object_names.size())
    {
        return nullptr;
    }

    return this->m_object_names[index];
}

u32  JsonObject::Crc32()const{
    return this->m_crc;
}

const char*  JsonObject::GetName()const{
    return this->m_name;
}

bool JsonObject::FindName(const char *pfindname)const
{
    u64 crc_work = ((u64)this->m_crc << 32) | this->mp_serialize->MakeCRC32((u8*)pfindname, strlen(pfindname));
    u32 crc32 = this->mp_serialize->MakeCRC32((u8*)&crc_work, sizeof(u64));
    return this->m_object.find(crc32) != m_object.end();
}
