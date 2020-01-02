
#include"common.h"
#include"seika.h"
#include"player.h"
#include"ground.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"debugproc.h"

cSeika* cSeika::numberOfObjects[NUMBER_OF_SEIKA]; // オブジェクト格納

LPDIRECT3DVERTEXBUFFER9 cSeika::pVertexBuffer;	// 頂点バッファ
VERTEX_3D*				cSeika::pVertex;		// 頂点バッファの中身を埋める

//頂点セット関数
void cSeika::SetVertex()
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
	pVertex[0].vtx = D3DXVECTOR3(-SEIKA_HORIZONTAL_SIZE / 2, -SEIKA_VERTICAL_SIZE / 2, 0.0f);	// 左下
	pVertex[1].vtx = D3DXVECTOR3(-SEIKA_HORIZONTAL_SIZE / 2, SEIKA_VERTICAL_SIZE / 2, 0.0f);	// 左上
	pVertex[2].vtx = D3DXVECTOR3(SEIKA_HORIZONTAL_SIZE / 2, -SEIKA_VERTICAL_SIZE / 2, 0.0f);	// 右下
	pVertex[3].vtx = D3DXVECTOR3(SEIKA_HORIZONTAL_SIZE / 2, SEIKA_VERTICAL_SIZE / 2, 0.0f);		// 右上

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
void cSeika::Init()
{
	InitDebugProc();

	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		// 指定プレイヤー数記憶領域を確保
		numberOfObjects[i] = new cSeika;

		// 前フレームの位置と処理後の位置(初期位置)
		numberOfObjects[i]->pastPosition.x = cPlayer::numberOfObjects[i]->position.x + SEIKA_HORIZONTAL_SIZE / 2;
		numberOfObjects[i]->pastPosition.y = cPlayer::numberOfObjects[i]->position.y + SEIKA_VERTICAL_SIZE / 2;

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

		// 描画
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
		// 指定プレイヤー数記憶領域を消去
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
			if (cPlayer::numberOfObjects[i]->directionHorizontal == DIRECTION_LEFT)
			{
				// 方向
				numberOfObjects[i]->directionHorizontal = DIRECTION_LEFT;
				// 移動
				numberOfObjects[i]->position.x = cPlayer::numberOfObjects[i]->position.x - SEIKA_HORIZONTAL_SIZE / 2;
			}
			// プレイヤーが右へ移動中もしくは横移動していない
			if (cPlayer::numberOfObjects[i]->directionHorizontal == DIRECTION_RIGHT)
			{
				// 方向
				numberOfObjects[i]->directionHorizontal = DIRECTION_RIGHT;
				// 移動
				numberOfObjects[i]->position.x = cPlayer::numberOfObjects[i]->position.x + SEIKA_HORIZONTAL_SIZE / 2;
			}
			if (cPlayer::numberOfObjects[i]->directionHorizontal == DIRECTION_NONE)
			{
				// 方向
				numberOfObjects[i]->directionHorizontal = DIRECTION_NONE;
			}

			numberOfObjects[i]->position.y = cPlayer::numberOfObjects[i]->position.y + SEIKA_HORIZONTAL_SIZE / 2;
		}
		// プレイヤーが聖火を保持してなく地面にも接していない
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

		// 重力時間
		numberOfObjects[i]->gravityTimer += 1.0f / 60.0f;

		// ジャンプ中での移動方向
		if (numberOfObjects[i]->jumping)
		{
			// 横移動
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

			// 上方向の遷移が強い && ジャンプ中天井へ当たっていない
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
			// ジャンプ中天井へ当たった
			else if (numberOfObjects[i]->hitCeilingWhileJumping)
			{
				numberOfObjects[i]->directionVertical = DIRECTION_DOWN;
				numberOfObjects[i]->position.y -= SEIKA_MAXIMUM_FALLSPEED;
			}
			// それ以外で下遷移が強い
			else
			{
				numberOfObjects[i]->directionVertical = DIRECTION_DOWN;
				numberOfObjects[i]->position.y
					+= SEIKA_JUMPPOWER * numberOfObjects[i]->gravityTimer - 0.5f * GRAVITY * numberOfObjects[i]->gravityTimer * numberOfObjects[i]->gravityTimer;

				// 最高落下速度を上回った
				if (SEIKA_JUMPPOWER * numberOfObjects[i]->gravityTimer - 0.5f * GRAVITY * numberOfObjects[i]->gravityTimer * numberOfObjects[i]->gravityTimer > SEIKA_MAXIMUM_FALLSPEED)
				{
					numberOfObjects[i]->position.y -= SEIKA_MAXIMUM_FALLSPEED;
				}
			}
		}
		// ジャンプ中ではない && 地面との当たり判定がない
		else if (!numberOfObjects[i]->jumping && numberOfObjects[i]->collision != COLLISION_GROUND)
		{
			numberOfObjects[i]->directionVertical = DIRECTION_DOWN;
			numberOfObjects[i]->position.y -= SEIKA_MAXIMUM_FALLSPEED / 2;
		}
		// 調整
		numberOfObjects[i]->position.y -= 0.001f;

		// プレイヤーとの当たり判定
		for (int j = 0; j < NUMBER_OF_PLAYER; j++)
		{
			if (cSeika::numberOfObjects[i]->jumped)
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
					cSeika::numberOfObjects[i]->jumped = false;
				}
			}
		}

		PrintDebugProc("衝突(聖火)　%d\n", numberOfObjects[i]->collision);


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


		// デバッグで最低落下制御
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

//ポリゴンの描画
void cSeika::Draw()
{
	DrawDebugProc();

	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;			// スケーリング行列
	D3DXMATRIX rotationMatrix;		// 回転行列
	D3DXMATRIX translationMatrix;	// 平行移動行列

	int i = 0;
	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
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
		pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_SEIKA));
		pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,
			0,
			2
		);
	}

}