//==================================================================
//
//メッシュウォール処理<meshwall.cpp>
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "meshwall.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;		//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;//インデックスバッファへのポインタ
D3DXVECTOR3 g_posMeshWall;//位置
D3DXVECTOR3 g_rotMeshWall;//向き
D3DXMATRIX g_mtxWorldMeshWall;//ワールドマトリックス

//==================================================================
//初期化処理
//==================================================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg000.jpg",
		&g_pTextureMeshWall);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHWALL_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall, NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHWALL_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	g_posMeshWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロック
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);
	float fTexX = 1.0f / MESHWALL_X_BLOCK;
	float fTexY = 1.0f / MESHWALL_Y_BLOCK;

	int nCntVtx = 0;
	int nXPos = 0;
	int nZPos = 0;

	for (int nCnt = 0; nCnt <= MESHWALL_Y_BLOCK; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 <= MESHWALL_X_BLOCK; nCnt2++)
		{
			pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f + ((NUM_WIDTH / MESHWALL_X_BLOCK) * nCnt2) - (NUM_WIDTH * 0.5f), NUM_HEIGHT - ((NUM_HEIGHT / MESHWALL_Y_BLOCK) * nCnt) - (NUM_HEIGHT * 0.5f), 0.0f);
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntVtx].tex = D3DXVECTOR2(fTexX * nCnt2, nCnt * fTexY);

			nCntVtx++;
		}
	}

	//pVtx[150].pos.y = 100.0f;
	//pVtx[300].pos.y = 50.0f;

	//頂点バッファのアンロック
	g_pVtxBuffMeshWall->Unlock();

	//インデックスバッファをロック
	WORD* pIdx;
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	int nX = MESHWALL_X_BLOCK + 1;
	int nZ = MESHWALL_Y_BLOCK;
	int nK = 0;
	nCntVtx = 0;

	for (int nCnt = 0; nCnt < MESHWALL_Y_BLOCK; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 <= MESHWALL_X_BLOCK; nCnt2++, nX++, nK++)
		{
			pIdx[nCntVtx] = nX;
			pIdx[nCntVtx + 1] = nK;
			nCntVtx += 2;
		}

		if (nCnt < MESHWALL_Y_BLOCK - 1)
		{
			pIdx[nCntVtx] = nK - 1;
			pIdx[nCntVtx + 1] = nX;
			nCntVtx += 2;
		}
	}

	//インデックスバッファのアンロック
	g_pIdxBuffMeshWall->Unlock();

}

//==================================================================
//終了処理
//==================================================================
void UninitMeshWall(void)
{
	//テクスチャの解放
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//インデックスバッファの解放
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//==================================================================
//更新処理
//==================================================================
void UpdateMeshWall(void)
{
}

//==================================================================
//描画処理
//==================================================================
void DrawMeshWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshWall);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshWall.y, g_rotMeshWall.x, g_rotMeshWall.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshWall, &g_mtxWorldMeshWall, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshWall.x, g_posMeshWall.y, g_posMeshWall.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshWall, &g_mtxWorldMeshWall, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshWall);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshWall);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshWall);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHWALL_VERTEX_NUM, 0, MESHWALL_PRIMITIVE_NUM);

	////ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
