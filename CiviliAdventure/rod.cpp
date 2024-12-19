#include "rod.h"
#include "input.h"
#include "rock.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureRod[128][RODTYPE_MAX] = {};
LPD3DXMESH g_pMeshRod[RODTYPE_MAX] = {};//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatRod[RODTYPE_MAX] = {};//マテリアルへのポインタ
DWORD g_dwNumMatRod[RODTYPE_MAX] = {};//マテリアルの数
Rod g_rod[MAX_ROD];
RodSize g_rodsize[RODTYPE_MAX];


void InitRod(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//各種変数の初期化

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/rodv.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatRod[0],
		NULL,
		&g_dwNumMatRod[0],
		&g_pMeshRod[0]);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/rodb.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatRod[1],
		NULL,
		&g_dwNumMatRod[1],
		&g_pMeshRod[1]);


	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ

	for (int nCnt = 0; nCnt < RODTYPE_MAX; nCnt++)
	{
		//頂点数の取得
		nNumVtx = g_pMeshRod[nCnt]->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshRod[nCnt]->GetFVF());
		//頂点バッファのロック
		g_pMeshRod[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//xの最小値比較
			if (vtx.x < g_rodsize[nCnt].vtxMin.x)
			{
				g_rodsize[nCnt].vtxMin.x = vtx.x;
			}

			//xの最大値比較
			if (vtx.x > g_rodsize[nCnt].vtxMax.x)
			{
				g_rodsize[nCnt].vtxMax.x = vtx.x;
			}


			//yの最小値比較
			if (vtx.y < g_rodsize[nCnt].vtxMin.y)
			{
				g_rodsize[nCnt].vtxMin.y = vtx.y;
			}

			//yの最大値比較
			if (vtx.y > g_rodsize[nCnt].vtxMax.y)
			{
				g_rodsize[nCnt].vtxMax.y = vtx.y;
			}

			//zの最小値比較
			if (vtx.z < g_rodsize[nCnt].vtxMin.z)
			{
				g_rodsize[nCnt].vtxMin.z = vtx.z;
			}

			//zの最大値比較
			if (vtx.z > g_rodsize[nCnt].vtxMax.z)
			{
				g_rodsize[nCnt].vtxMax.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		g_pMeshRod[nCnt]->UnlockVertexBuffer();

		g_rodsize[nCnt].size = g_rodsize[nCnt].vtxMax - g_rodsize[nCnt].vtxMin;

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatRod[nCnt]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatRod[nCnt]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureRod[nCntMat][nCnt]);
			}
		}
	}
}

void UninitRod(void)
{
	for (int nCnt = 0; nCnt < MAX_ROD; nCnt++)
	{
		if (g_rod[nCnt].bUse == true)
		{
			g_rod[nCnt].bUse = false;
		}
	}

	for (int nCnt = 0; nCnt < RODTYPE_MAX; nCnt++)
	{
		//テクスチャの解放
		if (g_pMeshRod[nCnt] != NULL)
		{
			g_pMeshRod[nCnt]->Release();
			g_pMeshRod[nCnt] = NULL;
		}

		//頂点バッファの解放
		if (g_pBuffMatRod[nCnt] != NULL)
		{
			g_pBuffMatRod[nCnt]->Release();
			g_pBuffMatRod[nCnt] = NULL;
		}

		for (int nCntTex = 0; nCntTex < 1; nCntTex++)
		{
			//テクスチャの破棄
			if (g_apTextureRod[nCntTex][nCnt] != NULL)
			{
				g_apTextureRod[nCntTex][nCnt]->Release();
				g_apTextureRod[nCntTex][nCnt] = NULL;
			}
		}
	}
}

void UpdateRod(void)
{
	for (int nCnt = 0; nCnt < MAX_ROD; nCnt++)
	{
		if (g_rod[nCnt].bUse == true)
		{
			g_rod[nCnt].posold = g_rod[nCnt].pos;

			g_rod[nCnt].pos += g_rod[nCnt].movepos;


			if (g_rod[nCnt].pos.x > 150.0f || g_rod[nCnt].pos.x < -150.0f)
			{
				g_rod[nCnt].movepos.x *= -1.0f;
			}

			if (g_rod[nCnt].pos.y > 150.0f || g_rod[nCnt].pos.y < 0.0f)
			{
				g_rod[nCnt].movepos.y *= -1.0f;
			}

			if (g_rod[nCnt].pos.z > 150.0f || g_rod[nCnt].pos.z < -150.0f)
			{
				g_rod[nCnt].movepos.z *= -1.0f;
			}
			CollisionPlayer(0);
		}
	}
}

void DrawRod(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	for (int nCnt = 0; nCnt < MAX_ROD; nCnt++)
	{
		if (g_rod[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_rod[nCnt].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rod[nCnt].rot.y, g_rod[nCnt].rot.x, g_rod[nCnt].rot.z);
			D3DXMatrixMultiply(&g_rod[nCnt].mtxWorld, &g_rod[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_rod[nCnt].pos.x, g_rod[nCnt].pos.y, g_rod[nCnt].pos.z);
			D3DXMatrixMultiply(&g_rod[nCnt].mtxWorld, &g_rod[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_rod[nCnt].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatRod[g_rod[nCnt].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatRod[g_rod[nCnt].nType]; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureRod[nCntMat][g_rod[nCnt].nType]);

				//モデル(パーツ)の描画
				g_pMeshRod[g_rod[nCnt].nType]->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

void CollisionRod(void)
{
	// プレイヤーの取得
	Player* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_ROD; nCnt++)
	{
		if (g_rod[nCnt].bUse == true)
		{
			if (pPlayer->posOld.y + pPlayer->size.y <= g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y >= g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f)
			{
				if (pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->pos.y = g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f - pPlayer->size.y;
					pPlayer->move.y = 0.0f;
						SetRock(D3DXVECTOR3(0.0f, 25.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ROCKTYPE_VERTICAL);

				}
			}
			
			if (pPlayer->posOld.y >= g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y && pPlayer->pos.y <= g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y)
			{
				if (pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->bJump = false;
					pPlayer->pos.y = (g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y);
					pPlayer->move.y = 0.0f;
 						SetRock(D3DXVECTOR3(0.0f, 25.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ROCKTYPE_VERTICAL);

				}
			}

			
			if (pPlayer->posOld.z + pPlayer->size.z * 0.5f <= g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f >= g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y*0.5f < g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y*0.5f > g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->pos.z = (g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f) - pPlayer->size.z * 0.5f;
					pPlayer->move.z = 0.0f;
						SetRock(D3DXVECTOR3(0.0f, 25.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ROCKTYPE_VERTICAL);

				}
			}


			if (pPlayer->posOld.z - pPlayer->size.z * 0.5f >= g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.z - pPlayer->size.z * 0.5f <= g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y*0.5f < g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y*0.5f > g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->pos.z = (g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f) + pPlayer->size.z * 0.5f;
					pPlayer->move.z = 0.0f;
						SetRock(D3DXVECTOR3(0.0f, 25.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ROCKTYPE_VERTICAL);

				}
			}

			if (pPlayer->posOld.x + pPlayer->size.x * 0.5f <= g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f >= g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y < g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y > g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f)
				{
					pPlayer->pos.x = (g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f) - pPlayer->size.x * 0.5f;
					pPlayer->move.x = 0.0f;
						SetRock(D3DXVECTOR3(0.0f, 25.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ROCKTYPE_VERTICAL);

				}
			}

			if (pPlayer->posOld.x - pPlayer->size.x * 0.5f >= g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f <= g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y < g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y > g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f)
				{
					pPlayer->pos.x = (g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f) + pPlayer->size.x * 0.5f;
					pPlayer->move.x = 0.0f;
					SetRock(D3DXVECTOR3(0.0f, 25.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ROCKTYPE_VERTICAL);
				}
			}

		}
	}
}

void SetRod(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 movepos, D3DXVECTOR3 moverot, int nType)
{
	for (int nCnt = 0; nCnt < MAX_ROD; nCnt++)
	{
		if (g_rod[nCnt].bUse == false)
		{
			g_rod[nCnt].pos = pos;
			g_rod[nCnt].rot = rot;
			g_rod[nCnt].movepos = movepos;
			g_rod[nCnt].moverot = moverot;
			g_rod[nCnt].nType = nType;
			g_rod[nCnt].bUse = true;
			break;
		}
	}
}

Rod* GetRod(void)
{
	return &g_rod[0];
}

RodSize* GetRodSize(void)
{
	return &g_rodsize[0];
}
