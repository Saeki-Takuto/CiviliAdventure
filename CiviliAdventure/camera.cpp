//==================================================================
//
//�J��������<camera.cpp>
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"

//�O���[�o���ϐ�
Camera g_camera;//�J�������

//==================================================================
//����������
//==================================================================
void InitCamera(void)
{
	//���_�E�����_�E��������w�肷��
	g_camera.posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_camera.rot = D3DXVECTOR3(-100.0f, 3.14f, 0.0f);

	float fDisX = g_camera.posV.x - g_camera.posR.x;
	float fDisY = g_camera.posV.y - g_camera.posR.y;
	float fDisZ = g_camera.posV.z - g_camera.posR.z;


	g_camera.fDistance = 300.0f;

	//�p�x�̐��K��
	g_camera.posV.x = g_camera.posR.x + cosf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
	g_camera.posV.y = g_camera.posR.y + sinf(g_camera.rot.x) * g_camera.fDistance;
	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;

	g_camera.ModeCamera = 1;
	g_camera.nCounterShake = 0;

}

//==================================================================
//�I������
//==================================================================
void UninitCamera(void)
{

}

//==================================================================
//�X�V����
//==================================================================
void UpdateCamera(void)
{


	if (KeyboardTrigger(DIK_O) == true)
	{
		g_camera.ModeCamera++;
	}
	else if (KeyboardTrigger(DIK_P) == true)
	{
		g_camera.ModeCamera--;
	}

	if (g_camera.ModeCamera < 0)
	{
		g_camera.ModeCamera = 0;
	}
	else if (g_camera.ModeCamera >= MODE_CAMERA_MAX)
	{
		g_camera.ModeCamera = MODE_CAMERA_MAX - 1;
	}

	if (g_camera.ModeCamera == MODE_CAMERA_PLAYER)
	{
		//�v���C���[�̒Ǐ]
		Player* pPlayer = GetPlayer();

		g_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y) * g_camera.posRDest.y + pPlayer->move.x;
		g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y) * g_camera.posRDest.y + pPlayer->move.z;


		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.1f;
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.1f;

		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;


	}
	else if (g_camera.ModeCamera == MODE_CAMERA_NORMAL)
	{
		//�J�����̈ړ�
		if (KeyboardRepeat(DIK_W) == true)
		{
			g_camera.posR.x += sinf(g_camera.rot.y) * 2.0f;
			g_camera.posR.z += cosf(g_camera.rot.y) * 2.0f;

		}
		else if (KeyboardRepeat(DIK_A) == true)
		{
			g_camera.posR.x += sinf(D3DX_PI * 0.5f + g_camera.rot.y) * 2.0f;
			g_camera.posR.z += cosf(D3DX_PI * 0.5f + g_camera.rot.y) * 2.0f;

		}
		else if (KeyboardRepeat(DIK_S) == true)
		{
			g_camera.posR.x += sinf(g_camera.rot.y) * 2.0f;
			g_camera.posR.z += cosf(g_camera.rot.y) * 2.0f;

		}
		else if (KeyboardRepeat(DIK_D) == true)
		{
			g_camera.posR.x += sinf(g_camera.rot.y) * 2.0f;
			g_camera.posR.z += cosf(g_camera.rot.y) * 2.0f;

		}
	}
	else if (g_camera.ModeCamera == MODE_CAMERA_SHAKE)
	{
		g_camera.nCounterShake++;

		if (g_camera.nCounterShake > 20*0.5f)
		{
			g_camera.posR.x += sinf(D3DX_PI * 0.5f + g_camera.rot.y) * 1.0f;
			g_camera.posR.z += cosf(D3DX_PI * 0.5f + g_camera.rot.y) * 1.0f;

		}
		else if (g_camera.nCounterShake < 20*0.5f)
		{
			g_camera.posR.x += sinf(D3DX_PI * 0.5f + g_camera.rot.y) * -1.0f;
			g_camera.posR.z += cosf(D3DX_PI * 0.5f + g_camera.rot.y) * -1.0f;

		}

		if (g_camera.nCounterShake > 20)
		{
			g_camera.nCounterShake = 0;
		}
	}

	//�J�����̈ړ�
	if (KeyboardRepeat(DIK_W) == true)
	{
		g_camera.posR.x += sinf(g_camera.rot.y) * -2.0f;
		g_camera.posR.z += cosf(g_camera.rot.y) * -2.0f;

	}
	else if (KeyboardRepeat(DIK_A) == true)
	{
		g_camera.posR.x += sinf(D3DX_PI * 0.5f + g_camera.rot.y) * 2.0f;
		g_camera.posR.z += cosf(D3DX_PI * 0.5f + g_camera.rot.y) * 2.0f;

	}
	else if (KeyboardRepeat(DIK_S) == true)
	{
		g_camera.posR.x += sinf(g_camera.rot.y) * 2.0f;
		g_camera.posR.z += cosf(g_camera.rot.y) * 2.0f;

	}
	else if (KeyboardRepeat(DIK_D) == true)
	{
		g_camera.posR.x += sinf(D3DX_PI * 0.5f + g_camera.rot.y) * -2.0f;
		g_camera.posR.z += cosf(D3DX_PI * 0.5f + g_camera.rot.y) * -2.0f;

	}

	//�����_�̐���
	if (KeyboardRepeat(DIK_X) == true)
	{
		g_camera.rot.y += 0.01f;
		g_camera.posR.x += sinf(D3DX_PI * 0.5f + g_camera.rot.y) * 2.0f;
		g_camera.posR.z += cosf(D3DX_PI * 0.5f + g_camera.rot.y) * 2.0f;

		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI * 2;
		}
	}
	else if (KeyboardRepeat(DIK_Z) == true)
	{
		g_camera.rot.y -= 0.01f;
		g_camera.posR.x += sinf(D3DX_PI * 0.5f + g_camera.rot.y) * -2.0f;
		g_camera.posR.z += cosf(D3DX_PI * 0.5f + g_camera.rot.y) * -2.0f;

		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2;
		}
	}

	//���_�̐���
	if (KeyboardRepeat(DIK_V) == true)
	{
		g_camera.rot.y += 0.01f;
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI * 2;
		}
	}
	else if (KeyboardRepeat(DIK_C) == true)
	{
		g_camera.rot.y -= 0.01f;
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2;
		}
	}

	//���_�̐���
	if (KeyboardRepeat(DIK_J) == true)
	{
		g_camera.rot.x += 0.01f;
		if (g_camera.rot.x > D3DX_PI)
		{
			g_camera.rot.x -= D3DX_PI * 2;
		}
	}
	else if (KeyboardRepeat(DIK_K) == true)
	{
		g_camera.rot.x -= 0.01f;
		if (g_camera.rot.x < D3DX_PI)
		{
			g_camera.rot.x += D3DX_PI * 2;
		}
	}

	//�p�x�̐��K��
	g_camera.posV.x = g_camera.posR.x + cosf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
	g_camera.posV.y = g_camera.posR.y + sinf(g_camera.rot.x) * g_camera.fDistance;
	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;
}

//==================================================================
//�Z�b�g����
//==================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		2000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);


	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

Camera* GetCamera(void)
{
	return &g_camera;
}