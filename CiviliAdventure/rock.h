//==================================================================
//
//モデル処理<rock.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _ROCK_H_	//このマクロ定義がされてなかったら
#define _ROCK_H_	//2重インクルード防止のマクロ定義

#include "main.h"
#include "player.h"

#define MAX_ROCK (1)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posold;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 movepos;
	D3DXVECTOR3 moverot;
	D3DXMATRIX mtxWorld;
	int nType;
	int nLife;
	bool bUse;
}Rock;

typedef struct
{
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 size;
}RockSize;

typedef enum
{
	ROCKTYPE_VERTICAL = 0,
	ROCKTYPE_BESIDE,
	ROCKTYPE_MAX
}ROCKTYPE;

//プロトタイプ宣言
void InitRock(void);//初期化処理
void UninitRock(void);//終了処理
void UpdateRock(void);//更新処理
void DrawRock(void);//描画処理
void CollisionRock(void);//当たり判定
void SetRock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 movepos, D3DXVECTOR3 moverot, int nType);
Rock* GetRock(void);
RockSize* GetRockSize(void);

#endif