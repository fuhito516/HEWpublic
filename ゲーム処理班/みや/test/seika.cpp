
#include"common.h"
#include"seika.h"
#include"player.h"
#include"ground.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"debugproc.h"

cSeika* cSeika::numberOfObjects[NUMBER_OF_SEIKA]; // �I�u�W�F�N�g�i�[

LPDIRECT3DVERTEXBUFFER9 cSeika::pVertexBuffer;	// ���_�o�b�t�@
VERTEX_3D*				cSeika::pVertex;		// ���_�o�b�t�@�̒��g�𖄂߂�

//���_�Z�b�g�֐�
void cSeika::SetVertex()
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
	pVertex[0].vtx = D3DXVECTOR3(-SEIKA_HORIZONTAL_SIZE / 2, -SEIKA_VERTICAL_SIZE / 2, 0.0f);	// ����
	pVertex[1].vtx = D3DXVECTOR3(-SEIKA_HORIZONTAL_SIZE / 2, SEIKA_VERTICAL_SIZE / 2, 0.0f);	// ����
	pVertex[2].vtx = D3DXVECTOR3(SEIKA_HORIZONTAL_SIZE / 2, -SEIKA_VERTICAL_SIZE / 2, 0.0f);	// �E��
	pVertex[3].vtx = D3DXVECTOR3(SEIKA_HORIZONTAL_SIZE / 2, SEIKA_VERTICAL_SIZE / 2, 0.0f);		// �E��

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

//������
void cSeika::Init()
{
	InitDebugProc();

	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		// �w��v���C���[���L���̈���m��
		numberOfObjects[i] = new cSeika;

		// �O�t���[���̈ʒu�Ə�����̈ʒu(�����ʒu)
		numberOfObjects[i]->pastPosition.x = cPlayer::numberOfObjects[i]->position.x + SEIKA_HORIZONTAL_SIZE / 2;
		numberOfObjects[i]->pastPosition.y = cPlayer::numberOfObjects[i]->position.y + SEIKA_VERTICAL_SIZE / 2;

		// �ړ�����
		numberOfObjects[i]->directionVertical = DIRECTION_NONE;
		numberOfObjects[i]->directionHorizontal = DIRECTION_DOWN;

		// �W�����v������
		numberOfObjects[i]->jumping = false;
		// �W�����v�Œ��̓V��ւ̓����蔻��
		numberOfObjects[i]->hitCeilingWhileJumping = false;
		// �W�����v�ϔ���
		numberOfObjects[i]->jumped = false;

		// �d�̓J�E���^�[
		numberOfObjects[i]->gravityTimer = 0;

		// �����蔻��(���ɓ������Ă���̂�)
		numberOfObjects[i]->collision = COLLISION_NONE;

		// �`��
		numberOfObjects[i]->position = D3DXVECTOR3(numberOfObjects[i]->pastPosition.x, numberOfObjects[i]->pastPosition.y, 0);
		numberOfObjects[i]->rotation = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->scale = D3DXVECTOR3(1, 1, 1);
		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);
	}

	SetVertex();

}

//�I������
void cSeika::Uninit()
{
	UninitDebugProc();

	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		// �w��v���C���[���L���̈������
		delete numberOfObjects[i];
	}
}

//�X�V����
void cSeika::Update()
{
	UpdateDebugProc();

	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		// �ʒu�ۊ�
		numberOfObjects[i]->pastPosition.x = numberOfObjects[i]->position.x;
		numberOfObjects[i]->pastPosition.y = numberOfObjects[i]->position.y;

		// �v���C���[�����Εێ���
		if (cPlayer::numberOfObjects[i]->retention)
		{
			numberOfObjects[i]->gravityTimer = 0;

			// �v���C���[�����ֈړ���
			if (cPlayer::numberOfObjects[i]->directionHorizontal == DIRECTION_LEFT)
			{
				// ����
				numberOfObjects[i]->directionHorizontal = DIRECTION_LEFT;
				// �ړ�
				numberOfObjects[i]->position.x = cPlayer::numberOfObjects[i]->position.x - SEIKA_HORIZONTAL_SIZE / 2;
			}
			// �v���C���[���E�ֈړ����������͉��ړ����Ă��Ȃ�
			if (cPlayer::numberOfObjects[i]->directionHorizontal == DIRECTION_RIGHT)
			{
				// ����
				numberOfObjects[i]->directionHorizontal = DIRECTION_RIGHT;
				// �ړ�
				numberOfObjects[i]->position.x = cPlayer::numberOfObjects[i]->position.x + SEIKA_HORIZONTAL_SIZE / 2;
			}
			if (cPlayer::numberOfObjects[i]->directionHorizontal == DIRECTION_NONE)
			{
				// ����
				numberOfObjects[i]->directionHorizontal = DIRECTION_NONE;
			}

			numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->position.y + SEIKA_HORIZONTAL_SIZE / 2;
		}
		// �v���C���[�����΂�ێ����ĂȂ��n�ʂɂ��ڂ��Ă��Ȃ�
		if (
			!cPlayer::numberOfObjects[i]->retention
			&&
			numberOfObjects[i]->collision != COLLISION_GROUND
			&&
			!numberOfObjects[i]->jumped
			)
		{
			numberOfObjects[i]->jumping = true;
		}

		// �d�͎���
		numberOfObjects[i]->gravityTimer += 1.0f / 60.0f;

		// �W�����v���ł̈ړ�����
		if (numberOfObjects[i]->jumping)
		{
			// ���ړ�
			if (numberOfObjects[i]->directionHorizontal == DIRECTION_LEFT)
			{
				numberOfObjects[i]->position.x -= SEIKA_MOVEMENT_SPEED;
			}
			if (
				numberOfObjects[i]->directionHorizontal == DIRECTION_RIGHT
				||
				numberOfObjects[i]->directionHorizontal == DIRECTION_NONE
				)
			{
				numberOfObjects[i]->position.x += SEIKA_MOVEMENT_SPEED;
			}

			// ������̑J�ڂ����� && �W�����v���V��֓������Ă��Ȃ�
			if (
				SEIKA_JUMPPOWER * numberOfObjects[i]->gravityTimer
				>
				GRAVITY * numberOfObjects[i]->gravityTimer * numberOfObjects[i]->gravityTimer / 2
				&& !numberOfObjects[i]->hitCeilingWhileJumping
				)
			{
				numberOfObjects[i]->directionVertical = DIRECTION_UP;
				numberOfObjects[i]->position.y +=
					SEIKA_JUMPPOWER * numberOfObjects[i]->gravityTimer
					- 0.5f * GRAVITY * numberOfObjects[i]->gravityTimer * numberOfObjects[i]->gravityTimer;
			}
			// �W�����v���V��֓�������
			else if (numberOfObjects[i]->hitCeilingWhileJumping)
			{
				numberOfObjects[i]->directionVertical = DIRECTION_DOWN;
				numberOfObjects[i]->position.y -= SEIKA_MAXIMUM_FALLSPEED;
			}
			// ����ȊO�ŉ��J�ڂ�����
			else
			{
				numberOfObjects[i]->directionVertical = DIRECTION_DOWN;
				numberOfObjects[i]->position.y
					+= SEIKA_JUMPPOWER * numberOfObjects[i]->gravityTimer - 0.5f * GRAVITY * numberOfObjects[i]->gravityTimer * numberOfObjects[i]->gravityTimer;

				// �ō��������x��������
				if (SEIKA_JUMPPOWER * numberOfObjects[i]->gravityTimer - 0.5f * GRAVITY * numberOfObjects[i]->gravityTimer * numberOfObjects[i]->gravityTimer > SEIKA_MAXIMUM_FALLSPEED)
				{
					numberOfObjects[i]->position.y -= SEIKA_MAXIMUM_FALLSPEED;
				}
			}
		}
		// �W�����v���ł͂Ȃ� && �n�ʂƂ̓����蔻�肪�Ȃ�
		else if (!numberOfObjects[i]->jumping && numberOfObjects[i]->collision != COLLISION_GROUND)
		{
			numberOfObjects[i]->directionVertical = DIRECTION_DOWN;
			numberOfObjects[i]->position.y -= SEIKA_MAXIMUM_FALLSPEED / 2;
		}
		// ����
		numberOfObjects[i]->position.y -= 0.001f;

		// �v���C���[�Ƃ̓����蔻��
		for (int j = 0; j < NUMBER_OF_PLAYER; j++)
		{
			if (cSeika::numberOfObjects[i]->jumped)
			{
				// �v���C���[��numberOfObjects[i]�͈̔͂ɂ߂荞��ł��鎞
				if (
					// �v���C���[�̑������΂̏�ɂ߂荞��
					(cPlayer::numberOfObjects[j]->position.y - PLAYER_VERTICAL_SIZE / 2 < cSeika::numberOfObjects[i]->position.y + SEIKA_VERTICAL_SIZE * cSeika::numberOfObjects[i]->scale.y / 2)
					&&
					// �v���C���[�̓������΂̉��ɂ߂荞��
					(cPlayer::numberOfObjects[j]->position.y + PLAYER_VERTICAL_SIZE / 2 > cSeika::numberOfObjects[i]->position.y - SEIKA_VERTICAL_SIZE * cSeika::numberOfObjects[i]->scale.y / 2)
					&&
					// �v���C���[�̉E�[�����΂̍��[�ɂ߂荞��
					(cPlayer::numberOfObjects[j]->position.x + PLAYER_HORIZONTAL_SIZE / 2 > cSeika::numberOfObjects[i]->position.x - SEIKA_HORIZONTAL_SIZE * cSeika::numberOfObjects[i]->scale.x / 2)
					&&
					// �v���C���[�̍��[�����΂̉E�[�ɂ߂荞��
					(cPlayer::numberOfObjects[j]->position.x - PLAYER_VERTICAL_SIZE / 2 < cSeika::numberOfObjects[i]->position.x + SEIKA_HORIZONTAL_SIZE * cSeika::numberOfObjects[i]->scale.x / 2)
					)
				{
					cPlayer::numberOfObjects[j]->retention = true;
					cSeika::numberOfObjects[i]->jumped = false;
				}
			}
		}

		PrintDebugProc("�Փ�(����)�@%d\n", numberOfObjects[i]->collision);


		// �n�ʂƂ̓����蔻��
		for (int j = 0; j < NUMBER_OF_GROUND; j++)
		{
			int cnt = 0;
			if (cGround::numberOfObjects[j]->use)
			{
				// ���΂�numberOfObjects[j]�͈̔͂ɂ߂荞��ł��鎞
				if (
					// ���΂̑����n�ʂ̏�ɂ߂荞��
					(cSeika::numberOfObjects[i]->position.y - SEIKA_VERTICAL_SIZE / 2 < cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
					&&
					// ���΂̓����n�ʂ̉��ɂ߂荞��
					(cSeika::numberOfObjects[i]->position.y + SEIKA_VERTICAL_SIZE / 2 > cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
					&&
					// ���΂̉E�[���n�ʂ̍��[�ɂ߂荞��
					(cSeika::numberOfObjects[i]->position.x + SEIKA_HORIZONTAL_SIZE / 2 > cGround::numberOfObjects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2)
					&&
					// ���΂̍��[���n�ʂ̉E�[�ɂ߂荞��
					(cSeika::numberOfObjects[i]->position.x - SEIKA_VERTICAL_SIZE / 2 < cGround::numberOfObjects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2)
					)
				{
					// �㔻��
					if (cSeika::numberOfObjects[i]->pastPosition.y + SEIKA_VERTICAL_SIZE / 2 < cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
					{
						cSeika::numberOfObjects[i]->collision = COLLISION_CEILING;
						cSeika::numberOfObjects[i]->hitCeilingWhileJumping = true;

						cSeika::numberOfObjects[i]->position.y = numberOfObjects[0]->pastPosition.y;
					}
					// ������
					if ((cSeika::numberOfObjects[i]->pastPosition.y - SEIKA_VERTICAL_SIZE / 2 > cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2))
					{
						cSeika::numberOfObjects[i]->collision = COLLISION_GROUND;
						cSeika::numberOfObjects[i]->gravityTimer = 0;
						cSeika::numberOfObjects[i]->jumping = false;
						cSeika::numberOfObjects[i]->hitCeilingWhileJumping = false;
						cSeika::numberOfObjects[i]->jumped = true;

						cSeika::numberOfObjects[i]->position.y = numberOfObjects[0]->pastPosition.y;
					}

					if (
						(cSeika::numberOfObjects[i]->pastPosition.x + SEIKA_HORIZONTAL_SIZE / 2 < cGround::numberOfObjects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2)
						||
						(cSeika::numberOfObjects[i]->pastPosition.x - SEIKA_HORIZONTAL_SIZE / 2 > cGround::numberOfObjects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2)
						)
					{
						cSeika::numberOfObjects[i]->collision = COLLISION_WALL;

						cSeika::numberOfObjects[i]->position.x = numberOfObjects[0]->pastPosition.x;
					}

					cnt++;
				}
			}
			if (cnt == 0)
			{
				cSeika::numberOfObjects[i]->collision = COLLISION_NONE;
			}			
		}


		// �f�o�b�O�ōŒᗎ������
		if (numberOfObjects[i]->position.y - SEIKA_VERTICAL_SIZE / 2 < -50.0f)
		{
			numberOfObjects[i]->position.y = -50.0f + SEIKA_VERTICAL_SIZE / 2;
			numberOfObjects[i]->collision = COLLISION_GROUND;
			numberOfObjects[i]->jumping = false;
			numberOfObjects[i]->hitCeilingWhileJumping = false;
			numberOfObjects[i]->gravityTimer = 0;
		}
	}
}

//�|���S���̕`��
void cSeika::Draw()
{
	DrawDebugProc();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;			// �X�P�[�����O�s��
	D3DXMATRIX rotationMatrix;		// ��]�s��
	D3DXMATRIX translationMatrix;	// ���s�ړ��s��

	int i = 0;
	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
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
		pDevice->SetTransform(D3DTS_WORLD, &numberOfObjects[i]->worldMatrix);

		// �`�悵�����|���S���̒��_�o�b�t�@���f�[�^�X�g���[��(�f�[�^�̒ʂ蓹)�Z�b�g
		pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));

		// �`�悵�����|���S���̒��_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �|���S���̕`��
		pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_SEIKA));
		pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,
			0,
			2
		);
	}

}