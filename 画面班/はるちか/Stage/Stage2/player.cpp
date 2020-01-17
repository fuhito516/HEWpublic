
#include"common.h"
#include"player.h"
#include"ground.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"
#include"Moveground.h"

#include"debugproc.h"
//�ǉ�
#include<math.h>
cPlayer* cPlayer::numberOfObjects[NUMBER_OF_PLAYER]; // �I�u�W�F�N�g�i�[

LPDIRECT3DVERTEXBUFFER9 cPlayer::pVertexBuffer;	// ���_�o�b�t�@
VERTEX_3D*				cPlayer::pVertex;		// ���_�o�b�t�@�̒��g�𖄂߂�

//���_�Z�b�g�֐�
void cPlayer::SetVertex()
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
	pVertex[0].vtx = D3DXVECTOR3(-PLAYER_HORIZONTAL_SIZE / 2, -PLAYER_VERTICAL_SIZE / 2, 0.0f);	// ����
	pVertex[1].vtx = D3DXVECTOR3(-PLAYER_HORIZONTAL_SIZE / 2, PLAYER_VERTICAL_SIZE / 2, 0.0f);	// ����
	pVertex[2].vtx = D3DXVECTOR3(PLAYER_HORIZONTAL_SIZE / 2, -PLAYER_VERTICAL_SIZE / 2, 0.0f);	// �E��
	pVertex[3].vtx = D3DXVECTOR3(PLAYER_HORIZONTAL_SIZE / 2, PLAYER_VERTICAL_SIZE / 2, 0.0f);	// �E��

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
void cPlayer::Init()
{
	InitDebugProc();

	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		// �w��v���C���[���L���̈���m��
		numberOfObjects[i] = new cPlayer;

		// �O�t���[���̈ʒu�Ə�����̈ʒu(�����ʒu)
		numberOfObjects[i]->pastPosition = D3DXVECTOR2(PLAYER_INITIAL_POSITION_X, PLAYER_INITIAL_POSITION_Y);

		// �ړ�����
		numberOfObjects[i]->directionVertical = DIRECTION_NONE;
		numberOfObjects[i]->directionHorizontal = DIRECTION_DOWN;

		// �W�����v�\����
		numberOfObjects[i]->jumpPossible = false;
		// �W�����v������
		numberOfObjects[i]->jumping = false;
		// �W�����v�Œ��̓V��ւ̓����蔻��
		numberOfObjects[i]->hitCeilingWhileJumping = false;

		// �d�̓J�E���^�[
		numberOfObjects[i]->gravityTimer = 0;

		// �����蔻��(���ɓ������Ă���̂�)
		numberOfObjects[i]->collision = COLLISION_NONE;

		// ���Εێ�
		numberOfObjects[i]->retention = true;

		// �`��
		numberOfObjects[i]->position = D3DXVECTOR3(PLAYER_INITIAL_POSITION_X, PLAYER_INITIAL_POSITION_Y, 0);
		numberOfObjects[i]->rotation = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->scale = D3DXVECTOR3(1, 1, 1);
		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);
	}

	SetVertex();

}

//�I������
void cPlayer::Uninit()
{
	UninitDebugProc();

	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		// �w��v���C���[���L���̈������
		delete numberOfObjects[i];
	}
}

//�X�V����
void cPlayer::Update()
{
	UpdateDebugProc();

	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		// �ʒu�ۊ�
		numberOfObjects[i]->pastPosition.x = numberOfObjects[i]->position.x;
		numberOfObjects[i]->pastPosition.y = numberOfObjects[i]->position.y;
	
		// ���ړ�
		if (GetKeyboardPress(DIK_A))
		{
			// ����
			numberOfObjects[i]->directionHorizontal = DIRECTION_LEFT;
			// �ړ�
			numberOfObjects[i]->position.x -= PLAYER_MOVEMENT_SPEED;
		}
		if (GetKeyboardPress(DIK_D))
		{
			// ����
			numberOfObjects[i]->directionHorizontal = DIRECTION_RIGHT;
			// �ړ�
			numberOfObjects[i]->position.x += PLAYER_MOVEMENT_SPEED;
		}
		if (!GetKeyboardPress(DIK_A) && !GetKeyboardPress(DIK_D))
		{
			// ����
			numberOfObjects[i]->directionHorizontal = DIRECTION_NONE;
		}
		if (GetKeyboardPress(DIK_SPACE) && numberOfObjects[i]->jumpPossible)
		{
			// ����
			numberOfObjects[i]->directionVertical = DIRECTION_UP;

			numberOfObjects[i]->jumpPossible = false;
			numberOfObjects[i]->jumping = true;
		}

		if (GetKeyboardPress(DIK_T) && numberOfObjects[i]->retention)
		{
			numberOfObjects[i]->retention = false;
		}

		// �d�͎���
		numberOfObjects[i]->gravityTimer += 1.0f / 60.0f;

		// �W�����v���ł̈ړ�
		if ( numberOfObjects[i]->jumping)
		{
			// ������̑J�ڂ����� && �W�����v���V��֓������Ă��Ȃ�
			if (
				PLAYER_JUMPPOWER * numberOfObjects[i]->gravityTimer
				>
				GRAVITY * numberOfObjects[i]->gravityTimer * numberOfObjects[i]->gravityTimer / 2
				&& !numberOfObjects[i]->hitCeilingWhileJumping
				)
			{
				// ����
				numberOfObjects[i]->directionVertical = DIRECTION_UP;
				// �ʒu
				numberOfObjects[i]->position.y += 
					PLAYER_JUMPPOWER * numberOfObjects[i]->gravityTimer
					- 0.5f * GRAVITY * numberOfObjects[i]->gravityTimer * numberOfObjects[i]->gravityTimer;
			}
			// �W�����v���V��֓�������
			else if (numberOfObjects[i]->hitCeilingWhileJumping)
			{
				// ����
				numberOfObjects[i]->directionVertical = DIRECTION_DOWN;
				// �ʒu
				numberOfObjects[i]->position.y -= PLAYER_MAXIMUM_FALLSPEED;
			}
			// �W�����v���ŉ��J�ڂ�����
			else
			{
				// ����
				numberOfObjects[i]->directionVertical = DIRECTION_DOWN;

				// �ō��������x��������
				if (PLAYER_JUMPPOWER * numberOfObjects[i]->gravityTimer - 0.5f * GRAVITY * numberOfObjects[i]->gravityTimer * numberOfObjects[i]->gravityTimer < -PLAYER_MAXIMUM_FALLSPEED)
				{
					numberOfObjects[i]->position.y -= PLAYER_MAXIMUM_FALLSPEED;
				}
				else
				{
					numberOfObjects[i]->position.y
						+= PLAYER_JUMPPOWER * numberOfObjects[i]->gravityTimer - 0.5f * GRAVITY * numberOfObjects[i]->gravityTimer * numberOfObjects[i]->gravityTimer;
				}
			}
		}
		// �W�����v���ł͂Ȃ� && �n�ʂƂ̓����蔻�肪�Ȃ�
		else if (!numberOfObjects[i]->jumping && numberOfObjects[i]->collision != COLLISION_GROUND)
		{
			numberOfObjects[i]->directionVertical = DIRECTION_DOWN;

			numberOfObjects[i]->position.y -= PLAYER_MAXIMUM_FALLSPEED ;
		}
		// ����
		numberOfObjects[i]->position.y -= 0.001f;

		// �f�o�b�O�ōŒᗎ������
		if (numberOfObjects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < -50.0f)
		{
			numberOfObjects[i]->position.y = -50.0f + PLAYER_VERTICAL_SIZE / 2 - 0.25f;
			numberOfObjects[i]->collision = COLLISION_GROUND;
			numberOfObjects[i]->jumping = false;
			numberOfObjects[i]->jumpPossible = true;
			numberOfObjects[i]->hitCeilingWhileJumping = false;
			numberOfObjects[i]->gravityTimer = 0;
		}

		// �n�ʂƂ̓����蔻��
		for (int j = 0; j < NUMBER_OF_GROUND; j++)
		{
			int cnt = 0;
			if (cGround::numberOfObjects[j]->use)
			{
				// �v���C���[��numberOfObjects[j]�͈̔͂ɂ߂荞��ł��鎞
				if (
					// �v���C���[�̑����n�ʂ̏�ɂ߂荞��
					(cPlayer::numberOfObjects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
					&&
					// �v���C���[�̓����n�ʂ̉��ɂ߂荞��
					(cPlayer::numberOfObjects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
					&&
					// �v���C���[�̉E�[���n�ʂ̍��[�ɂ߂荞��
					(cPlayer::numberOfObjects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cGround::numberOfObjects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2)
					&&
					// �v���C���[�̍��[���n�ʂ̉E�[�ɂ߂荞��
					(cPlayer::numberOfObjects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cGround::numberOfObjects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2)
					)

				{
				
					// �㔻��
					if (cPlayer::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_CEILING;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = true;
						cPlayer::numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->pastPosition.y;

					}
					// ������
					if ((cPlayer::numberOfObjects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2))
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_GROUND;
						cPlayer::numberOfObjects[i]->gravityTimer = 0;
						cPlayer::numberOfObjects[i]->jumping = false;
						cPlayer::numberOfObjects[i]->jumpPossible = true;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = false;
						cPlayer::numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->pastPosition.y;
					}

					// ������
					if (
						(cPlayer::numberOfObjects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f
							<
							cGround::numberOfObjects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2)
						||
						(cPlayer::numberOfObjects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f
							>
							cGround::numberOfObjects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2)
						)
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_WALL;
						cPlayer::numberOfObjects[i]->position.x = cPlayer::numberOfObjects[i]->pastPosition.x;
					}

					cnt++;
				}
			}
			if (cnt == 0)
			{
				cPlayer::numberOfObjects[i]->collision = COLLISION_NONE;
			}
		}
		//================================================
		//�������̓����蔻��
		//
		//================================================
		for (int j = 0; j < NUMBER_OF_GROUND_MOVE; j++)
		{
			int cnt = 0;
			if (cMoveGround::MovenumberOfObjects[j]->use)
			{
				// �v���C���[��MovenumberOfObjects[j]�͈̔͂ɂ߂荞��ł��鎞
				if (
					// �v���C���[�̑����n�ʂ̏�ɂ߂荞��
					(cPlayer::numberOfObjects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cMoveGround::MovenumberOfObjects[j]->Mposition.y + GROUND_VERTICAL_SIZE * cMoveGround::MovenumberOfObjects[j]->Mscale.y / 2)
					&&
					// �v���C���[�̓����n�ʂ̉��ɂ߂荞��
					(cPlayer::numberOfObjects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cMoveGround::MovenumberOfObjects[j]->Mposition.y - GROUND_VERTICAL_SIZE * cMoveGround::MovenumberOfObjects[j]->Mscale.y / 2)
					&&
					// �v���C���[�̉E�[���n�ʂ̍��[�ɂ߂荞��
					(cPlayer::numberOfObjects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cMoveGround::MovenumberOfObjects[j]->Mposition.x - GROUND_HORIZONTAL_SIZE * cMoveGround::MovenumberOfObjects[j]->Mscale.x / 2)
					&&
					// �v���C���[�̍��[���n�ʂ̉E�[�ɂ߂荞��
					(cPlayer::numberOfObjects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cMoveGround::MovenumberOfObjects[j]->Mposition.x + GROUND_HORIZONTAL_SIZE * cMoveGround::MovenumberOfObjects[j]->Mscale.x / 2)
					)
				{
					//�ǉ��������蔻��
					if (cPlayer::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2
						&&
						cPlayer::numberOfObjects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2
						&&
						cPlayer::numberOfObjects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f < cGround::numberOfObjects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2
						&&
						cPlayer::numberOfObjects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cGround::numberOfObjects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2)
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_GROUND;
						cPlayer::numberOfObjects[i]->gravityTimer = 0;
						cPlayer::numberOfObjects[i]->jumping = false;
						cPlayer::numberOfObjects[i]->jumpPossible = true;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = false;
						cPlayer::numberOfObjects[i]->position.y = cMoveGround::MovenumberOfObjects[j]->Mposition.y + GROUND_VERTICAL_SIZE / 2 + PLAYER_VERTICAL_SIZE / 2 - 0.25f;

					}
					
					//�����܂ł��������̓����蔻��I


					// �㔻��
					if (cPlayer::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cMoveGround::MovenumberOfObjects[j]->Mposition.y - GROUND_VERTICAL_SIZE * cMoveGround::MovenumberOfObjects[j]->Mscale.y / 2)
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_CEILING;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = true;
						cPlayer::numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->pastPosition.y;
					}
					// ������
					if ((cPlayer::numberOfObjects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cMoveGround::MovenumberOfObjects[j]->Mposition.y + GROUND_VERTICAL_SIZE * cMoveGround::MovenumberOfObjects[j]->Mscale.y / 2))
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_GROUND;
						cPlayer::numberOfObjects[i]->gravityTimer = 0;
						cPlayer::numberOfObjects[i]->jumping = false;
						cPlayer::numberOfObjects[i]->jumpPossible = true;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = false;
						cPlayer::numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->pastPosition.y;
					}

					// ������
					if (
						(cPlayer::numberOfObjects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 - 0.8f
							<
							cMoveGround::MovenumberOfObjects[j]->Mposition.x -  cMoveGround::MovenumberOfObjects[j]->Mscale.x / 2
							&& cMoveGround::MovenumberOfObjects[j]->Mposition.y+cMoveGround::MovenumberOfObjects[j]->Mscale.y/2<cPlayer::numberOfObjects[i]->pastPosition.y + PLAYER_HORIZONTAL_SIZE / 2 + 0.8f)
						||
						(cPlayer::numberOfObjects[i]->pastPosition.x+ PLAYER_HORIZONTAL_SIZE / 2 + 0.8f
							>
							cMoveGround::MovenumberOfObjects[j]->Mposition.x +  cMoveGround::MovenumberOfObjects[j]->Mscale.x / 2
							&& cMoveGround::MovenumberOfObjects[j]->Mposition.y- cMoveGround::MovenumberOfObjects[j]->Mscale.y / 2>cPlayer::numberOfObjects[i]->pastPosition.y - PLAYER_HORIZONTAL_SIZE / 2 - 0.8f)
						)
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_WALL;
						//�ǉ��n�ʂ̃|�W�V�����[�v���C���[�̃|�W�V�������������Ƃŋ��������߂鏈��
						D3DXVECTOR3 distance = cMoveGround::MovenumberOfObjects[j]->Mposition- cPlayer::numberOfObjects[i]->position;
						//�P�ʃx�N�g��
						//D3DXVec3Normalize���P�ʃx�N�g���ɂ���֐�
						D3DXVec3Normalize(&distance, &distance);
						cPlayer::numberOfObjects[i]->position -= distance*0.5f;
					}

					cnt++;
				}
			}
			if (cnt == 0)
			{
				cPlayer::numberOfObjects[i]->collision = COLLISION_NONE;
			}
		}
		
		PrintDebugProc("���ΕۗL�@%d\n", numberOfObjects[i]->retention);
	}
}

//�|���S���̕`��
void cPlayer::Draw()
{
	DrawDebugProc();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;			// �X�P�[�����O�s��
	D3DXMATRIX rotationMatrix;		// ��]�s��
	D3DXMATRIX translationMatrix;	// ���s�ړ��s��

	int i = 0;
	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
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
		pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_BABY));
		pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,
			0,
			2
		);
	}

}