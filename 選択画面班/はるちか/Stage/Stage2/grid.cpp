
#include"common.h"
#include"grid.h"

#include"direct3d.h"
#include"texture.h"

cGrid* cGrid::numberOfGrid;	// �I�u�W�F�N�g�i�[

LPDIRECT3DVERTEXBUFFER9	cGrid::pVertexBuffer;	// ���_�o�b�t�@
VERTEX_3D*				cGrid::pVertex;			// ���_�o�b�t�@�̒��g�𖄂߂�

D3DXVECTOR3 cGrid::position;	// �ʒu(�������W)
D3DXVECTOR3 cGrid::rotation;	// ��]
D3DXVECTOR3 cGrid::scale;		// �傫��
D3DXMATRIX cGrid::worldMatrix;	// ���[���h�}�g���b�N�X

// ���_�Z�b�g
void cGrid::SetVertex_Grid()
{

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//�I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * NUMBER_OF_VERTEX_OF_GRID,	// ���_�f�[�^�悤�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)//���_��
		D3DUSAGE_WRITEONLY,	// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,		// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,	// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pVertexBuffer,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL
	);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	// ���_�̗v�f��
	int countOfVertex = 0;
	// �c
	for (int i = 0; i < NUMBER_OF_GRAIN; i++)
	{
		pVertex[countOfVertex].vtx = D3DXVECTOR3
		(
			-(NUMBER_OF_GRAIN - 1) * SPACEING_BETWEEN_GRID_LINES / 2 + i * SPACEING_BETWEEN_GRID_LINES,
			0,
			HALF_LENGTH_OF_GRID
		);
		countOfVertex++;

		pVertex[countOfVertex].vtx = D3DXVECTOR3
		(
			-(NUMBER_OF_GRAIN - 1) * SPACEING_BETWEEN_GRID_LINES / 2 + i * SPACEING_BETWEEN_GRID_LINES,
			0,
			-HALF_LENGTH_OF_GRID
		);
		countOfVertex++;
	}
	// ��
	for (int i = 0; i < NUMBER_OF_GRAIN; i++)
	{
		pVertex[countOfVertex].vtx = D3DXVECTOR3
		(
			-HALF_LENGTH_OF_GRID,
			0,
			(NUMBER_OF_GRAIN - 1) * SPACEING_BETWEEN_GRID_LINES / 2 - i * SPACEING_BETWEEN_GRID_LINES
		);
		countOfVertex++;

		pVertex[countOfVertex].vtx = D3DXVECTOR3
		(
			HALF_LENGTH_OF_GRID,
			0,
			(NUMBER_OF_GRAIN - 1) * SPACEING_BETWEEN_GRID_LINES / 2 - i * SPACEING_BETWEEN_GRID_LINES
		);
		countOfVertex++;
	}

	// �@���x�N�g���̐ݒ�
	for (int i = 0; i < NUMBER_OF_VERTEX_OF_GRID; i++)
		pVertex[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���ˌ�
	for (int i = 0; i < NUMBER_OF_VERTEX_OF_GRID; i++)
		pVertex[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// �������͐ԐF
	if (NUMBER_OF_GRAIN % 2 == 1)
	{
		pVertex[NUMBER_OF_GRAIN * 2 / 2 - 1].diffuse					   = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVertex[NUMBER_OF_GRAIN * 2 / 2].diffuse						   = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVertex[NUMBER_OF_GRAIN * 2 + NUMBER_OF_GRAIN * 2 / 2 - 1].diffuse = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVertex[NUMBER_OF_GRAIN * 2 + NUMBER_OF_GRAIN * 2 / 2].diffuse	   = D3DXCOLOR(1.0f, 0, 0, 1.0f);
	}

	// �e�N�X�`��
	for (int i = 0; i < NUMBER_OF_VERTEX_OF_GRID; i++)
		pVertex[i].tex = D3DXVECTOR2(0.0f, 0.0f);

	// ���_�f�[�^���A�����b�N����
	pVertexBuffer->Unlock();

}

//������
void cGrid::Init()
{
	numberOfGrid = new cGrid;	// ���ɈӖ��͂Ȃ�

	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	rotation = D3DXVECTOR3(0, 0, 0);			// ��](rad)
	scale	 = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// �傫��
	// �s�񏉊���

	// ���_�ݒ�
	SetVertex_Grid();
}

//�I������
void cGrid::Uninit()
{
	delete numberOfGrid;
}

//�X�V����
void cGrid::Update()
{

}

//�|���S���̕`��
void cGrid::Draw()
{

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;			// �X�P�[�����O�s��
	D3DXMATRIX RotationMatrix;		// ��]�s��
	D3DXMATRIX translationMatrix;	// ���s�ړ��s��

	// �s�񏉊���
	D3DXMatrixIdentity(&worldMatrix);

	D3DXMatrixScaling(&scaleMatrix, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scaleMatrix);

	D3DXMatrixRotationYawPitchRoll(&RotationMatrix, rotation.y, rotation.x, rotation.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &RotationMatrix);

	D3DXMatrixTranslation(&translationMatrix, position.x, position.y, position.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);

	// ���[���h�}�g���b�N�X��ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &worldMatrix);

	// �`�悵�����|���S���̒��_�o�b�t�@���f�[�^�X�g���[��(�f�[�^�̒ʂ蓹)�Z�b�g
	pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));

	// �`�悵�����|���S���̒��_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, NUMBER_OF_LINE_OF_GRID);

}