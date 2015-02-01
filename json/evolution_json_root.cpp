#include "evolution_json_parse_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::UTILITY;

RESULT EVOLUTION::FUNCTION::CreateJsonRoot(IJsonRoot** root, const char* json, u32 work_size){
    try{
        *root = NEW JsonRoot(json, work_size);
    }
    catch (...)
    {
        return _RESULT::E_no_instance;
    }
    return _RESULT::S_ok;
}


//IUnknown
u32 JsonRoot::AddRef(){
    return this->m_instance_counter.AddRef();
}

RESULT JsonRoot::QueryInterface(EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown *>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IJsonRoot))
    {
        *ppvObject = static_cast<IJsonRoot*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_JsonRoot))
    {
        *ppvObject = static_cast<JsonRoot*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }
    return _RESULT::S_ok;
}

u32 JsonRoot::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

JsonRoot::JsonRoot(const char* json, u32 buffer_size) :m_json_serialize(json, buffer_size){

    const char* work = json;

    char c = m_json_serialize.Search("[{");
    if (c == '['){
        m_json_serialize.SetIndex(m_json_serialize.GetIndex() + 1);
        mp_value = NEW JsonArray(0, "Root", &m_json_serialize);
    }
    else if (c == '{'){
        mp_value = NEW JsonObject(0, "Root", &m_json_serialize);
    }
}

JsonRoot::~JsonRoot(){
    EVOLUTION_RELEASE(mp_value);
}

IJsonObject* JsonRoot::GetJsonObject(){
    IJsonObject* object;
    RESULT result = mp_value->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_IJsonObject, (void**)&object);
    if (result != EVOLUTION::_RESULT::S_ok)
    {
        throw JsonException::CONVERSION;
    }
    return object;
}

IJsonArray* JsonRoot::GetJsonArray(){
    IJsonArray* _array;
    RESULT result = mp_value->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_IJsonObject, (void**)&_array);
    if (result != EVOLUTION::_RESULT::S_ok)
    {
        throw JsonException::CONVERSION;
    }
    return _array;
}
