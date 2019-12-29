
#include"common.h"
#include"moveground.h"
#include"player.h"
#include"seika.h"
#include"direct3d.h"
#include"texture.h"
#include"input.h"

cMoveGround* cMoveGround::numberOfObjects[NUMBER_OF_GROUND_MOVE]; // �I�u�W�F�N�g�i�[

LPDIRECT3DVERTEXBUFFER9 cMoveGround::pVertexBuffer;	// ���_�o�b�t�@
VERTEX_3D*				cMoveGround::pVertex;		// ���_�o�b�t�@�̒��g�𖄂߂�

//���_�Z�b�g�֐�
void cMoveGround::SetVertex()
{

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4,	// ���_�f�[�^�悤�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)//���_��
		D3DUSAGE_WRITEONLY,		// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,			// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,		// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pVertexBuffer,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL
	);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	// ���_���W�̐ݒ�
	pVertex[0].vtx = D3DXVECTOR3(-GROUND_HORIZONTAL_SIZE_MOVE / 2, -GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// ����
	pVertex[1].vtx = D3DXVECTOR3(-GROUND_HORIZONTAL_SIZE_MOVE / 2, GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// ����
	pVertex[2].vtx = D3DXVECTOR3(GROUND_HORIZONTAL_SIZE_MOVE / 2, -GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// �E��
	pVertex[3].vtx = D3DXVECTOR3(GROUND_HORIZONTAL_SIZE_MOVE / 2, GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// �E��

																								// �@���x�N�g���̐ݒ�
	for (int i = 0; i < 4; i++)
		pVertex[i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���ˌ��̐ݒ� // �F
	for (int i = 0; i < 4; i++)
		pVertex[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ��

																// �e�N�X�`�����W�̐ݒ�
	pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�f�[�^���A�����b�N����
	pVertexBuffer->Unlock();

}

// �n�ʐݒ�
void cMoveGround::SetGround(D3DXVECTOR2 _position, D3DXVECTOR2 _size, float _moveWidth)
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (!numberOfObjects[i]->use)
		{
			// �ǉ��ݒ�
			numberOfObjects[i]->moveWidth = _moveWidth;

			// �g�p
			numberOfObjects[i]->use = true;

			// �ʒu�Ƒ傫���w��
			numberOfObjects[i]->pastPosition.x = numberOfObjects[i]->position.x = _position.x;
			numberOfObjects[i]->pastPosition.y = numberOfObjects[i]->position.y = _position.y;
			numberOfObjects[i]->scale.x = _size.x;
			numberOfObjects[i]->scale.y = _size.y;

			return;
		}
	}
}

//������
void cMoveGround::Init()
{
	SetVertex();

	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		numberOfObjects[i] = new cMoveGround;

		// �ǉ��p�����[�^
		numberOfObjects[i]->speed = GROUND_MOVE_SPEED;
		numberOfObjects[i]->moveWidth = 0;

		// �g�p
		numberOfObjects[i]->use = false;

		// �T�C�Y
		numberOfObjects[i]->size = D3DXVECTOR2(1, 1);

		// �s��
		numberOfObjects[i]->pastPosition = numberOfObjects[i]->position = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->rotation = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);
	}
}

//�I������
void cMoveGround::Uninit()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		delete numberOfObjects[i];
	}
}

//�X�V����
void cMoveGround::Update()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (numberOfObjects[i]->use)
		{
			numberOfObjects[i]->position.y += numberOfObjects[i]->speed;

			if (
				numberOfObjects[i]->position.y < numberOfObjects[i]->pastPosition.y - numberOfObjects[i]->moveWidth / 2
				||
				numberOfObjects[i]->position.y > numberOfObjects[i]->pastPosition.y + numberOfObjects[i]->moveWidth / 2
				)
			{
				numberOfObjects[i]->speed *= -1;
			}
		}
	}
}

//�|���S���̕`��
void cMoveGround::Draw()
{

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pMoveDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;			// �X�P�[�����O�s��
	D3DXMATRIX rotationMatrix;		// ��]�s��
	D3DXMATRIX translationMatrix;	// ���s�ړ��s��

	
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (numberOfObjects[i]->use)
		{
			// �s�񏉊���
			D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);

			D3DXMatrixScaling(&scaleMatrix, numberOfObjects[i]->scale.x, numberOfObjects[i]->scale.y, numberOfObjects[i]->scale.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &scaleMatrix);

			D3DXMatrixRotationYawPitchRoll(&rotationMatrix, numberOfObjects[i]->rotation.y, numberOfObjects[i]->rotation.x, numberOfObjects[i]->rotation.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &rotationMatrix);

			D3DXMatrixTranslation(&translationMatrix, numberOfObjects[i]->position.x, numberOfObjects[i]->position.y, numberOfObjects[i]->position.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &translationMatrix);

			// ���[���h�}�g���b�N�X��ݒ�
			pMoveDevice->SetTransform(D3DTS_WORLD, &numberOfObjects[i]->worldMatrix);

			// �`�悵�����|���S���̒��_�o�b�t�@���f�[�^�X�g���[��(�f�[�^�̒ʂ蓹)�Z�b�g
			pMoveDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));

			// �`�悵�����|���S���̒��_�t�H�[�}�b�g�̐ݒ�
			pMoveDevice->SetFVF(FVF_VERTEX_3D);

			// �|���S���̕`��
			pMoveDevice->SetTexture(0, NULL);
			pMoveDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				2
			);
		}
	}
}