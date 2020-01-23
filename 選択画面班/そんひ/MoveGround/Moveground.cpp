
#include"common.h"
#include"Moveground.h"
#include"player.h"
#include"seika.h"
#include"direct3d.h"
#include"texture.h"
#include"input.h"

//cMoveGround* cMoveGround::MovenumberOfObjects[NUMBER_OF_GROUND_MOVE]; // �I�u�W�F�N�g�i�[
cVerticalMoveGround* cVerticalMoveGround::VerticalMovenumberOfObjects[NUMBER_OF_GROUND_MOVE]; // �I�u�W�F�N�g�i�[

LPDIRECT3DVERTEXBUFFER9 cMoveGround::pMoveVertexBuffer;	// ���_�o�b�t�@
VERTEX_3D*				cMoveGround::pMoveVertex;		// ���_�o�b�t�@�̒��g�𖄂߂�
//���_�Z�b�g�֐�
void cMoveGround::MoveSetVertex()
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
		&pMoveVertexBuffer,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL
	);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pMoveVertexBuffer->Lock(0, 0, (void**)&pMoveVertex, 0);

	// ���_���W�̐ݒ�
	pMoveVertex[0].vtx = D3DXVECTOR3(-GROUND_HORIZONTAL_SIZE_MOVE / 2, -GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// ����
	pMoveVertex[1].vtx = D3DXVECTOR3(-GROUND_HORIZONTAL_SIZE_MOVE / 2, GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// ����
	pMoveVertex[2].vtx = D3DXVECTOR3(GROUND_HORIZONTAL_SIZE_MOVE / 2, -GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// �E��
	pMoveVertex[3].vtx = D3DXVECTOR3(GROUND_HORIZONTAL_SIZE_MOVE / 2, GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// �E��

	// �@���x�N�g���̐ݒ�
	for (int i = 0; i < 4; i++)
		pMoveVertex[i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���ˌ��̐ݒ� // �F
	for (int i = 0; i < 4; i++)
		pMoveVertex[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ��

    // �e�N�X�`�����W�̐ݒ�
	pMoveVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pMoveVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pMoveVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pMoveVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�f�[�^���A�����b�N����
	pMoveVertexBuffer->Unlock();

}

void cMoveGround::MoveSetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize){}
void cMoveGround::MoveInit(){}
void cMoveGround::MoveUninit(){}
void cMoveGround::MoveUpdate(){}
void cMoveGround::MoveDraw(){}

// �n�ʐݒ�
void cVerticalMoveGround::MoveSetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize)
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (!VerticalMovenumberOfObjects[i]->use)
		{
			// �g�p
			VerticalMovenumberOfObjects[i]->use = true;

			// �t���[���J�E���^�[
			VerticalMovenumberOfObjects[i]->frameCounter = 0;

			// �ʒu�Ƒ傫���w��
			VerticalMovenumberOfObjects[i]->Mposition.x = _mposition.x;
			VerticalMovenumberOfObjects[i]->Mposition.y = _mposition.y;
			VerticalMovenumberOfObjects[i]->Mscale.x = _msize.x;
			VerticalMovenumberOfObjects[i]->Mscale.y = _msize.y;

			//�����ʒu�̊i�[

			return;
		}
	}
}


//������
void cVerticalMoveGround::MoveInit()
{
	//float t = 0;
	//t += 0.1f;
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		VerticalMovenumberOfObjects[i] = new cVerticalMoveGround;

		// �g�p
		VerticalMovenumberOfObjects[i]->use = false;

		// �T�C�Y
		VerticalMovenumberOfObjects[i]->size = D3DXVECTOR2(1, 1);

		// �s��
		VerticalMovenumberOfObjects[i]->Mposition = D3DXVECTOR3(0, 15, 0);
		VerticalMovenumberOfObjects[i]->Mrotation = D3DXVECTOR3(0, 0, 0);
		VerticalMovenumberOfObjects[i]->Mscale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		D3DXMatrixIdentity(&VerticalMovenumberOfObjects[i]->MworldMatrix);
	}

	MoveSetVertex();

}

//�I������
void cVerticalMoveGround::MoveUninit()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		delete VerticalMovenumberOfObjects[i];
	}
}


//�|���S���̕`��
void cVerticalMoveGround::MoveDraw()
{

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pMoveDevice = MyDirect3D_GetDevice();

	D3DXMATRIX MovescaleMatrix;			// �X�P�[�����O�s��
	D3DXMATRIX MoverotationMatrix;		// ��]�s��
	D3DXMATRIX MovetranslationMatrix;	// ���s�ړ��s��

	
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (VerticalMovenumberOfObjects[i]->use)
		{
			// �s�񏉊���
			D3DXMatrixIdentity(&VerticalMovenumberOfObjects[i]->MworldMatrix);

			D3DXMatrixScaling(&MovescaleMatrix, VerticalMovenumberOfObjects[i]->Mscale.x, VerticalMovenumberOfObjects[i]->Mscale.y, VerticalMovenumberOfObjects[i]->Mscale.z);
			D3DXMatrixMultiply(&VerticalMovenumberOfObjects[i]->MworldMatrix, &VerticalMovenumberOfObjects[i]->MworldMatrix, &MovescaleMatrix);

			D3DXMatrixRotationYawPitchRoll(&MoverotationMatrix, VerticalMovenumberOfObjects[i]->Mrotation.y, VerticalMovenumberOfObjects[i]->Mrotation.x, VerticalMovenumberOfObjects[i]->Mrotation.z);
			D3DXMatrixMultiply(&VerticalMovenumberOfObjects[i]->MworldMatrix, &VerticalMovenumberOfObjects[i]->MworldMatrix, &MoverotationMatrix);

			D3DXMatrixTranslation(&MovetranslationMatrix, VerticalMovenumberOfObjects[i]->Mposition.x, VerticalMovenumberOfObjects[i]->Mposition.y, VerticalMovenumberOfObjects[i]->Mposition.z);
			D3DXMatrixMultiply(&VerticalMovenumberOfObjects[i]->MworldMatrix, &VerticalMovenumberOfObjects[i]->MworldMatrix, &MovetranslationMatrix);

			// ���[���h�}�g���b�N�X��ݒ�
			pMoveDevice->SetTransform(D3DTS_WORLD, &VerticalMovenumberOfObjects[i]->MworldMatrix);

			// �`�悵�����|���S���̒��_�o�b�t�@���f�[�^�X�g���[��(�f�[�^�̒ʂ蓹)�Z�b�g
			pMoveDevice->SetStreamSource(0, pMoveVertexBuffer, 0, sizeof(VERTEX_3D));

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

//�c�ړ��X�V����
void cVerticalMoveGround::MoveUpdate()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{

		if (VerticalMovenumberOfObjects[i]->use)
		{
			VerticalMovenumberOfObjects[i]->Mposition.y += VerticalMovenumberOfObjects[i]->spead;

			if (VerticalMovenumberOfObjects[i]->Mposition.y<0) {
				VerticalMovenumberOfObjects[i]->spead *= -1;
			}
			else if (VerticalMovenumberOfObjects[i]->Mposition.y>10) {
				VerticalMovenumberOfObjects[i]->spead *= -1;
			}
			// �t���[���J�E���^�[
			VerticalMovenumberOfObjects[i]->frameCounter++;
		}
	}
}