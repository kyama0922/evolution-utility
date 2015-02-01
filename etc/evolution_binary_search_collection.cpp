#include "evolution_binary_search_collection.h"

using namespace EVOLUTION;
using namespace EVOLUTION::UTILITY;


//データインデックスの検索
s32 BinarySearchCollection::FindIndex(u32 key, s32* last_key)const{
    s32 i = -1;
    s32 min = 0, max = this->m_use_container_count;
    do{
        i = (min + max) / 2;
        if (last_key != nullptr)
        {
            *last_key = i;
        }

        if (mp_container_table[i].key == key)
        {
            return i;
        }
        if (key < mp_container_table[i].key)
        {
            max = i - 1;
        }
        else if (mp_container_table[i].key < key)
        {
            min = i + 1;
        }
    } while (min <= max);
    return -1;
}
//データを右側にスライド
void BinarySearchCollection::RightSlideData(s32 start_index, s32 slide_count){
    for (s32 i = this->m_use_container_count + slide_count - 1; start_index < i; i--)
    {
        this->mp_container_table[i].key = this->mp_container_table[i - slide_count].key;
        this->mp_container_table[i].val = this->mp_container_table[i - slide_count].val;
    }
}
//データを左側にスライド
void BinarySearchCollection::LeftSlideData(s32 start_index, s32 slide_count){
    for (s32 i = start_index, count = this->m_use_container_count - start_index; i < this->m_use_container_count; i++)
    {
        this->mp_container_table[i].key = this->mp_container_table[i + slide_count].key;
        this->mp_container_table[i].val = this->mp_container_table[i + slide_count].val;
    }
}


BinarySearchCollection::BinarySearchCollection(s32 table_count) :m_max_container_count(0), m_use_container_count(0), mp_container_table(nullptr){
    this->CreateTable(table_count);
}

BinarySearchCollection::~BinarySearchCollection(){
    EVOLUTION_DELETE_ARRAY(mp_container_table);
}

//データのコピー
void BinarySearchCollection::CopyTable(Container* dest, const Container* src, s32 count){
    for (s32 i = 0; i < count; i++)
    {
        dest[i].key = src[i].key;
        dest[i].val = src[i].val;
    }
}

//データテーブルの作成
void BinarySearchCollection::CreateTable(s32 table_count){
    m_max_container_count = table_count;
    mp_container_table = NEW Container[m_max_container_count];
}

//データテーブルの再確保
void BinarySearchCollection::ReCreateTable(s32 table_count){
    if (table_count < this->m_use_container_count)
    {
        return;
    }
    m_max_container_count = table_count;
    Container* temp = NEW Container[m_max_container_count];
    this->CopyTable(temp, this->mp_container_table, m_use_container_count);

    //スワップ
    temp = (Container*)((ptr_t)temp ^ (ptr_t)this->mp_container_table);
    this->mp_container_table = (Container*)((ptr_t)this->mp_container_table ^ (ptr_t)temp);
    temp = (Container*)((ptr_t)temp ^ (ptr_t)this->mp_container_table);
    EVOLUTION_DELETE_ARRAY(temp);
}

//テーブルの追加
void BinarySearchCollection::AddTable(u32 magnification){
    m_max_container_count *= magnification;
    if (m_max_container_count == 0)
    {
        m_max_container_count = 2 * magnification;
    }
    Container* temp = NEW Container[m_max_container_count];

    this->CopyTable(temp, this->mp_container_table, m_use_container_count);

    //スワップ
    temp = (Container*)((ptr_t)temp ^ (ptr_t)this->mp_container_table);
    this->mp_container_table = (Container*)((ptr_t)this->mp_container_table ^ (ptr_t)temp);
    temp = (Container*)((ptr_t)temp ^ (ptr_t)this->mp_container_table);
    EVOLUTION_DELETE_ARRAY(temp);
}

//中身をソートします。(基数ソート)
void BinarySearchCollection::Sort(){
    const u32 r = 0x80000000;
    const s32 n = m_use_container_count;
    s32 i, j, k;
    u32 m = 1;

    Container* temp = NEW Container[m_use_container_count];
    u32* radix = NEW u32[m_use_container_count];

    u32 flag = 0x00000001;
    do{
        for (i = 0; i < n; i++){
            radix[i] = (this->mp_container_table[i].key & m) % 0x0F;
        }

        k = 0;
        for (i = 0; i <= 0x0F; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (radix[j] == i)
                {
                    temp[k].key = this->mp_container_table[j].key;
                    temp[k].val = this->mp_container_table[j].val;
                    ++k;
                }
            }
        }

        for (i = 0; i < n; i++){
            this->mp_container_table[i].key = temp[i].key;
            this->mp_container_table[i].val = temp[i].val;
        }

        if (m == r)
        {
            EVOLUTION_DISABLED_STATE(flag, 0x00000001);
        }
        m <<= 1;
    } while (m <= r && EVOLUTION_IS_STATE(flag, 0x00000001));
    EVOLUTION_DELETE_ARRAY(temp);
}

//ソートせずに高速にデータを挿入します。
//データ挿入が終わり次第ソート関数を明示的に読んでください。
void BinarySearchCollection::InsertNotSort(u32 key, ptr_t val){
    if (m_max_container_count - 1 < this->m_use_container_count)
    {
        this->AddTable();
    }
    this->mp_container_table[this->m_use_container_count].key = key;
    this->mp_container_table[this->m_use_container_count].val = val;
    this->m_use_container_count++;
}

//データを挿入
void BinarySearchCollection::Insert(u32 key, ptr_t val){
    //追加用テーブルの確認
    if (m_max_container_count - 1 < this->m_use_container_count)
    {
        this->AddTable();
    }

    s32 last_index;
    s32 index = this->FindIndex(key, &last_index);
    if (index == -1)
    {
        index = last_index;
        if (this->mp_container_table[index].key < key)
        {
            this->RightSlideData(index);
        }
        else
        {
            this->RightSlideData(index - 1);
        }
    }
    this->mp_container_table[index].key = key;
    this->mp_container_table[index].val = val;
    this->m_use_container_count++;
}

//データの検索
Container* BinarySearchCollection::Find(u32 key)const{
    s32 index = this->FindIndex(key, nullptr);
    if (index == -1)
    {
        return nullptr;
    }
    return &this->mp_container_table[index];
}

//データを削除
void BinarySearchCollection::Delete(u32 key){
    s32 index = this->FindIndex(key, nullptr);
    if (index == -1)
    {
        return;
    }
    this->LeftSlideData(index);
    this->m_use_container_count--;
}

//現在のテーブル数を取得
s32 BinarySearchCollection::GetTableSize()const{
    return this->m_max_container_count;
}
//現在のテーブル使用数を取得
s32 BinarySearchCollection::GetUseTableCount()const{
    return this->m_use_container_count;
}
//データをTableから取得
Container* BinarySearchCollection::GetContainer(s32 index)const{
    return (index < this->m_use_container_count) ? &this->mp_container_table[index] : nullptr;
}

void BinarySearchCollection::Swap(BinarySearchCollection& src){
    //データテーブルのスワップ
    src.mp_container_table = (Container*)((ptr_t)src.mp_container_table ^ (ptr_t)this->mp_container_table);
    this->mp_container_table = (Container*)((ptr_t)this->mp_container_table ^ (ptr_t)src.mp_container_table);
    src.mp_container_table = (Container*)((ptr_t)src.mp_container_table ^ (ptr_t)this->mp_container_table);


    //最大コレクション数のスワップ
    src.m_max_container_count = src.m_max_container_count ^ this->m_max_container_count;
    this->m_max_container_count = this->m_max_container_count ^ src.m_max_container_count;
    src.m_max_container_count = src.m_max_container_count ^ this->m_max_container_count;

    //使用数のスワップ
    src.m_use_container_count = src.m_use_container_count ^ this->m_use_container_count;
    this->m_use_container_count = this->m_use_container_count ^ src.m_use_container_count;
    src.m_use_container_count = src.m_use_container_count ^ this->m_use_container_count;
}