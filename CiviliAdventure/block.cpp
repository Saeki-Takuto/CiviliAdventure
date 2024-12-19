#include "block.h"
#include "fade.h"
#include "game.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureBlock[128] = {};
LPD3DXMESH g_pMeshBlock = NULL;//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatBlock = NULL;//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatBlock = 0;//�}�e���A���̐�
D3DXVECTOR3 g_posBlock;//�ʒu
D3DXVECTOR3 g_rotBlock;//����
D3DXMATRIX g_mtxWorldBlock;//���[���h�}�g���b�N�X
D3DXVECTOR3 g_vtxMinBlock, g_vtxMaxBlock;//���f���̍ŏ��l�A�ő�l

void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e��ϐ��̏�����

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/box000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatBlock,
		NULL,
		&g_dwNumMatBlock,
		&g_pMeshBlock);

	g_posBlock = D3DXVECTOR3(0.0f, 0.0f, 500.0f);

	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	//���_���̎擾
	nNumVtx = g_pMeshBlock->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshBlock->GetFVF());
	//���_�o�b�t�@�̃��b�N
	g_pMeshBlock->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//x�̍ő�l��r
		if (vtx.x > g_vtxMaxBlock.x)
		{
			g_vtxMaxBlock.x = vtx.x;
		}

		//y�̍ő�l��r
		if (vtx.y > g_vtxMaxBlock.y)
		{
			g_vtxMaxBlock.y = vtx.y;
		}

		//z�̍ő�l��r
		if (vtx.z > g_vtxMaxBlock.z)
		{
			g_vtxMaxBlock.z = vtx.z;
		}

		//x�̍ŏ��l��r
		if (vtx.x < g_vtxMinBlock.x)
		{
			g_vtxMinBlock.x = vtx.x;
		}

		//y�̍ŏ��l��r
		if (vtx.y < g_vtxMinBlock.y)
		{
			g_vtxMinBlock.y = vtx.y;
		}

		//z�̍ŏ��l��r
		if (vtx.z < g_vtxMinBlock.z)
		{
			g_vtxMinBlock.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pMeshBlock->UnlockVertexBuffer();

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatBlock->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBlock; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureBlock[nCntMat]);
		}
	}

}

void UninitBlock(void)
{
	//�e�N�X�`���̉��
	if (g_pMeshBlock != NULL)
	{
		g_pMeshBlock->Release();
		g_pMeshBlock = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pBuffMatBlock != NULL)
	{
		g_pBuffMatBlock->Release();
		g_pBuffMatBlock = NULL;
	}

	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureBlock[nCnt] != NULL)
		{
			g_apTextureBlock[nCnt]->Release();
			g_apTextureBlock[nCnt] = NULL;
		}
	}
}

void UpdateBlock(void)
{
	
}

void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldBlock);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotBlock.y, g_rotBlock.x, g_rotBlock.z);
	D3DXMatrixMultiply(&g_mtxWorldBlock, &g_mtxWorldBlock, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posBlock.x, g_posBlock.y, g_posBlock.z);
	D3DXMatrixMultiply(&g_mtxWorldBlock, &g_mtxWorldBlock, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBlock);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatBlock->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBlock; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBlock[nCntMat]);

		//���f��(�p�[�c)�̕`��
		g_pMeshBlock->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

void CollisionBlock(void)
{
	Player* pPlayer = GetPlayer();

	//���E�̓����蔻��
	if (pPlayer->pos.z - pPlayer->size.z * 0.5f < g_posBlock.z + g_vtxMaxBlock.z && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_posBlock.z + g_vtxMinBlock.z)
	{
		if (pPlayer->posOld.x + pPlayer->size.x * 0.5f <= g_posBlock.x + g_vtxMinBlock.x && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_posBlock.x + g_vtxMinBlock.x)
		{
			pPlayer->pos.x = g_posBlock.x + g_vtxMinBlock.x - pPlayer->size.x * 0.5f;
			pPlayer->move.x = 0.0f;
			SetGameState(GAMESTATE_END);
			SetFade(MODE_RESULT);
		}
		else if (pPlayer->posOld.x - pPlayer->size.x * 0.5f >= g_posBlock.x + g_vtxMaxBlock.x && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_posBlock.x + g_vtxMaxBlock.x)
		{
			pPlayer->pos.x = g_posBlock.x + g_vtxMaxBlock.x + pPlayer->size.x * 0.5f;
			pPlayer->move.x = 0.0f;
			SetGameState(GAMESTATE_END);
			SetFade(MODE_RESULT);
		}
	}

	//�㉺�̓����蔻��
	if (pPlayer->pos.x - pPlayer->size.x * 0.5f < g_posBlock.x + g_vtxMaxBlock.x && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_posBlock.x + g_vtxMinBlock.x)
	{
		if (pPlayer->posOld.z + pPlayer->size.z*0.5f <= g_posBlock.z + g_vtxMinBlock.z && pPlayer->pos.z + pPlayer->size.z*0.5f > g_posBlock.z + g_vtxMinBlock.z)
		{
			pPlayer->pos.z = g_posBlock.z + g_vtxMinBlock.z - pPlayer->size.z*0.5f;
			pPlayer->move.z = 0.0f;
			SetGameState(GAMESTATE_END);
			SetFade(MODE_RESULT);
		}
		else if (pPlayer->posOld.z - pPlayer->size.z*0.5f >= g_posBlock.z + g_vtxMaxBlock.z && pPlayer->pos.z - pPlayer->size.z*0.5f < g_posBlock.z + g_vtxMaxBlock.z)
		{
			pPlayer->pos.z = g_posBlock.z + g_vtxMaxBlock.z + pPlayer->size.z*0.5f;
			pPlayer->move.z = 0.0f;
			SetGameState(GAMESTATE_END);
			SetFade(MODE_RESULT);
		}
	}
}