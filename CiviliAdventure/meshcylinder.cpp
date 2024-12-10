//==================================================================
//
//���b�V���t�B�[���h����<meshcylinder.cpp>
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "meshcylinder.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshCylinder;//�ʒu
D3DXVECTOR3 g_rotMeshCylinder;//����
D3DXMATRIX g_mtxWorldMeshCylinder;//���[���h�}�g���b�N�X

//==================================================================
//����������
//==================================================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg000.jpg",
		&g_pTextureMeshCylinder);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHCYLINDER_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder, NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHCYLINDER_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);

	g_posMeshCylinder = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);
	float fTexX = 1.0f / MESHCYLINDER_X_BLOCK;
	float fTexY = 1.0f / MESHCYLINDER_Z_BLOCK;


	int nCntVtx = 0;
	int nXPos = 0;
	int nZPos = 0;

	for (int nCnt = 0; nCnt <= MESHCYLINDER_Z_BLOCK; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 <= MESHCYLINDER_X_BLOCK; nCnt2++)
		{
			pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f + ((NUM_WIDTH / MESHCYLINDER_X_BLOCK) * nCnt2) - (NUM_WIDTH * 0.5f), 0.0f, NUM_HEIGHT - ((NUM_HEIGHT / MESHCYLINDER_Z_BLOCK) * nCnt) - (NUM_HEIGHT * 0.5f));
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntVtx].tex = D3DXVECTOR2(fTexX * nCnt2, nCnt * fTexY);

			nCntVtx++;
		}
	}


	////���_���W��ݒ�
	//pVtx[0].pos = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
	//pVtx[2].pos = D3DXVECTOR3(150.0f, 0.0f, 150.0f);
	//pVtx[3].pos = D3DXVECTOR3(-150.0f, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(150.0f, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	//pVtx[8].pos = D3DXVECTOR3(150.0f, 0.0f, -150.0f);

	////�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	//pVtx[0].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[1].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[2].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[3].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[4].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[5].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[6].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[7].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[8].nor = D3DXVECTOR3(0.0, 1.0, 0.0);


	////���_�J���[�̐ݒ�
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	////�e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	//pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	//pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshCylinder->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	int nX = MESHCYLINDER_X_BLOCK + 1;
	int nZ = MESHCYLINDER_Z_BLOCK;
	int nK = 0;
	nCntVtx = 0;

	for (int nCnt = 0; nCnt < MESHCYLINDER_Z_BLOCK; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 <= MESHCYLINDER_X_BLOCK; nCnt2++, nX++, nK++)
		{
			pIdx[nCntVtx] = nX;
			pIdx[nCntVtx + 1] = nK;
			nCntVtx += 2;
		}

		pIdx[nCntVtx] = nK - 1;
		pIdx[nCntVtx + 1] = nK;
		nCntVtx += 2;
	}



	////�C���f�b�N�X�̐ݒ�
	//pIdx[0]  = 3;
	//pIdx[1]  = 0;

	//pIdx[2]  = 4;
	//pIdx[3]  = 1;

	//pIdx[4]  = 5;
	//pIdx[5]  = 2;

	//pIdx[6]  = 2;
	//pIdx[7]  = 6;

	//pIdx[8]  = 6;
	//pIdx[9]  = 3;

	//pIdx[10] = 7;
	//pIdx[11] = 4;

	//pIdx[12] = 8;
	//pIdx[13] = 5;

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshCylinder->Unlock();

}

//==================================================================
//�I������
//==================================================================
void UninitMeshCylinder(void)
{
	//�e�N�X�`���̉��
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//==================================================================
//�X�V����
//==================================================================
void UpdateMeshCylinder(void)
{
}

//==================================================================
//�`�揈��
//==================================================================
void DrawMeshCylinder(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshCylinder);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCylinder.y, g_rotMeshCylinder.x, g_rotMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCylinder.x, g_posMeshCylinder.y, g_posMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshCylinder);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHCYLINDER_VERTEX_NUM, 0, MESHCYLINDER_PRIMITIVE_NUM);

	////�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
