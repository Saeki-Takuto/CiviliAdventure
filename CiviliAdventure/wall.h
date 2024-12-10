//==================================================================
//
//壁処理<wall.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _WALL_H_	//このマクロ定義がされてなかったら
#define _WALL_H_	//2重インクルード防止のマクロ定義

#include "main.h"
#define NUM_WALL (8)//敵の種類


typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Wall;

//プロトタイプ宣言
void InitWall(void);//初期化処理
void UninitWall(void);//終了処理
void UpdateWall(void);//更新処理
void DrawWall(void);//描画処理
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float alpha);
void CollisionWall(void);

#endif