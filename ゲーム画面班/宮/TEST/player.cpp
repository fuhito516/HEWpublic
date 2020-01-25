
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

// 頂点設定
void cPlayer::SetVertex()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	// プレイヤー
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

	pVertex[0].vtx = D3DXVECTOR3(-PLAYER_HORIZONTAL_SIZE / 2, -PLAYER_VERTICAL_SIZE / 2, 0.0f);	// 左下
	pVertex[1].vtx = D3DXVECTOR3(-PLAYER_HORIZONTAL_SIZE / 2, PLAYER_VERTICAL_SIZE / 2, 0.0f);	// 左上
	pVertex[2].vtx = D3DXVECTOR3(PLAYER_HORIZONTAL_SIZE / 2, -PLAYER_VERTICAL_SIZE / 2, 0.0f);	// 右下
	pVertex[3].vtx = D3DXVECTOR3(PLAYER_HORIZONTAL_SIZE / 2, PLAYER_VERTICAL_SIZE / 2, 0.0f);	// 右上
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

	// 矢
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

	pVertex_ya[0].vtx = D3DXVECTOR3(0, -YA_VERTICAL_SIZE / 2, 0.0f);	// 左下
	pVertex_ya[1].vtx = D3DXVECTOR3(0, YA_VERTICAL_SIZE / 2, 0.0f);	// 左上
	pVertex_ya[2].vtx = D3DXVECTOR3(YA_HORIZONTAL_SIZE, -YA_VERTICAL_SIZE / 2, 0.0f);	// 右下
	pVertex_ya[3].vtx = D3DXVECTOR3(YA_HORIZONTAL_SIZE, YA_VERTICAL_SIZE / 2, 0.0f);	// 右上
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

// 初期化
void cPlayer::Init()
{
	InitDebugProc();

	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		// 指定プレイヤー数記憶領域を確保
		numberOfObjects[i] = new cPlayer;

		// 前フレームの位置と処理後の位置(初期位置)
		numberOfObjects[i]->pastPosition = D3DXVECTOR2(PLAYER_INITIAL_POSITION_X, PLAYER_INITIAL_POSITION_Y);

		// 移動方向
		numberOfObjects[i]->directionVertical = DIRECTION_NONE;
		numberOfObjects[i]->pastDirectionHorizontal = numberOfObjects[i]->directionHorizontal = DIRECTION_RIGHT;

		// ジャンプ可能判定
		numberOfObjects[i]->jumpPossible = false;
		// ジャンプ中判定
		numberOfObjects[i]->jumping = false;
		// ジャンプ最中の天井への当たり判定
		numberOfObjects[i]->hitCeilingWhileJumping = false;

		// 重力カウンター
		numberOfObjects[i]->gravityTimer = 0;

		// 当たり判定(何に当たっているのか)
		numberOfObjects[i]->collision = COLLISION_NONE;

		// 聖火を投げるモード
		numberOfObjects[i]->throwMode = false;
		// 聖火保持
		numberOfObjects[i]->retention = true;
		// 聖火の投げる方向
		numberOfObjects[i]->throwDegree = 45;

		// 描画
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
// 終了
void cPlayer::Uninit()
{
	UninitDebugProc();

	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		delete numberOfObjects[i];
	}
}
// 更新
void cPlayer::Update()
{
	UpdateDebugProc();

	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		// 位置保管
		numberOfObjects[i]->pastPosition.x = numberOfObjects[i]->position.x;
		numberOfObjects[i]->pastPosition.y = numberOfObjects[i]->position.y;
	
		// 左移動
		if (GetKeyboardPress(DIK_A))
		{
			// 方向
			numberOfObjects[i]->pastDirectionHorizontal = numberOfObjects[i]->directionHorizontal = DIRECTION_LEFT;
			// 位置x
			numberOfObjects[i]->position.x -= PLAYER_MOVEMENT_SPEED;
		}
		if (GetKeyboardPress(DIK_D))
		{
			// 方向
			numberOfObjects[i]->pastDirectionHorizontal = numberOfObjects[i]->directionHorizontal = DIRECTION_RIGHT;
			// 位置x
			numberOfObjects[i]->position.x += PLAYER_MOVEMENT_SPEED;
		}
		// 移動してないとき
		if (!GetKeyboardPress(DIK_A) && !GetKeyboardPress(DIK_D))
		{
			// 方向
			numberOfObjects[i]->directionHorizontal = DIRECTION_NONE;
		}
		if (GetKeyboardPress(DIK_SPACE) && numberOfObjects[i]->jumpPossible)
		{
			// 方向
			numberOfObjects[i]->directionVertical = DIRECTION_UP;

			numberOfObjects[i]->jumpPossible = false;
			numberOfObjects[i]->jumping = true;
		}

		// 投げるモード移行
		PrintDebugProc("聖火を投げるモード　%d\n", numberOfObjects[i]->throwMode);
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
			// 角度制御
			if (numberOfObjects[i]->throwDegree > 90)
			{
				numberOfObjects[i]->throwDegree = 90;
			}
			if (numberOfObjects[i]->throwDegree < 0)
			{
				numberOfObjects[i]->throwDegree = 0;
			}

			// 矢角度
			if (numberOfObjects[i]->pastDirectionHorizontal == DIRECTION_LEFT)
			{
				numberOfObjects[i]->rotation_ya.z = D3DXToRadian(180 - numberOfObjects[i]->throwDegree);
			}
			else
			{
				numberOfObjects[i]->rotation_ya.z = D3DXToRadian(numberOfObjects[i]->throwDegree);
			}

			//PrintDebugProc("聖火を投げる方向　%d度\n", numberOfObjects[i]->throwDegree);

			if (GetKeyboardTrigger(DIK_G))
			{
				numberOfObjects[i]->retention = false;
				numberOfObjects[i]->throwMode = false;
			}
		}

		// 重力時間
		numberOfObjects[i]->gravityTimer += 1.0f / FRAME_PER_SECOND;

		// ジャンプ中での移動
		if ( numberOfObjects[i]->jumping)
		{
			// 上方向の遷移が強い && ジャンプ中天井へ当たっていない
			if (
				PLAYER_JUMPPOWER - GRAVITY * numberOfObjects[i]->gravityTimer > 0
				&& !numberOfObjects[i]->hitCeilingWhileJumping
				)
			{
				// 方向
				numberOfObjects[i]->directionVertical = DIRECTION_UP;
				// 位置
				numberOfObjects[i]->position.y +=
					PLAYER_JUMPPOWER - GRAVITY * numberOfObjects[i]->gravityTimer;
			}
			// ジャンプ中天井へ当たった
			else if (numberOfObjects[i]->hitCeilingWhileJumping)
			{
				// 方向
				numberOfObjects[i]->directionVertical = DIRECTION_DOWN;
				// 位置
				numberOfObjects[i]->position.y -= PLAYER_MAXIMUM_FALLSPEED;
			}
			// ジャンプ中で下遷移が強い
			else
			{
				// 方向
				numberOfObjects[i]->directionVertical = DIRECTION_DOWN;

				// 最高落下速度を上回った
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
		// ジャンプ中ではない && 地面との当たり判定がない
		else if (!numberOfObjects[i]->jumping && numberOfObjects[i]->collision != COLLISION_GROUND)
		{
			numberOfObjects[i]->directionVertical = DIRECTION_DOWN;

			numberOfObjects[i]->position.y -= PLAYER_MAXIMUM_FALLSPEED;
		}
		// 調整
		numberOfObjects[i]->position.y -= 0.01f;

		// 当たり判定
		int cnt = 0;
		// 地面との当たり判定
		for (int j = 0; j < NUMBER_OF_GROUND; j++)
		{
			if (cGround::numberOfObjects[j]->use)
			{
				// プレイヤーがnumberOfObjects[j]の範囲にめり込んでいる時
				if (
					// プレイヤーの足が地面の上にめり込む
					(cPlayer::numberOfObjects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
					&&
					// プレイヤーの頭が地面の下にめり込む
					(cPlayer::numberOfObjects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
					&&
					// プレイヤーの右端が地面の左端にめり込む
					(cPlayer::numberOfObjects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cGround::numberOfObjects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2)
					&&
					// プレイヤーの左端が地面の右端にめり込む
					(cPlayer::numberOfObjects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cGround::numberOfObjects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2)
					)
				{
					// 過去の位置が埋まっていたら上へ押し出す
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

					// 上判定
					if (cPlayer::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_CEILING;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = true;
						//cPlayer::numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->pastPosition.y;
						cPlayer::numberOfObjects[i]->position.y = cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2 - PLAYER_VERTICAL_SIZE / 2;
					}
					// 下判定
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

					// 横判定
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
		// 橋との当たり判定
		for (int j = 0; j < NUMBER_OF_BRIDGE; j++)
		{
			if ( cBridge::numberOfObjects[j]->turnOn )
			{
				// プレイヤーがnumberOfObjects[j]の範囲にめり込んでいる時
				if (
					// プレイヤーの足が地面の上にめり込む
					(cPlayer::numberOfObjects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cBridge::numberOfObjects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.y / 2)
					&&
					// プレイヤーの頭が地面の下にめり込む
					(cPlayer::numberOfObjects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cBridge::numberOfObjects[j]->bridgePosition.y - BRIDGE_VERTICAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.y / 2)
					&&
					// プレイヤーの右端が地面の左端にめり込む
					(cPlayer::numberOfObjects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cBridge::numberOfObjects[j]->bridgePosition.x - BRIDGE_HORIZONTAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.x / 2)
					&&
					// プレイヤーの左端が地面の右端にめり込む
					(cPlayer::numberOfObjects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cBridge::numberOfObjects[j]->bridgePosition.x + BRIDGE_HORIZONTAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.x / 2)
					)
				{
					// 過去の位置が埋まっていたら上へ押し出す
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

					// 上判定
					if (cPlayer::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cBridge::numberOfObjects[j]->bridgePosition.y - BRIDGE_VERTICAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.y / 2)
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_CEILING;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = true;
						cPlayer::numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->pastPosition.y;
					}
					// 下判定
					if ((cPlayer::numberOfObjects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cBridge::numberOfObjects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE * cBridge::numberOfObjects[j]->bridgeScale.y / 2))
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_BRIDGE;
						cPlayer::numberOfObjects[i]->gravityTimer = 0;
						cPlayer::numberOfObjects[i]->jumping = false;
						cPlayer::numberOfObjects[i]->jumpPossible = true;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = false;
						cPlayer::numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->pastPosition.y;
					}

					// 横判定
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

		// デバッグで最低落下制御
		if (numberOfObjects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < -50.0f)
		{
			numberOfObjects[i]->position.y = -50.0f + PLAYER_VERTICAL_SIZE / 2 - 0.25f;
			numberOfObjects[i]->collision = COLLISION_GROUND;
			numberOfObjects[i]->jumping = false;
			numberOfObjects[i]->jumpPossible = true;
			numberOfObjects[i]->hitCeilingWhileJumping = false;
			numberOfObjects[i]->gravityTimer = 0;
		}
		//PrintDebugProc("聖火保有　%d\n", numberOfObjects[i]->retention);
	}
}
// 描画
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