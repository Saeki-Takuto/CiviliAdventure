//==================================================================
//
//モデル処理<rod.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _ROD_H_	//このマクロ定義がされてなかったら
#define _ROD_H_	//2重インクルード防止のマクロ定義

#include "main.h"
#include "player.h"

#define MAX_ROD (128)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posold;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 movepos;
	D3DXVECTOR3 moverot;
	D3DXMATRIX mtxWorld;
	int nType;
	bool bUse;
}Rod;

typedef struct
{
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 size;
}RodSize;

typedef enum
{
	RODTYPE_VERTICAL=0,
	RODTYPE_BESIDE,
	RODTYPE_MAX
}RODTYPE;

//プロトタイプ宣言
void InitRod(void);//初期化処理
void UninitRod(void);//終了処理
void UpdateRod(void);//更新処理
void DrawRod(void);//描画処理
void CollisionRod(void);//当たり判定
void SetRod(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 movepos, D3DXVECTOR3 moverot, int nType);
Rod* GetRod(void);
RodSize* GetRodSize(void);

#endif