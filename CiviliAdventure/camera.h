//==================================================================
//
//カメラ処理<camera.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _CAMERA_H_	//このマクロ定義がされてなかったら
#define _CAMERA_H_	//2重インクルード防止のマクロ定義

#include "main.h"

typedef enum
{
	MODE_CAMERA_NORMAL = 0,
	MODE_CAMERA_PLAYER,
	MODE_CAMERA_MAX
}MODE_CAMERA;

typedef struct
{
	D3DXVECTOR3 posV;//視点
	D3DXVECTOR3 posR;//注視点
	D3DXVECTOR3 posVDest;
	D3DXVECTOR3 posRDest;
	D3DXVECTOR3 vecU;//上方向ベクトル
	D3DXMATRIX mtxProjection;//プロジェクションマトリックス
	D3DXMATRIX mtxView;//ビューマトリックス
	D3DXVECTOR3 rot;//向き
	float fDistance;//視点から注視点の距離
	int ModeCamera;
}Camera;

//プロトタイプ宣言
void InitCamera(void);//初期化処理
void UninitCamera(void);//終了処理
void UpdateCamera(void);//更新処理
void SetCamera(void);//セット処理
Camera* GetCamera(void);

#endif