//==================================================================
//
//�e����<shadow.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _SHADOW_H_	//���̃}�N����`������ĂȂ�������
#define _SHADOW_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Shadow;

//�v���g�^�C�v�錾
void InitShadow(void);//����������
void UninitShadow(void);//�I������
void UpdateShadow(void);//�X�V����
void DrawShadow(void);//�`�揈��
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);

#endif