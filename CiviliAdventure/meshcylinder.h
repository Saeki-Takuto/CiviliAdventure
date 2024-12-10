//==================================================================
//
//���b�V���t�B�[���h����<meshcylinder.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _MESHCYLINDER_H_	//���̃}�N����`������ĂȂ�������
#define _MESHCYLINDER_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#define MESHCYLINDER_X_BLOCK (30)
#define MESHCYLINDER_Z_BLOCK (30)


#define MESHCYLINDER_VERTEX_NUM ((MESHCYLINDER_X_BLOCK+1)*(MESHCYLINDER_Z_BLOCK+1))
#define MESHCYLINDER_INDEX_NUM (MESHCYLINDER_PRIMITIVE_NUM+2)
#define MESHCYLINDER_PRIMITIVE_NUM (((MESHCYLINDER_X_BLOCK*MESHCYLINDER_Z_BLOCK)*2)+(4*(MESHCYLINDER_Z_BLOCK-1)))


#define NUM_WIDTH (300)
#define NUM_HEIGHT (300)

//�v���g�^�C�v�錾
void InitMeshCylinder(void);//����������
void UninitMeshCylinder(void);//�I������
void UpdateMeshCylinder(void);//�X�V����
void DrawMeshCylinder(void);//�`�揈��

#endif