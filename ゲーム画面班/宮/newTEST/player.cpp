
#include"common.h"
#include"player.h"
#include"ground.h"
#include"bridge.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"debugproc.h"

cPlayer* cPlayer::objects[NUMBER_OF_PLAYER];

LPDIRECT3DVERTEXBUFFER9 cPlayer::pVertexBuffer;
VERTEX_3D*				cPlayer::pVertex;
LPDIRECT3DVERTEXBUFFER9 cPlayer::pVertexBuffer_ya;
VERTEX_3D*				cPlayer::pVertex_ya;

// �R���X�g���N�^
cPlayer::cPlayer(D3DXVECTOR3 _position)
{
	// �O�t���[���̈ʒu�Ə�����̈ʒu(�����ʒu)
	pastPosition = D3DXVECTOR2(PLAYER_INITIAL_POSITION_X, PLAYER_INITIAL_POSITION_Y);

	// �ړ�����
	directionVertical = DIRECTION_NONE;
	pastDirectionHorizontal = directionHorizontal = DIRECTION_RIGHT;

	// �W�����v�\����
	jumpPossible = false;
	// �W�����v������
	jumping = false;
	// �W�����v�Œ��̓V��ւ̓����蔻��
	hitCeilingWhileJumping = false;

	// �d�̓J�E���^�[
	gravityTimer = 0;

	// �����蔻��(���ɓ������Ă���̂�)
	collision = COLLISION_NONE;

	// ���΂𓊂��郂�[�h
	throwMode = false;
	// ���Εێ�
	retention = true;
	// ���΂̓��������
	throwDegree = 45;

	// �`��
	D3DXMatrixIdentity(&worldMatrix);
	position = D3DXVECTOR3(PLAYER_INITIAL_POSITION_X, PLAYER_INITIAL_POSITION_Y, 0);
	rotation = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(1, 1, 1);

	D3DXMatrixIdentity(&worldMatrix_ya);
	position_ya = D3DXVECTOR3(PLAYER_INITIAL_POSITION_X, PLAYER_INITIAL_POSITION_Y, 0);
	rotation_ya = D3DXVECTOR3(0, 0, 0);
	scale_ya = D3DXVECTOR3(1, 1, 1);
}

// ���_�ݒ�
void cPlayer::SetVertex()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	// �v���C���[
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

	pVertex[0].vtx = D3DXVECTOR3(-PLAYER_HORIZONTAL_SIZE / 2, -PLAYER_VERTICAL_SIZE / 2, 0.0f);	// ����
	pVertex[1].vtx = D3DXVECTOR3(-PLAYER_HORIZONTAL_SIZE / 2, PLAYER_VERTICAL_SIZE / 2, 0.0f);	// ����
	pVertex[2].vtx = D3DXVECTOR3(PLAYER_HORIZONTAL_SIZE / 2, -PLAYER_VERTICAL_SIZE / 2, 0.0f);	// �E��
	pVertex[3].vtx = D3DXVECTOR3(PLAYER_HORIZONTAL_SIZE / 2, PLAYER_VERTICAL_SIZE / 2, 0.0f);	// �E��
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

	// ��
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVertexBuffer_ya,
		NULL
	);

	pVertexBuffer_ya->Lock(0, 0, (void**)&pVertex_ya, 0);

	pVertex_ya[0].vtx = D3DXVECTOR3(0, -YA_VERTICAL_SIZE / 2, 0.0f);	// ����
	pVertex_ya[1].vtx = D3DXVECTOR3(0, YA_VERTICAL_SIZE / 2, 0.0f);	// ����
	pVertex_ya[2].vtx = D3DXVECTOR3(YA_HORIZONTAL_SIZE, -YA_VERTICAL_SIZE / 2, 0.0f);	// �E��
	pVertex_ya[3].vtx = D3DXVECTOR3(YA_HORIZONTAL_SIZE, YA_VERTICAL_SIZE / 2, 0.0f);	// �E��
	for (int i = 0; i < 4; i++)
	{
		pVertex_ya[i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}
	for (int i = 0; i < 4; i++)
	{
		pVertex_ya[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	pVertex_ya[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVertex_ya[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVertex_ya[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVertex_ya[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVertexBuffer_ya->Unlock();
}

// ������
void cPlayer::Init()
{
	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		objects[i] = NULL;
	}

	SetVertex();
}
// �I��
void cPlayer::Uninit()
{
	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		if (objects[i] != NULL)
		{
			delete objects[i];
			objects[i] = NULL;
		}
	}
}
// �X�V
void cPlayer::Update()
{
	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		if (objects[i] != NULL)
		{
			// �ʒu�ۊ�
			objects[i]->pastPosition.x = objects[i]->position.x;
			objects[i]->pastPosition.y = objects[i]->position.y;

			// ���ړ�
			if (GetKeyboardPress(DIK_A))
			{
				// ����
				objects[i]->pastDirectionHorizontal = objects[i]->directionHorizontal = DIRECTION_LEFT;
				// �ʒux
				objects[i]->position.x -= PLAYER_MOVEMENT_SPEED;
			}
			if (GetKeyboardPress(DIK_D))
			{
				// ����
				objects[i]->pastDirectionHorizontal = objects[i]->directionHorizontal = DIRECTION_RIGHT;
				// �ʒux
				objects[i]->position.x += PLAYER_MOVEMENT_SPEED;
			}
			// �ړ����ĂȂ��Ƃ�
			if (!GetKeyboardPress(DIK_A) && !GetKeyboardPress(DIK_D))
			{
				// ����
				objects[i]->directionHorizontal = DIRECTION_NONE;
			}
			if (GetKeyboardPress(DIK_SPACE) && objects[i]->jumpPossible)
			{
				// ����
				objects[i]->directionVertical = DIRECTION_UP;

				objects[i]->jumpPossible = false;
				objects[i]->jumping = true;
			}

			// �����郂�[�h�ڍs
			PrintDebugProc("���΂𓊂��郂�[�h�@%d\n", objects[i]->throwMode);
			if (GetKeyboardTrigger(DIK_T) && objects[i]->retention)
			{
				objects[i]->throwMode = !objects[i]->throwMode;
			}
			if (objects[i]->throwMode)
			{
				if (GetKeyboardPress(DIK_W))
				{
					objects[i]->throwDegree++;
				}
				if (GetKeyboardPress(DIK_S))
				{
					objects[i]->throwDegree--;
				}
				// �p�x����
				if (objects[i]->throwDegree > 90)
				{
					objects[i]->throwDegree = 90;
				}
				if (objects[i]->throwDegree < 0)
				{
					objects[i]->throwDegree = 0;
				}

				// ��p�x
				if (objects[i]->pastDirectionHorizontal == DIRECTION_LEFT)
				{
					objects[i]->rotation_ya.z = D3DXToRadian(180 - objects[i]->throwDegree);
				}
				else
				{
					objects[i]->rotation_ya.z = D3DXToRadian(objects[i]->throwDegree);
				}

				//PrintDebugProc("���΂𓊂�������@%d�x\n", objects[i]->throwDegree);

				if (GetKeyboardTrigger(DIK_G))
				{
					objects[i]->retention = false;
					objects[i]->throwMode = false;
				}
			}

			// �d�͎���
			objects[i]->gravityTimer += 1.0f / FRAME_PER_SECOND;

			// �W�����v���ł̈ړ�
			if (objects[i]->jumping)
			{
				// ������̑J�ڂ����� && �W�����v���V��֓������Ă��Ȃ�
				if (
					PLAYER_JUMPPOWER - GRAVITY * objects[i]->gravityTimer > 0
					&& !objects[i]->hitCeilingWhileJumping
					)
				{
					// ����
					objects[i]->directionVertical = DIRECTION_UP;
					// �ʒu
					objects[i]->position.y +=
						PLAYER_JUMPPOWER - GRAVITY * objects[i]->gravityTimer;
				}
				// �W�����v���V��֓�������
				else if (objects[i]->hitCeilingWhileJumping)
				{
					// ����
					objects[i]->directionVertical = DIRECTION_DOWN;
					// �ʒu
					objects[i]->position.y -= PLAYER_MAXIMUM_FALLSPEED;
				}
				// �W�����v���ŉ��J�ڂ�����
				else
				{
					// ����
					objects[i]->directionVertical = DIRECTION_DOWN;

					// �ō��������x��������
					if (PLAYER_JUMPPOWER - GRAVITY * objects[i]->gravityTimer < -PLAYER_MAXIMUM_FALLSPEED)
					{
						objects[i]->position.y -= PLAYER_MAXIMUM_FALLSPEED;
					}
					else
					{
						objects[i]->position.y +=
							PLAYER_JUMPPOWER - GRAVITY * objects[i]->gravityTimer;
					}
				}
			}
			// �W�����v���ł͂Ȃ� && �n�ʂƂ̓����蔻�肪�Ȃ�
			else if (!objects[i]->jumping && objects[i]->collision != COLLISION_GROUND)
			{
				objects[i]->directionVertical = DIRECTION_DOWN;

				objects[i]->position.y -= PLAYER_MAXIMUM_FALLSPEED;
			}
			// ����
			objects[i]->position.y -= 0.01f;

			// �����蔻��
			int cnt = 0;
			// �n�ʂƂ̓����蔻��
			for (int j = 0; j < NUMBER_OF_GROUND; j++)
			{
				if (cGround::objects[j]->use)
				{
					// �v���C���[��objects[j]�͈̔͂ɂ߂荞��ł��鎞
					if (
						// �v���C���[�̑����n�ʂ̏�ɂ߂荞��
						(cPlayer::objects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cGround::objects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2)
						&&
						// �v���C���[�̓����n�ʂ̉��ɂ߂荞��
						(cPlayer::objects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cGround::objects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2)
						&&
						// �v���C���[�̉E�[���n�ʂ̍��[�ɂ߂荞��
						(cPlayer::objects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cGround::objects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2)
						&&
						// �v���C���[�̍��[���n�ʂ̉E�[�ɂ߂荞��
						(cPlayer::objects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cGround::objects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2)
						)
					{
						// �ߋ��̈ʒu�����܂��Ă������։����o��
						if (cPlayer::objects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cGround::objects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2
							&&
							cPlayer::objects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cGround::objects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2
							&&
							cPlayer::objects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f < cGround::objects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2
							&&
							cPlayer::objects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cGround::objects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2)
						{
							cPlayer::objects[i]->collision = COLLISION_GROUND;
							cPlayer::objects[i]->gravityTimer = 0;
							cPlayer::objects[i]->jumping = false;
							cPlayer::objects[i]->jumpPossible = true;
							cPlayer::objects[i]->hitCeilingWhileJumping = false;
							cPlayer::objects[i]->position.y = cGround::objects[j]->position.y + GROUND_VERTICAL_SIZE / 2 + PLAYER_VERTICAL_SIZE / 2 - 0.25f;
						}

						// �㔻��
						if (cPlayer::objects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cGround::objects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2)
						{
							cPlayer::objects[i]->collision = COLLISION_CEILING;
							cPlayer::objects[i]->hitCeilingWhileJumping = true;
							//cPlayer::objects[i]->position.y = cPlayer::objects[i]->pastPosition.y;
							cPlayer::objects[i]->position.y = cGround::objects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2 - PLAYER_VERTICAL_SIZE / 2;
						}
						// ������
						if ((cPlayer::objects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cGround::objects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2))
						{
							cPlayer::objects[i]->collision = COLLISION_GROUND;
							cPlayer::objects[i]->gravityTimer = 0;
							cPlayer::objects[i]->jumping = false;
							cPlayer::objects[i]->jumpPossible = true;
							cPlayer::objects[i]->hitCeilingWhileJumping = false;
							//cPlayer::objects[i]->position.y = cPlayer::objects[i]->pastPosition.y;
							cPlayer::objects[i]->position.y = cGround::objects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2 + PLAYER_VERTICAL_SIZE / 2;
						}

						// ������
						if (
							(cPlayer::objects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f
								<
								cGround::objects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2)
							||
							(cPlayer::objects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f
								>
								cGround::objects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2)
							)
						{
							cPlayer::objects[i]->collision = COLLISION_WALL;
							cPlayer::objects[i]->position.x = cPlayer::objects[i]->pastPosition.x;
						}

						cnt++;
					}
				}
			}
			// ���Ƃ̓����蔻��
			for (int j = 0; j < NUMBER_OF_BRIDGE; j++)
			{
				if (cBridge::objects[j]->collision)
				{
					// �v���C���[��objects[j]�͈̔͂ɂ߂荞��ł��鎞
					if (
						// �v���C���[�̑����n�ʂ̏�ɂ߂荞��
						(cPlayer::objects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cBridge::objects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE * cBridge::objects[j]->bridgeScale.y / 2)
						&&
						// �v���C���[�̓����n�ʂ̉��ɂ߂荞��
						(cPlayer::objects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cBridge::objects[j]->bridgePosition.y - BRIDGE_VERTICAL_SIZE * cBridge::objects[j]->bridgeScale.y / 2)
						&&
						// �v���C���[�̉E�[���n�ʂ̍��[�ɂ߂荞��
						(cPlayer::objects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cBridge::objects[j]->bridgePosition.x - BRIDGE_HORIZONTAL_SIZE * cBridge::objects[j]->bridgeScale.x / 2)
						&&
						// �v���C���[�̍��[���n�ʂ̉E�[�ɂ߂荞��
						(cPlayer::objects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cBridge::objects[j]->bridgePosition.x + BRIDGE_HORIZONTAL_SIZE * cBridge::objects[j]->bridgeScale.x / 2)
						)
					{
						// �ߋ��̈ʒu�����܂��Ă������։����o��
						if (cPlayer::objects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cBridge::objects[j]->bridgePosition.y - BRIDGE_VERTICAL_SIZE * cBridge::objects[j]->bridgeScale.y / 2
							&&
							cPlayer::objects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cBridge::objects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE * cBridge::objects[j]->bridgeScale.y / 2
							&&
							cPlayer::objects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f < cBridge::objects[j]->bridgePosition.x + BRIDGE_HORIZONTAL_SIZE * cBridge::objects[j]->bridgeScale.x / 2
							&&
							cPlayer::objects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cBridge::objects[j]->bridgePosition.x - BRIDGE_HORIZONTAL_SIZE * cBridge::objects[j]->bridgeScale.x / 2)
						{
							cPlayer::objects[i]->collision = COLLISION_BRIDGE;
							cPlayer::objects[i]->gravityTimer = 0;
							cPlayer::objects[i]->jumping = false;
							cPlayer::objects[i]->jumpPossible = true;
							cPlayer::objects[i]->hitCeilingWhileJumping = false;
							cPlayer::objects[i]->position.y = cBridge::objects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE / 2 + PLAYER_VERTICAL_SIZE / 2 - 0.25f;
						}

						// �㔻��
						if (cPlayer::objects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cBridge::objects[j]->bridgePosition.y - BRIDGE_VERTICAL_SIZE * cBridge::objects[j]->bridgeScale.y / 2)
						{
							cPlayer::objects[i]->collision = COLLISION_CEILING;
							cPlayer::objects[i]->hitCeilingWhileJumping = true;
							cPlayer::objects[i]->position.y = cPlayer::objects[i]->pastPosition.y;
						}
						// ������
						if ((cPlayer::objects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cBridge::objects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE * cBridge::objects[j]->bridgeScale.y / 2))
						{
							cPlayer::objects[i]->collision = COLLISION_BRIDGE;
							cPlayer::objects[i]->gravityTimer = 0;
							cPlayer::objects[i]->jumping = false;
							cPlayer::objects[i]->jumpPossible = true;
							cPlayer::objects[i]->hitCeilingWhileJumping = false;
							cPlayer::objects[i]->position.y = cPlayer::objects[i]->pastPosition.y;
						}

						// ������
						if (
							(cPlayer::objects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f
								<
								cBridge::objects[j]->bridgePosition.x - BRIDGE_HORIZONTAL_SIZE * cBridge::objects[j]->bridgeScale.x / 2)
							||
							(cPlayer::objects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f
								>
								cBridge::objects[j]->bridgePosition.x + BRIDGE_HORIZONTAL_SIZE * cBridge::objects[j]->bridgeScale.x / 2)
							)
						{
							cPlayer::objects[i]->collision = COLLISION_WALL;
							cPlayer::objects[i]->position.x = cPlayer::objects[i]->pastPosition.x;
						}

						cnt++;
					}
				}
			}

			if (cnt == 0)
			{
				cPlayer::objects[i]->collision = COLLISION_NONE;
			}

			objects[i]->position_ya = objects[i]->position;

			// �f�o�b�O�ōŒᗎ������
			if (objects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < -50.0f)
			{
				objects[i]->position.y = -50.0f + PLAYER_VERTICAL_SIZE / 2 - 0.25f;
				objects[i]->collision = COLLISION_GROUND;
				objects[i]->jumping = false;
				objects[i]->jumpPossible = true;
				objects[i]->hitCeilingWhileJumping = false;
				objects[i]->gravityTimer = 0;
			}
			//PrintDebugProc("���ΕۗL�@%d\n", objects[i]->retention);
		}
	}
}
// �`��
void cPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		if (objects[i] != NULL)
		{
			D3DXMatrixIdentity(&objects[i]->worldMatrix);

			D3DXMatrixScaling(&scaleMatrix, objects[i]->scale.x, objects[i]->scale.y, objects[i]->scale.z);
			D3DXMatrixMultiply(&objects[i]->worldMatrix, &objects[i]->worldMatrix, &scaleMatrix);

			D3DXMatrixRotationYawPitchRoll(&rotationMatrix, objects[i]->rotation.y, objects[i]->rotation.x, objects[i]->rotation.z);
			D3DXMatrixMultiply(&objects[i]->worldMatrix, &objects[i]->worldMatrix, &rotationMatrix);

			D3DXMatrixTranslation(&translationMatrix, objects[i]->position.x, objects[i]->position.y, objects[i]->position.z);
			D3DXMatrixMultiply(&objects[i]->worldMatrix, &objects[i]->worldMatrix, &translationMatrix);

			pDevice->SetTransform(D3DTS_WORLD, &objects[i]->worldMatrix);

			pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));
			pDevice->SetFVF(FVF_VERTEX_3D);

			pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_BABY));
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				2
			);

			if (objects[i]->throwMode)
			{
				D3DXMatrixIdentity(&objects[i]->worldMatrix_ya);
				D3DXMatrixIdentity(&scaleMatrix);
				D3DXMatrixIdentity(&rotationMatrix);
				D3DXMatrixIdentity(&translationMatrix);

				D3DXMatrixScaling(&scaleMatrix, objects[i]->scale_ya.x, objects[i]->scale_ya.y, objects[i]->scale_ya.z);
				D3DXMatrixMultiply(&objects[i]->worldMatrix_ya, &objects[i]->worldMatrix_ya, &scaleMatrix);

				D3DXMatrixRotationYawPitchRoll(&rotationMatrix, objects[i]->rotation_ya.y, objects[i]->rotation_ya.x, objects[i]->rotation_ya.z);
				D3DXMatrixMultiply(&objects[i]->worldMatrix_ya, &objects[i]->worldMatrix_ya, &rotationMatrix);

				D3DXMatrixTranslation(&translationMatrix, objects[i]->position_ya.x, objects[i]->position_ya.y, objects[i]->position_ya.z);
				D3DXMatrixMultiply(&objects[i]->worldMatrix_ya, &objects[i]->worldMatrix_ya, &translationMatrix);

				pDevice->SetTransform(D3DTS_WORLD, &objects[i]->worldMatrix_ya);

				pDevice->SetStreamSource(0, pVertexBuffer_ya, 0, sizeof(VERTEX_3D));
				pDevice->SetFVF(FVF_VERTEX_3D);

				pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_YA));
				pDevice->DrawPrimitive
				(
					D3DPT_TRIANGLESTRIP,
					0,
					2
				);
			}
		}
	}
}

void cPlayer::Set(D3DXVECTOR3 _position)
{
	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		if (objects[i] == NULL)
		{
			objects[i] = new cPlayer(_position);
			break;
		}
	}
}