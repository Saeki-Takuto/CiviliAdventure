//==================================================================
//
//影処理<shadow.cpp>
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "shadow.h"

//グローバル変数宣言
Shadow g_aShadow[64];

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;		//テクスチャへのポインタ
//D3DXVECTOR3 g_posShadow;//位置
//D3DXVECTOR3 g_rotShadow;//向き
//D3DXMATRIX g_mtxWorldShadow;//ワールドマトリックス

//==================================================================
//初期化処理
//==================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&g_pTextureShadow);


	for (int nCntShadow = 0; nCntShadow < 64; nCntShadow++)
	{
		g_aShadow[nCntShadow].bUse = false;
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 64,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow, NULL);

	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < 64; nCntShadow++)
	{
		//頂点座標を設定
		pVtx[0].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x-10.0f, g_aShadow[nCntShadow].pos.y+0.1f, g_aShadow[nCntShadow].pos.z+10.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x+10.0f, g_aShadow[nCntShadow].pos.y+0.1f, g_aShadow[nCntShadow].pos.z+10.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x-10.0f, g_aShadow[nCntShadow].pos.y+0.1f, g_aShadow[nCntShadow].pos.z-10.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x+10.0f, g_aShadow[nCntShadow].pos.y+0.1f, g_aShadow[nCntShadow].pos.z-10.0f);

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
	}
	//頂点バッファのアンロック
	g_pVtxBuffShadow->Unlock();
}

//==================================================================
//終了処理
//==================================================================
void UninitShadow(void)
{
	//テクスチャの解放
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//==================================================================
//更新処理
//==================================================================
void UpdateShadow(void)
{
}

//==================================================================
//描画処理
//==================================================================
void DrawShadow(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < 64; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, 0.1f, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntShadow * 4, 2);
		}
	}
	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow<64;nCntShadow++)
	{
		//bUseがfalseの場合、pos,rotを代入しbUseをtrueにする
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;
			break;
		}
	}
	return nCntShadow;//影の番号(index)を返す
}

void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	//引数で指定された番号の影のposを設定
	g_aShadow[nIdxShadow].pos = pos;
}
