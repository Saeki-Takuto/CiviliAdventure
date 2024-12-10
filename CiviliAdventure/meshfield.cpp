//==================================================================
//
//���b�V���t�B�[���h����<meshfield.cpp>
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "meshfield.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshField;//�ʒu
D3DXVECTOR3 g_rotMeshField;//����
D3DXMATRIX g_mtxWorldMeshField;//���[���h�}�g���b�N�X

//==================================================================
//����������
//==================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg000.jpg",
		&g_pTextureMeshField);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)* MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField, NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	g_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);
	float fTexX = 1.0f / MESHFIELD_X_BLOCK;
	float fTexY = 1.0f / MESHFIELD_Z_BLOCK;


	int nCntVtx = 0;
	int nXPos = 0;
	int nZPos = 0;

	for (int nCnt = 0; nCnt <= MESHFIELD_Z_BLOCK; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 <= MESHFIELD_X_BLOCK; nCnt2++)
		{
			pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f+((NUM_WIDTH/ MESHFIELD_X_BLOCK)*nCnt2)-(NUM_WIDTH*0.5f),0.0f, NUM_HEIGHT-((NUM_HEIGHT/ MESHFIELD_Z_BLOCK)*nCnt)-(NUM_HEIGHT*0.5f));
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntVtx].tex = D3DXVECTOR2(fTexX*nCnt2,nCnt * fTexY);

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
	g_pVtxBuffMeshField->Unlock();
																																																																							
	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	int nX = MESHFIELD_X_BLOCK+1;
	int nZ = MESHFIELD_Z_BLOCK;
	int nK = 0;
	nCntVtx = 0;

	for (int nCnt = 0; nCnt < MESHFIELD_Z_BLOCK; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 <= MESHFIELD_X_BLOCK; nCnt2++,nX++,nK++)
		{
			pIdx[nCntVtx] = nX;
			pIdx[nCntVtx + 1] = nK;
			nCntVtx+=2;
		}
		
		if (nCnt < MESHFIELD_Z_BLOCK - 1)
		{
			pIdx[nCntVtx] = nK - 1;
			pIdx[nCntVtx + 1] = nX;
			nCntVtx += 2;
		}
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
	g_pIdxBuffMeshField->Unlock();

}

//==================================================================
//�I������
//==================================================================
void UninitMeshField(void)
{
	//�e�N�X�`���̉��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//==================================================================
//�X�V����
//==================================================================
void UpdateMeshField(void)
{
}

//==================================================================
//�`�揈��
//==================================================================
void DrawMeshField(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIELD_VERTEX_NUM, 0, MESHFIELD_PRIMITIVE_NUM);

	////�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
