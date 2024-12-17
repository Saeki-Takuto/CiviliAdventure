//==================================================================
//
//���f������<rock.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _ROCK_H_	//���̃}�N����`������ĂȂ�������
#define _ROCK_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "player.h"

#define MAX_ROCK (1)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posold;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 movepos;
	D3DXVECTOR3 moverot;
	D3DXMATRIX mtxWorld;
	int nType;
	int nLife;
	bool bUse;
}Rock;

typedef struct
{
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 size;
}RockSize;

typedef enum
{
	ROCKTYPE_VERTICAL = 0,
	ROCKTYPE_BESIDE,
	ROCKTYPE_MAX
}ROCKTYPE;

//�v���g�^�C�v�錾
void InitRock(void);//����������
void UninitRock(void);//�I������
void UpdateRock(void);//�X�V����
void DrawRock(void);//�`�揈��
void CollisionRock(void);//�����蔻��
void SetRock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 movepos, D3DXVECTOR3 moverot, int nType);
Rock* GetRock(void);
RockSize* GetRockSize(void);

#endif