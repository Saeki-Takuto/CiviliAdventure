//==================================================================
//
//ポリゴン処理<meshfield.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _POLYGON_H_	//このマクロ定義がされてなかったら
#define _POLYGON_H_	//2重インクルード防止のマクロ定義

#include "main.h"

//プロトタイプ宣言
void InitPolygon(void);//初期化処理
void UninitPolygon(void);//終了処理
void UpdatePolygon(void);//更新処理
void DrawPolygon(void);//描画処理

#endif