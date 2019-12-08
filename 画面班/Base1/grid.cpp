
#include"grid.h"
// �V�X�e��
#include"common.h"
#include"directx.h"
// �`��
#include"texture.h"
#include"sprite.h"
#include"vertex.h"

cGrid gcGrid;

void cGrid::Init_Grid()
{	
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//�I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * GRID_NUMBER_OF_VERTEX,	// ���_�f�[�^�悤�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)//���_��
		D3DUSAGE_WRITEONLY,		// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,			// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,		// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pVertexBuffer,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL
	);
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);
	
	int count_of_vtx = 0;
	// �c
	for (int i = 0; i < GRID_NUMBER; i++)
	{
		pVertex[count_of_vtx].vtx = 
			D3DXVECTOR3(-(GRID_NUMBER - 1) * GRID_INTERVALLENGTH / 2 + i * GRID_INTERVALLENGTH, 0, GRID_HALF_OF_LINELENGTH);
		count_of_vtx++;
		pVertex[count_of_vtx].vtx = 
			D3DXVECTOR3(-(GRID_NUMBER - 1) * GRID_INTERVALLENGTH / 2 + i * GRID_INTERVALLENGTH, 0, -GRID_HALF_OF_LINELENGTH);
		count_of_vtx++;
	}
	// ��
	for (int i = 0; i < GRID_NUMBER; i++)
	{
		pVertex[count_of_vtx].vtx =
			D3DXVECTOR3(-GRID_HALF_OF_LINELENGTH, 0, (GRID_NUMBER - 1) * GRID_INTERVALLENGTH / 2 - i * GRID_INTERVALLENGTH);
		count_of_vtx++;
		pVertex[count_of_vtx].vtx =
			D3DXVECTOR3(GRID_HALF_OF_LINELENGTH, 0, (GRID_NUMBER - 1) * GRID_INTERVALLENGTH / 2 - i * GRID_INTERVALLENGTH);
		count_of_vtx++;
	}

	// �@���x�N�g���̐ݒ�
	for (int i = 0; i < GRID_NUMBER_OF_VERTEX; i++)
		pVertex[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���ˌ�
	for (int i = 0; i < GRID_NUMBER_OF_VERTEX; i++)
		pVertex[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	if (GRID_NUMBER % 2 == 1)
	{
		pVertex[GRID_NUMBER * 2 / 2 - 1].diffuse					= D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVertex[GRID_NUMBER * 2 / 2].diffuse						= D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVertex[GRID_NUMBER * 2 + GRID_NUMBER * 2 / 2 - 1].diffuse	= D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVertex[GRID_NUMBER * 2 + GRID_NUMBER * 2 / 2].diffuse		= D3DXCOLOR(1.0f, 0, 0, 1.0f);
	}

	// �e�N�X�`��
	for (int i = 0; i < GRID_NUMBER_OF_VERTEX; i++)
		pVertex[i].tex = D3DXVECTOR2(0.0f, 0.0f);

	// ���_�f�[�^���A�����b�N����
	pVertexBuffer->Unlock();
}
void cGrid::Uninit_Grid()
{

}
void cGrid::Update_Grid()
{

}
void cGrid::Draw_Grid()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX mtxScl;	// �X�P�[�����O�s��
	D3DXMATRIX mtxRot;	// ��]�s��
	D3DXMATRIX mtxTrs;	// ���s�ړ��s��

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	rot = D3DXVECTOR3(0, 0, 0);				// ����(��])(rad)
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// �傫��(�X�P�[��)

	D3DXMatrixIdentity(&worldMtx);

	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&worldMtx, &worldMtx, &mtxScl);

	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&worldMtx, &worldMtx, &mtxRot);

	D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&worldMtx, &worldMtx, &mtxTrs);

	pDevice->SetTransform(D3DTS_WORLD, &worldMtx);

	// �`�悵�����|���S���̒��_�o�b�t�@���f�[�^�X�g���[��(�f�[�^�̒ʂ蓹)�Z�b�g
	pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));
	// �`�悵�����|���S���̒��_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	// �|���S���̕`��
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, GRID_NUMBER_OF_LINE);
}

cGrid* GetGrid()
{
	return &gcGrid;
}