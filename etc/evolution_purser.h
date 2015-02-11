#ifndef __EVOLUTION_PURSER_H__
#define __EVOLUTION_PURSER_H__

#include "../evolution_utility.h"

namespace EVOLUTION{
    namespace UTILITY{

        class Purser{
        private:
            const c8* cp_text;
            u32 m_index;
            c8* mp_buffer;
            u32 m_buffer_count;
        public:
            Purser(u32 buffer_count);
            ~Purser();


            void SetText(c8* text);
           
            const c8* Search(const c8* key);

            bool IsEnd();

            void SetIndex(u32 index);

            u32 GetIndex();
        };
        
    }
}

#endif // !__EVOLUTION_PURSER_H__
