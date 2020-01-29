
#include"common.h"
#include"player.h"
#include"ground.h"
#include"Moveground.h"
#include"bridge.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"debugproc.h"


//�A�j���[�V��������
#define ANIMATION_SECOND (0.8f)
#define NUMBER_OF_SHEETS (11)

cPlayer* cPlayer::objects[NUMBER_OF_PLAYER];

LPDIRECT3DVERTEXBUFFER9 cPlayer::pVertexBuffer;
VERTEX_3D*				cPlayer::pVertex;
LPDIRECT3DVERTEXBUFFER9 cPlayer::pVertexBuffer_ya;
VERTEX_3D*				cPlayer::pVertex_ya;

// �A�j���[�V����
static int frame = 0;
static float second = 0;
static float animation_seconds = 0;
static const float secondPerSheet = ANIMATION_SECOND / NUMBER_OF_SHEETS;

// �R���X�g���N�^
cPlayer::cPlayer(D3DXVECTOR3 _position)
{
	// �O�t���[���̈ʒu�Ə�����̈ʒu(�����ʒu)
	pastPosition = D3DXVECTOR2(PLAYER_INITIAL_POSITION_X, PLAYER_INITIAL_POSITION_Y);

	// �ړ�����
	directionVertical = DIRECTION_NONE;
	pastDirectionHorizontal = directionHorizontal = DIRECTION_RIGHT;

	// �W�����v
	jumpPossible = false;
	jumping = false;
	hitCeilingWhileJumping = false;

	// �d�̓^�C�}�[
	gravityTimer = 0;

	// �Փ�
	collision = COLLISION_NONE;

	// ����
	throwMode = false;
	retention = true;
	throwDegree = 45;

	// �`��
	frameAnimation = 0;

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

	// �A�j���[�V����
	frame = 0;
	second = 0;
	animation_seconds = 0;

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
				frame++;

				// ����
				objects[i]->pastDirectionHorizontal = objects[i]->directionHorizontal = DIRECTION_LEFT;
				// �ʒux
				objects[i]->position.x -= PLAYER_MOVEMENT_SPEED;
			}
			if (GetKeyboardPress(DIK_D))
			{
				frame++;

				// ����
				objects[i]->pastDirectionHorizontal = objects[i]->directionHorizontal = DIRECTION_RIGHT;
				// �ʒux
				objects[i]->position.x += PLAYER_MOVEMENT_SPEED;
			}

			// �A�j���[�V����
			second = (float)frame / (float)FRAME_PER_SECOND;
			animation_seconds = ((int)(second * 100) % (int)(100 * ANIMATION_SECOND)) / 100.0f;

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
				if (cGround::objects[j] != NULL)
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
			}
			// ���Ƃ̓����蔻��
			for (int j = 0; j < NUMBER_OF_BRIDGE; j++)
			{
				if (cBridge::objects[j] != NULL)
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
			}

			//==========================================================================================================
			// �c�ړ��������蔻��
			//===========================================================================================================

			for (int j = 0; j < NUMBER_OF_GROUND_MOVE; j++)
			{

				if (cVerticalMoveGround::objects[j] != NULL)
				{
					if (cVerticalMoveGround::objects[j]->use)
					{
						if (cVerticalMoveGround::objects[j]->use)
						{
							// �v���C���[��MovenumberOfObjects[j]�͈̔͂ɂ߂荞��ł��鎞
							if (
								// �v���C���[�̑����n�ʂ̏�ɂ߂荞��
								(cPlayer::objects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cVerticalMoveGround::objects[j]->Mposition.y + GROUND_VERTICAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.y / 2)
								&&
								// �v���C���[�̓����n�ʂ̉��ɂ߂荞��
								(cPlayer::objects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cVerticalMoveGround::objects[j]->Mposition.y - GROUND_VERTICAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.y / 2)
								&&
								// �v���C���[�̉E�[���n�ʂ̍��[�ɂ߂荞��
								(cPlayer::objects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cVerticalMoveGround::objects[j]->Mposition.x - GROUND_HORIZONTAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.x / 2)
								&&
								// �v���C���[�̍��[���n�ʂ̉E�[�ɂ߂荞��
								(cPlayer::objects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cVerticalMoveGround::objects[j]->Mposition.x + GROUND_HORIZONTAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.x / 2)
								)
							{

								cPlayer::objects[i]->collision = COLLISION_GROUND;
								cPlayer::objects[i]->gravityTimer = 0;
								cPlayer::objects[i]->jumping = false;
								cPlayer::objects[i]->jumpPossible = true;
								cPlayer::objects[i]->hitCeilingWhileJumping = false;
								cPlayer::objects[i]->pastPosition.y = cVerticalMoveGround::objects[j]->Mposition.y + GROUND_VERTICAL_SIZE / 2 + PLAYER_VERTICAL_SIZE / 2 + 0.30f;
								cPlayer::objects[i]->position.y = cPlayer::objects[i]->pastPosition.y;

								//�����܂�
								// �㔻��
								if (cPlayer::objects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cVerticalMoveGround::objects[j]->Mposition.y - GROUND_VERTICAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.y / 2 + cVerticalMoveGround::objects[j]->spead)

								{
									cPlayer::objects[i]->collision = COLLISION_CEILING;
									cPlayer::objects[i]->hitCeilingWhileJumping = true;
									cPlayer::objects[i]->position.y = cPlayer::objects[i]->pastPosition.y;
								}
								// ������
								if ((cPlayer::objects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cVerticalMoveGround::objects[j]->Mposition.y + GROUND_VERTICAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.y / 2))
								{
									cPlayer::objects[i]->collision = COLLISION_GROUND;
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
										cVerticalMoveGround::objects[j]->Mposition.x - GROUND_HORIZONTAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.x / 2)
									||
									(cPlayer::objects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f
										>
										cVerticalMoveGround::objects[j]->Mposition.x + GROUND_HORIZONTAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.x / 2)
									)
								{
									cPlayer::objects[i]->collision = COLLISION_WALL;
									cPlayer::objects[i]->position.x = cPlayer::objects[i]->pastPosition.x;
								}

								cnt++;
							}
						}
					}
				}
			}

				//======================================================================================================================
				// ���ړ��������蔻��
				//===================================================================================================================-==
			for (int j = 0; j < NUMBER_OF_GROUND_MOVE; j++)
			{
				if (cHorizontalMoveGround::objects[j] != NULL)
				{
					if (cHorizontalMoveGround::objects[j]->use)
					{
						int cnt = 0;
						if (cHorizontalMoveGround::objects[j]->use)
						{
							// �v���C���[��objects[j]�͈̔͂ɂ߂荞��ł��鎞
							if (
								// �v���C���[�̑����n�ʂ̏�ɂ߂荞��
								(cPlayer::objects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cHorizontalMoveGround::objects[j]->Mposition.y + GROUND_VERTICAL_SIZE * cHorizontalMoveGround::objects[j]->Mscale.y / 2)
								&&
								// �v���C���[�̓����n�ʂ̉��ɂ߂荞��
								(cPlayer::objects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cHorizontalMoveGround::objects[j]->Mposition.y - GROUND_VERTICAL_SIZE * cHorizontalMoveGround::objects[j]->Mscale.y / 2)
								&&
								// �v���C���[�̉E�[���n�ʂ̍��[�ɂ߂荞��
								(cPlayer::objects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cHorizontalMoveGround::objects[j]->Mposition.x - GROUND_HORIZONTAL_SIZE * cHorizontalMoveGround::objects[j]->Mscale.x / 2)
								&&
								// �v���C���[�̍��[���n�ʂ̉E�[�ɂ߂荞��
								(cPlayer::objects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cHorizontalMoveGround::objects[j]->Mposition.x + GROUND_HORIZONTAL_SIZE * cHorizontalMoveGround::objects[j]->Mscale.x / 2)
								)
							{
								//�ǉ��������蔻��
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
									cPlayer::objects[i]->position.y = cHorizontalMoveGround::objects[j]->Mposition.y + GROUND_VERTICAL_SIZE / 2 + PLAYER_VERTICAL_SIZE / 2 - 0.25f;

								}

								//�����܂ł��������̓����蔻��I


								// �㔻��
								if (cPlayer::objects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cHorizontalMoveGround::objects[j]->Mposition.y - GROUND_VERTICAL_SIZE * cHorizontalMoveGround::objects[j]->Mscale.y / 2)
								{
									cPlayer::objects[i]->collision = COLLISION_CEILING;
									cPlayer::objects[i]->hitCeilingWhileJumping = true;
									cPlayer::objects[i]->position.y = cPlayer::objects[i]->pastPosition.y;
								}
								// ������
								if ((cPlayer::objects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cHorizontalMoveGround::objects[j]->Mposition.y + GROUND_VERTICAL_SIZE * cHorizontalMoveGround::objects[j]->Mscale.y / 2))
								{
									cPlayer::objects[i]->collision = COLLISION_GROUND;
									cPlayer::objects[i]->gravityTimer = 0;
									cPlayer::objects[i]->jumping = false;
									cPlayer::objects[i]->jumpPossible = true;
									cPlayer::objects[i]->hitCeilingWhileJumping = false;
									cPlayer::objects[i]->position.y = cPlayer::objects[i]->pastPosition.y;
								}

								// ������
								//�u���b�N����
								if (
									(cPlayer::objects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 - 0.8f
										<
										cHorizontalMoveGround::objects[j]->Mposition.x - cHorizontalMoveGround::objects[j]->Mscale.x / 2
										&& cHorizontalMoveGround::objects[j]->Mposition.y + cHorizontalMoveGround::objects[j]->Mscale.y / 2>cPlayer::objects[i]->pastPosition.y + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f)
									||
									//�u���b�N�E��
									(cPlayer::objects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 + 0.8f
									>
										cHorizontalMoveGround::objects[j]->Mposition.x + cHorizontalMoveGround::objects[j]->Mscale.x / 2
										&& cHorizontalMoveGround::objects[j]->Mposition.y - cHorizontalMoveGround::objects[j]->Mscale.y / 2 > cPlayer::objects[i]->pastPosition.y - PLAYER_HORIZONTAL_SIZE / 2 - 0.8f)
									)
								{
									cPlayer::objects[i]->collision = COLLISION_WALL;
									//�ǉ��n�ʂ̃|�W�V�����[�v���C���[�̃|�W�V�������������Ƃŋ��������߂鏈��
									D3DXVECTOR3 distance = cHorizontalMoveGround::objects[j]->Mposition - cPlayer::objects[i]->position;
									//�P�ʃx�N�g��
									//D3DXVec3Normalize���P�ʃx�N�g���ɂ���֐�
									D3DXVec3Normalize(&distance, &distance);
									cPlayer::objects[i]->position -= distance * 0.3f;
								}

								cnt++;
							}
						}
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
			SetVertex();

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

			// �A�j���[�V����
			if (objects[i]->pastDirectionHorizontal == DIRECTION_RIGHT)
			{
				pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_R1));
			}
			if (objects[i]->pastDirectionHorizontal == DIRECTION_LEFT)
			{
				pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_L1));
			}

			//�E
			if (objects[i]->directionHorizontal == DIRECTION_RIGHT)
			{
				if (animation_seconds >= secondPerSheet * 0 && animation_seconds < secondPerSheet * 1)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_R1));
				}
				if (animation_seconds >= secondPerSheet * 1 && animation_seconds < secondPerSheet * 2)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_R2));
				}
				if (animation_seconds >= secondPerSheet * 2 && animation_seconds < secondPerSheet * 3)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_R3));
				}
				if (animation_seconds >= secondPerSheet * 3 && animation_seconds < secondPerSheet * 4)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_R4));
				}
				if (animation_seconds >= secondPerSheet * 4 && animation_seconds < secondPerSheet * 5)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_R5));
				}
				if (animation_seconds >= secondPerSheet * 5 && animation_seconds < secondPerSheet * 6)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_R6));
				}
				if (animation_seconds >= secondPerSheet * 6 && animation_seconds < secondPerSheet * 7)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_R7));
				}
				if (animation_seconds >= secondPerSheet * 7 && animation_seconds < secondPerSheet * 8)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_R8));
				}
				if (animation_seconds >= secondPerSheet * 8 && animation_seconds < secondPerSheet * 9)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_R9));
				}
				if (animation_seconds >= secondPerSheet * 9 && animation_seconds < secondPerSheet * 10)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_R10));
				}
				if (animation_seconds >= secondPerSheet * 10 && animation_seconds < secondPerSheet * 11)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_R11));
				}
			}
			//��
			if (objects[i]->directionHorizontal == DIRECTION_LEFT)
			{
				if (animation_seconds >= secondPerSheet * 0 && animation_seconds < secondPerSheet * 1)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_L1));
				}
				if (animation_seconds >= secondPerSheet * 1 && animation_seconds < secondPerSheet * 2)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_L2));
				}
				if (animation_seconds >= secondPerSheet * 2 && animation_seconds < secondPerSheet * 3)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_L3));
				}
				if (animation_seconds >= secondPerSheet * 3 && animation_seconds < secondPerSheet * 4)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_L4));
				}
				if (animation_seconds >= secondPerSheet * 4 && animation_seconds < secondPerSheet * 5)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_L5));
				}
				if (animation_seconds >= secondPerSheet * 5 && animation_seconds < secondPerSheet * 6)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_L6));
				}
				if (animation_seconds >= secondPerSheet * 6 && animation_seconds < secondPerSheet * 7)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_L7));
				}
				if (animation_seconds >= secondPerSheet * 7 && animation_seconds < secondPerSheet * 8)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_L8));
				}
				if (animation_seconds >= secondPerSheet * 8 && animation_seconds < secondPerSheet * 9)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_L9));
				}
				if (animation_seconds >= secondPerSheet * 9 && animation_seconds < secondPerSheet * 10)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_L10));
				}
				if (animation_seconds >= secondPerSheet * 10 && animation_seconds < secondPerSheet * 11)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_PLAYER_L11));
				}
			}

			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				2
			);
			// �A�j���[�V����
			objects[i]->frameAnimation++;

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