//==================================================================
//
//�Q�[������<game.cpp>
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

//�O���[�o���ϐ��錾
GAMESTATE g_gameState = GAMESTATE_NONE;//�Q�[���̏��
int g_nCounterGameState=0;//��ԊǗ��J�E���^�[
bool g_bPause = false;//�|�[�Y�����ǂ���
Game g_aGame;

//�Q�[����ʂ̏���������
void InitGame(void)
{

	InitMeshField();
	InitMeshWall();
	//InitBillboard();
	InitRod();
	InitShadow();
	InitBlock();
	InitPlayer();
	InitWall();
	InitCamera();
	InitLight();
	InitPause();


	SetWall(D3DXVECTOR3(0.0f, 150.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
	SetWall(D3DXVECTOR3(0.0f, 150.0f, -150.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 1.0f);
	SetWall(D3DXVECTOR3(150.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 1.0f);
	SetWall(D3DXVECTOR3(-150.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), 1.0f);

	SetWall(D3DXVECTOR3(0.0f, 150.0f, 150.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 0.5f);
	SetWall(D3DXVECTOR3(0.0f, 150.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.5f);
	SetWall(D3DXVECTOR3(150.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), 0.5f);
	SetWall(D3DXVECTOR3(-150.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 0.5f);

	SetRod(D3DXVECTOR3(50.0f, 0.0f, 10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), RODTYPE_VERTICAL);
	SetRod(D3DXVECTOR3(10.0f, 0.0f, 10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), RODTYPE_VERTICAL);
	SetRod(D3DXVECTOR3(50.0f, 100.0f, 10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), RODTYPE_BESIDE);
	SetRod(D3DXVECTOR3(50.0f, 50.0f, 10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), RODTYPE_BESIDE);


	
	g_gameState = GAMESTATE_NORMAL;//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;

	g_bPause = false;//�|�[�Y����

	PlaySound(SOUND_LABEL_BGM03);

	//for (int nCnt = 0; nCnt < 4;nCnt++)
	//{
	//	SetBlock(D3DXVECTOR3(600, 800-40*nCnt, 0.0f), 40, 40, 0);
	//}
}

//�Q�[����ʂ̏I������
void UninitGame(void)
{
	//�|�[�Y�̏I������
	UninitPause();

	//UninitPlayer();

	//UninitBlock();

	UninitMeshField();
	UninitMeshWall();
	UninitWall();
	UninitRod();
	UninitPlayer();
	UninitBlock();
	UninitShadow();
	UninitCamera();
	UninitLight();
	//UninitBillboard();


	//���y�̒�~
	StopSound();
}

//�Q�[����ʂ̍X�V����
void UpdateGame(void)
{
	int nNum2;
	if (KeyboardTrigger(DIK_P) == true|| JoypadTrigger(JOYKEY_START)==true)
	{//�|�[�Y�L�[(P)�������ꂽ

		if (g_bPause == false)
		{
			//�T�E���h�̐ݒ�
			PlaySound(SOUND_LABEL_SE04);
		}
		else
		{
			//�T�E���h�̐ݒ�
			PlaySound(SOUND_LABEL_SE05);

		}
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{//�|�[�Y��
		UpdatePause();
	}

	if (g_bPause == false)
	{//�|�[�Y���łȂ����

		UpdateMeshField();
		UpdateMeshWall();
		UpdateShadow();
		UpdateRod();
		UpdatePlayer();
		UpdateBlock();
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
	//	case GAMESTATE_NORMAL://�ʏ���
	//		break;
	//	case GAMESTATE_END://�I�����
	//		g_nCounterGameState++;
	//		if (g_nCounterGameState >= 60)
	//		{
	//			//���[�h�ݒ�(���U���g��ʂɈڍs)
	//			SetFade(MODE_RESULT);

	//			ResetRanking();

	//			//�����L���O�̐ݒ�
	//			SetRankingScore(GetTime());

	//			g_nCounterGameState = 0;
	//			g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�

	//		}
	//		break;
	//	case GAMESTATE_GAMEOVER://�I�����
	//		g_nCounterGameState++;
	//		if (g_nCounterGameState >= 50)
	//		{
	//			//���[�h�ݒ�(���U���g��ʂɈڍs)
	//			SetFade(MODE_RESULT);

	//			g_nCounterGameState = 0;
	//			g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�
	//		}
	//		break;
	//	}
	//}
}

//�Q�[����ʂ̕`�揈��
void DrawGame(void)
{

	SetCamera();
	DrawMeshField();
	DrawMeshWall();
	DrawRod();
	DrawShadow();
	DrawPlayer();
	DrawBlock();
	DrawWall();
	//DrawBillboard();

	if (g_bPause == true)
	{
		//�|�[�Y�̕`�揈��
		DrawPause();
	}
}

//�Q�[���̏�Ԃ̐ݒ�
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//�Q�[���̏�Ԃ̎擾
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//�|�[�Y�̗L�������ݒ�
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

Game* GetGame(void)
{
	return &g_aGame;
}
