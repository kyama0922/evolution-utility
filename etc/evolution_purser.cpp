#include "evolution_purser.h"

using namespace EVOLUTION;
using namespace EVOLUTION::UTILITY;


Purser::Purser(u32 buffer_count) : m_buffer_count(buffer_count){
    mp_buffer = NEW char[buffer_count];
    mp_buffer[0] = '\0';
}

Purser::~Purser(){
    EVOLUTION_DELETE_ARRAY(this->mp_buffer);
}


void  Purser::SetText(c8* text){
    this->m_index = 0;
    this->mp_buffer[0] = '\0';
    this->cp_text = text;
}

const c8* Purser::Search(const c8* key){
    if (cp_text == nullptr || cp_text[m_index] == '\0'){
        return nullptr;
    }

    c8 search_str[128];
    s32 len = EVOLUTION::FUNCTION::Strlen(key);
    s32 index = 0;
    s32 i = 0;
    while (i < len)
    {
        if (key[i] == '[')
        {
            while (key[i] != ']')
            {
                search_str[index++] = key[i];
            }
            continue;
        }
        search_str[index++] = key[i];
    }

}

bool  Purser::IsEnd(){
    return this->cp_text[m_index] == '\0';
}

void  Purser::SetIndex(u32 index){
    this->m_index = index;
}

u32  Purser::GetIndex(){
    return this->m_index;
}
