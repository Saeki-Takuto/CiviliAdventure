//==================================================================
//
//メッシュフィールド処理<meshfield.cpp>
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "meshfield.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;		//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;//インデックスバッファへのポインタ
D3DXVECTOR3 g_posMeshField;//位置
D3DXVECTOR3 g_rotMeshField;//向き
D3DXMATRIX g_mtxWorldMeshField;//ワールドマトリックス

//==================================================================
//初期化処理
//==================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg000.jpg",
		&g_pTextureMeshField);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)* MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField, NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	g_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロック
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);
	float fTexX = 1.0f / MESHFIELD_X_BLOCK;
	float fTexY = 1.0f / MESHFIELD_Z_BLOCK;


	int nCntVtx = 0;
	int nXPos = 0;
	int nZPos = 0;

	for (int nCnt = 0; nCnt <= MESHFIELD_Z_BLOCK; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 <= MESHFIELD_X_BLOCK; nCnt2++)
		{
			pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f+((NUM_WIDTH/ MESHFIELD_X_BLOCK)*nCnt2)-(NUM_WIDTH*0.5f),0.0f, NUM_HEIGHT-((NUM_HEIGHT/ MESHFIELD_Z_BLOCK)*nCnt)-(NUM_HEIGHT*0.5f));
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntVtx].tex = D3DXVECTOR2(fTexX*nCnt2,nCnt * fTexY);

			nCntVtx++;
		}
	}

	////頂点座標を設定
	//pVtx[0].pos = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
	//pVtx[2].pos = D3DXVECTOR3(150.0f, 0.0f, 150.0f);
	//pVtx[3].pos = D3DXVECTOR3(-150.0f, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(150.0f, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	//pVtx[8].pos = D3DXVECTOR3(150.0f, 0.0f, -150.0f);

	////各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
	//pVtx[0].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[1].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[2].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[3].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[4].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[5].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[6].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[7].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[8].nor = D3DXVECTOR3(0.0, 1.0, 0.0);


	////頂点カラーの設定
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	////テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	//pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	//pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	
	//頂点バッファのアンロック
	g_pVtxBuffMeshField->Unlock();
																																																																							
	//インデックスバッファをロック
	WORD* pIdx;
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	int nX = MESHFIELD_X_BLOCK+1;
	int nZ = MESHFIELD_Z_BLOCK;
	int nK = 0;
	nCntVtx = 0;

	for (int nCnt = 0; nCnt < MESHFIELD_Z_BLOCK; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 <= MESHFIELD_X_BLOCK; nCnt2++,nX++,nK++)
		{
			pIdx[nCntVtx] = nX;
			pIdx[nCntVtx + 1] = nK;
			nCntVtx+=2;
		}
		
		if (nCnt < MESHFIELD_Z_BLOCK - 1)
		{
			pIdx[nCntVtx] = nK - 1;
			pIdx[nCntVtx + 1] = nX;
			nCntVtx += 2;
		}
	}

	

	////インデックスの設定
	//pIdx[0]  = 3;
	//pIdx[1]  = 0;

	//pIdx[2]  = 4;
	//pIdx[3]  = 1;

	//pIdx[4]  = 5;
	//pIdx[5]  = 2;

	//pIdx[6]  = 2;
	//pIdx[7]  = 6;

	//pIdx[8]  = 6;
	//pIdx[9]  = 3;

	//pIdx[10] = 7;
	//pIdx[11] = 4;

	//pIdx[12] = 8;
	//pIdx[13] = 5;

	//インデックスバッファのアンロック
	g_pIdxBuffMeshField->Unlock();

}

//==================================================================
//終了処理
//==================================================================
void UninitMeshField(void)
{
	//テクスチャの解放
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//インデックスバッファの解放
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//==================================================================
//更新処理
//==================================================================
void UpdateMeshField(void)
{
}

//==================================================================
//描画処理
//==================================================================
void DrawMeshField(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIELD_VERTEX_NUM, 0, MESHFIELD_PRIMITIVE_NUM);

	////ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
