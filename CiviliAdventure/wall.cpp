//==================================================================
//
//壁処理<wall.cpp>
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "wall.h"
#include "player.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;		//テクスチャへのポインタ
Wall g_aWall[NUM_WALL];
//D3DXVECTOR3 g_posWall;//位置
//D3DXVECTOR3 g_rotWall;//向き
//D3DXMATRIX g_mtxWorldWall;//ワールドマトリックス

//==================================================================
//初期化処理
//==================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wall000.jpg",
		&g_pTextureWall);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4*NUM_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall, NULL);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].bUse = false;
	}

	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標を設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[1].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[2].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[3].nor = D3DXVECTOR3(0.0, 1.0, 0.0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//頂点バッファのアンロック
	g_pVtxBuffWall->Unlock();
}

//==================================================================
//終了処理
//==================================================================
void UninitWall(void)
{
	//テクスチャの解放
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//==================================================================
//更新処理
//==================================================================
void UpdateWall(void)
{
}

//==================================================================
//描画処理
//==================================================================
void DrawWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall*4, 2);
		}
	}
}

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float alpha)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].bUse = true;

			//頂点座標を設定
			pVtx[0].pos = D3DXVECTOR3(-150.0f, +150.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+150.0f, +150.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-150.0f, -150.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+150.0f, -150.0f, 0.0f);

			//各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
			pVtx[0].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
			pVtx[1].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
			pVtx[2].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
			pVtx[3].nor = D3DXVECTOR3(0.0, 1.0, 0.0);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


			break;
		}
		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffWall->Unlock();
}

void CollisionWall(void)
{
	Player* pPlayer = GetPlayer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	D3DXMATRIX mtxWorld[4];//ワールドマトリックス
	D3DXVECTOR3 pos[4];

	//壁ごとの4頂点取得
	for (int nCntMatrix = 0; nCntMatrix < 4; nCntMatrix++)
	{
		D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld[nCntMatrix]);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, pVtx[nCntMatrix].pos.x, pVtx[nCntMatrix].pos.y, pVtx[nCntMatrix].pos.z);
		D3DXMatrixMultiply(&mtxWorld[nCntMatrix], &mtxWorld[nCntMatrix], &mtxTrans);

		//ワールド座標行列の設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld[nCntMatrix]);

		pos[nCntMatrix] = D3DXVECTOR3(mtxWorld[nCntMatrix]._41, mtxWorld[nCntMatrix]._42, mtxWorld[nCntMatrix]._43);
	}

	//頂点バッファのアンロック
	g_pVtxBuffWall->Unlock();

	D3DXVECTOR3 aPos[4];

	aPos[0] = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);
	aPos[1] = D3DXVECTOR3(150.0f, 0.0f, 150.0f);
	aPos[2] = D3DXVECTOR3(150.0f, 0.0f, -150.0f);
	aPos[3] = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);

	float hoge = sinf(D3DX_PI);
	float ham = sinf(D3DX_PI * 0.5f);

	//if (((pos[1].z - pos[0].z) * (pPlayer->posOld.x - pos[0].x)) - ((pos[1].x - pos[0].x) * (pPlayer->posOld.z - pPlayer->size.z * 0.5f - pos[0].z)) > 0)
	//{
	//	if (((pos[1].z - pos[0].z) * (pPlayer->pos.x - pos[0].x)) - ((pos[1].x - pos[0].x) * (pPlayer->pos.z + pPlayer->size.z * 0.5f - pos[0].z)) < 0)
	//	{
	//		if (pos[0].x <= pPlayer->pos.x && pPlayer->pos.x <= pos[1].x)
	//		{
	//			pPlayer->pos.z = pos[0].z - pPlayer->size.z * 0.5f;
	//			pPlayer->move.z = 0.0f;
	//		}
	//	}
	//}

	//if (aPos[1].x - aPos[0].x * pPlayer->posOld.x - aPos[0].x < 0)
	//{
	//	if (aPos[1].z - aPos[0].z * pPlayer->posOld.z - aPos[0].z < 0)
	//	{
	//		if (aPos[1].x - aPos[0].x * pPlayer->pos.x - aPos[0].x > 0)
	//		{
	//			if (aPos[1].z - aPos[0].z * pPlayer->pos.z - aPos[0].z > 0)
	//			{
	//				int nCnt = 0;
	//			}
	//		}
	//	}
	//}

	if (((aPos[1].z-aPos[0].z)*(pPlayer->posOld.x-aPos[0].x))- ((aPos[1].x - aPos[0].x) * (pPlayer->posOld.z-pPlayer->size.z*0.5f - aPos[0].z))>0)
	{
		if (((aPos[1].z - aPos[0].z) * (pPlayer->pos.x - aPos[0].x)) - ((aPos[1].x - aPos[0].x) * (pPlayer->pos.z + pPlayer->size.z * 0.5f - aPos[0].z)) < 0)
		{
			if (aPos[0].x <= pPlayer->pos.x && pPlayer->pos.x <= aPos[1].x)
			{
				pPlayer->pos.z = aPos[0].z - pPlayer->size.z * 0.5f;
				pPlayer->move.z = 0.0f;
			}

			if (aPos[0].z <= pPlayer->pos.z && pPlayer->pos.z <= aPos[1].z)
			{
				pPlayer->pos.x = aPos[0].x - pPlayer->size.x * 0.5f;
				pPlayer->move.x = 0.0f;
			}
		}
	}
}
