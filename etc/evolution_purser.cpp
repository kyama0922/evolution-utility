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

    s32 len = EVOLUTION::FUNCTION::Strlen(key);
    const c8* search_key = key;
    s32 buffer_index = 0;
    
    do
    {
        if (*search_key == '\\')
        {

        }
        else if (*search_key == '*')
        {

        }
        else if (*search_key == '[')
        {
            const c8* start = search_key + 1;
            const c8* end = start;
            while ( *(end++ + 1) != ']');
            const c8* work = start;
            do
            {
                if (*work == '-')
                {
                    for (c8 c = *(work++ - 1); c <= *work; c++)
                    {
                        if (cp_text[m_index] == c)
                        {
                            this->mp_buffer[buffer_index++] = cp_text[m_index];
                            search_key = end+1;
                            break;
                        }
                    }
                    if (start < search_key)
                    {
                        break;
                    }
                }
                else if (cp_text[m_index] == *work)
                {
                    this->mp_buffer[buffer_index++] = cp_text[m_index];
                    search_key = end;
                    break;
                }
            } while (work++ <= end);
        }
        else if (*search_key == cp_text[m_index])
        {
            this->mp_buffer[buffer_index++] = cp_text[m_index];
            search_key++;
        }
        else
        {
            search_key = key;
            buffer_index = 0;
        }
    } while (cp_text[++m_index] != '\0' && *search_key != '\0');
    this->mp_buffer[buffer_index] = '\0';
    return this->mp_buffer;
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
