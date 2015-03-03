#ifndef __EVOLUTION_UTILITY__
#define __EVOLUTION_UTILITY__

//EVOLUTIONライブラリで扱う基本型情報のヘッダ
#include <evolution.h>

//----------------------------------------------------
//数学関係
//----------------------------------------------------
#include "math/evolution_math.h"

//----------------------------------------------------
//ファイル関係
//----------------------------------------------------

//Zipアーカイブ扱うクラス
#include "file/evolution_zip_loader.h"

//----------------------------------------------------
//ETC
//----------------------------------------------------

//Jsonのパーサー
#include "json/evolution_json_parse_interface.h"

//関数
#include "function/evolution_utility_function.h"

//カラー
#include "etc/evolution_color.h"

//コレクション
#include "etc/evolution_collection.h"

//コレクション
#include "etc/evolution_binary_search_collection.h"

#endif //!__EVOLUTION_UTILITY_H__