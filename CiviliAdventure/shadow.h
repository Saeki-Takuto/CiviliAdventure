//==================================================================
//
//影処理<shadow.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _SHADOW_H_	//このマクロ定義がされてなかったら
#define _SHADOW_H_	//2重インクルード防止のマクロ定義

#include "main.h"

//影の構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Shadow;

//プロトタイプ宣言
void InitShadow(void);//初期化処理
void UninitShadow(void);//終了処理
void UpdateShadow(void);//更新処理
void DrawShadow(void);//描画処理
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);

#endif