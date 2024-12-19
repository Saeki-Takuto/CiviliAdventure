#include "block.h"
#include "fade.h"
#include "game.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureBlock[128] = {};
LPD3DXMESH g_pMeshBlock = NULL;//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatBlock = NULL;//マテリアルへのポインタ
DWORD g_dwNumMatBlock = 0;//マテリアルの数
D3DXVECTOR3 g_posBlock;//位置
D3DXVECTOR3 g_rotBlock;//向き
D3DXMATRIX g_mtxWorldBlock;//ワールドマトリックス
D3DXVECTOR3 g_vtxMinBlock, g_vtxMaxBlock;//モデルの最小値、最大値

void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//各種変数の初期化

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/box000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatBlock,
		NULL,
		&g_dwNumMatBlock,
		&g_pMeshBlock);

	g_posBlock = D3DXVECTOR3(0.0f, 0.0f, 500.0f);

	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ
	//頂点数の取得
	nNumVtx = g_pMeshBlock->GetNumVertices();
	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshBlock->GetFVF());
	//頂点バッファのロック
	g_pMeshBlock->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//xの最大値比較
		if (vtx.x > g_vtxMaxBlock.x)
		{
			g_vtxMaxBlock.x = vtx.x;
		}

		//yの最大値比較
		if (vtx.y > g_vtxMaxBlock.y)
		{
			g_vtxMaxBlock.y = vtx.y;
		}

		//zの最大値比較
		if (vtx.z > g_vtxMaxBlock.z)
		{
			g_vtxMaxBlock.z = vtx.z;
		}

		//xの最小値比較
		if (vtx.x < g_vtxMinBlock.x)
		{
			g_vtxMinBlock.x = vtx.x;
		}

		//yの最小値比較
		if (vtx.y < g_vtxMinBlock.y)
		{
			g_vtxMinBlock.y = vtx.y;
		}

		//zの最小値比較
		if (vtx.z < g_vtxMinBlock.z)
		{
			g_vtxMinBlock.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	//頂点バッファのアンロック
	g_pMeshBlock->UnlockVertexBuffer();

	D3DXMATERIAL* pMat;//マテリアルへのポインタ

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatBlock->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBlock; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureBlock[nCntMat]);
		}
	}

}

void UninitBlock(void)
{
	//テクスチャの解放
	if (g_pMeshBlock != NULL)
	{
		g_pMeshBlock->Release();
		g_pMeshBlock = NULL;
	}

	//頂点バッファの解放
	if (g_pBuffMatBlock != NULL)
	{
		g_pBuffMatBlock->Release();
		g_pBuffMatBlock = NULL;
	}

	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		//テクスチャの破棄
		if (g_apTextureBlock[nCnt] != NULL)
		{
			g_apTextureBlock[nCnt]->Release();
			g_apTextureBlock[nCnt] = NULL;
		}
	}
}

void UpdateBlock(void)
{
	
}

void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldBlock);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotBlock.y, g_rotBlock.x, g_rotBlock.z);
	D3DXMatrixMultiply(&g_mtxWorldBlock, &g_mtxWorldBlock, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posBlock.x, g_posBlock.y, g_posBlock.z);
	D3DXMatrixMultiply(&g_mtxWorldBlock, &g_mtxWorldBlock, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBlock);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatBlock->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBlock; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureBlock[nCntMat]);

		//モデル(パーツ)の描画
		g_pMeshBlock->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

void CollisionBlock(void)
{
	Player* pPlayer = GetPlayer();

	//左右の当たり判定
	if (pPlayer->pos.z - pPlayer->size.z * 0.5f < g_posBlock.z + g_vtxMaxBlock.z && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_posBlock.z + g_vtxMinBlock.z)
	{
		if (pPlayer->posOld.x + pPlayer->size.x * 0.5f <= g_posBlock.x + g_vtxMinBlock.x && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_posBlock.x + g_vtxMinBlock.x)
		{
			pPlayer->pos.x = g_posBlock.x + g_vtxMinBlock.x - pPlayer->size.x * 0.5f;
			pPlayer->move.x = 0.0f;
			SetGameState(GAMESTATE_END);
			SetFade(MODE_RESULT);
		}
		else if (pPlayer->posOld.x - pPlayer->size.x * 0.5f >= g_posBlock.x + g_vtxMaxBlock.x && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_posBlock.x + g_vtxMaxBlock.x)
		{
			pPlayer->pos.x = g_posBlock.x + g_vtxMaxBlock.x + pPlayer->size.x * 0.5f;
			pPlayer->move.x = 0.0f;
			SetGameState(GAMESTATE_END);
			SetFade(MODE_RESULT);
		}
	}

	//上下の当たり判定
	if (pPlayer->pos.x - pPlayer->size.x * 0.5f < g_posBlock.x + g_vtxMaxBlock.x && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_posBlock.x + g_vtxMinBlock.x)
	{
		if (pPlayer->posOld.z + pPlayer->size.z*0.5f <= g_posBlock.z + g_vtxMinBlock.z && pPlayer->pos.z + pPlayer->size.z*0.5f > g_posBlock.z + g_vtxMinBlock.z)
		{
			pPlayer->pos.z = g_posBlock.z + g_vtxMinBlock.z - pPlayer->size.z*0.5f;
			pPlayer->move.z = 0.0f;
			SetGameState(GAMESTATE_END);
			SetFade(MODE_RESULT);
		}
		else if (pPlayer->posOld.z - pPlayer->size.z*0.5f >= g_posBlock.z + g_vtxMaxBlock.z && pPlayer->pos.z - pPlayer->size.z*0.5f < g_posBlock.z + g_vtxMaxBlock.z)
		{
			pPlayer->pos.z = g_posBlock.z + g_vtxMaxBlock.z + pPlayer->size.z*0.5f;
			pPlayer->move.z = 0.0f;
			SetGameState(GAMESTATE_END);
			SetFade(MODE_RESULT);
		}
	}
}