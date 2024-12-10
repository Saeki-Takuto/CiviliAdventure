//==================================================================
//
//ゲーム処理<game.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//ゲームの状態
typedef enum
{
	GAMESTATE_NONE=0,//何もしていない状態
	GAMESTATE_NORMAL,//通常状態
	GAMESTATE_WASUKE,
	GAMESTATE_END,//クリア状態
	GAMESTATE_GAMEOVER,//ゲームオーバー状態
	GAMESTATE_MAX
}GAMESTATE;

//ゲーム構造体の定義
typedef struct
{
	int nNowStage;

}Game;

//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
void SetEnablePause(bool bPause);
GAMESTATE GetGameState(void);
Game* GetGame(void);
#endif


