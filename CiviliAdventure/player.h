//==================================================================
//
//���f������<model.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _PLAYER_H_	//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_	//2�d�C���N���[�h�h�~�̃}�N����`

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

//���[�V�����̎��
typedef enum
{
	MOTION_TYPE_NEUTRAL=0,	//�ҋ@
	MOTION_TYPE_MOVE,		//�ړ�
	MOTION_TYPE_ACTION,		//�A�N�V����
	MOTION_TYPE_JUMP,		//�W�����v
	MOTION_TYPE_LANDING,	//���n
	MOTION_TYPE_MAX
}MOTIONTYPE;

//�L�[�̍\����
typedef struct
{
	float fPosX;	//�ʒuX
	float fPosY;	//�ʒuY
	float fPosZ;	//�ʒuZ

	float fRotX;	//����X
	float fRotY;	//����Y
	float fRotZ;	//����Z
}KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;		//�Đ��t���[��
	KEY aKey[PLAYER_MAX_PARTS];	//�e�p�[�c�̃L�[�v�f
}KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;				//���[�v���邩�ǂ���
	int nNumKey;			//�L�[�̑���
	KEY_INFO aKeyInfo[5];	//�L�[���
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

//�v���C���[�̍\����
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
	Model aModel[12];							//���f���i�p�[�c)
	int nNumModel;								//���f��(�p�[�c)�̑���
	MOTION_INFO aMotionInfo[MOTION_TYPE_MAX];	//���[�V�������
	int nNumMotion;								//���[�V�����̑���
	MOTIONTYPE motionType;						//���[�V�����̎��
	bool bLoopMotion;							//���[�v���邩�ǂ���
	int nNumKey;								//�L�[�̑���
	int nKey;
	int nCounterMotion;
	bool bJump;
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);		//����������
void UninitPlayer(void);	//�I������
void UpdatePlayer(void);	//�X�V����
void DrawPlayer(void);		//�`�揈��
Player* GetPlayer();

#endif