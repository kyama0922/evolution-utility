#include "evolution_collection.h"

using namespace EVOLUTION;
using namespace EVOLUTION::UTILITY;


Collection::Collection(){

}

Collection::~Collection(){
    for (s32 i = 0; i < this->m_collection.GetUseTableCount(); i++)
    {
        MapCollection<IUnknown*>::MapContainer* collector = this->m_collection.GetContainer(i);
        if (collector){
            collector->val->Release();
        }
    }
}

//アイテムの取得します。
//※取得できなかった場合はnullを返す
IUnknown* Collection::QueryItem(u32 hash){
    MapCollection<IUnknown*>::MapContainer* collector = this->m_collection.Find(hash);
    if (collector == nullptr)
    {
        return nullptr;
    }
    collector->val->AddRef();
    return collector->val;
}

//アイテムの追加
//※参照カウンタが1増加
void Collection::InsertItem(u32 hash, IUnknown* item){
    item->AddRef();
    MapCollection<IUnknown*>::MapContainer* collector = this->m_collection.Find(hash);
    if (collector == nullptr)
    {
        this->m_collection.Insert(hash, item);
    }
}

//アイテムを開放します。
void Collection::ReleaseItem(u32 hash){
    MapCollection<IUnknown*>::MapContainer* collector = this->m_collection.Find(hash);
    if (collector == nullptr)
    {
        return;
    }
    u32 count = collector->val->Release();
    if (count == 0)
    {
        this->m_collection.Delete(collector->key);
    }
}

//アイテムの検索
bool Collection::Find(u32 hash){
    MapCollection<IUnknown*>::MapContainer* collector = this->m_collection.Find(hash);
    if (collector == nullptr)
    {
        return false;
    }
    return true;
}

void Collection::ReleaseAll(){
    for (s32 i = 0; i < this->m_collection.GetUseTableCount(); i++)
    {
        MapCollection<IUnknown*>::MapContainer* collector = this->m_collection.GetContainer(i);
        if (collector){
            collector->val->Release();
        }
    }
    MapCollection<IUnknown*>().Swap(this->m_collection);
}