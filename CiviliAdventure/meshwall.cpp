//==================================================================
//
//���b�V���E�H�[������<meshwall.cpp>
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "meshwall.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshWall;//�ʒu
D3DXVECTOR3 g_rotMeshWall;//����
D3DXMATRIX g_mtxWorldMeshWall;//���[���h�}�g���b�N�X

//==================================================================
//����������
//==================================================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg000.jpg",
		&g_pTextureMeshWall);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHWALL_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall, NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHWALL_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	g_posMeshWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);
	float fTexX = 1.0f / MESHWALL_X_BLOCK;
	float fTexY = 1.0f / MESHWALL_Y_BLOCK;

	int nCntVtx = 0;
	int nXPos = 0;
	int nZPos = 0;

	for (int nCnt = 0; nCnt <= MESHWALL_Y_BLOCK; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 <= MESHWALL_X_BLOCK; nCnt2++)
		{
			pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f + ((NUM_WIDTH / MESHWALL_X_BLOCK) * nCnt2) - (NUM_WIDTH * 0.5f), NUM_HEIGHT - ((NUM_HEIGHT / MESHWALL_Y_BLOCK) * nCnt) - (NUM_HEIGHT * 0.5f), 0.0f);
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntVtx].tex = D3DXVECTOR2(fTexX * nCnt2, nCnt * fTexY);

			nCntVtx++;
		}
	}

	//pVtx[150].pos.y = 100.0f;
	//pVtx[300].pos.y = 50.0f;

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshWall->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	int nX = MESHWALL_X_BLOCK + 1;
	int nZ = MESHWALL_Y_BLOCK;
	int nK = 0;
	nCntVtx = 0;

	for (int nCnt = 0; nCnt < MESHWALL_Y_BLOCK; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 <= MESHWALL_X_BLOCK; nCnt2++, nX++, nK++)
		{
			pIdx[nCntVtx] = nX;
			pIdx[nCntVtx + 1] = nK;
			nCntVtx += 2;
		}

		if (nCnt < MESHWALL_Y_BLOCK - 1)
		{
			pIdx[nCntVtx] = nK - 1;
			pIdx[nCntVtx + 1] = nX;
			nCntVtx += 2;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshWall->Unlock();

}

//==================================================================
//�I������
//==================================================================
void UninitMeshWall(void)
{
	//�e�N�X�`���̉��
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//==================================================================
//�X�V����
//==================================================================
void UpdateMeshWall(void)
{
}

//==================================================================
//�`�揈��
//==================================================================
void DrawMeshWall(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshWall);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshWall.y, g_rotMeshWall.x, g_rotMeshWall.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshWall, &g_mtxWorldMeshWall, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshWall.x, g_posMeshWall.y, g_posMeshWall.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshWall, &g_mtxWorldMeshWall, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshWall);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshWall);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshWall);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHWALL_VERTEX_NUM, 0, MESHWALL_PRIMITIVE_NUM);

	////�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
