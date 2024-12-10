//==================================================================
//
//メッシュフィールド処理<meshfield.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _MESHFIELD_H_	//このマクロ定義がされてなかったら
#define _MESHFIELD_H_	//2重インクルード防止のマクロ定義

#include "main.h"
#define MESHFIELD_X_BLOCK (20)
#define MESHFIELD_Z_BLOCK (20)


#define MESHFIELD_VERTEX_NUM ((MESHFIELD_X_BLOCK+1)*(MESHFIELD_Z_BLOCK+1))
#define MESHFIELD_INDEX_NUM (MESHFIELD_PRIMITIVE_NUM+2)
#define MESHFIELD_PRIMITIVE_NUM (((MESHFIELD_X_BLOCK*MESHFIELD_Z_BLOCK)*2))+(4*(MESHFIELD_Z_BLOCK-1))


#define NUM_WIDTH (300)
#define NUM_HEIGHT (300)

//プロトタイプ宣言
void InitMeshField(void);//初期化処理
void UninitMeshField(void);//終了処理
void UpdateMeshField(void);//更新処理
void DrawMeshField(void);//描画処理

#endif