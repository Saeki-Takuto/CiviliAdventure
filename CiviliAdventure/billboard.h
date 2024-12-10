//==================================================================
//
//ビルボード処理<billboard.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _BILLBOARD_H_	//このマクロ定義がされてなかったら
#define _BILLBOARD_H_	//2重インクルード防止のマクロ定義

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 rot;
	bool bUse;
}Billboard;

//プロトタイプ宣言
void InitBillboard(void);//初期化処理
void UninitBillboard(void);//終了処理
void UpdateBillboard(void);//更新処理
void DrawBillboard(void);//描画処理
void SetBillboard(D3DXVECTOR3 pos,D3DXVECTOR3 dir);

#endif