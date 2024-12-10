//==================================================================
//
//�r���{�[�h����<billboard.cpp>
//Author:Saeki Takuto
//
//==================================================================

#include "billboard.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;		//�e�N�X�`���ւ̃|�C���^
Billboard g_billboard;

void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg000.jpg",
		&g_pTextureBillboard);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard, NULL);

	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W��ݒ�
	pVtx[0].pos = D3DXVECTOR3(-150.0f, +150.0f, -50.0f);
	pVtx[1].pos = D3DXVECTOR3(+150.0f, +150.0f, -50.0f);
	pVtx[2].pos = D3DXVECTOR3(-150.0f, -150.0f, -50.0f);
	pVtx[3].pos = D3DXVECTOR3(+150.0f, -150.0f, -50.0f);

	//�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0, 0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0, 0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0, 0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0, 0.0f,-1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBillboard->Unlock();

}

void UninitBillboard(void)
{
}

void UpdateBillboard(void)
{
}

void DrawBillboard(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_billboard.mtxWorld);

	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�J�����̋t�s���ݒ�
	g_billboard.mtxWorld._11 = mtxView._11;
	g_billboard.mtxWorld._12 = mtxView._12;
	g_billboard.mtxWorld._13 = mtxView._13;
	g_billboard.mtxWorld._21 = mtxView._21;
	g_billboard.mtxWorld._22 = mtxView._22;
	g_billboard.mtxWorld._23 = mtxView._23;
	g_billboard.mtxWorld._31 = mtxView._31;
	g_billboard.mtxWorld._32 = mtxView._32;
	g_billboard.mtxWorld._33 = mtxView._33;

	////�����𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_billboard.rot.y, g_billboard.rot.x, g_billboard.rot.z);
	//D3DXMatrixMultiply(&g_billboard.mtxWorld, &g_billboard.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_billboard.pos.x, g_billboard.pos.y, g_billboard.pos.z);
	D3DXMatrixMultiply(&g_billboard.mtxWorld, &g_billboard.mtxWorld, &mtxTrans);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);//Z�̔�r���@
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);//Z�o�b�t�@�ɏ������܂Ȃ�

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_billboard.mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBillboard);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);//Z�o�b�t�@�ɏ�������

	//�A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
}
