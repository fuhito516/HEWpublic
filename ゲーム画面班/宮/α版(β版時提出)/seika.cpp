
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

//頂点セット関数
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

//初期化
void cSeika::Init()
{
	InitDebugProc();

	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		numberOfObjects[i] = new cSeika;

		// 持主
		numberOfObjects[i]->owner = i;

		// 移動方向
		numberOfObjects[i]->directionVertical = DIRECTION_NONE;
		numberOfObjects[i]->directionHorizontal = DIRECTION_DOWN;

		// ジャンプ中判定
		numberOfObjects[i]->jumping = false;
		// ジャンプ最中の天井への当たり判定
		numberOfObjects[i]->hitCeilingWhileJumping = false;
		// ジャンプ済判定
		numberOfObjects[i]->jumped = false;

		// 重力カウンター
		numberOfObjects[i]->gravityTimer = 0;

		// 当たり判定(何に当たっているのか)
		numberOfObjects[i]->collision = COLLISION_NONE;

		// 前フレームの位置と処理後の位置(初期位置)
		numberOfObjects[i]->pastPosition.x = cPlayer::numberOfObjects[i]->position.x + SEIKA_HORIZONTAL_SIZE / 2;
		numberOfObjects[i]->pastPosition.y = cPlayer::numberOfObjects[i]->position.y + SEIKA_VERTICAL_SIZE / 2;

		numberOfObjects[i]->position = D3DXVECTOR3(numberOfObjects[i]->pastPosition.x, numberOfObjects[i]->pastPosition.y, 0);
		numberOfObjects[i]->rotation = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->scale = D3DXVECTOR3(1, 1, 1);
		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);
	}

	SetVertex();
}

//終了処理
void cSeika::Uninit()
{
	UninitDebugProc();

	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		delete numberOfObjects[i];
	}
}

//更新処理
void cSeika::Update()
{
	UpdateDebugProc();

	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		// 位置保管
		numberOfObjects[i]->pastPosition.x = numberOfObjects[i]->position.x;
		numberOfObjects[i]->pastPosition.y = numberOfObjects[i]->position.y;

		// プレイヤーが聖火保持中
		if (cPlayer::numberOfObjects[i]->retention)
		{
			numberOfObjects[i]->gravityTimer = 0;

			// プレイヤーが左へ移動中
			if (cPlayer::numberOfObjects[i]->pastDirectionHorizontal == DIRECTION_LEFT)
			{
				// 方向
				numberOfObjects[i]->directionHorizontal = DIRECTION_LEFT;
				// 位置x
				numberOfObjects[i]->position.x = cPlayer::numberOfObjects[i]->position.x - SEIKA_HORIZONTAL_SIZE / 2;
			}
			// プレイヤーが右へ移動中
			if (cPlayer::numberOfObjects[i]->pastDirectionHorizontal == DIRECTION_RIGHT)
			{
				// 方向
				numberOfObjects[i]->directionHorizontal = DIRECTION_RIGHT;
				// 位置x
				numberOfObjects[i]->position.x = cPlayer::numberOfObjects[i]->position.x + SEIKA_HORIZONTAL_SIZE / 2;
			}

			// 位置y
			numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->position.y + SEIKA_HORIZONTAL_SIZE / 2;
		}

		// プレイヤーが聖火を保持せず、地面にも接したことがない
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
		
		// プレイヤーが保持していないとき
		if (!cPlayer::numberOfObjects[i]->retention)
		{
			// 落ちたあと && 地面との当たり判定がない
			if (
				numberOfObjects[i]->jumped
				&&
				numberOfObjects[i]->collision != COLLISION_GROUND
				)
			{
				numberOfObjects[i]->directionVertical = DIRECTION_DOWN;
				numberOfObjects[i]->position.y -= SEIKA_MAXSPEED;
			}

			// 空中での移動
			if (numberOfObjects[i]->jumping)
			{
				// ！変更中！
				// 重力時間
				numberOfObjects[i]->gravityTimer += 1.0f / FRAME_PER_SECOND;

				// 横移動
				if (numberOfObjects[i]->directionHorizontal == DIRECTION_LEFT)
				{
					numberOfObjects[i]->position.x -= SEIKA_MOVEMENT_SPEED * (float)cos(D3DXToRadian((double)cPlayer::numberOfObjects[numberOfObjects[i]->owner]->throwDegree));
				}
				if (numberOfObjects[i]->directionHorizontal == DIRECTION_RIGHT)
				{
					numberOfObjects[i]->position.x += SEIKA_MOVEMENT_SPEED * (float)cos(D3DXToRadian((double)cPlayer::numberOfObjects[numberOfObjects[i]->owner]->throwDegree));
				}

				// 縦移動
				// ジャンプ中天井へ当たっていない
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

					// 最高速度を上回った
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
				// ジャンプ中天井へ当たった
				else
				{
					numberOfObjects[i]->directionVertical = DIRECTION_DOWN;
					numberOfObjects[i]->position.y -= SEIKA_MAXSPEED;
				}
			}

			// プレイヤーとの当たり判定
			if (cSeika::numberOfObjects[i]->jumped)
			{
				for (int j = 0; j < NUMBER_OF_PLAYER; j++)
				{
					if (!cPlayer::numberOfObjects[j]->retention)
					{
						// プレイヤーがnumberOfObjects[i]の範囲にめり込んでいる時
						if (
							// プレイヤーの足が聖火の上にめり込む
							(cPlayer::numberOfObjects[j]->position.y - PLAYER_VERTICAL_SIZE / 2 < cSeika::numberOfObjects[i]->position.y + SEIKA_VERTICAL_SIZE * cSeika::numberOfObjects[i]->scale.y / 2)
							&&
							// プレイヤーの頭が聖火の下にめり込む
							(cPlayer::numberOfObjects[j]->position.y + PLAYER_VERTICAL_SIZE / 2 > cSeika::numberOfObjects[i]->position.y - SEIKA_VERTICAL_SIZE * cSeika::numberOfObjects[i]->scale.y / 2)
							&&
							// プレイヤーの右端が聖火の左端にめり込む
							(cPlayer::numberOfObjects[j]->position.x + PLAYER_HORIZONTAL_SIZE / 2 > cSeika::numberOfObjects[i]->position.x - SEIKA_HORIZONTAL_SIZE * cSeika::numberOfObjects[i]->scale.x / 2)
							&&
							// プレイヤーの左端が聖火の右端にめり込む
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

			// 調整
			numberOfObjects[i]->position.y -= 0.001f;

			// 地面との当たり判定
			for (int j = 0; j < NUMBER_OF_GROUND; j++)
			{
				int cnt = 0;
				if (cGround::numberOfObjects[j]->use)
				{
					// 聖火がnumberOfObjects[j]の範囲にめり込んでいる時
					if (
						// 聖火の足が地面の上にめり込む
						(cSeika::numberOfObjects[i]->position.y - SEIKA_VERTICAL_SIZE / 2 < cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
						&&
						// 聖火の頭が地面の下にめり込む
						(cSeika::numberOfObjects[i]->position.y + SEIKA_VERTICAL_SIZE / 2 > cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
						&&
						// 聖火の右端が地面の左端にめり込む
						(cSeika::numberOfObjects[i]->position.x + SEIKA_HORIZONTAL_SIZE / 2 > cGround::numberOfObjects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2)
						&&
						// 聖火の左端が地面の右端にめり込む
						(cSeika::numberOfObjects[i]->position.x - SEIKA_VERTICAL_SIZE / 2 < cGround::numberOfObjects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::numberOfObjects[j]->scale.x / 2)
						)
					{
						// 過去の位置が埋まっていたら上へ押し出す
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

						// 上判定
						if (cSeika::numberOfObjects[i]->pastPosition.y + SEIKA_VERTICAL_SIZE / 2 < cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
						{
							cSeika::numberOfObjects[i]->collision = COLLISION_CEILING;
							cSeika::numberOfObjects[i]->hitCeilingWhileJumping = true;

							cSeika::numberOfObjects[i]->position.y = numberOfObjects[0]->pastPosition.y;
						}
						// 下判定
						if ((cSeika::numberOfObjects[i]->pastPosition.y - SEIKA_VERTICAL_SIZE / 2 > cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2))
						{
							cSeika::numberOfObjects[i]->collision = COLLISION_GROUND;
							cSeika::numberOfObjects[i]->gravityTimer = 0;
							cSeika::numberOfObjects[i]->jumping = false;
							cSeika::numberOfObjects[i]->hitCeilingWhileJumping = false;
							cSeika::numberOfObjects[i]->jumped = true;

							cSeika::numberOfObjects[i]->position.y = numberOfObjects[0]->pastPosition.y;
						}

						// 左右判定
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

		//// 動く地面との当たり判定
		//for (int j = 0; j < NUMBER_OF_GROUND; j++)
		//{
		//	int cnt = 0;
		//	if (cMoveGround::numberOfObjects[j]->use)
		//	{
		//		// プレイヤーがnumberOfObjects[j]の範囲にめり込んでいる時
		//		if (
		//			// プレイヤーの足が地面の上にめり込む
		//			(cSeika::numberOfObjects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cMoveGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cMoveGround::numberOfObjects[j]->scale.y / 2)
		//			&&
		//			// プレイヤーの頭が地面の下にめり込む
		//			(cSeika::numberOfObjects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cMoveGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cMoveGround::numberOfObjects[j]->scale.y / 2)
		//			&&
		//			// プレイヤーの右端が地面の左端にめり込む
		//			(cSeika::numberOfObjects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cMoveGround::numberOfObjects[j]->position.x - GROUND_HORIZONTAL_SIZE * cMoveGround::numberOfObjects[j]->scale.x / 2)
		//			&&
		//			// プレイヤーの左端が地面の右端にめり込む
		//			(cSeika::numberOfObjects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cMoveGround::numberOfObjects[j]->position.x + GROUND_HORIZONTAL_SIZE * cMoveGround::numberOfObjects[j]->scale.x / 2)
		//			)
		//		{
		//			// 過去の位置が埋まっていたら上へ押し出す
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

		//			// 上判定
		//			if (cSeika::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cMoveGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cMoveGround::numberOfObjects[j]->scale.y / 2)
		//			{
		//				cSeika::numberOfObjects[i]->collision = COLLISION_CEILING;
		//				cSeika::numberOfObjects[i]->hitCeilingWhileJumping = true;
		//				cSeika::numberOfObjects[i]->position.y = cSeika::numberOfObjects[i]->pastPosition.y;
		//			}
		//			// 下判定
		//			if ((cSeika::numberOfObjects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cMoveGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cMoveGround::numberOfObjects[j]->scale.y / 2))
		//			{
		//				cSeika::numberOfObjects[i]->collision = COLLISION_GROUND;
		//				cSeika::numberOfObjects[i]->gravityTimer = 0;
		//				cSeika::numberOfObjects[i]->jumping = false;
		//				cSeika::numberOfObjects[i]->hitCeilingWhileJumping = false;
		//				cSeika::numberOfObjects[i]->position.y = cSeika::numberOfObjects[i]->pastPosition.y;
		//			}

		//			// 横判定
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

		// デバッグで最低落下制御
		if (numberOfObjects[i]->position.y - SEIKA_VERTICAL_SIZE / 2 < -50.0f)
		{
			numberOfObjects[i]->position.y = -50.0f + SEIKA_VERTICAL_SIZE / 2;
			numberOfObjects[i]->collision = COLLISION_GROUND;
			numberOfObjects[i]->jumping = false;
			numberOfObjects[i]->hitCeilingWhileJumping = false;
			numberOfObjects[i]->jumped = true;
			numberOfObjects[i]->gravityTimer = 0;
		}
		/*PrintDebugProc("聖火の持主　%d\n", numberOfObjects[i]->owner);
		PrintDebugProc("聖火が空中　%d\n", numberOfObjects[i]->jumping);
		PrintDebugProc("聖火が屋根　%d\n", numberOfObjects[i]->hitCeilingWhileJumping);
		PrintDebugProc("聖火が地面　%d\n", numberOfObjects[i]->jumped);
		PrintDebugProc("聖火の位置　%d\n", (int)numberOfObjects[i]->position.y);*/
	}
}

//ポリゴンの描画
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