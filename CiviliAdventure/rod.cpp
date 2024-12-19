#include "rod.h"
#include "input.h"
#include "rock.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureRod[128][RODTYPE_MAX] = {};
LPD3DXMESH g_pMeshRod[RODTYPE_MAX] = {};//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatRod[RODTYPE_MAX] = {};//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatRod[RODTYPE_MAX] = {};//�}�e���A���̐�
Rod g_rod[MAX_ROD];
RodSize g_rodsize[RODTYPE_MAX];


void InitRod(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e��ϐ��̏�����

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/rodv.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatRod[0],
		NULL,
		&g_dwNumMatRod[0],
		&g_pMeshRod[0]);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/rodb.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatRod[1],
		NULL,
		&g_dwNumMatRod[1],
		&g_pMeshRod[1]);


	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	for (int nCnt = 0; nCnt < RODTYPE_MAX; nCnt++)
	{
		//���_���̎擾
		nNumVtx = g_pMeshRod[nCnt]->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshRod[nCnt]->GetFVF());
		//���_�o�b�t�@�̃��b�N
		g_pMeshRod[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//x�̍ŏ��l��r
			if (vtx.x < g_rodsize[nCnt].vtxMin.x)
			{
				g_rodsize[nCnt].vtxMin.x = vtx.x;
			}

			//x�̍ő�l��r
			if (vtx.x > g_rodsize[nCnt].vtxMax.x)
			{
				g_rodsize[nCnt].vtxMax.x = vtx.x;
			}


			//y�̍ŏ��l��r
			if (vtx.y < g_rodsize[nCnt].vtxMin.y)
			{
				g_rodsize[nCnt].vtxMin.y = vtx.y;
			}

			//y�̍ő�l��r
			if (vtx.y > g_rodsize[nCnt].vtxMax.y)
			{
				g_rodsize[nCnt].vtxMax.y = vtx.y;
			}

			//z�̍ŏ��l��r
			if (vtx.z < g_rodsize[nCnt].vtxMin.z)
			{
				g_rodsize[nCnt].vtxMin.z = vtx.z;
			}

			//z�̍ő�l��r
			if (vtx.z > g_rodsize[nCnt].vtxMax.z)
			{
				g_rodsize[nCnt].vtxMax.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_pMeshRod[nCnt]->UnlockVertexBuffer();

		g_rodsize[nCnt].size = g_rodsize[nCnt].vtxMax - g_rodsize[nCnt].vtxMin;

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatRod[nCnt]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatRod[nCnt]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureRod[nCntMat][nCnt]);
			}
		}
	}
}

void UninitRod(void)
{
	for (int nCnt = 0; nCnt < MAX_ROD; nCnt++)
	{
		if (g_rod[nCnt].bUse == true)
		{
			g_rod[nCnt].bUse = false;
		}
	}

	for (int nCnt = 0; nCnt < RODTYPE_MAX; nCnt++)
	{
		//�e�N�X�`���̉��
		if (g_pMeshRod[nCnt] != NULL)
		{
			g_pMeshRod[nCnt]->Release();
			g_pMeshRod[nCnt] = NULL;
		}

		//���_�o�b�t�@�̉��
		if (g_pBuffMatRod[nCnt] != NULL)
		{
			g_pBuffMatRod[nCnt]->Release();
			g_pBuffMatRod[nCnt] = NULL;
		}

		for (int nCntTex = 0; nCntTex < 1; nCntTex++)
		{
			//�e�N�X�`���̔j��
			if (g_apTextureRod[nCntTex][nCnt] != NULL)
			{
				g_apTextureRod[nCntTex][nCnt]->Release();
				g_apTextureRod[nCntTex][nCnt] = NULL;
			}
		}
	}
}

void UpdateRod(void)
{
	for (int nCnt = 0; nCnt < MAX_ROD; nCnt++)
	{
		if (g_rod[nCnt].bUse == true)
		{
			g_rod[nCnt].posold = g_rod[nCnt].pos;

			g_rod[nCnt].pos += g_rod[nCnt].movepos;


			if (g_rod[nCnt].pos.x > 150.0f || g_rod[nCnt].pos.x < -150.0f)
			{
				g_rod[nCnt].movepos.x *= -1.0f;
			}

			if (g_rod[nCnt].pos.y > 150.0f || g_rod[nCnt].pos.y < 0.0f)
			{
				g_rod[nCnt].movepos.y *= -1.0f;
			}

			if (g_rod[nCnt].pos.z > 150.0f || g_rod[nCnt].pos.z < -150.0f)
			{
				g_rod[nCnt].movepos.z *= -1.0f;
			}
			CollisionPlayer(0);
		}
	}
}

void DrawRod(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCnt = 0; nCnt < MAX_ROD; nCnt++)
	{
		if (g_rod[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_rod[nCnt].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rod[nCnt].rot.y, g_rod[nCnt].rot.x, g_rod[nCnt].rot.z);
			D3DXMatrixMultiply(&g_rod[nCnt].mtxWorld, &g_rod[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_rod[nCnt].pos.x, g_rod[nCnt].pos.y, g_rod[nCnt].pos.z);
			D3DXMatrixMultiply(&g_rod[nCnt].mtxWorld, &g_rod[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_rod[nCnt].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatRod[g_rod[nCnt].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatRod[g_rod[nCnt].nType]; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureRod[nCntMat][g_rod[nCnt].nType]);

				//���f��(�p�[�c)�̕`��
				g_pMeshRod[g_rod[nCnt].nType]->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

void CollisionRod(void)
{
	// �v���C���[�̎擾
	Player* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_ROD; nCnt++)
	{
		if (g_rod[nCnt].bUse == true)
		{
			if (pPlayer->posOld.y + pPlayer->size.y <= g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y >= g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f)
			{
				if (pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->pos.y = g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f - pPlayer->size.y;
					pPlayer->move.y = 0.0f;
						SetRock(D3DXVECTOR3(0.0f, 25.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ROCKTYPE_VERTICAL);

				}
			}
			
			if (pPlayer->posOld.y >= g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y && pPlayer->pos.y <= g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y)
			{
				if (pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->bJump = false;
					pPlayer->pos.y = (g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y);
					pPlayer->move.y = 0.0f;
 						SetRock(D3DXVECTOR3(0.0f, 25.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ROCKTYPE_VERTICAL);

				}
			}

			
			if (pPlayer->posOld.z + pPlayer->size.z * 0.5f <= g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f >= g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y*0.5f < g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y*0.5f > g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->pos.z = (g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f) - pPlayer->size.z * 0.5f;
					pPlayer->move.z = 0.0f;
						SetRock(D3DXVECTOR3(0.0f, 25.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ROCKTYPE_VERTICAL);

				}
			}


			if (pPlayer->posOld.z - pPlayer->size.z * 0.5f >= g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.z - pPlayer->size.z * 0.5f <= g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y*0.5f < g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y*0.5f > g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f < g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f > g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f)
				{
					pPlayer->pos.z = (g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f) + pPlayer->size.z * 0.5f;
					pPlayer->move.z = 0.0f;
						SetRock(D3DXVECTOR3(0.0f, 25.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ROCKTYPE_VERTICAL);

				}
			}

			if (pPlayer->posOld.x + pPlayer->size.x * 0.5f <= g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f && pPlayer->pos.x + pPlayer->size.x * 0.5f >= g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y < g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y > g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f)
				{
					pPlayer->pos.x = (g_rod[nCnt].pos.x - g_rodsize[g_rod[nCnt].nType].size.x * 0.5f) - pPlayer->size.x * 0.5f;
					pPlayer->move.x = 0.0f;
						SetRock(D3DXVECTOR3(0.0f, 25.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ROCKTYPE_VERTICAL);

				}
			}

			if (pPlayer->posOld.x - pPlayer->size.x * 0.5f >= g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f && pPlayer->pos.x - pPlayer->size.x * 0.5f <= g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f)
			{
				if (pPlayer->pos.y - pPlayer->size.y < g_rod[nCnt].pos.y + g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.y + pPlayer->size.y > g_rod[nCnt].pos.y - g_rodsize[g_rod[nCnt].nType].size.y * 0.5f && pPlayer->pos.z - pPlayer->size.z * 0.5f < g_rod[nCnt].pos.z + g_rodsize[g_rod[nCnt].nType].size.z * 0.5f && pPlayer->pos.z + pPlayer->size.z * 0.5f > g_rod[nCnt].pos.z - g_rodsize[g_rod[nCnt].nType].size.z * 0.5f)
				{
					pPlayer->pos.x = (g_rod[nCnt].pos.x + g_rodsize[g_rod[nCnt].nType].size.x * 0.5f) + pPlayer->size.x * 0.5f;
					pPlayer->move.x = 0.0f;
					SetRock(D3DXVECTOR3(0.0f, 25.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ROCKTYPE_VERTICAL);
				}
			}

		}
	}
}

void SetRod(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 movepos, D3DXVECTOR3 moverot, int nType)
{
	for (int nCnt = 0; nCnt < MAX_ROD; nCnt++)
	{
		if (g_rod[nCnt].bUse == false)
		{
			g_rod[nCnt].pos = pos;
			g_rod[nCnt].rot = rot;
			g_rod[nCnt].movepos = movepos;
			g_rod[nCnt].moverot = moverot;
			g_rod[nCnt].nType = nType;
			g_rod[nCnt].bUse = true;
			break;
		}
	}
}

Rod* GetRod(void)
{
	return &g_rod[0];
}

RodSize* GetRodSize(void)
{
	return &g_rodsize[0];
}
