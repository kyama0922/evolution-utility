﻿#ifndef __EVOLUTION_BINARY_SEARCH_COLLECTION_H__
#define __EVOLUTION_BINARY_SEARCH_COLLECTION_H__

#include <evolution_type.h>

namespace EVOLUTION{
    namespace UTILITY{

        struct Container{
            u32 key;
            ptr_t val;
        };
        //二分探索を用いたコンテナ
        class BinarySearchCorrection{
        private:
            s32 m_max_container_count;
            s32 m_use_container_count;
            Container* mp_container_table;

            //データインデックスの検索
            s32 FindIndex(u32 key, s32* last_key)const;
            //データを右側にスライド
            void RightSlideData(s32 start_index, s32 slide_count = 1);
            //データを左側にスライド
            void LeftSlideData(s32 start_index, s32 slide_count = 1);
            //データのコピー
            void CopyTable(Container* dest, const Container* src, s32 count);
            //データテーブルの作成
            void CreateTable(s32 table_count);
        public:
            BinarySearchCorrection(s32 table_count = 64);
            ~BinarySearchCorrection();
            //データテーブルの再確保
            void ReCreateTable(s32 table_count);
            //テーブルの追加
            void AddCreateTable(u32 magnification = 2);
            //中身をソートします。(基数ソート)
            void Sort();
            //ソートせずに高速にデータを挿入します。
            //データ挿入が終わり次第ソート関数を明示的に読んでください。
            void InsertNotSort(u32 key, ptr_t val);
            //データを挿入
            void Insert(u32 key, ptr_t val);
            //データの検索
            Container* Find(u32 key)const;
            //データを削除
            void Delete(u32 key);
            //現在のテーブル数を取得
            s32 GetTableSize()const;
            //現在のテーブル使用数を取得
            s32 GetUseTableCount()const;
            //データをTableから取得
            Container* GetContainer(s32 index)const;
        };
    }
}


#endif //!__EVOLUTION_BINARY_SEARCH_COLLECTION_H__