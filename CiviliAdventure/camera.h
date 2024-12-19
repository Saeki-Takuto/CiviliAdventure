//==================================================================
//
//�J��������<camera.h>
//Author:Saeki Takuto
//
//==================================================================
#ifndef _CAMERA_H_	//���̃}�N����`������ĂȂ�������
#define _CAMERA_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

typedef enum
{
	MODE_CAMERA_NORMAL = 0,
	MODE_CAMERA_PLAYER,
	MODE_CAMERA_SHAKE,
	MODE_CAMERA_MAX
}MODE_CAMERA;

typedef struct
{
	D3DXVECTOR3 posV;//���_
	D3DXVECTOR3 posR;//�����_
	D3DXVECTOR3 posVDest;
	D3DXVECTOR3 posRDest;
	D3DXVECTOR3 vecU;//������x�N�g��
	D3DXMATRIX mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;//�r���[�}�g���b�N�X
	D3DXVECTOR3 rot;//����
	float fDistance;//���_���璍���_�̋���
	int ModeCamera;
	int nCounterShake;
}Camera;

//�v���g�^�C�v�錾
void InitCamera(void);//����������
void UninitCamera(void);//�I������
void UpdateCamera(void);//�X�V����
void SetCamera(void);//�Z�b�g����
Camera* GetCamera(void);

#endif