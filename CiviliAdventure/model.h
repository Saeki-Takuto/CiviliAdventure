//==================================================================
//
//���f������<model.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _MODEL_H_	//���̃}�N����`������ĂȂ�������
#define _MODEL_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//���f���̍\����
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture[128];
	LPD3DXMESH pMesh;		//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;			//�}�e���A���̐�
	int nIdxModelParent;	//�e���f���̃C���f�b�N�X
	D3DXVECTOR3 pos;		//�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
}Model;

//�v���g�^�C�v�錾
void InitModel(void);//����������
void UninitModel(void);//�I������
void UpdateModel(void);//�X�V����
void DrawModel(void);//�`�揈��

#endif