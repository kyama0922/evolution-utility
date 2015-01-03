#ifndef __EVOLUTION_COLLECTION_H__
#define __EVOLUTION_COLLECTION_H__

#include <evolution_type.h>
#include "evolution_binary_search_collection.h"

namespace EVOLUTION{
    namespace UTILITY{

        //---------------------------------------------------------------------------
        //IUnknownインターフェイスを継承しているオブジェクトを管理できるクラス
        //ハッシュ値で保管します。
        //---------------------------------------------------------------------------
        class Collection{
        private:
            MapCollection<IUnknown*> m_collection;
        public:
            Collection();
            ~Collection();

            //アイテムの取得します。使用しなくなったItemは[Release]してください。
            //※取得できなかった場合はnullを返す
            IUnknown* QueryItem(u32 hash);

            //アイテムの追加
            //※参照カウンタが1増加
            void InsertItem(u32 hash, IUnknown* item);

            //アイテムを開放します。
            void ReleaseItem(u32 hash);

            //アイテムの検索
            bool Find(u32 hash);

            //すべてアイテムを開放します。
            void ReleaseAll();
        };

    }
    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID{
        // {600E805B-6B83-44d9-A1B0-0C52C5EFED9E}
        static const EVOLUTION_IID IID_Collection =
        { 0x600e805b, 0x6b83, 0x44d9, { 0xa1, 0xb0, 0xc, 0x52, 0xc5, 0xef, 0xed, 0x9e } };
    }
}

#endif // !__EVOLUTION_COLLECTION_H__