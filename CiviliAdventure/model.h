//==================================================================
//
//モデル処理<model.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _MODEL_H_	//このマクロ定義がされてなかったら
#define _MODEL_H_	//2重インクルード防止のマクロ定義

#include "main.h"

//モデルの構造体
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture[128];
	LPD3DXMESH pMesh;		//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアルへのポインタ
	DWORD dwNumMat;			//マテリアルの数
	int nIdxModelParent;	//親モデルのインデックス
	D3DXVECTOR3 pos;		//位置(オフセット)
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
}Model;

//プロトタイプ宣言
void InitModel(void);//初期化処理
void UninitModel(void);//終了処理
void UpdateModel(void);//更新処理
void DrawModel(void);//描画処理

#endif