//==================================================================
//
//���f������<rod.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _ROD_H_	//���̃}�N����`������ĂȂ�������
#define _ROD_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "player.h"

#define MAX_ROD (128)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posold;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 movepos;
	D3DXVECTOR3 moverot;
	D3DXMATRIX mtxWorld;
	int nType;
	bool bUse;
}Rod;

typedef struct
{
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 size;
}RodSize;

typedef enum
{
	RODTYPE_VERTICAL=0,
	RODTYPE_BESIDE,
	RODTYPE_MAX
}RODTYPE;

//�v���g�^�C�v�錾
void InitRod(void);//����������
void UninitRod(void);//�I������
void UpdateRod(void);//�X�V����
void DrawRod(void);//�`�揈��
void CollisionRod(void);//�����蔻��
void SetRod(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 movepos, D3DXVECTOR3 moverot, int nType);
Rod* GetRod(void);
RodSize* GetRodSize(void);

#endif