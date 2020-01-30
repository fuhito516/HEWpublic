
#include"common.h"
#include"Moveground.h"
#include"player.h"
#include"seika.h"
#include"direct3d.h"
#include"texture.h"
#include"input.h"

//cMoveGround* cMoveGround::MovenumberOfObjects[NUMBER_OF_GROUND_MOVE]; // �I�u�W�F�N�g�i�[
cHorizontalMoveGround* cHorizontalMoveGround::objects[NUMBER_OF_GROUND_MOVE]; // �I�u�W�F�N�g�i�[

																			  // �n�ʐݒ�
void cHorizontalMoveGround::SetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize, D3DXVECTOR2 _distance)
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (!objects[i]->use)
		{
			// �g�p
			objects[i]->use = true;

			// �t���[���J�E���^�[
			objects[i]->frameCounter = 0;

			// �ʒu�Ƒ傫���w��
			objects[i]->Mposition.x = _mposition.x;
			objects[i]->Mposition.y = _mposition.y;
			objects[i]->Mscale.x = _msize.x;
			objects[i]->Mscale.y = _msize.y;

			//�ړ�����
			objects[i]->distance.x = _distance.x;
			objects[i]->distance.y = _distance.y;

			//�����ʒu�̊i�[
			objects[i]->fastMovePos.x = objects[i]->Mposition.x;
			objects[i]->fastMovePos.y = objects[i]->Mposition.y;
			objects[i]->fastMovePos.z = 0;
			return;
		}
	}
}


//������
void cHorizontalMoveGround::Init()
{
	float t = 0;
	t += 0.1f;
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		objects[i] = new cHorizontalMoveGround;


		// �g�p
		objects[i]->use = false;

		// �T�C�Y
		objects[i]->size = D3DXVECTOR2(1, 1);

		// �s��
		objects[i]->Mposition = D3DXVECTOR3(0, t, 0);
		objects[i]->Mrotation = D3DXVECTOR3(0, 0, 0);
		objects[i]->Mscale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		D3DXMatrixIdentity(&objects[i]->MworldMatrix);
	}

	SetVertex();

}

//�I������
void cHorizontalMoveGround::Uninit()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		delete objects[i];
	}
}


//�|���S���̕`��
void cHorizontalMoveGround::Draw()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pMoveDevice = MyDirect3D_GetDevice();

	D3DXMATRIX MovescaleMatrix;			// �X�P�[�����O�s��
	D3DXMATRIX MoverotationMatrix;		// ��]�s��
	D3DXMATRIX MovetranslationMatrix;	// ���s�ړ��s��


	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (objects[i]->use)
		{
			// �s�񏉊���
			D3DXMatrixIdentity(&objects[i]->MworldMatrix);

			D3DXMatrixScaling(&MovescaleMatrix, objects[i]->Mscale.x, objects[i]->Mscale.y, objects[i]->Mscale.z);
			D3DXMatrixMultiply(&objects[i]->MworldMatrix, &objects[i]->MworldMatrix, &MovescaleMatrix);

			D3DXMatrixRotationYawPitchRoll(&MoverotationMatrix, objects[i]->Mrotation.y, objects[i]->Mrotation.x, objects[i]->Mrotation.z);
			D3DXMatrixMultiply(&objects[i]->MworldMatrix, &objects[i]->MworldMatrix, &MoverotationMatrix);

			D3DXMatrixTranslation(&MovetranslationMatrix, objects[i]->Mposition.x, objects[i]->Mposition.y, objects[i]->Mposition.z);
			D3DXMatrixMultiply(&objects[i]->MworldMatrix, &objects[i]->MworldMatrix, &MovetranslationMatrix);

			// ���[���h�}�g���b�N�X��ݒ�
			pMoveDevice->SetTransform(D3DTS_WORLD, &objects[i]->MworldMatrix);

			// �`�悵�����|���S���̒��_�o�b�t�@���f�[�^�X�g���[��(�f�[�^�̒ʂ蓹)�Z�b�g
			pMoveDevice->SetStreamSource(0, pMoveVertexBuffer, 0, sizeof(VERTEX_3D));

			// �`�悵�����|���S���̒��_�t�H�[�}�b�g�̐ݒ�
			pMoveDevice->SetFVF(FVF_VERTEX_3D);

			// �|���S���̕`��
			pMoveDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_GROUND));
			pMoveDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				2
			);
		}
	}
}

//���ړ��X�V����
void cHorizontalMoveGround::Update()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (objects[i]->use)
		{
			if (objects[i]->distance.x > 0) {
				objects[i]->Mposition.x += objects[i]->spead;

				if (objects[i]->Mposition.x<objects[i]->fastMovePos.x - objects[i]->distance.x) {
					objects[i]->spead *= -1;
				}
				else if (objects[i]->Mposition.x>objects[i]->fastMovePos.x + objects[i]->distance.x) {
					objects[i]->spead *= -1;
				}
			}


			if (objects[i]->distance.x < 0) {

				objects[i]->Mposition.x -= objects[i]->spead;
				if (objects[i]->Mposition.x<objects[i]->fastMovePos.x - objects[i]->distance.x*-1) {
					objects[i]->spead *= -1;
				}
				else if (objects[i]->Mposition.x>objects[i]->fastMovePos.x + objects[i]->distance.x*-1) {
					objects[i]->spead *= -1;
				}
			}
			// �t���[���J�E���^�[
			objects[i]->frameCounter++;
		}
	}
}