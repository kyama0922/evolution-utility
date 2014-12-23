#include "evolution_collection.h"

using namespace EVOLUTION;
using namespace EVOLUTION::UTILITY;


Collection::Collection(){

}

Collection::~Collection(){
    for (std::map<u32, IUnknown*>::iterator it = this->m_collection.begin(); it != this->m_collection.end(); it++)
    {
        it->second->Release();
    }
    std::map<u32, IUnknown*>().swap(this->m_collection);
}

//アイテムの取得します。
//※取得できなかった場合はnullを返す
IUnknown* Collection::QueryItem(u32 hash){
    std::map<u32, IUnknown*>::iterator it = this->m_collection.find(hash);
    if (this->m_collection.end() == it)
    {
        return nullptr;
    }
    it->second->AddRef();
    return it->second;
}

//アイテムの追加
//※参照カウンタが1増加
void Collection::InsertItem(u32 hash, IUnknown* item){
    item->AddRef();
    std::map<u32, IUnknown*>::iterator it = this->m_collection.find(hash);
    if (this->m_collection.end() == it)
    {
        this->m_collection[hash] = item;
    }
}

//アイテムを開放します。
void Collection::ReleaseItem(u32 hash){
    std::map<u32, IUnknown*>::iterator it = this->m_collection.find(hash);
    if (this->m_collection.end() == it)
    {
        return;
    }
    u32 count = it->second->Release();
    if (count == 0)
    {
        this->m_collection.erase(it);
    }
}

//アイテムの検索
bool Collection::Find(u32 hash){
    std::map<u32, IUnknown*>::iterator it = this->m_collection.find(hash);
    if (this->m_collection.end() == it)
    {
        return false;
    }
    return true;
}

void Collection::ReleaseAll(){
    for (std::map<u32, IUnknown*>::iterator it = this->m_collection.begin(); it != this->m_collection.end(); it++)
    {
        it->second->Release();
    }
    std::map<u32, IUnknown*>().swap(this->m_collection);
}