
#include"common.h"
#include"Moveground.h"
#include"player.h"
#include"seika.h"
#include"direct3d.h"
#include"texture.h"
#include"input.h"

//cMoveGround* cMoveGround::MovenumberOfObjects[NUMBER_OF_GROUND_MOVE]; // �I�u�W�F�N�g�i�[
cHorizontalMoveGround* cHorizontalMoveGround::HorizontalMovenumberOfObjects[NUMBER_OF_GROUND_MOVE]; // �I�u�W�F�N�g�i�[

// �n�ʐݒ�
void cHorizontalMoveGround::MoveSetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize)
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (!HorizontalMovenumberOfObjects[i]->use)
		{
			// �g�p
			HorizontalMovenumberOfObjects[i]->use = true;

			// �t���[���J�E���^�[
			HorizontalMovenumberOfObjects[i]->frameCounter = 0;

			// �ʒu�Ƒ傫���w��
			HorizontalMovenumberOfObjects[i]->Mposition.x = _mposition.x;
			HorizontalMovenumberOfObjects[i]->Mposition.y = _mposition.y;
			HorizontalMovenumberOfObjects[i]->Mscale.x = _msize.x;
			HorizontalMovenumberOfObjects[i]->Mscale.y = _msize.y;

			//�����ʒu�̊i�[
			HorizontalMovenumberOfObjects[i]->fastMovePos.x = HorizontalMovenumberOfObjects[i]->Mposition.x;
			HorizontalMovenumberOfObjects[i]->fastMovePos.y = HorizontalMovenumberOfObjects[i]->Mposition.y;
			HorizontalMovenumberOfObjects[i]->fastMovePos.z = 0;
			return;
		}
	}
}


//������
void cHorizontalMoveGround::MoveInit()
{
	float t = 0;
	t += 0.1f;
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		HorizontalMovenumberOfObjects[i] = new cHorizontalMoveGround;


		// �g�p
		HorizontalMovenumberOfObjects[i]->use = false;

		// �T�C�Y
		HorizontalMovenumberOfObjects[i]->size = D3DXVECTOR2(1, 1);

		// �s��
		HorizontalMovenumberOfObjects[i]->Mposition = D3DXVECTOR3(0, t, 0);
		HorizontalMovenumberOfObjects[i]->Mrotation = D3DXVECTOR3(0, 0, 0);
		HorizontalMovenumberOfObjects[i]->Mscale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		D3DXMatrixIdentity(&HorizontalMovenumberOfObjects[i]->MworldMatrix);
	}

	MoveSetVertex();

}

//�I������
void cHorizontalMoveGround::MoveUninit()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		delete HorizontalMovenumberOfObjects[i];
	}
}


//�|���S���̕`��
void cHorizontalMoveGround::MoveDraw()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pMoveDevice = MyDirect3D_GetDevice();

	D3DXMATRIX MovescaleMatrix;			// �X�P�[�����O�s��
	D3DXMATRIX MoverotationMatrix;		// ��]�s��
	D3DXMATRIX MovetranslationMatrix;	// ���s�ړ��s��


	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (HorizontalMovenumberOfObjects[i]->use)
		{
			// �s�񏉊���
			D3DXMatrixIdentity(&HorizontalMovenumberOfObjects[i]->MworldMatrix);

			D3DXMatrixScaling(&MovescaleMatrix, HorizontalMovenumberOfObjects[i]->Mscale.x, HorizontalMovenumberOfObjects[i]->Mscale.y, HorizontalMovenumberOfObjects[i]->Mscale.z);
			D3DXMatrixMultiply(&HorizontalMovenumberOfObjects[i]->MworldMatrix, &HorizontalMovenumberOfObjects[i]->MworldMatrix, &MovescaleMatrix);

			D3DXMatrixRotationYawPitchRoll(&MoverotationMatrix, HorizontalMovenumberOfObjects[i]->Mrotation.y, HorizontalMovenumberOfObjects[i]->Mrotation.x, HorizontalMovenumberOfObjects[i]->Mrotation.z);
			D3DXMatrixMultiply(&HorizontalMovenumberOfObjects[i]->MworldMatrix, &HorizontalMovenumberOfObjects[i]->MworldMatrix, &MoverotationMatrix);

			D3DXMatrixTranslation(&MovetranslationMatrix, HorizontalMovenumberOfObjects[i]->Mposition.x, HorizontalMovenumberOfObjects[i]->Mposition.y, HorizontalMovenumberOfObjects[i]->Mposition.z);
			D3DXMatrixMultiply(&HorizontalMovenumberOfObjects[i]->MworldMatrix, &HorizontalMovenumberOfObjects[i]->MworldMatrix, &MovetranslationMatrix);

			// ���[���h�}�g���b�N�X��ݒ�
			pMoveDevice->SetTransform(D3DTS_WORLD, &HorizontalMovenumberOfObjects[i]->MworldMatrix);

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
void cHorizontalMoveGround::MoveUpdate()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (HorizontalMovenumberOfObjects[i]->use)
		{
			HorizontalMovenumberOfObjects[i]->Mposition.x += HorizontalMovenumberOfObjects[i]->spead;

			if (HorizontalMovenumberOfObjects[i]->Mposition.x<HorizontalMovenumberOfObjects[i]->fastMovePos.x) {
				HorizontalMovenumberOfObjects[i]->spead *= -1;
			}
			else if (HorizontalMovenumberOfObjects[i]->Mposition.x>HorizontalMovenumberOfObjects[i]->fastMovePos.x + 5) {
				HorizontalMovenumberOfObjects[i]->spead *= -1;
			}
			// �t���[���J�E���^�[
			HorizontalMovenumberOfObjects[i]->frameCounter++;
		}
	}
}