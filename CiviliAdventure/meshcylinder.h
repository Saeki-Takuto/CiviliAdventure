//==================================================================
//
//メッシュフィールド処理<meshcylinder.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _MESHCYLINDER_H_	//このマクロ定義がされてなかったら
#define _MESHCYLINDER_H_	//2重インクルード防止のマクロ定義

#include "main.h"
#define MESHCYLINDER_X_BLOCK (30)
#define MESHCYLINDER_Z_BLOCK (30)


#define MESHCYLINDER_VERTEX_NUM ((MESHCYLINDER_X_BLOCK+1)*(MESHCYLINDER_Z_BLOCK+1))
#define MESHCYLINDER_INDEX_NUM (MESHCYLINDER_PRIMITIVE_NUM+2)
#define MESHCYLINDER_PRIMITIVE_NUM (((MESHCYLINDER_X_BLOCK*MESHCYLINDER_Z_BLOCK)*2)+(4*(MESHCYLINDER_Z_BLOCK-1)))


#define NUM_WIDTH (300)
#define NUM_HEIGHT (300)

//プロトタイプ宣言
void InitMeshCylinder(void);//初期化処理
void UninitMeshCylinder(void);//終了処理
void UpdateMeshCylinder(void);//更新処理
void DrawMeshCylinder(void);//描画処理

#endif