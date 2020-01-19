
#include"common.h"
#include"seika.h"
#include"player.h"
#include"ground.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"debugproc.h"

cSeika* cSeika::numberOfObjects[NUMBER_OF_SEIKA];

LPDIRECT3DVERTEXBUFFER9 cSeika::pVertexBuffer;
VERTEX_3D*				cSeika::pVertex;

//���_�Z�b�g�֐�
void cSeika::SetVertex()
{

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVertexBuffer,
		NULL
	);

	pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vtx = D3DXVECTOR3(-SEIKA_HORIZONTAL_SIZE / 2, -SEIKA_VERTICAL_SIZE / 2, 0.0f);
	pVertex[1].vtx = D3DXVECTOR3(-SEIKA_HORIZONTAL_SIZE / 2, SEIKA_VERTICAL_SIZE / 2, 0.0f);
	pVertex[2].vtx = D3DXVECTOR3(SEIKA_HORIZONTAL_SIZE / 2, -SEIKA_VERTICAL_SIZE / 2, 0.0f);
	pVertex[3].vtx = D3DXVECTOR3(SEIKA_HORIZONTAL_SIZE / 2, SEIKA_VERTICAL_SIZE / 2, 0.0f);
	for (int i = 0; i < 4; i++)
	{
		pVertex[i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}
	for (int i = 0; i < 4; i++)
	{
		pVertex[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVertexBuffer->Unlock();
}

//������
void cSeika::Init()
{
	InitDebugProc();

	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		numberOfObjects[i] = new cSeika;

		// ����
		numberOfObjects[i]->owner = i;

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

		// �O�t���[���̈ʒu�Ə�����̈ʒu(�����ʒu)
		numberOfObjects[i]->pastPosition.x = cPlayer::numberOfObjects[i]->position.x + SEIKA_HORIZONTAL_SIZE / 2;
		numberOfObjects[i]->pastPosition.y = cPlayer::numberOfObjects[i]->position.y + SEIKA_VERTICAL_SIZE / 2;

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
			if (cPlayer::numberOfObjects[i]->pastDirectionHorizontal == DIRECTION_LEFT)
			{
				// ����
				numberOfObjects[i]->directionHorizontal = DIRECTION_LEFT;
				// �ʒux
				numberOfObjects[i]->position.x = cPlayer::numberOfObjects[i]->position.x - SEIKA_HORIZONTAL_SIZE / 2;
			}
			// �v���C���[���E�ֈړ���
			if (cPlayer::numberOfObjects[i]->pastDirectionHorizontal == DIRECTION_RIGHT)
			{
				// ����
				numberOfObjects[i]->directionHorizontal = DIRECTION_RIGHT;
				// �ʒux
				numberOfObjects[i]->position.x = cPlayer::numberOfObjects[i]->position.x + SEIKA_HORIZONTAL_SIZE / 2;
			}

			// �ʒuy
			numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->position.y + SEIKA_HORIZONTAL_SIZE / 2;
		}

		// �v���C���[�����΂�ێ������A�n�ʂɂ��ڂ������Ƃ��Ȃ�
		if (
			!cPlayer::numberOfObjects[i]->retention
			&&
			!numberOfObjects[i]->jumped
			)
		{
			numberOfObjects[i]->jumping = true;
		}
		else
		{
			numberOfObjects[i]->jumping = false;
		}
		
		// �v���C���[���ێ����Ă��Ȃ��Ƃ�
		if (!cPlayer::numberOfObjects[i]->retention)
		{
			// ���������� && �n�ʂƂ̓����蔻�肪�Ȃ�
			if (
				numberOfObjects[i]->jumped
				&&
				numberOfObjects[i]->collision != COLLISION_GROUND
				)
			{
				numberOfObjects[i]->directionVertical = DIRECTION_DOWN;
				numberOfObjects[i]->position.y -= SEIKA_MAXSPEED;
			}

			// �󒆂ł̈ړ�
			if (numberOfObjects[i]->jumping)
			{
				// �I�ύX���I
				// �d�͎���
				numberOfObjects[i]->gravityTimer += 1.0f / FRAME_PER_SECOND;

				// ���ړ�
				if (numberOfObjects[i]->directionHorizontal == DIRECTION_LEFT)
				{
					numberOfObjects[i]->position.x -= SEIKA_MOVEMENT_SPEED * (float)cos(D3DXToRadian((double)cPlayer::numberOfObjects[numberOfObjects[i]->owner]->throwDegree));
				}
				if (numberOfObjects[i]->directionHorizontal == DIRECTION_RIGHT)
				{
					numberOfObjects[i]->position.x += SEIKA_MOVEMENT_SPEED * (float)cos(D3DXToRadian((double)cPlayer::numberOfObjects[numberOfObjects[i]->owner]->throwDegree));
				}

				// �c�ړ�
				// �W�����v���V��֓������Ă��Ȃ�
				if (!numberOfObjects[i]->hitCeilingWhileJumping)
				{
					if (SEIKA_MOVEMENT_SPEED * (float)sin(D3DXToRadian((double)cPlayer::numberOfObjects[numberOfObjects[i]->owner]->throwDegree)) - GRAVITY * numberOfObjects[i]->gravityTimer > 0)
					{
						numberOfObjects[i]->directionVertical = DIRECTION_UP;
					}
					else
					{
						numberOfObjects[i]->directionVertical = DIRECTION_DOWN;
					}

					// �ō����x��������
					if (SEIKA_MOVEMENT_SPEED * (float)sin(D3DXToRadian((double)cPlayer::numberOfObjects[numberOfObjects[i]->owner]->throwDegree)) - GRAVITY * numberOfObjects[i]->gravityTimer < -SEIKA_MAXSPEED)
					{
						numberOfObjects[i]->position.y += -SEIKA_MAXSPEED;
					}
					else
					{
						numberOfObjects[i]->position.y +=
							SEIKA_MOVEMENT_SPEED * (float)sin(D3DXToRadian((double)cPlayer::numberOfObjects[numberOfObjects[i]->owner]->throwDegree)) - GRAVITY * numberOfObjects[i]->gravityTimer;
					}
				}
				// �W�����v���V��֓�������
				else
				{
					numberOfObjects[i]->directionVertical = DIRECTION_DOWN;
					numberOfObjects[i]->position.y -= SEIKA_MAXSPEED;
				}
			}

			// �v���C���[�Ƃ̓����蔻��
			if (cSeika::numberOfObjects[i]->jumped)
			{
				for (int j = 0; j < NUMBER_OF_PLAYER; j++)
				{
					if (!cPlayer::numberOfObjects[j]->retention)
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
							cSeika::numberOfObjects[i]->owner = j;
							cSeika::numberOfObjects[i]->collision = COLLISION_PLAYER;
							cSeika::numberOfObjects[i]->gravityTimer = 0;
							cSeika::numberOfObjects[i]->jumping = false;
							cSeika::numberOfObjects[i]->hitCeilingWhileJumping = false;
							cSeika::numberOfObjects[i]->jumped = false;

							return;
						}
					}
				}
			}

			// ����
			numberOfObjects[i]->position.y -= 0.001f;

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
						// �ߋ��̈ʒu�����܂��Ă������։����o��
						if (
							cSeika::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2
							&&
							cSeika::numberOfObjects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2
							&&
							cSeika::numberOfObjects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f < cGround::numberOfObjects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2
							&&
							cSeika::numberOfObjects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cGround::numberOfObjects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2
							)
						{
							cSeika::numberOfObjects[i]->collision = COLLISION_GROUND;
							cSeika::numberOfObjects[i]->gravityTimer = 0;
							cSeika::numberOfObjects[i]->jumping = false;
							cSeika::numberOfObjects[i]->hitCeilingWhileJumping = false;
							cSeika::numberOfObjects[i]->jumped = true;
							cSeika::numberOfObjects[i]->position.y = cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE / 2 + PLAYER_VERTICAL_SIZE / 2 - 0.25f;
						}

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

						// ���E����
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
		}

		//// �����n�ʂƂ̓����蔻��
		//for (int j = 0; j < NUMBER_OF_GROUND; j++)
		//{
		//	int cnt = 0;
		//	if (cMoveGround::numberOfObjects[j]->use)
		//	{
		//		// �v���C���[��numberOfObjects[j]�͈̔͂ɂ߂荞��ł��鎞
		//		if (
		//			// �v���C���[�̑����n�ʂ̏�ɂ߂荞��
		//			(cSeika::numberOfObjects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cMoveGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cMoveGround::numberOfObjects[j]->scale.y / 2)
		//			&&
		//			// �v���C���[�̓����n�ʂ̉��ɂ߂荞��
		//			(cSeika::numberOfObjects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cMoveGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cMoveGround::numberOfObjects[j]->scale.y / 2)
		//			&&
		//			// �v���C���[�̉E�[���n�ʂ̍��[�ɂ߂荞��
		//			(cSeika::numberOfObjects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cMoveGround::numberOfObjects[j]->position.x - GROUND_HORIZONTAL_SIZE * cMoveGround::numberOfObjects[j]->scale.x / 2)
		//			&&
		//			// �v���C���[�̍��[���n�ʂ̉E�[�ɂ߂荞��
		//			(cSeika::numberOfObjects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cMoveGround::numberOfObjects[j]->position.x + GROUND_HORIZONTAL_SIZE * cMoveGround::numberOfObjects[j]->scale.x / 2)
		//			)
		//		{
		//			// �ߋ��̈ʒu�����܂��Ă������։����o��
		//			if (cSeika::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cMoveGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cMoveGround::numberOfObjects[j]->scale.y / 2
		//				&&
		//				cSeika::numberOfObjects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cMoveGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cMoveGround::numberOfObjects[j]->scale.y / 2
		//				&&
		//				cSeika::numberOfObjects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f < cMoveGround::numberOfObjects[j]->position.x + GROUND_HORIZONTAL_SIZE * cMoveGround::numberOfObjects[j]->scale.x / 2
		//				&&
		//				cSeika::numberOfObjects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cMoveGround::numberOfObjects[j]->position.x - GROUND_HORIZONTAL_SIZE * cMoveGround::numberOfObjects[j]->scale.x / 2)
		//			{
		//				cSeika::numberOfObjects[i]->collision = COLLISION_GROUND;
		//				cSeika::numberOfObjects[i]->gravityTimer = 0;
		//				cSeika::numberOfObjects[i]->jumping = false;
		//				cSeika::numberOfObjects[i]->hitCeilingWhileJumping = false;
		//				cSeika::numberOfObjects[i]->position.y = cMoveGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE / 2 + PLAYER_VERTICAL_SIZE / 2 - 0.25f;
		//			}

		//			// �㔻��
		//			if (cSeika::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cMoveGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cMoveGround::numberOfObjects[j]->scale.y / 2)
		//			{
		//				cSeika::numberOfObjects[i]->collision = COLLISION_CEILING;
		//				cSeika::numberOfObjects[i]->hitCeilingWhileJumping = true;
		//				cSeika::numberOfObjects[i]->position.y = cSeika::numberOfObjects[i]->pastPosition.y;
		//			}
		//			// ������
		//			if ((cSeika::numberOfObjects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cMoveGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cMoveGround::numberOfObjects[j]->scale.y / 2))
		//			{
		//				cSeika::numberOfObjects[i]->collision = COLLISION_GROUND;
		//				cSeika::numberOfObjects[i]->gravityTimer = 0;
		//				cSeika::numberOfObjects[i]->jumping = false;
		//				cSeika::numberOfObjects[i]->hitCeilingWhileJumping = false;
		//				cSeika::numberOfObjects[i]->position.y = cSeika::numberOfObjects[i]->pastPosition.y;
		//			}

		//			// ������
		//			if (
		//				(cSeika::numberOfObjects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f
		//					<
		//					cMoveGround::numberOfObjects[j]->position.x - GROUND_HORIZONTAL_SIZE * cMoveGround::numberOfObjects[j]->scale.x / 2)
		//				||
		//				(cSeika::numberOfObjects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f
		//					>
		//					cMoveGround::numberOfObjects[j]->position.x + GROUND_HORIZONTAL_SIZE * cMoveGround::numberOfObjects[j]->scale.x / 2)
		//				)
		//			{
		//				cSeika::numberOfObjects[i]->collision = COLLISION_WALL;
		//				cSeika::numberOfObjects[i]->position.x = cSeika::numberOfObjects[i]->pastPosition.x;
		//			}

		//			cnt++;
		//		}
		//	}
		//	if (cSeika::numberOfObjects[i]->collision && cnt == 0)
		//	{
		//		cSeika::numberOfObjects[i]->collision = COLLISION_NONE;
		//	}
		//}

		// �f�o�b�O�ōŒᗎ������
		if (numberOfObjects[i]->position.y - SEIKA_VERTICAL_SIZE / 2 < -50.0f)
		{
			numberOfObjects[i]->position.y = -50.0f + SEIKA_VERTICAL_SIZE / 2;
			numberOfObjects[i]->collision = COLLISION_GROUND;
			numberOfObjects[i]->jumping = false;
			numberOfObjects[i]->hitCeilingWhileJumping = false;
			numberOfObjects[i]->jumped = true;
			numberOfObjects[i]->gravityTimer = 0;
		}
		/*PrintDebugProc("���΂̎���@%d\n", numberOfObjects[i]->owner);
		PrintDebugProc("���΂��󒆁@%d\n", numberOfObjects[i]->jumping);
		PrintDebugProc("���΂������@%d\n", numberOfObjects[i]->hitCeilingWhileJumping);
		PrintDebugProc("���΂��n�ʁ@%d\n", numberOfObjects[i]->jumped);
		PrintDebugProc("���΂̈ʒu�@%d\n", (int)numberOfObjects[i]->position.y);*/
	}
}

//�|���S���̕`��
void cSeika::Draw()
{
	DrawDebugProc();

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);

		D3DXMatrixScaling(&scaleMatrix, numberOfObjects[i]->scale.x, numberOfObjects[i]->scale.y, numberOfObjects[i]->scale.z);
		D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &scaleMatrix);
		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, numberOfObjects[i]->rotation.y, numberOfObjects[i]->rotation.x, numberOfObjects[i]->rotation.z);
		D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &rotationMatrix);
		D3DXMatrixTranslation(&translationMatrix, numberOfObjects[i]->position.x, numberOfObjects[i]->position.y, numberOfObjects[i]->position.z);
		D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &translationMatrix);

		pDevice->SetTransform(D3DTS_WORLD, &numberOfObjects[i]->worldMatrix);

		pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));
		pDevice->SetFVF(FVF_VERTEX_3D);

		pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_SEIKA));
		pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,
			0,
			2
		);
	}

}