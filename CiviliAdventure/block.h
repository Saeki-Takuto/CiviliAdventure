//==================================================================
//
//モデル処理<block.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _BLOCK_H_	//このマクロ定義がされてなかったら
#define _BLOCK_H_	//2重インクルード防止のマクロ定義

#include "main.h"
#include "player.h"

//プロトタイプ宣言
void InitBlock(void);//初期化処理
void UninitBlock(void);//終了処理
void UpdateBlock(void);//更新処理
void DrawBlock(void);//描画処理
void CollisionBlock(void);//当たり判定

#endif