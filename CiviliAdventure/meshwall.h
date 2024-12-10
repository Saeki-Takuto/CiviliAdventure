//==================================================================
//
//���b�V���E�H�[������<meshwall.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _MESHWALL_H_	//���̃}�N����`������ĂȂ�������
#define _MESHWALL_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#define MESHWALL_X_BLOCK (2)
#define MESHWALL_Y_BLOCK (2)

#define MAX_MESHWALL (4)


#define MESHWALL_VERTEX_NUM ((MESHWALL_X_BLOCK+1)*(MESHWALL_Y_BLOCK+1))
#define MESHWALL_INDEX_NUM (MESHWALL_PRIMITIVE_NUM+2)
#define MESHWALL_PRIMITIVE_NUM (((MESHWALL_X_BLOCK*MESHWALL_Y_BLOCK)*2))+(4*(MESHWALL_Y_BLOCK-1))


#define NUM_WIDTH (300)
#define NUM_HEIGHT (300)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}MeshWall;

//�v���g�^�C�v�錾
void InitMeshWall(void);//����������
void UninitMeshWall(void);//�I������
void UpdateMeshWall(void);//�X�V����
void DrawMeshWall(void);//�`�揈��

#endif