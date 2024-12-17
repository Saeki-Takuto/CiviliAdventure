#include "rock.h"
#include "input.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureRock[128][ROCKTYPE_MAX] = {};
LPD3DXMESH g_pMeshRock[ROCKTYPE_MAX] = {};//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatRock[ROCKTYPE_MAX] = {};//マテリアルへのポインタ
DWORD g_dwNumMatRock[ROCKTYPE_MAX] = {};//マテリアルの数
Rock g_rock[MAX_ROCK];
RockSize g_rocksize[ROCKTYPE_MAX];


void InitRock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//各種変数の初期化

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/rock.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatRock[0],
		NULL,
		&g_dwNumMatRock[0],
		&g_pMeshRock[0]);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/rodb.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatRock[1],
		NULL,
		&g_dwNumMatRock[1],
		&g_pMeshRock[1]);


	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ

	for (int nCnt = 0; nCnt < ROCKTYPE_MAX; nCnt++)
	{
		//頂点数の取得
		nNumVtx = g_pMeshRock[nCnt]->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshRock[nCnt]->GetFVF());
		//頂点バッファのロック
		g_pMeshRock[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//xの最小値比較
			if (vtx.x < g_rocksize[nCnt].vtxMin.x)
			{
				g_rocksize[nCnt].vtxMin.x = vtx.x;
			}

			//xの最大値比較
			if (vtx.x > g_rocksize[nCnt].vtxMax.x)
			{
				g_rocksize[nCnt].vtxMax.x = vtx.x;
			}


			//yの最小値比較
			if (vtx.y < g_rocksize[nCnt].vtxMin.y)
			{
				g_rocksize[nCnt].vtxMin.y = vtx.y;
			}

			//yの最大値比較
			if (vtx.y > g_rocksize[nCnt].vtxMax.y)
			{
				g_rocksize[nCnt].vtxMax.y = vtx.y;
			}

			//zの最小値比較
			if (vtx.z < g_rocksize[nCnt].vtxMin.z)
			{
				g_rocksize[nCnt].vtxMin.z = vtx.z;
			}

			//zの最大値比較
			if (vtx.z > g_rocksize[nCnt].vtxMax.z)
			{
				g_rocksize[nCnt].vtxMax.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		g_pMeshRock[nCnt]->UnlockVertexBuffer();

		g_rocksize[nCnt].size = g_rocksize[nCnt].vtxMax - g_rocksize[nCnt].vtxMin;

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatRock[nCnt]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatRock[nCnt]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureRock[nCntMat][nCnt]);
			}
		}
	}
}

void UninitRock(void)
{
	for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
	{
		if (g_rock[nCnt].bUse == true)
		{
			g_rock[nCnt].bUse = false;
		}
	}

	for (int nCnt = 0; nCnt < ROCKTYPE_MAX; nCnt++)
	{
		//テクスチャの解放
		if (g_pMeshRock[nCnt] != NULL)
		{
			g_pMeshRock[nCnt]->Release();
			g_pMeshRock[nCnt] = NULL;
		}

		//頂点バッファの解放
		if (g_pBuffMatRock[nCnt] != NULL)
		{
			g_pBuffMatRock[nCnt]->Release();
			g_pBuffMatRock[nCnt] = NULL;
		}

		for (int nCntTex = 0; nCntTex < 1; nCntTex++)
		{
			//テクスチャの破棄
			if (g_apTextureRock[nCntTex][nCnt] != NULL)
			{
				g_apTextureRock[nCntTex][nCnt]->Release();
				g_apTextureRock[nCntTex][nCnt] = NULL;
			}
		}
	}
}

void UpdateRock(void)
{
	for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
	{
		if (g_rock[nCnt].bUse == true)
		{
			g_rock[nCnt].posold = g_rock[nCnt].pos;

			g_rock[nCnt].pos += g_rock[nCnt].movepos;


			if (g_rock[nCnt].pos.x > 150.0f || g_rock[nCnt].pos.x < -150.0f)
			{
				g_rock[nCnt].movepos.x *= -1.0f;
			}

			if (g_rock[nCnt].pos.y > 150.0f || g_rock[nCnt].pos.y < 0.0f)
			{
				g_rock[nCnt].movepos.y *= -1.0f;
			}

			g_rock[nCnt].nLife--;

			if (g_rock[nCnt].nLife <= 0)
			{
				g_rock[nCnt].bUse = false;
			}


			//if (g_rock[nCnt].pos.z > 150.0f || g_rock[nCnt].pos.z < -150.0f)
			//{
			//	g_rock[nCnt].movepos.z *= -1.0f;
			//}
		}

	}
}

void DrawRock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
	{
		if (g_rock[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_rock[nCnt].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rock[nCnt].rot.y, g_rock[nCnt].rot.x, g_rock[nCnt].rot.z);
			D3DXMatrixMultiply(&g_rock[nCnt].mtxWorld, &g_rock[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_rock[nCnt].pos.x, g_rock[nCnt].pos.y, g_rock[nCnt].pos.z);
			D3DXMatrixMultiply(&g_rock[nCnt].mtxWorld, &g_rock[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_rock[nCnt].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatRock[g_rock[nCnt].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatRock[g_rock[nCnt].nType]; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureRock[nCntMat][g_rock[nCnt].nType]);

				//モデル(パーツ)の描画
				g_pMeshRock[g_rock[nCnt].nType]->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

void CollisionRock(void)
{
	// プレイヤーの取得
	Player* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
	{
		if (g_rock[nCnt].bUse == true)
		{
			if (pPlayer->posOld.y + pPlayer->size.y <= g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y >= g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f)
			{
				if (pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->pos.y = g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f - pPlayer->size.y;
					pPlayer->move.y = 0.0f;
				}
			}

			if (pPlayer->posOld.y >= g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y && pPlayer->pos.y <= g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y)
			{
				if (pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->bJump = false;
					pPlayer->pos.y = (g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y);
					pPlayer->move.y = 0.0f;
				}
			}

			if (pPlayer->posOld.z + pPlayer->size.z * 0.5f <= g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f >= g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y < g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y > g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->pos.z = (g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f) - pPlayer->size.z * 0.5f;
					pPlayer->move.z = 0.0f;
				}
			}

			if (pPlayer->posOld.z - pPlayer->size.z * 0.5f >= g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.z - pPlayer->size.z * 0.5f <= g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y < g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y > g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->pos.z = (g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f) + pPlayer->size.z * 0.5f;
					pPlayer->move.z = 0.0f;
				}
			}

			if (pPlayer->posOld.x + pPlayer->size.x * 0.5f <= g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f >= g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y < g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y > g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f)
				{
					pPlayer->pos.x = (g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f) - pPlayer->size.x * 0.5f;
					pPlayer->move.x = 0.0f;
				}
			}

			if (pPlayer->posOld.x - pPlayer->size.x * 0.5f >= g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f <= g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y < g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y > g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f)
				{
					pPlayer->pos.x = (g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f) + pPlayer->size.x * 0.5f;
					pPlayer->move.x = 0.0f;
				}
			}

			CollisionPlayer(1);
		}
	}
}

void SetRock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 movepos, D3DXVECTOR3 moverot, int nType)
{
	for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
	{
		if (g_rock[nCnt].bUse == false)
		{
			g_rock[nCnt].pos = pos;
			g_rock[nCnt].rot = rot;
			g_rock[nCnt].movepos = movepos;
			g_rock[nCnt].moverot = moverot;
			g_rock[nCnt].nType = nType;
			g_rock[nCnt].nLife = 60 * 5;
			g_rock[nCnt].bUse = true;
			break;
		}
	}
}

Rock* GetRock(void)
{
	return &g_rock[0];
}

RockSize* GetRockSize(void)
{
	return &g_rocksize[0];
}
