#include "player.h"
#include "input.h"
#include "shadow.h"
#include "block.h"
#include "wall.h"
#include "rod.h"
//�O���[�o���ϐ�
Player g_player;
int g_nCntMotion;
int g_nMotion;
bool g_bFinishMotion;

static KEY_INFO g_aKeyNeutral[] =
{
	//�j���[�g����
	{40,

	{{0.0f,0.0f,0.0f,0.09f,0.0f,0.0f,}, //0

	{0.0f,0.0f,0.0f,-0.03f,0.0f,0.0f,}, //1

	{0.0f,0.0f,0.0f,0.0f,0.03f,0.72f,}, //2

	{0.0f,0.0f,0.0f,0.0f,-0.03f,0.13f,}, //3

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.19f,}, //4

	{0.0f,0.0f,0.0f,0.0f,0.0f,-0.72f,}, //5

	{0.0f,0.0f,0.0f,0.0f,0.0f,-0.13f,}, //6

	{0.0f,0.0f,0.0f,0.0f,0.0f,-0.25f,}, //7

	{0.0f,0.0f,0.0f,-0.09f,0.0f,-0.19f,}, //8

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}, //9

	{0.0f,0.0f,0.0f,-0.13f,0.0f,0.22f,}, //10

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}}, //11

	},

	{40,

	{{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}, //0

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}, //1

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}, //2

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}, //3

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}, //4

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}, //5

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}, //6

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}, //7

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}, //8

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}, //9

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}, //10

	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,}}, //11

	},
};

void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.bJump = false;

	g_player.nNumKey = 2;
	g_player.bLoopMotion = true;


	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	for (int nCntModel = 0; nCntModel < PLAYER_MAX_PARTS; nCntModel++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(PLAYER_PARTS[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[nCntModel].pBuffMat,
			NULL,
			&g_player.aModel[nCntModel].dwNumMat,
			&g_player.aModel[nCntModel].pMesh);
	}

	g_player.nNumModel = 12;

	//�e�p�[�c�̊K�w�\���ݒ�
	g_player.aModel[0].nIdxModelParent = -1;
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[1].nIdxModelParent = 0;
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[2].nIdxModelParent = 0;
	g_player.aModel[2].pos = D3DXVECTOR3(-7.0f, 12.0f, 0.0f);
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[3].nIdxModelParent = 2;
	g_player.aModel[3].pos = D3DXVECTOR3(-4.0f, 1.0f, 0.0f);
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[4].nIdxModelParent = 3;
	g_player.aModel[4].pos = D3DXVECTOR3(-5.3f, 0.0f, 0.0f);
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[5].nIdxModelParent = 0;
	g_player.aModel[5].pos = D3DXVECTOR3(7.0f, 12.0f, 0.0f);
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[6].nIdxModelParent = 5;
	g_player.aModel[6].pos = D3DXVECTOR3(4.0f, 1.0f, 0.0f);
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[7].nIdxModelParent = 6;
	g_player.aModel[7].pos = D3DXVECTOR3(5.3f, 0.0f, 0.0f);
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[8].nIdxModelParent = 0;
	g_player.aModel[8].pos = D3DXVECTOR3(-3.0f, -1.0f, 0.0f);
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[9].nIdxModelParent = 8;
	g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[10].nIdxModelParent = 0;
	g_player.aModel[10].pos = D3DXVECTOR3(3.0f, -1.0f, 0.0f);
	g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[11].nIdxModelParent = 10;
	g_player.aModel[11].pos = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
	g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_player.aModel[nCntModel].pTexture[nCntMat]);
			}
		}

		//���_���̎擾
		nNumVtx = g_player.aModel[nCntModel].pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[nCntModel].pMesh->GetFVF());
		//���_�o�b�t�@�̃��b�N
		g_player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//x�̍ő�l��r
			if (vtx.x > g_player.vtxMaxBlock.x)
			{
				g_player.vtxMaxBlock.x = vtx.x;
			}

			//y�̍ő�l��r
			if (vtx.y > g_player.vtxMaxBlock.y)
			{
				g_player.vtxMaxBlock.y = vtx.y;
			}

			//x�̍ő�l��r
			if (vtx.z > g_player.vtxMaxBlock.z)
			{
				g_player.vtxMaxBlock.z = vtx.z;
			}

			//x�̍ŏ��l��r
			if (vtx.x < g_player.vtxMinBlock.x)
			{
				g_player.vtxMinBlock.x = vtx.x;
			}

			//y�̍ŏ��l��r
			if (vtx.y < g_player.vtxMinBlock.y)
			{
				g_player.vtxMinBlock.y = vtx.y;
			}

			//x�̍ŏ��l��r
			if (vtx.z < g_player.vtxMinBlock.z)
			{
				g_player.vtxMinBlock.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_player.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}

	g_player.size = g_player.vtxMaxBlock - g_player.vtxMinBlock;

	g_player.g_nIdxShadow = SetShadow(g_player.pos,g_player.rot);
}

void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{

		//�e�N�X�`���̉��
		if (g_player.aModel[nCntModel].pMesh != NULL)
		{
			g_player.aModel[nCntModel].pMesh->Release();
			g_player.aModel[nCntModel].pMesh = NULL;
		}

		//���_�o�b�t�@�̉��
		if (g_player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_player.aModel[nCntModel].pBuffMat->Release();
			g_player.aModel[nCntModel].pBuffMat = NULL;
		}

		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			//�e�N�X�`���̔j��
			if (g_player.aModel[nCntModel].pTexture[nCnt] != NULL)
			{
				g_player.aModel[nCntModel].pTexture[nCnt]->Release();
				g_player.aModel[nCntModel].pTexture[nCnt] = NULL;
			}
		}
	}
}

void UpdatePlayer(void)
{

	//�S���f��(�p�[�c)�̍X�V
	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		if (g_player.nKey >= g_player.nNumKey)
		{
			g_player.nKey = 0;
		}

		D3DXVECTOR3 fPosB, fRotB;

		int nDis = (g_player.nKey + 1) % g_player.nNumKey;


		fPosB.x = g_aKeyNeutral[nDis].aKey[nCntModel].fPosX - g_aKeyNeutral[g_player.nKey].aKey[nCntModel].fPosX;
		fPosB.y = g_aKeyNeutral[nDis].aKey[nCntModel].fPosY - g_aKeyNeutral[g_player.nKey].aKey[nCntModel].fPosY;
		fPosB.z = g_aKeyNeutral[nDis].aKey[nCntModel].fPosZ - g_aKeyNeutral[g_player.nKey].aKey[nCntModel].fPosZ;

		fRotB.x = g_aKeyNeutral[nDis].aKey[nCntModel].fRotX - g_aKeyNeutral[g_player.nKey].aKey[nCntModel].fRotX;
		fRotB.y = g_aKeyNeutral[nDis].aKey[nCntModel].fRotY - g_aKeyNeutral[g_player.nKey].aKey[nCntModel].fRotY;
		fRotB.z = g_aKeyNeutral[nDis].aKey[nCntModel].fRotZ - g_aKeyNeutral[g_player.nKey].aKey[nCntModel].fRotZ;

		D3DXVECTOR3 fPosA, fRotA;

		float fDis = (float)g_player.nCounterMotion / g_aKeyNeutral[g_player.nKey].nFrame;

		fPosA.x = g_aKeyNeutral[g_player.nKey].aKey[nCntModel].fPosX + fPosB.x * fDis;
		fPosA.y = g_aKeyNeutral[g_player.nKey].aKey[nCntModel].fPosY + fPosB.y * fDis;
		fPosA.z = g_aKeyNeutral[g_player.nKey].aKey[nCntModel].fPosZ + fPosB.z * fDis;

		fRotA.x = g_aKeyNeutral[g_player.nKey].aKey[nCntModel].fRotX + fRotB.x * fDis;
		fRotA.y = g_aKeyNeutral[g_player.nKey].aKey[nCntModel].fRotY + fRotB.y * fDis;
		fRotA.z = g_aKeyNeutral[g_player.nKey].aKey[nCntModel].fRotZ + fRotB.z * fDis;

		g_player.aModel[nCntModel].pos += fPosA;
		g_player.aModel[nCntModel].rot = fRotA;
	}
	g_player.nCounterMotion++;
	if (g_player.nCounterMotion >= g_aKeyNeutral[g_player.nKey].nFrame)
	{
		g_player.nCounterMotion = 0.0f;
		g_player.nKey++;
	}

	if (KeyboardRepeat(DIK_0) == true)
	{
		g_player.aModel[1].rot.x += 0.01f;
	}

	Camera* pCamera = GetCamera();

	if (KeyboardRepeat(DIK_DOWN) == true)
	{
		g_player.move.x += sinf(pCamera->rot.y);
		g_player.move.z += cosf(pCamera->rot.y);
		//g_player.rot.y = pCamera->rot.y;
		g_player.rotDest.y = pCamera->rot.y-D3DX_PI;
	}
	else if (KeyboardRepeat(DIK_UP) == true)
	{
		g_player.move.x -= sinf(pCamera->rot.y);
		g_player.move.z -= cosf(pCamera->rot.y);
		//g_player.rot.y = pCamera->rot.y;
		g_player.rotDest.y = pCamera->rot.y;

	}
	else if (KeyboardRepeat(DIK_RIGHT) == true)
	{
		g_player.move.z += sinf(pCamera->rot.y);
		g_player.move.x -= cosf(pCamera->rot.y);
		//g_player.rot.y = pCamera->rot.y;
		g_player.rotDest.y = pCamera->rot.y+D3DX_PI*0.5f;

	}
	else if (KeyboardRepeat(DIK_LEFT) == true)
	{
		g_player.move.z -= sinf(pCamera->rot.y);
		g_player.move.x += cosf(pCamera->rot.y);
		//g_player.rot.y = pCamera->rot.y;
		g_player.rotDest.y = pCamera->rot.y - D3DX_PI*0.5f;

	}
	
	if (KeyboardTrigger(DIK_SPACE) == true || JoypadTrigger(JOYKEY_A))
	{//SPACE�������ꂽ(�W�����v)
		if (g_player.bJump == false)
		{
			g_player.move.y += 4.0f;
			g_player.bJump = true;
		}
	}



	if (g_player.rotDest.y - g_player.rot.y >= D3DX_PI)
	{
		g_player.rot.y += D3DX_PI*2;
	}
	else if (g_player.rotDest.y - g_player.rot.y <= -D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2;
	}


	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;

	g_player.move.y -= 0.1f;


	//�O��̈ʒu��ۑ�
	g_player.posOld = g_player.pos;

	g_player.pos += g_player.move;

	CollisionBlock();
	CollisionWall();
	CollisionRod();

	if (g_player.pos.y < 0.0f)
	{
		g_player.pos.y = 0.0f;
		g_player.move.y = 0.0f;
		g_player.bJump = false;
	}


	//�ړ��ʂ��X�V(����������)
	g_player.move.x += (0.0f - g_player.move.x) * 0.17f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.17f;


	SetPositionShadow(g_player.g_nIdxShadow,g_player.pos);
}

void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�S���f��(�p�[�c�̕`��)
	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X

		//�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		//�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//�p�[�c�̈ʒu(�I�t�Z�b�g)�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//�p�[�c�́u�e�̃}�g���b�N�X�v��ݒ�
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{//�e���f��������ꍇ
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{//�e���f�����Ȃ��ꍇ
			mtxParent = g_player.mtxWorld;
		}

		//�Z�o�����u�p�[�c�̃��[���h�}�g���b�N�X�v�Ɓu�e�̃}�g���b�N�X�v���|�����킹��
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
						   &g_player.aModel[nCntModel].mtxWorld,
						   &mtxParent);

		//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD,
			&g_player.aModel[nCntModel].mtxWorld);
		
		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_player.aModel[nCntModel].pTexture[nCntMat]);

			//���f��(�p�[�c)�̕`��
			g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

Player* GetPlayer()
{
	return &g_player;
}
