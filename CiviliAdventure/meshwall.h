//==================================================================
//
//メッシュウォール処理<meshwall.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _MESHWALL_H_	//このマクロ定義がされてなかったら
#define _MESHWALL_H_	//2重インクルード防止のマクロ定義

#include "main.h"
#define MESHWALL_X_BLOCK (2)
#define MESHWALL_Y_BLOCK (2)

#define MAX_MESHWALL (4)


#define MESHWALL_VERTEX_NUM ((MESHWALL_X_BLOCK+1)*(MESHWALL_Y_BLOCK+1))
#define MESHWALL_INDEX_NUM (MESHWALL_PRIMITIVE_NUM+2)
#define MESHWALL_PRIMITIVE_NUM (((MESHWALL_X_BLOCK*MESHWALL_Y_BLOCK)*2))+(4*(MESHWALL_Y_BLOCK-1))


#define NUM_WIDTH (300)
#define NUM_HEIGHT (300)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}MeshWall;

//プロトタイプ宣言
void InitMeshWall(void);//初期化処理
void UninitMeshWall(void);//終了処理
void UpdateMeshWall(void);//更新処理
void DrawMeshWall(void);//描画処理

#endif