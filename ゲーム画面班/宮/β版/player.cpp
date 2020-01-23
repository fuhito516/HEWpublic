
#include"common.h"
#include"player.h"
#include"ground.h"
#include"bridge.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"debugproc.h"

cPlayer* cPlayer::numberOfObjects[NUMBER_OF_PLAYER];

LPDIRECT3DVERTEXBUFFER9 cPlayer::pVertexBuffer;
VERTEX_3D*				cPlayer::pVertex;
LPDIRECT3DVERTEXBUFFER9 cPlayer::pVertexBuffer_ya;
VERTEX_3D*				cPlayer::pVertex_ya;

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
	InitDebugProc();

	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		// �w��v���C���[���L���̈���m��
		numberOfObjects[i] = new cPlayer;

		// �O�t���[���̈ʒu�Ə�����̈ʒu(�����ʒu)
		numberOfObjects[i]->pastPosition = D3DXVECTOR2(PLAYER_INITIAL_POSITION_X, PLAYER_INITIAL_POSITION_Y);

		// �ړ�����
		numberOfObjects[i]->directionVertical = DIRECTION_NONE;
		numberOfObjects[i]->pastDirectionHorizontal = numberOfObjects[i]->directionHorizontal = DIRECTION_RIGHT;

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

		// ���΂𓊂��郂�[�h
		numberOfObjects[i]->throwMode = false;
		// ���Εێ�
		numberOfObjects[i]->retention = true;
		// ���΂̓��������
		numberOfObjects[i]->throwDegree = 45;

		// �`��
		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);
		numberOfObjects[i]->position = D3DXVECTOR3(PLAYER_INITIAL_POSITION_X, PLAYER_INITIAL_POSITION_Y, 0);
		numberOfObjects[i]->rotation = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->scale = D3DXVECTOR3(1, 1, 1);

		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix_ya);
		numberOfObjects[i]->position_ya = D3DXVECTOR3(PLAYER_INITIAL_POSITION_X, PLAYER_INITIAL_POSITION_Y, 0);
		numberOfObjects[i]->rotation_ya = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->scale_ya = D3DXVECTOR3(1, 1, 1);
	}

	SetVertex();

}
// �I��
void cPlayer::Uninit()
{
	UninitDebugProc();

	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		delete numberOfObjects[i];
	}
}
// �X�V
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
			numberOfObjects[i]->pastDirectionHorizontal = numberOfObjects[i]->directionHorizontal = DIRECTION_LEFT;
			// �ʒux
			numberOfObjects[i]->position.x -= PLAYER_MOVEMENT_SPEED;
		}
		if (GetKeyboardPress(DIK_D))
		{
			// ����
			numberOfObjects[i]->pastDirectionHorizontal = numberOfObjects[i]->directionHorizontal = DIRECTION_RIGHT;
			// �ʒux
			numberOfObjects[i]->position.x += PLAYER_MOVEMENT_SPEED;
		}
		// �ړ����ĂȂ��Ƃ�
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

		// �����郂�[�h�ڍs
		PrintDebugProc("���΂𓊂��郂�[�h�@%d\n", numberOfObjects[i]->throwMode);
		if (GetKeyboardTrigger(DIK_T) && numberOfObjects[i]->retention)
		{
			numberOfObjects[i]->throwMode = !numberOfObjects[i]->throwMode;
		}
		if ( numberOfObjects[i]->throwMode )
		{
			if (GetKeyboardPress(DIK_W))
			{
				numberOfObjects[i]->throwDegree++;
			}
			if (GetKeyboardPress(DIK_S))
			{
				numberOfObjects[i]->throwDegree--;
			}
			// �p�x����
			if (numberOfObjects[i]->throwDegree > 90)
			{
				numberOfObjects[i]->throwDegree = 90;
			}
			if (numberOfObjects[i]->throwDegree < 0)
			{
				numberOfObjects[i]->throwDegree = 0;
			}

			// ��p�x
			if (numberOfObjects[i]->pastDirectionHorizontal == DIRECTION_LEFT)
			{
				numberOfObjects[i]->rotation_ya.z = D3DXToRadian(180 - numberOfObjects[i]->throwDegree);
			}
			else
			{
				numberOfObjects[i]->rotation_ya.z = D3DXToRadian(numberOfObjects[i]->throwDegree);
			}

			//PrintDebugProc("���΂𓊂�������@%d�x\n", numberOfObjects[i]->throwDegree);

			if (GetKeyboardTrigger(DIK_G))
			{
				numberOfObjects[i]->retention = false;
				numberOfObjects[i]->throwMode = false;
			}
		}

		// �d�͎���
		numberOfObjects[i]->gravityTimer += 1.0f / FRAME_PER_SECOND;

		// �W�����v���ł̈ړ�
		if ( numberOfObjects[i]->jumping)
		{
			// ������̑J�ڂ����� && �W�����v���V��֓������Ă��Ȃ�
			if (
				PLAYER_JUMPPOWER - GRAVITY * numberOfObjects[i]->gravityTimer > 0
				&& !numberOfObjects[i]->hitCeilingWhileJumping
				)
			{
				// ����
				numberOfObjects[i]->directionVertical = DIRECTION_UP;
				// �ʒu
				numberOfObjects[i]->position.y +=
					PLAYER_JUMPPOWER - GRAVITY * numberOfObjects[i]->gravityTimer;
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
				if (PLAYER_JUMPPOWER - GRAVITY * numberOfObjects[i]->gravityTimer < -PLAYER_MAXIMUM_FALLSPEED)
				{
					numberOfObjects[i]->position.y -= PLAYER_MAXIMUM_FALLSPEED;
				}
				else
				{
					numberOfObjects[i]->position.y +=
						PLAYER_JUMPPOWER - GRAVITY * numberOfObjects[i]->gravityTimer;
				}
			}
		}
		// �W�����v���ł͂Ȃ� && �n�ʂƂ̓����蔻�肪�Ȃ�
		else if (!numberOfObjects[i]->jumping && numberOfObjects[i]->collision != COLLISION_GROUND)
		{
			numberOfObjects[i]->directionVertical = DIRECTION_DOWN;

			numberOfObjects[i]->position.y -= PLAYER_MAXIMUM_FALLSPEED;
		}
		// ����
		numberOfObjects[i]->position.y -= 0.01f;

		// �����蔻��
		int cnt = 0;
		// �n�ʂƂ̓����蔻��
		for (int j = 0; j < NUMBER_OF_GROUND; j++)
		{
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
					// �ߋ��̈ʒu�����܂��Ă������։����o��
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
						cPlayer::numberOfObjects[i]->position.y = cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE / 2 + PLAYER_VERTICAL_SIZE / 2 - 0.25f;
					}

					// �㔻��
					if (cPlayer::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_CEILING;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = true;
						//cPlayer::numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->pastPosition.y;
						cPlayer::numberOfObjects[i]->position.y = cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2 - PLAYER_VERTICAL_SIZE / 2;
					}
					// ������
					if ((cPlayer::numberOfObjects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2))
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_GROUND;
						cPlayer::numberOfObjects[i]->gravityTimer = 0;
						cPlayer::numberOfObjects[i]->jumping = false;
						cPlayer::numberOfObjects[i]->jumpPossible = true;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = false;
						//cPlayer::numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->pastPosition.y;
						cPlayer::numberOfObjects[i]->position.y = cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2 + PLAYER_VERTICAL_SIZE / 2;
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
		}
		// ���Ƃ̓����蔻��
		for (int j = 0; j < NUMBER_OF_BRIDGE; j++)
		{
			if ( cBridge::numberOfObjects[j]->turnOn )
			{
				// �v���C���[��numberOfObjects[j]�͈̔͂ɂ߂荞��ł��鎞
				if (
					// �v���C���[�̑����n�ʂ̏�ɂ߂荞��
					(cPlayer::numberOfObjects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cBridge::numberOfObjects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.y / 2)
					&&
					// �v���C���[�̓����n�ʂ̉��ɂ߂荞��
					(cPlayer::numberOfObjects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cBridge::numberOfObjects[j]->bridgePosition.y - BRIDGE_VERTICAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.y / 2)
					&&
					// �v���C���[�̉E�[���n�ʂ̍��[�ɂ߂荞��
					(cPlayer::numberOfObjects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cBridge::numberOfObjects[j]->bridgePosition.x - BRIDGE_HORIZONTAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.x / 2)
					&&
					// �v���C���[�̍��[���n�ʂ̉E�[�ɂ߂荞��
					(cPlayer::numberOfObjects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cBridge::numberOfObjects[j]->bridgePosition.x + BRIDGE_HORIZONTAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.x / 2)
					)
				{
					// �ߋ��̈ʒu�����܂��Ă������։����o��
					if (cPlayer::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cBridge::numberOfObjects[j]->bridgePosition.y - BRIDGE_VERTICAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.y / 2
						&&
						cPlayer::numberOfObjects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cBridge::numberOfObjects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.y / 2
						&&
						cPlayer::numberOfObjects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f < cBridge::numberOfObjects[j]->bridgePosition.x + BRIDGE_HORIZONTAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.x / 2
						&&
						cPlayer::numberOfObjects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cBridge::numberOfObjects[j]->bridgePosition.x - BRIDGE_HORIZONTAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.x / 2)
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_BRIDGE;
						cPlayer::numberOfObjects[i]->gravityTimer = 0;
						cPlayer::numberOfObjects[i]->jumping = false;
						cPlayer::numberOfObjects[i]->jumpPossible = true;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = false;
						cPlayer::numberOfObjects[i]->position.y = cBridge::numberOfObjects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE / 2 + PLAYER_VERTICAL_SIZE / 2 - 0.25f;
					}

					// �㔻��
					if (cPlayer::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cBridge::numberOfObjects[j]->bridgePosition.y - BRIDGE_VERTICAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.y / 2)
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_CEILING;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = true;
						cPlayer::numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->pastPosition.y;
					}
					// ������
					if ((cPlayer::numberOfObjects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cBridge::numberOfObjects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.y / 2))
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_BRIDGE;
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
							cBridge::numberOfObjects[j]->bridgePosition.x - BRIDGE_HORIZONTAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.x / 2)
						||
						(cPlayer::numberOfObjects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f
							>
							cBridge::numberOfObjects[j]->bridgePosition.x + BRIDGE_HORIZONTAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.x / 2)
						)
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_WALL;
						cPlayer::numberOfObjects[i]->position.x = cPlayer::numberOfObjects[i]->pastPosition.x;
					}

					cnt++;
				}
			}
		}

		if (cnt == 0)
		{
			cPlayer::numberOfObjects[i]->collision = COLLISION_NONE;
		}

		numberOfObjects[i]->position_ya = numberOfObjects[i]->position;

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
		//PrintDebugProc("���ΕۗL�@%d\n", numberOfObjects[i]->retention);
	}
}
// �`��
void cPlayer::Draw()
{
	DrawDebugProc();

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
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

		pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_BABY));
		pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,
			0,
			2
		);

		if ( numberOfObjects[i]->throwMode )
		{
			D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix_ya);
			D3DXMatrixIdentity(&scaleMatrix);
			D3DXMatrixIdentity(&rotationMatrix);
			D3DXMatrixIdentity(&translationMatrix);

			D3DXMatrixScaling(&scaleMatrix, numberOfObjects[i]->scale_ya.x, numberOfObjects[i]->scale_ya.y, numberOfObjects[i]->scale_ya.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix_ya, &numberOfObjects[i]->worldMatrix_ya, &scaleMatrix);

			D3DXMatrixRotationYawPitchRoll(&rotationMatrix, numberOfObjects[i]->rotation_ya.y, numberOfObjects[i]->rotation_ya.x, numberOfObjects[i]->rotation_ya.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix_ya, &numberOfObjects[i]->worldMatrix_ya, &rotationMatrix);

			D3DXMatrixTranslation(&translationMatrix, numberOfObjects[i]->position_ya.x, numberOfObjects[i]->position_ya.y, numberOfObjects[i]->position_ya.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix_ya, &numberOfObjects[i]->worldMatrix_ya, &translationMatrix);

			pDevice->SetTransform(D3DTS_WORLD, &numberOfObjects[i]->worldMatrix_ya);

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