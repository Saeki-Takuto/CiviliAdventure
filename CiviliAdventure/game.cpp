//==================================================================
//
//ゲーム処理<game.cpp>
//Author:Saeki Takuto
//
//==================================================================
#include "input.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "pause.h"
#include "rankingscore.h"
#include "time.h"
#include "memory.h"
#include "player.h"
#include "block.h"
#include "meshfield.h"
#include "meshwall.h"
#include "shadow.h"
#include "wall.h"
#include "light.h"
#include "rod.h"
#include "rock.h"
#include "time.h"

//グローバル変数宣言
GAMESTATE g_gameState = GAMESTATE_NONE;//ゲームの状態
int g_nCounterGameState=0;//状態管理カウンター
bool g_bPause = false;//ポーズ中かどうか
Game g_aGame;

//ゲーム画面の初期化処理
void InitGame(void)
{
	InitMeshField();
	//InitMeshWall();
	//InitBillboard();
	InitRod();
	InitRock();
	InitShadow();
	InitBlock();
	InitPlayer();
	InitWall();
	InitTime();
	InitCamera();
	InitLight();
	InitPause();

	SetWall(D3DXVECTOR3(0.0f, 150.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f,0);
	SetWall(D3DXVECTOR3(0.0f, 150.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 1.0f,0);
	SetWall(D3DXVECTOR3(150.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 1.0f,1);
	SetWall(D3DXVECTOR3(-150.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), 1.0f,1);
	
	SetWall(D3DXVECTOR3(0.0f, 150.0f, 500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 0.5f,0);
	SetWall(D3DXVECTOR3(0.0f, 150.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.5f,0);
	SetWall(D3DXVECTOR3(150.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), 0.5f,1);
	SetWall(D3DXVECTOR3(150.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 0.5f,1);

	SetRod(D3DXVECTOR3(50.0f, 30.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), RODTYPE_BESIDE);
	SetRod(D3DXVECTOR3(50.0f, 10.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), RODTYPE_BESIDE);

	SetRod(D3DXVECTOR3(-75.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), RODTYPE_VERTICAL);
	SetRod(D3DXVECTOR3(75.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), RODTYPE_VERTICAL);

	SetRod(D3DXVECTOR3(-75.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), RODTYPE_VERTICAL);
	SetRod(D3DXVECTOR3(75.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), RODTYPE_VERTICAL);

	SetRod(D3DXVECTOR3(50.0f, 150.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), RODTYPE_BESIDE);
	SetRod(D3DXVECTOR3(50.0f, 75.0f,  200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), RODTYPE_BESIDE);


	g_gameState = GAMESTATE_NORMAL;//通常状態に設定
	g_nCounterGameState = 0;

	g_bPause = false;//ポーズ解除

	PlaySound(SOUND_LABEL_BGM03);
}

//ゲーム画面の終了処理
void UninitGame(void)
{
	//ポーズの終了処理
	UninitPause();
	UninitMeshField();
	//UninitMeshWall();
	UninitWall();
	UninitRod();
	UninitRock();
	UninitPlayer();
	UninitBlock();
	UninitShadow();
	UninitTime();
	UninitCamera();
	UninitLight();
	//UninitBillboard();


	//音楽の停止
	StopSound();
}

//ゲーム画面の更新処理
void UpdateGame(void)
{
	int nNum2;
	if (KeyboardTrigger(DIK_P) == true|| JoypadTrigger(JOYKEY_START)==true)
	{//ポーズキー(P)が押された

		if (g_bPause == false)
		{
			//サウンドの設定
			PlaySound(SOUND_LABEL_SE04);
		}
		else
		{
			//サウンドの設定
			PlaySound(SOUND_LABEL_SE05);

		}
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{//ポーズ中
		UpdatePause();
	}

	if (g_bPause == false)
	{//ポーズ中でなければ

		UpdateMeshField();
		//UpdateMeshWall();
		UpdateShadow();
		UpdateRod();
		UpdateRock();
		UpdatePlayer();
		UpdateBlock();
		UpdateTime();
		UpdateWall();
		UpdateCamera();
		UpdateLight();
		//UpdateBillboard();


		Player* pPlayer = GetPlayer();

	}
	//	if (GetTime()<=0)
	//	{
	//		g_gameState = GAMESTATE_GAMEOVER;
	//	}
	//	else if (pPlayer->bClear==true)
	//	{
	//		g_gameState = GAMESTATE_END;
	//	}

	//	if (KeyboardTrigger(DIK_C))
	//	{
	//		g_gameState = GAMESTATE_END;
	//	}

	//	switch (g_gameState)
	//	{
	//	case GAMESTATE_NORMAL://通常状態
	//		break;
	//	case GAMESTATE_END://終了状態
	//		g_nCounterGameState++;
	//		if (g_nCounterGameState >= 60)
	//		{
	//			//モード設定(リザルト画面に移行)
	//			SetFade(MODE_RESULT);

	//			ResetRanking();

	//			//ランキングの設定
	//			SetRankingScore(GetTime());

	//			g_nCounterGameState = 0;
	//			g_gameState = GAMESTATE_NONE;//何もしていない状態に設定

	//		}
	//		break;
	//	case GAMESTATE_GAMEOVER://終了状態
	//		g_nCounterGameState++;
	//		if (g_nCounterGameState >= 50)
	//		{
	//			//モード設定(リザルト画面に移行)
	//			SetFade(MODE_RESULT);

	//			g_nCounterGameState = 0;
	//			g_gameState = GAMESTATE_NONE;//何もしていない状態に設定
	//		}
	//		break;
	//	}
	//}
}

//ゲーム画面の描画処理
void DrawGame(void)
{

	SetCamera();
	DrawMeshField();
	//DrawMeshWall();
	DrawRod();
	DrawRock();
	DrawShadow();
	DrawPlayer();
	DrawBlock();
	DrawWall();
	DrawTime();
	//DrawBillboard();

	if (g_bPause == true)
	{
		//ポーズの描画処理
		DrawPause();
	}
}

//ゲームの状態の設定
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//ゲームの状態の取得
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//ポーズの有効無効設定
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

Game* GetGame(void)
{
	return &g_aGame;
}
