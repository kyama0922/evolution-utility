#include "evolution_json_parse_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::UTILITY;




JsonSerialize::JsonSerialize(const char* json, u32 buffer_count) : str_master(json), str_json(json), m_index(0), m_buffer_count(buffer_count), m_json_len(strlen(json)){
    mp_buffer = NEW char[buffer_count];
    mp_buffer[0] = '\0';

    //CRC32テーブルの作成
    for (u32 i = 0; i < 256; i++) {
        u32 c = i;
        for (int j = 0; j < 8; j++) {
            c = (c & 1) ? (0xEDB88320 ^ (c >> 1)) : (c >> 1);
        }
        crc_table[i] = c;
    }
}

JsonSerialize::~JsonSerialize(){
    EVOLUTION_DELETE_ARRAY(this->mp_buffer);
}

char JsonSerialize::Search(const char* key){
    if (str_json[m_index] == '\0'){
        return '\0';
    }
    u32 key_count = strlen(key);
    do
    {
        for (u32 i = 0; i < key_count; i++)
        {
            if (str_json[m_index] == key[i]){
                return str_json[m_index];
            }
        }
    } while (str_json[m_index] != '\0' &&  ++m_index);
    return '\0';
}

const char*  JsonSerialize::SkipIgnore(const char* key){
    if (str_json[m_index] == '\0'){
        return '\0';
    }
    u32 key_count = strlen(key);
    bool skip;
    do
    {
        skip = false;
        for (u32 i = 0; i < key_count; i++)
        {
            if (str_json[m_index] == key[i]){
                skip = true;
                break;
            }
        }
    } while (skip && ++m_index);
    return &str_json[m_index];
}

const char*  JsonSerialize::Skip(const char* key){
    if (str_json[m_index] == '\0'){
        return nullptr;
    }
    u32 key_count = strlen(key);
    do
    {
        for (u32 i = 0; i < key_count; i++)
        {
            if (str_json[m_index] == key[i]){
                return &str_json[m_index];
            }
        }
    } while (str_json[m_index] != '\0' &&  ++m_index);
    return nullptr;
}
const char* JsonSerialize::GetKeyName(){
    if (str_json[m_index] == '\0'){
        return nullptr;
    }
    const char* name_start = this->SkipIgnore("{[ \",\n\r");
    const char* name_end = this->Skip("\":]}\n\r");
    this->SkipIgnore("\"");
    u32 len = name_end - name_start;
    u32 i;
    for (i = 0; i < len; i++)
    {
        this->mp_buffer[i] = name_start[i];
    }
    this->mp_buffer[i] = 0;
    return this->mp_buffer;
}

double JsonSerialize::GetNumber(){
    if (str_json[m_index] == '\0'){
        return 0.0;
    }
    const char* name_start = this->SkipIgnore("{[ \",:\n\r");
    const char* name_end = this->Skip(" ,]}\n\r");
    u32 len = name_end - name_start;
    u32 i;
    for (i = 0; i < len; i++)
    {
        this->mp_buffer[i] = name_start[i];
    }
    this->mp_buffer[i] = 0;
    return atof(this->mp_buffer);
}

bool JsonSerialize::IsEnd(){
    return this->str_json[m_index] == '\0';
}

void JsonSerialize::SetIndex(u32 index){
    if (m_json_len < index){
        return;
    }
    this->m_index = index;
}

u32 JsonSerialize::GetIndex(){
    return this->m_index;
}

u32 JsonSerialize::MakeCRC32(const u8 *buf, u32 len)const{
    u32 c = 0xFFFFFFFF;
    for (u32 i = 0; i < len; i++) {
        c = crc_table[(c ^ buf[i]) & 0xFF] ^ (c >> 8);
    }
    return c ^ 0xFFFFFFFF;
}
