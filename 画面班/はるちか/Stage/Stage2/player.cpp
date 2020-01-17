
#include"common.h"
#include"player.h"
#include"ground.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"
#include"Moveground.h"

#include"debugproc.h"
//追加
#include<math.h>
cPlayer* cPlayer::numberOfObjects[NUMBER_OF_PLAYER]; // オブジェクト格納

LPDIRECT3DVERTEXBUFFER9 cPlayer::pVertexBuffer;	// 頂点バッファ
VERTEX_3D*				cPlayer::pVertex;		// 頂点バッファの中身を埋める

//頂点セット関数
void cPlayer::SetVertex()
{

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4,	// 頂点データように確保するバッファサイズ(バイト単位)//頂点数
		D3DUSAGE_WRITEONLY,		// 頂点バッファの使用法
		FVF_VERTEX_3D,			// 使用する頂点フォーマット
		D3DPOOL_MANAGED,		// リソースのバッファを保持するメモリクラスを指定
		&pVertexBuffer,			// 頂点バッファインターフェースへのポインタ
		NULL
	);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	// 頂点座標の設定
	pVertex[0].vtx = D3DXVECTOR3(-PLAYER_HORIZONTAL_SIZE / 2, -PLAYER_VERTICAL_SIZE / 2, 0.0f);	// 左下
	pVertex[1].vtx = D3DXVECTOR3(-PLAYER_HORIZONTAL_SIZE / 2, PLAYER_VERTICAL_SIZE / 2, 0.0f);	// 左上
	pVertex[2].vtx = D3DXVECTOR3(PLAYER_HORIZONTAL_SIZE / 2, -PLAYER_VERTICAL_SIZE / 2, 0.0f);	// 右下
	pVertex[3].vtx = D3DXVECTOR3(PLAYER_HORIZONTAL_SIZE / 2, PLAYER_VERTICAL_SIZE / 2, 0.0f);	// 右上

	// 法線ベクトルの設定
	for (int i = 0; i < 4; i++)
		pVertex[i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// 反射光の設定 // 色
	for (int i = 0; i < 4; i++)
		pVertex[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 白

	// テクスチャ座標の設定
	pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点データをアンロックする
	pVertexBuffer->Unlock();

}

//初期化
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
		numberOfObjects[i]->directionHorizontal = DIRECTION_DOWN;

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

		// 聖火保持
		numberOfObjects[i]->retention = true;

		// 描画
		numberOfObjects[i]->position = D3DXVECTOR3(PLAYER_INITIAL_POSITION_X, PLAYER_INITIAL_POSITION_Y, 0);
		numberOfObjects[i]->rotation = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->scale = D3DXVECTOR3(1, 1, 1);
		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);
	}

	SetVertex();

}

//終了処理
void cPlayer::Uninit()
{
	UninitDebugProc();

	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		// 指定プレイヤー数記憶領域を消去
		delete numberOfObjects[i];
	}
}

//更新処理
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
			numberOfObjects[i]->directionHorizontal = DIRECTION_LEFT;
			// 移動
			numberOfObjects[i]->position.x -= PLAYER_MOVEMENT_SPEED;
		}
		if (GetKeyboardPress(DIK_D))
		{
			// 方向
			numberOfObjects[i]->directionHorizontal = DIRECTION_RIGHT;
			// 移動
			numberOfObjects[i]->position.x += PLAYER_MOVEMENT_SPEED;
		}
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

		if (GetKeyboardPress(DIK_T) && numberOfObjects[i]->retention)
		{
			numberOfObjects[i]->retention = false;
		}

		// 重力時間
		numberOfObjects[i]->gravityTimer += 1.0f / 60.0f;

		// ジャンプ中での移動
		if ( numberOfObjects[i]->jumping)
		{
			// 上方向の遷移が強い && ジャンプ中天井へ当たっていない
			if (
				PLAYER_JUMPPOWER * numberOfObjects[i]->gravityTimer
				>
				GRAVITY * numberOfObjects[i]->gravityTimer * numberOfObjects[i]->gravityTimer / 2
				&& !numberOfObjects[i]->hitCeilingWhileJumping
				)
			{
				// 方向
				numberOfObjects[i]->directionVertical = DIRECTION_UP;
				// 位置
				numberOfObjects[i]->position.y += 
					PLAYER_JUMPPOWER * numberOfObjects[i]->gravityTimer
					- 0.5f * GRAVITY * numberOfObjects[i]->gravityTimer * numberOfObjects[i]->gravityTimer;
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
		// ジャンプ中ではない && 地面との当たり判定がない
		else if (!numberOfObjects[i]->jumping && numberOfObjects[i]->collision != COLLISION_GROUND)
		{
			numberOfObjects[i]->directionVertical = DIRECTION_DOWN;

			numberOfObjects[i]->position.y -= PLAYER_MAXIMUM_FALLSPEED ;
		}
		// 調整
		numberOfObjects[i]->position.y -= 0.001f;

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

		// 地面との当たり判定
		for (int j = 0; j < NUMBER_OF_GROUND; j++)
		{
			int cnt = 0;
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
				
					// 上判定
					if (cPlayer::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cGround::numberOfObjects[j]->position.y - GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2)
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_CEILING;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = true;
						cPlayer::numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->pastPosition.y;

					}
					// 下判定
					if ((cPlayer::numberOfObjects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cGround::numberOfObjects[j]->position.y + GROUND_VERTICAL_SIZE * cGround::numberOfObjects[j]->scale.y / 2))
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_GROUND;
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
		//動く床の当たり判定
		//
		//================================================
		for (int j = 0; j < NUMBER_OF_GROUND_MOVE; j++)
		{
			int cnt = 0;
			if (cMoveGround::MovenumberOfObjects[j]->use)
			{
				// プレイヤーがMovenumberOfObjects[j]の範囲にめり込んでいる時
				if (
					// プレイヤーの足が地面の上にめり込む
					(cPlayer::numberOfObjects[i]->position.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f < cMoveGround::MovenumberOfObjects[j]->Mposition.y + GROUND_VERTICAL_SIZE * cMoveGround::MovenumberOfObjects[j]->Mscale.y / 2)
					&&
					// プレイヤーの頭が地面の下にめり込む
					(cPlayer::numberOfObjects[i]->position.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f > cMoveGround::MovenumberOfObjects[j]->Mposition.y - GROUND_VERTICAL_SIZE * cMoveGround::MovenumberOfObjects[j]->Mscale.y / 2)
					&&
					// プレイヤーの右端が地面の左端にめり込む
					(cPlayer::numberOfObjects[i]->position.x + PLAYER_HORIZONTAL_SIZE / 2 - 0.8f > cMoveGround::MovenumberOfObjects[j]->Mposition.x - GROUND_HORIZONTAL_SIZE * cMoveGround::MovenumberOfObjects[j]->Mscale.x / 2)
					&&
					// プレイヤーの左端が地面の右端にめり込む
					(cPlayer::numberOfObjects[i]->position.x - PLAYER_VERTICAL_SIZE / 2 + 0.8f < cMoveGround::MovenumberOfObjects[j]->Mposition.x + GROUND_HORIZONTAL_SIZE * cMoveGround::MovenumberOfObjects[j]->Mscale.x / 2)
					)
				{
					//追加分当たり判定
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
					
					//ここまでが動く床の当たり判定！


					// 上判定
					if (cPlayer::numberOfObjects[i]->pastPosition.y + PLAYER_VERTICAL_SIZE / 2 - 0.25f < cMoveGround::MovenumberOfObjects[j]->Mposition.y - GROUND_VERTICAL_SIZE * cMoveGround::MovenumberOfObjects[j]->Mscale.y / 2)
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_CEILING;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = true;
						cPlayer::numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->pastPosition.y;
					}
					// 下判定
					if ((cPlayer::numberOfObjects[i]->pastPosition.y - PLAYER_VERTICAL_SIZE / 2 + 0.25f > cMoveGround::MovenumberOfObjects[j]->Mposition.y + GROUND_VERTICAL_SIZE * cMoveGround::MovenumberOfObjects[j]->Mscale.y / 2))
					{
						cPlayer::numberOfObjects[i]->collision = COLLISION_GROUND;
						cPlayer::numberOfObjects[i]->gravityTimer = 0;
						cPlayer::numberOfObjects[i]->jumping = false;
						cPlayer::numberOfObjects[i]->jumpPossible = true;
						cPlayer::numberOfObjects[i]->hitCeilingWhileJumping = false;
						cPlayer::numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->pastPosition.y;
					}

					// 横判定
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
						//追加地面のポジションープレイヤーのポジションを引くことで距離を求める処理
						D3DXVECTOR3 distance = cMoveGround::MovenumberOfObjects[j]->Mposition- cPlayer::numberOfObjects[i]->position;
						//単位ベクトル
						//D3DXVec3Normalizeが単位ベクトルにする関数
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
		
		PrintDebugProc("聖火保有　%d\n", numberOfObjects[i]->retention);
	}
}

//ポリゴンの描画
void cPlayer::Draw()
{
	DrawDebugProc();

	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;			// スケーリング行列
	D3DXMATRIX rotationMatrix;		// 回転行列
	D3DXMATRIX translationMatrix;	// 平行移動行列

	int i = 0;
	for (int i = 0; i < NUMBER_OF_PLAYER; i++)
	{
		// 行列初期化
		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);

		D3DXMatrixScaling(&scaleMatrix, numberOfObjects[i]->scale.x, numberOfObjects[i]->scale.y, numberOfObjects[i]->scale.z);
		D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &scaleMatrix);

		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, numberOfObjects[i]->rotation.y, numberOfObjects[i]->rotation.x, numberOfObjects[i]->rotation.z);
		D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &rotationMatrix);

		D3DXMatrixTranslation(&translationMatrix, numberOfObjects[i]->position.x, numberOfObjects[i]->position.y, numberOfObjects[i]->position.z);
		D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &translationMatrix);

		// ワールドマトリックスを設定
		pDevice->SetTransform(D3DTS_WORLD, &numberOfObjects[i]->worldMatrix);

		// 描画したいポリゴンの頂点バッファをデータストリーム(データの通り道)セット
		pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));

		// 描画したいポリゴンの頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// ポリゴンの描画
		pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_BABY));
		pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,
			0,
			2
		);
	}

}