//==================================================================
//
//ビルボード処理<billboard.cpp>
//Author:Saeki Takuto
//
//==================================================================

#include "billboard.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;		//テクスチャへのポインタ
Billboard g_billboard;

void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg000.jpg",
		&g_pTextureBillboard);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard, NULL);

	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標を設定
	pVtx[0].pos = D3DXVECTOR3(-150.0f, +150.0f, -50.0f);
	pVtx[1].pos = D3DXVECTOR3(+150.0f, +150.0f, -50.0f);
	pVtx[2].pos = D3DXVECTOR3(-150.0f, -150.0f, -50.0f);
	pVtx[3].pos = D3DXVECTOR3(+150.0f, -150.0f, -50.0f);

	//各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0, 0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0, 0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0, 0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0, 0.0f,-1.0f);

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

	//頂点バッファのアンロック
	g_pVtxBuffBillboard->Unlock();

}

void UninitBillboard(void)
{
}

void UpdateBillboard(void)
{
}

void DrawBillboard(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_billboard.mtxWorld);

	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//カメラの逆行列を設定
	g_billboard.mtxWorld._11 = mtxView._11;
	g_billboard.mtxWorld._12 = mtxView._12;
	g_billboard.mtxWorld._13 = mtxView._13;
	g_billboard.mtxWorld._21 = mtxView._21;
	g_billboard.mtxWorld._22 = mtxView._22;
	g_billboard.mtxWorld._23 = mtxView._23;
	g_billboard.mtxWorld._31 = mtxView._31;
	g_billboard.mtxWorld._32 = mtxView._32;
	g_billboard.mtxWorld._33 = mtxView._33;

	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_billboard.rot.y, g_billboard.rot.x, g_billboard.rot.z);
	//D3DXMatrixMultiply(&g_billboard.mtxWorld, &g_billboard.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_billboard.pos.x, g_billboard.pos.y, g_billboard.pos.z);
	D3DXMatrixMultiply(&g_billboard.mtxWorld, &g_billboard.mtxWorld, &mtxTrans);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);//Zの比較方法
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);//Zバッファに書き込まない

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_billboard.mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBillboard);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);//Zバッファに書き込む

	//アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
}
