//==================================================================
//
//モデル処理<model.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _PLAYER_H_	//このマクロ定義がされてなかったら
#define _PLAYER_H_	//2重インクルード防止のマクロ定義

#include "main.h"
#include "model.h"

#define PLAYER_MAX_PARTS (12)

static const char* PLAYER_PARTS[PLAYER_MAX_PARTS] =
{
	"data/MODEL/00_body.x",
	"data/MODEL/01_head.x",
	"data/MODEL/02_Rshoulder.x",
	"data/MODEL/03_Rarm.x",
	"data/MODEL/04_Rhand.x",
	"data/MODEL/05_Lshoulder.x",
	"data/MODEL/06_Larm.x",
	"data/MODEL/07_Lhand.x",
	"data/MODEL/08_Rleg.x",
	"data/MODEL/09_Rfoot.x",
	"data/MODEL/10_Lleg.x",
	"data/MODEL/11_Lfoot.x",
};

//モーションの種類
typedef enum
{
	MOTION_TYPE_NEUTRAL=0,	//待機
	MOTION_TYPE_MOVE,		//移動
	MOTION_TYPE_ACTION,		//アクション
	MOTION_TYPE_JUMP,		//ジャンプ
	MOTION_TYPE_LANDING,	//着地
	MOTION_TYPE_MAX
}MOTIONTYPE;

//キーの構造体
typedef struct
{
	float fPosX;	//位置X
	float fPosY;	//位置Y
	float fPosZ;	//位置Z

	float fRotX;	//向きX
	float fRotY;	//向きY
	float fRotZ;	//向きZ
}KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;		//再生フレーム
	KEY aKey[PLAYER_MAX_PARTS];	//各パーツのキー要素
}KEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;				//ループするかどうか
	int nNumKey;			//キーの総数
	KEY_INFO aKeyInfo[5];	//キー情報
}MOTION_INFO;

//static KEY_INFO g_aKeyNeutral[] =
//{
//	{40,
//	{{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},
//	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f}}},
//	{40,
//	{{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},
//	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f}}}
//};

//プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 move;
	D3DXVECTOR3 vtxMinBlock, vtxMaxBlock;
	D3DXVECTOR3 size;
	int g_nIdxShadow;
	D3DXMATRIX mtxWorld;
	Model aModel[12];							//モデル（パーツ)
	int nNumModel;								//モデル(パーツ)の総数
	MOTION_INFO aMotionInfo[MOTION_TYPE_MAX];	//モーション情報
	int nNumMotion;								//モーションの総数
	MOTIONTYPE motionType;						//モーションの種類
	bool bLoopMotion;							//ループするかどうか
	int nNumKey;								//キーの総数
	int nKey;
	int nCounterMotion;
	bool bJump;
}Player;

//プロトタイプ宣言
void InitPlayer(void);		//初期化処理
void UninitPlayer(void);	//終了処理
void UpdatePlayer(void);	//更新処理
void DrawPlayer(void);		//描画処理
Player* GetPlayer();

#endif