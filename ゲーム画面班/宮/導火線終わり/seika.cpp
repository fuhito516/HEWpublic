
// メイン
#include"seika.h"
#include"common.h"
#include"direct3d.h"
#include"texture.h"
#include"input.h"
#include"debugproc.h"
// 対象
#include"player.h"
#include"ground.h"
#include"Moveground.h"
#include"bridge.h"

cSeika* cSeika::objects[NUMBER_OF_SEIKA];

LPDIRECT3DVERTEXBUFFER9 cSeika::pVertexBuffer;
VERTEX_3D*				cSeika::pVertex;
LPDIRECT3DVERTEXBUFFER9 cSeika::pVertexBuffer_light;
VERTEX_3D*				cSeika::pVertex_light;

// コンストラクタ
cSeika::cSeika()
{
	// 持主
	owner = 0;

	// 移動方向
	directionVertical = DIRECTION_NONE;
	directionHorizontal = DIRECTION_DOWN;

	// ジャンプ
	jumping = false;
	hitCeilingWhileJumping = false;
	// ジャンプ済判定
	jumped = false;

	// 重力カウンター
	gravityTimer = 0;

	// 当たり判定(何に当たっているのか)
	collision = COLLISION_NONE;

	// 前フレームの位置と処理後の位置(初期位置)
	pastPosition.x = cPlayer::objects[0]->position.x + SEIKA_HORIZONTAL_SIZE / 2;
	pastPosition.y = cPlayer::objects[0]->position.y + SEIKA_VERTICAL_SIZE / 2;

	// 描画
	D3DXMatrixIdentity(&worldMatrix);
	position = D3DXVECTOR3(pastPosition.x, pastPosition.y, 0);
	rotation = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(1, 1, 1);
}

// 頂点
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

	// light
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVertexBuffer_light,
		NULL
	);

	pVertexBuffer_light->Lock(0, 0, (void**)&pVertex_light, 0);

	pVertex_light[0].vtx = D3DXVECTOR3(-SCREEN_WIDTH / 4, -SCREEN_WIDTH / 8, 0.0f);
	pVertex_light[1].vtx = D3DXVECTOR3(-SCREEN_WIDTH / 4, SCREEN_WIDTH / 8, 0.0f);
	pVertex_light[2].vtx = D3DXVECTOR3(SCREEN_WIDTH / 4, -SCREEN_WIDTH / 8, 0.0f);
	pVertex_light[3].vtx = D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_WIDTH / 8, 0.0f);
	for (int i = 0; i < 4; i++)
	{
		pVertex_light[i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}
	for (int i = 0; i < 4; i++)
	{
		pVertex_light[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	pVertex_light[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVertex_light[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVertex_light[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVertex_light[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	pVertexBuffer_light->Unlock();
}
// 初期化
void cSeika::Init()
{
	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		objects[i] = NULL;
	}

	SetVertex();
}

//終了処理
void cSeika::Uninit()
{
	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		if (objects != NULL)
		{
			delete objects[i];
			objects[i] = NULL;
		}
	}
}

//更新処理
void cSeika::Update()
{
	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		if (objects != NULL)
		{
			// 位置保管
			objects[i]->pastPosition.x = objects[i]->position.x;
			objects[i]->pastPosition.y = objects[i]->position.y;

			// プレイヤーが聖火保持中
			if (cPlayer::objects[i]->retention)
			{
				objects[i]->gravityTimer = 0;

				// プレイヤーが左へ移動中
				if (cPlayer::objects[i]->pastDirectionHorizontal == DIRECTION_LEFT)
				{
					// 方向
					objects[i]->directionHorizontal = DIRECTION_LEFT;
					// 位置x
					objects[i]->position.x = cPlayer::objects[i]->position.x - SEIKA_HORIZONTAL_SIZE / 2;
				}
				// プレイヤーが右へ移動中
				if (cPlayer::objects[i]->pastDirectionHorizontal == DIRECTION_RIGHT)
				{
					// 方向
					objects[i]->directionHorizontal = DIRECTION_RIGHT;
					// 位置x
					objects[i]->position.x = cPlayer::objects[i]->position.x + SEIKA_HORIZONTAL_SIZE / 2;
				}

				// 位置y
				objects[i]->position.y = cPlayer::objects[i]->position.y + SEIKA_HORIZONTAL_SIZE / 2;
			}

			// プレイヤーが聖火を保持せず、地面にも接したことがない
			if (
				!cPlayer::objects[i]->retention
				&&
				!objects[i]->jumped
				)
			{
				objects[i]->jumping = true;
			}
			else
			{
				objects[i]->jumping = false;
			}

			// プレイヤーが保持していないとき
			if (!cPlayer::objects[i]->retention)
			{
				// 落ちたあと && 地面との当たり判定がない
				if (
					objects[i]->jumped
					&&
					objects[i]->collision != COLLISION_GROUND
					)
				{
					objects[i]->directionVertical = DIRECTION_DOWN;
					objects[i]->position.y -= SEIKA_MAXSPEED;
				}

				// 空中での移動
				if (objects[i]->jumping)
				{
					// ！変更中！
					// 重力時間
					objects[i]->gravityTimer += 1.0f / FRAME_PER_SECOND;

					// 横移動
					if (objects[i]->directionHorizontal == DIRECTION_LEFT)
					{
						objects[i]->position.x -= SEIKA_MOVEMENT_SPEED * (float)cos(D3DXToRadian((double)cPlayer::objects[objects[i]->owner]->throwDegree));
					}
					if (objects[i]->directionHorizontal == DIRECTION_RIGHT)
					{
						objects[i]->position.x += SEIKA_MOVEMENT_SPEED * (float)cos(D3DXToRadian((double)cPlayer::objects[objects[i]->owner]->throwDegree));
					}

					// 縦移動
					// ジャンプ中天井へ当たっていない
					if (!objects[i]->hitCeilingWhileJumping)
					{
						if (SEIKA_MOVEMENT_SPEED * (float)sin(D3DXToRadian((double)cPlayer::objects[objects[i]->owner]->throwDegree)) - GRAVITY * objects[i]->gravityTimer > 0)
						{
							objects[i]->directionVertical = DIRECTION_UP;
						}
						else
						{
							objects[i]->directionVertical = DIRECTION_DOWN;
						}

						// 最高速度を上回った
						if (SEIKA_MOVEMENT_SPEED * (float)sin(D3DXToRadian((double)cPlayer::objects[objects[i]->owner]->throwDegree)) - GRAVITY * objects[i]->gravityTimer < -SEIKA_MAXSPEED)
						{
							objects[i]->position.y += -SEIKA_MAXSPEED;
						}
						else
						{
							objects[i]->position.y +=
								SEIKA_MOVEMENT_SPEED * (float)sin(D3DXToRadian((double)cPlayer::objects[objects[i]->owner]->throwDegree)) - GRAVITY * objects[i]->gravityTimer;
						}
					}
					// ジャンプ中天井へ当たった
					else
					{
						objects[i]->directionVertical = DIRECTION_DOWN;
						objects[i]->position.y -= SEIKA_MAXSPEED;
					}
				}

				// プレイヤーとの当たり判定
				if (cSeika::objects[i]->jumped)
				{
					for (int j = 0; j < NUMBER_OF_PLAYER; j++)
					{
						if (cPlayer::objects[j] != NULL)
						{
							if (!cPlayer::objects[j]->retention)
							{
								// プレイヤーがobjects[i]の範囲にめり込んでいる時
								if (
									// プレイヤーの足が聖火の上にめり込む
									(cPlayer::objects[j]->position.y - PLAYER_VERTICAL_SIZE / 2 < cSeika::objects[i]->position.y + SEIKA_VERTICAL_SIZE * cSeika::objects[i]->scale.y / 2)
									&&
									// プレイヤーの頭が聖火の下にめり込む
									(cPlayer::objects[j]->position.y + PLAYER_VERTICAL_SIZE / 2 > cSeika::objects[i]->position.y - SEIKA_VERTICAL_SIZE * cSeika::objects[i]->scale.y / 2)
									&&
									// プレイヤーの右端が聖火の左端にめり込む
									(cPlayer::objects[j]->position.x + PLAYER_HORIZONTAL_SIZE / 2 > cSeika::objects[i]->position.x - SEIKA_HORIZONTAL_SIZE * cSeika::objects[i]->scale.x / 2)
									&&
									// プレイヤーの左端が聖火の右端にめり込む
									(cPlayer::objects[j]->position.x - PLAYER_VERTICAL_SIZE / 2 < cSeika::objects[i]->position.x + SEIKA_HORIZONTAL_SIZE * cSeika::objects[i]->scale.x / 2)
									)
								{
									cPlayer::objects[j]->retention = true;
									cSeika::objects[i]->owner = j;
									cSeika::objects[i]->collision = COLLISION_PLAYER;
									cSeika::objects[i]->gravityTimer = 0;
									cSeika::objects[i]->jumping = false;
									cSeika::objects[i]->hitCeilingWhileJumping = false;
									cSeika::objects[i]->jumped = false;

									return;
								}
							}
						}
					}
				}

				// 調整
				objects[i]->position.y -= 0.001f;

				int cnt = 0;
				// 地面との当たり判定
				for (int j = 0; j < NUMBER_OF_GROUND; j++)
				{
					if (cGround::objects[j] != NULL)
					{
						if (cGround::objects[j]->use)
						{
							// 聖火がobjects[j]の範囲にめり込んでいる時
							if (
								// 聖火の足が地面の上にめり込む
								(cSeika::objects[i]->position.y - SEIKA_VERTICAL_SIZE / 2 < cGround::objects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2)
								&&
								// 聖火の頭が地面の下にめり込む
								(cSeika::objects[i]->position.y + SEIKA_VERTICAL_SIZE / 2 > cGround::objects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2)
								&&
								// 聖火の右端が地面の左端にめり込む
								(cSeika::objects[i]->position.x + SEIKA_HORIZONTAL_SIZE / 2 > cGround::objects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2)
								&&
								// 聖火の左端が地面の右端にめり込む
								(cSeika::objects[i]->position.x - SEIKA_VERTICAL_SIZE / 2 < cGround::objects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2)
								)
							{
								// 過去の位置が埋まっていたら上へ押し出す
								if (
									cSeika::objects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cGround::objects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2
									&&
									cSeika::objects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cGround::objects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2
									&&
									cSeika::objects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f < cGround::objects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2
									&&
									cSeika::objects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cGround::objects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2
									)
								{
									cSeika::objects[i]->collision = COLLISION_GROUND;
									cSeika::objects[i]->gravityTimer = 0;
									cSeika::objects[i]->jumping = false;
									cSeika::objects[i]->hitCeilingWhileJumping = false;
									cSeika::objects[i]->jumped = true;
									cSeika::objects[i]->position.y = cGround::objects[j]->position.y + GROUND_VERTICAL_SIZE / 2 + PLAYER_VERTICAL_SIZE / 2 - 0.25f;
								}

								// 上判定
								if (cSeika::objects[i]->pastPosition.y + SEIKA_VERTICAL_SIZE / 2 < cGround::objects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2)
								{
									cSeika::objects[i]->collision = COLLISION_CEILING;
									cSeika::objects[i]->hitCeilingWhileJumping = true;

									cSeika::objects[i]->position.y = objects[0]->pastPosition.y;
								}
								// 下判定
								if ((cSeika::objects[i]->pastPosition.y - SEIKA_VERTICAL_SIZE / 2 > cGround::objects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2))
								{
									cSeika::objects[i]->collision = COLLISION_GROUND;
									cSeika::objects[i]->gravityTimer = 0;
									cSeika::objects[i]->jumping = false;
									cSeika::objects[i]->hitCeilingWhileJumping = false;
									cSeika::objects[i]->jumped = true;

									cSeika::objects[i]->position.y = objects[0]->pastPosition.y;
								}

								// 左右判定
								if (
									(cSeika::objects[i]->pastPosition.x + SEIKA_HORIZONTAL_SIZE / 2 < cGround::objects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2)
									||
									(cSeika::objects[i]->pastPosition.x - SEIKA_HORIZONTAL_SIZE / 2 > cGround::objects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2)
									)
								{
									cSeika::objects[i]->collision = COLLISION_WALL;

									cSeika::objects[i]->position.x = objects[0]->pastPosition.x;
								}

								cnt++;
							}
						}
					}
				}

				// 橋との当たり判定
				for (int j = 0; j < NUMBER_OF_BRIDGE; j++)
				{
					if (cBridge::objects[j] != NULL)
					{
						if (cBridge::objects[j]->use)
						{
							// 聖火がobjects[j]の範囲にめり込んでいる時
							if (
								// 聖火の足が地面の上にめり込む
								(cSeika::objects[i]->position.y - SEIKA_VERTICAL_SIZE / 2 < cBridge::objects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE * cBridge::objects[j]->bridgeScale.y / 2)
								&&
								// 聖火の頭が地面の下にめり込む
								(cSeika::objects[i]->position.y + SEIKA_VERTICAL_SIZE / 2 > cBridge::objects[j]->bridgePosition.y - BRIDGE_VERTICAL_SIZE * cBridge::objects[j]->bridgeScale.y / 2)
								&&
								// 聖火の右端が地面の左端にめり込む
								(cSeika::objects[i]->position.x + SEIKA_HORIZONTAL_SIZE / 2 > cBridge::objects[j]->bridgePosition.x - BRIDGE_HORIZONTAL_SIZE * cBridge::objects[j]->bridgeScale.x / 2)
								&&
								// 聖火の左端が地面の右端にめり込む
								(cSeika::objects[i]->position.x - SEIKA_VERTICAL_SIZE / 2 < cBridge::objects[j]->bridgePosition.x + BRIDGE_HORIZONTAL_SIZE * cBridge::objects[j]->bridgeScale.x / 2)
								)
							{
								// 過去の位置が埋まっていたら上へ押し出す
								if (
									cSeika::objects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cBridge::objects[j]->bridgePosition.y - BRIDGE_VERTICAL_SIZE * cBridge::objects[j]->bridgeScale.y / 2
									&&
									cSeika::objects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cBridge::objects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE * cBridge::objects[j]->bridgeScale.y / 2
									&&
									cSeika::objects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f < cBridge::objects[j]->bridgePosition.x + BRIDGE_HORIZONTAL_SIZE * cBridge::objects[j]->bridgeScale.x / 2
									&&
									cSeika::objects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cBridge::objects[j]->bridgePosition.x - BRIDGE_HORIZONTAL_SIZE * cBridge::objects[j]->bridgeScale.x / 2
									)
								{
									cSeika::objects[i]->collision = COLLISION_BRIDGE;
									cSeika::objects[i]->gravityTimer = 0;
									cSeika::objects[i]->jumping = false;
									cSeika::objects[i]->hitCeilingWhileJumping = false;
									cSeika::objects[i]->jumped = true;
									cSeika::objects[i]->position.y = cBridge::objects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE / 2 + PLAYER_VERTICAL_SIZE / 2 - 0.25f;
								}

								// 上判定
								if (cSeika::objects[i]->pastPosition.y + SEIKA_VERTICAL_SIZE / 2 < cBridge::objects[j]->bridgePosition.y - BRIDGE_VERTICAL_SIZE * cBridge::objects[j]->bridgeScale.y / 2)
								{
									cSeika::objects[i]->collision = COLLISION_CEILING;
									cSeika::objects[i]->hitCeilingWhileJumping = true;

									cSeika::objects[i]->position.y = objects[0]->pastPosition.y;
								}
								// 下判定
								if ((cSeika::objects[i]->pastPosition.y - SEIKA_VERTICAL_SIZE / 2 > cBridge::objects[j]->bridgePosition.y + BRIDGE_VERTICAL_SIZE * cBridge::objects[j]->bridgeScale.y / 2))
								{
									cSeika::objects[i]->collision = COLLISION_BRIDGE;
									cSeika::objects[i]->gravityTimer = 0;
									cSeika::objects[i]->jumping = false;
									cSeika::objects[i]->hitCeilingWhileJumping = false;
									cSeika::objects[i]->jumped = true;

									cSeika::objects[i]->position.y = objects[0]->pastPosition.y;
								}

								// 左右判定
								if (
									(cSeika::objects[i]->pastPosition.x + SEIKA_HORIZONTAL_SIZE / 2 < cBridge::objects[j]->bridgePosition.x - BRIDGE_HORIZONTAL_SIZE * cBridge::objects[j]->bridgeScale.x / 2)
									||
									(cSeika::objects[i]->pastPosition.x - SEIKA_HORIZONTAL_SIZE / 2 > cBridge::objects[j]->bridgePosition.x + BRIDGE_HORIZONTAL_SIZE * cBridge::objects[j]->bridgeScale.x / 2)
									)
								{
									cSeika::objects[i]->collision = COLLISION_WALL;

									cSeika::objects[i]->position.x = objects[0]->pastPosition.x;
								}

								cnt++;
							}
						}
					}
				}

				//==========================================================================================================
				// 縦移動床当たり判定
				//===========================================================================================================

				for (int j = 0; j < NUMBER_OF_GROUND_MOVE; j++)
				{

					if (cVerticalMoveGround::objects[j] != NULL)
					{
						if (cVerticalMoveGround::objects[j]->use)
						{
							if (cVerticalMoveGround::objects[j]->use)
							{
								// プレイヤーがMovenumberOfObjects[j]の範囲にめり込んでいる時
								if (
									// プレイヤーの足が地面の上にめり込む
									(cSeika::objects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cVerticalMoveGround::objects[j]->Mposition.y + GROUND_VERTICAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.y / 2)
									&&
									// プレイヤーの頭が地面の下にめり込む
									(cSeika::objects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cVerticalMoveGround::objects[j]->Mposition.y - GROUND_VERTICAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.y / 2)
									&&
									// プレイヤーの右端が地面の左端にめり込む
									(cSeika::objects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cVerticalMoveGround::objects[j]->Mposition.x - GROUND_HORIZONTAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.x / 2)
									&&
									// プレイヤーの左端が地面の右端にめり込む
									(cSeika::objects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cVerticalMoveGround::objects[j]->Mposition.x + GROUND_HORIZONTAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.x / 2)
									)
								{

									cSeika::objects[i]->collision = COLLISION_GROUND;
									cSeika::objects[i]->gravityTimer = 0;
									cSeika::objects[i]->jumping = false;
									cSeika::objects[i]->jumped = true;
									cSeika::objects[i]->hitCeilingWhileJumping = false;
									cSeika::objects[i]->pastPosition.y = cVerticalMoveGround::objects[j]->Mposition.y + GROUND_VERTICAL_SIZE / 2 + PLAYER_VERTICAL_SIZE / 2 + 0.30f;
									cSeika::objects[i]->position.y = cSeika::objects[i]->pastPosition.y;

									//ここまで
									// 上判定
									if (cSeika::objects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cVerticalMoveGround::objects[j]->Mposition.y - GROUND_VERTICAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.y / 2 + cVerticalMoveGround::objects[j]->spead)

									{
										cSeika::objects[i]->collision = COLLISION_CEILING;
										cSeika::objects[i]->hitCeilingWhileJumping = true;
										cSeika::objects[i]->position.y = cSeika::objects[i]->pastPosition.y;
									}
									// 下判定
									if ((cSeika::objects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cVerticalMoveGround::objects[j]->Mposition.y + GROUND_VERTICAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.y / 2))
									{
										cSeika::objects[i]->collision = COLLISION_GROUND;
										cSeika::objects[i]->gravityTimer = 0;
										cSeika::objects[i]->jumping = false;
										cSeika::objects[i]->jumped = true;
										cSeika::objects[i]->hitCeilingWhileJumping = false;
										cSeika::objects[i]->position.y = cSeika::objects[i]->pastPosition.y;
									}

									// 横判定
									if (
										(cSeika::objects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f
											<
											cVerticalMoveGround::objects[j]->Mposition.x - GROUND_HORIZONTAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.x / 2)
										||
										(cSeika::objects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f
											>
											cVerticalMoveGround::objects[j]->Mposition.x + GROUND_HORIZONTAL_SIZE * cVerticalMoveGround::objects[j]->Mscale.x / 2)
										)
									{
										cSeika::objects[i]->collision = COLLISION_WALL;
										cSeika::objects[i]->position.x = cSeika::objects[i]->pastPosition.x;
									}

									cnt++;
								}
							}
						}
					}
				}

				//======================================================================================================================
				// 横移動床当たり判定
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
								// プレイヤーがobjects[j]の範囲にめり込んでいる時
								if (
									// プレイヤーの足が地面の上にめり込む
									(cSeika::objects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cHorizontalMoveGround::objects[j]->Mposition.y + GROUND_VERTICAL_SIZE * cHorizontalMoveGround::objects[j]->Mscale.y / 2)
									&&
									// プレイヤーの頭が地面の下にめり込む
									(cSeika::objects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cHorizontalMoveGround::objects[j]->Mposition.y - GROUND_VERTICAL_SIZE * cHorizontalMoveGround::objects[j]->Mscale.y / 2)
									&&
									// プレイヤーの右端が地面の左端にめり込む
									(cSeika::objects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cHorizontalMoveGround::objects[j]->Mposition.x - GROUND_HORIZONTAL_SIZE * cHorizontalMoveGround::objects[j]->Mscale.x / 2)
									&&
									// プレイヤーの左端が地面の右端にめり込む
									(cSeika::objects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cHorizontalMoveGround::objects[j]->Mposition.x + GROUND_HORIZONTAL_SIZE * cHorizontalMoveGround::objects[j]->Mscale.x / 2)
									)
								{
									//追加分当たり判定
									if (cSeika::objects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cGround::objects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2
										&&
										cSeika::objects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cGround::objects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::objects[j]->scale.y / 2
										&&
										cSeika::objects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 + 0.8f < cGround::objects[j]->position.x + GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2
										&&
										cSeika::objects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cGround::objects[j]->position.x - GROUND_HORIZONTAL_SIZE * cGround::objects[j]->scale.x / 2)
									{
										cSeika::objects[i]->collision = COLLISION_GROUND;
										cSeika::objects[i]->gravityTimer = 0;
										cSeika::objects[i]->jumping = false;
										cSeika::objects[i]->jumped = true;
										cSeika::objects[i]->hitCeilingWhileJumping = false;
										cSeika::objects[i]->position.y = cHorizontalMoveGround::objects[j]->Mposition.y + GROUND_VERTICAL_SIZE / 2 + PLAYER_VERTICAL_SIZE / 2 - 0.25f;

									}

									//ここまでが動く床の当たり判定！


									// 上判定
									if (cSeika::objects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cHorizontalMoveGround::objects[j]->Mposition.y - GROUND_VERTICAL_SIZE * cHorizontalMoveGround::objects[j]->Mscale.y / 2)
									{
										cSeika::objects[i]->collision = COLLISION_CEILING;
										cSeika::objects[i]->hitCeilingWhileJumping = true;
										cSeika::objects[i]->position.y = cSeika::objects[i]->pastPosition.y;
									}
									// 下判定
									if ((cSeika::objects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cHorizontalMoveGround::objects[j]->Mposition.y + GROUND_VERTICAL_SIZE * cHorizontalMoveGround::objects[j]->Mscale.y / 2))
									{
										cSeika::objects[i]->collision = COLLISION_GROUND;
										cSeika::objects[i]->gravityTimer = 0;
										cSeika::objects[i]->jumping = false;
										cSeika::objects[i]->jumped = true;
										cSeika::objects[i]->hitCeilingWhileJumping = false;
										cSeika::objects[i]->position.y = cSeika::objects[i]->pastPosition.y;
									}

									// 横判定
									//ブロック左上
									if (
										(cSeika::objects[i]->pastPosition.x - PLAYER_HORIZONTAL_SIZE / 2 - 0.8f
											<
											cHorizontalMoveGround::objects[j]->Mposition.x - cHorizontalMoveGround::objects[j]->Mscale.x / 2
											&& cHorizontalMoveGround::objects[j]->Mposition.y + cHorizontalMoveGround::objects[j]->Mscale.y / 2>cSeika::objects[i]->pastPosition.y + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f)
										||
										//ブロック右上
										(cSeika::objects[i]->pastPosition.x + PLAYER_HORIZONTAL_SIZE / 2 + 0.8f
										>
											cHorizontalMoveGround::objects[j]->Mposition.x + cHorizontalMoveGround::objects[j]->Mscale.x / 2
											&& cHorizontalMoveGround::objects[j]->Mposition.y - cHorizontalMoveGround::objects[j]->Mscale.y / 2 > cSeika::objects[i]->pastPosition.y - PLAYER_HORIZONTAL_SIZE / 2 - 0.8f)
										)
									{
										cSeika::objects[i]->collision = COLLISION_WALL;
										//追加地面のポジションープレイヤーのポジションを引くことで距離を求める処理
										D3DXVECTOR3 distance = cHorizontalMoveGround::objects[j]->Mposition - cSeika::objects[i]->position;
										//単位ベクトル
										//D3DXVec3Normalizeが単位ベクトルにする関数
										D3DXVec3Normalize(&distance, &distance);
										cSeika::objects[i]->position -= distance * 0.3f;
									}

									cnt++;
								}
							}
						}
					}
				}

				if (cnt == 0)
				{
					cSeika::objects[i]->collision = COLLISION_NONE;
				}
			}

			// デバッグで最低落下制御
			if (objects[i]->position.y - SEIKA_VERTICAL_SIZE / 2 < -50.0f)
			{
				objects[i]->position.y = -50.0f + SEIKA_VERTICAL_SIZE / 2;
				objects[i]->collision = COLLISION_GROUND;
				objects[i]->jumping = false;
				objects[i]->hitCeilingWhileJumping = false;
				objects[i]->jumped = true;
				objects[i]->gravityTimer = 0;
			}

			/*PrintDebugProc("聖火の持主　%d\n", objects[i]->owner);
			PrintDebugProc("聖火が空中　%d\n", objects[i]->jumping);
			PrintDebugProc("聖火が屋根　%d\n", objects[i]->hitCeilingWhileJumping);
			PrintDebugProc("聖火が地面　%d\n", objects[i]->jumped);
			PrintDebugProc("聖火の位置　%d\n", (int)objects[i]->position.y);*/
		}
	}
}

//ポリゴンの描画
void cSeika::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
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

			pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_SEIKA));
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				2
			);
		}
	}
}

void cSeika::Set()
{
	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		if (objects != NULL)
		{
			objects[i] = new cSeika;
			break;
		}
	}
}