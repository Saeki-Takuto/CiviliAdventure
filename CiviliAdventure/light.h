//==================================================================
//
//ライト処理<ligit.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _LIGHT_H_	//このマクロ定義がされてなかったら
#define _LIGHT_H_	//2重インクルード防止のマクロ定義

#include "main.h"

//プロトタイプ宣言
void InitLight(void);//初期化処理
void UninitLight(void);//終了処理
void UpdateLight(void);//更新処理

#endif