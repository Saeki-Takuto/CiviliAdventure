//==================================================================
//
//���b�V���t�B�[���h����<meshfield.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _MESHFIELD_H_	//���̃}�N����`������ĂȂ�������
#define _MESHFIELD_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#define MESHFIELD_X_BLOCK (20)
#define MESHFIELD_Z_BLOCK (20)


#define MESHFIELD_VERTEX_NUM ((MESHFIELD_X_BLOCK+1)*(MESHFIELD_Z_BLOCK+1))
#define MESHFIELD_INDEX_NUM (MESHFIELD_PRIMITIVE_NUM+2)
#define MESHFIELD_PRIMITIVE_NUM (((MESHFIELD_X_BLOCK*MESHFIELD_Z_BLOCK)*2))+(4*(MESHFIELD_Z_BLOCK-1))


#define NUM_WIDTH (300)
#define NUM_HEIGHT (1000)

//�v���g�^�C�v�錾
void InitMeshField(void);//����������
void UninitMeshField(void);//�I������
void UpdateMeshField(void);//�X�V����
void DrawMeshField(void);//�`�揈��

#endif