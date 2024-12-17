//==================================================================
//
//�Ǐ���<wall.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _WALL_H_	//���̃}�N����`������ĂȂ�������
#define _WALL_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#define NUM_WALL (8)//�G�̎��


typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Wall;

//�v���g�^�C�v�錾
void InitWall(void);//����������
void UninitWall(void);//�I������
void UpdateWall(void);//�X�V����
void DrawWall(void);//�`�揈��
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float alpha,int nType);
void CollisionWall(void);

#endif