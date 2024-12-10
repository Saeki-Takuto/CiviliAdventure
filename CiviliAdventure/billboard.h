//==================================================================
//
//�r���{�[�h����<billboard.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _BILLBOARD_H_	//���̃}�N����`������ĂȂ�������
#define _BILLBOARD_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 rot;
	bool bUse;
}Billboard;

//�v���g�^�C�v�錾
void InitBillboard(void);//����������
void UninitBillboard(void);//�I������
void UpdateBillboard(void);//�X�V����
void DrawBillboard(void);//�`�揈��
void SetBillboard(D3DXVECTOR3 pos,D3DXVECTOR3 dir);

#endif