#include "rock.h"
#include "input.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureRock[128][ROCKTYPE_MAX] = {};
LPD3DXMESH g_pMeshRock[ROCKTYPE_MAX] = {};//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatRock[ROCKTYPE_MAX] = {};//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatRock[ROCKTYPE_MAX] = {};//�}�e���A���̐�
Rock g_rock[MAX_ROCK];
RockSize g_rocksize[ROCKTYPE_MAX];


void InitRock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e��ϐ��̏�����

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/rock.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatRock[0],
		NULL,
		&g_dwNumMatRock[0],
		&g_pMeshRock[0]);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/rodb.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatRock[1],
		NULL,
		&g_dwNumMatRock[1],
		&g_pMeshRock[1]);


	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	for (int nCnt = 0; nCnt < ROCKTYPE_MAX; nCnt++)
	{
		//���_���̎擾
		nNumVtx = g_pMeshRock[nCnt]->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshRock[nCnt]->GetFVF());
		//���_�o�b�t�@�̃��b�N
		g_pMeshRock[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//x�̍ŏ��l��r
			if (vtx.x < g_rocksize[nCnt].vtxMin.x)
			{
				g_rocksize[nCnt].vtxMin.x = vtx.x;
			}

			//x�̍ő�l��r
			if (vtx.x > g_rocksize[nCnt].vtxMax.x)
			{
				g_rocksize[nCnt].vtxMax.x = vtx.x;
			}


			//y�̍ŏ��l��r
			if (vtx.y < g_rocksize[nCnt].vtxMin.y)
			{
				g_rocksize[nCnt].vtxMin.y = vtx.y;
			}

			//y�̍ő�l��r
			if (vtx.y > g_rocksize[nCnt].vtxMax.y)
			{
				g_rocksize[nCnt].vtxMax.y = vtx.y;
			}

			//z�̍ŏ��l��r
			if (vtx.z < g_rocksize[nCnt].vtxMin.z)
			{
				g_rocksize[nCnt].vtxMin.z = vtx.z;
			}

			//z�̍ő�l��r
			if (vtx.z > g_rocksize[nCnt].vtxMax.z)
			{
				g_rocksize[nCnt].vtxMax.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_pMeshRock[nCnt]->UnlockVertexBuffer();

		g_rocksize[nCnt].size = g_rocksize[nCnt].vtxMax - g_rocksize[nCnt].vtxMin;

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatRock[nCnt]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatRock[nCnt]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureRock[nCntMat][nCnt]);
			}
		}
	}
}

void UninitRock(void)
{
	for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
	{
		if (g_rock[nCnt].bUse == true)
		{
			g_rock[nCnt].bUse = false;
		}
	}

	for (int nCnt = 0; nCnt < ROCKTYPE_MAX; nCnt++)
	{
		//�e�N�X�`���̉��
		if (g_pMeshRock[nCnt] != NULL)
		{
			g_pMeshRock[nCnt]->Release();
			g_pMeshRock[nCnt] = NULL;
		}

		//���_�o�b�t�@�̉��
		if (g_pBuffMatRock[nCnt] != NULL)
		{
			g_pBuffMatRock[nCnt]->Release();
			g_pBuffMatRock[nCnt] = NULL;
		}

		for (int nCntTex = 0; nCntTex < 1; nCntTex++)
		{
			//�e�N�X�`���̔j��
			if (g_apTextureRock[nCntTex][nCnt] != NULL)
			{
				g_apTextureRock[nCntTex][nCnt]->Release();
				g_apTextureRock[nCntTex][nCnt] = NULL;
			}
		}
	}
}

void UpdateRock(void)
{
	for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
	{
		if (g_rock[nCnt].bUse == true)
		{
			g_rock[nCnt].posold = g_rock[nCnt].pos;

			g_rock[nCnt].pos += g_rock[nCnt].movepos;


			if (g_rock[nCnt].pos.x > 150.0f || g_rock[nCnt].pos.x < -150.0f)
			{
				g_rock[nCnt].movepos.x *= -1.0f;
			}

			if (g_rock[nCnt].pos.y > 150.0f || g_rock[nCnt].pos.y < 0.0f)
			{
				g_rock[nCnt].movepos.y *= -1.0f;
			}

			g_rock[nCnt].nLife--;

			if (g_rock[nCnt].nLife <= 0)
			{
				g_rock[nCnt].bUse = false;
			}


			//if (g_rock[nCnt].pos.z > 150.0f || g_rock[nCnt].pos.z < -150.0f)
			//{
			//	g_rock[nCnt].movepos.z *= -1.0f;
			//}
		}

	}
}

void DrawRock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
	{
		if (g_rock[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_rock[nCnt].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rock[nCnt].rot.y, g_rock[nCnt].rot.x, g_rock[nCnt].rot.z);
			D3DXMatrixMultiply(&g_rock[nCnt].mtxWorld, &g_rock[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_rock[nCnt].pos.x, g_rock[nCnt].pos.y, g_rock[nCnt].pos.z);
			D3DXMatrixMultiply(&g_rock[nCnt].mtxWorld, &g_rock[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_rock[nCnt].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatRock[g_rock[nCnt].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatRock[g_rock[nCnt].nType]; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureRock[nCntMat][g_rock[nCnt].nType]);

				//���f��(�p�[�c)�̕`��
				g_pMeshRock[g_rock[nCnt].nType]->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

void CollisionRock(void)
{
	// �v���C���[�̎擾
	Player* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
	{
		if (g_rock[nCnt].bUse == true)
		{
			if (pPlayer->posOld.y + pPlayer->size.y <= g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y >= g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f)
			{
				if (pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->pos.y = g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f - pPlayer->size.y;
					pPlayer->move.y = 0.0f;
				}
			}

			if (pPlayer->posOld.y >= g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y && pPlayer->pos.y <= g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y)
			{
				if (pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->bJump = false;
					pPlayer->pos.y = (g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y);
					pPlayer->move.y = 0.0f;
				}
			}

			if (pPlayer->posOld.z + pPlayer->size.z * 0.5f <= g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f >= g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y < g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y > g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->pos.z = (g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f) - pPlayer->size.z * 0.5f;
					pPlayer->move.z = 0.0f;
				}
			}

			if (pPlayer->posOld.z - pPlayer->size.z * 0.5f >= g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.z - pPlayer->size.z * 0.5f <= g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y < g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y > g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->pos.z = (g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f) + pPlayer->size.z * 0.5f;
					pPlayer->move.z = 0.0f;
				}
			}

			if (pPlayer->posOld.x + pPlayer->size.x * 0.5f <= g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f >= g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y < g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y > g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f)
				{
					pPlayer->pos.x = (g_rock[nCnt].pos.x - g_rocksize[g_rock[nCnt].nType].size.x * 0.5f) - pPlayer->size.x * 0.5f;
					pPlayer->move.x = 0.0f;
				}
			}

			if (pPlayer->posOld.x - pPlayer->size.x * 0.5f >= g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f <= g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y < g_rock[nCnt].pos.y + g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y > g_rock[nCnt].pos.y - g_rocksize[g_rock[nCnt].nType].size.y * 0.5f && pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rock[nCnt].pos.z + g_rocksize[g_rock[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rock[nCnt].pos.z - g_rocksize[g_rock[nCnt].nType].size.z * 0.5f)
				{
					pPlayer->pos.x = (g_rock[nCnt].pos.x + g_rocksize[g_rock[nCnt].nType].size.x * 0.5f) + pPlayer->size.x * 0.5f;
					pPlayer->move.x = 0.0f;
				}
			}

			CollisionPlayer(1);
		}
	}
}

void SetRock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 movepos, D3DXVECTOR3 moverot, int nType)
{
	for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
	{
		if (g_rock[nCnt].bUse == false)
		{
			g_rock[nCnt].pos = pos;
			g_rock[nCnt].rot = rot;
			g_rock[nCnt].movepos = movepos;
			g_rock[nCnt].moverot = moverot;
			g_rock[nCnt].nType = nType;
			g_rock[nCnt].nLife = 60 * 5;
			g_rock[nCnt].bUse = true;
			break;
		}
	}
}

Rock* GetRock(void)
{
	return &g_rock[0];
}

RockSize* GetRockSize(void)
{
	return &g_rocksize[0];
}
