//==================================================================
//
//ライト処理<light.cpp>
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "light.h"
//グローバル変数
D3DLIGHT9 g_light;//ライト情報

void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir;//ライトの方向ベクトル

	//ライトをクリアする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	//ライトの種類を設定
	g_light.Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光を設定
	g_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

	//正規化する(大きさ1のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);
	g_light.Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(0, &g_light);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);
}

void UninitLight(void)
{
}

void UpdateLight(void)
{

}
