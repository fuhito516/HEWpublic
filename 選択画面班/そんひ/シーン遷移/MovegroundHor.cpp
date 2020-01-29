
#include"common.h"
#include"Moveground.h"
#include"player.h"
#include"seika.h"
#include"direct3d.h"
#include"texture.h"
#include"input.h"

//cMoveGround* cMoveGround::MovenumberOfObjects[NUMBER_OF_GROUND_MOVE]; // オブジェクト格納
cHorizontalMoveGround* cHorizontalMoveGround::objects[NUMBER_OF_GROUND_MOVE]; // オブジェクト格納

																			  // 地面設定
void cHorizontalMoveGround::SetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize, D3DXVECTOR2 _distance)
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (!objects[i]->use)
		{
			// 使用
			objects[i]->use = true;

			// フレームカウンター
			objects[i]->frameCounter = 0;

			// 位置と大きさ指定
			objects[i]->Mposition.x = _mposition.x;
			objects[i]->Mposition.y = _mposition.y;
			objects[i]->Mscale.x = _msize.x;
			objects[i]->Mscale.y = _msize.y;

			//移動距離
			objects[i]->distance.x = _distance.x;
			objects[i]->distance.y = _distance.y;

			//初期位置の格納
			objects[i]->fastMovePos.x = objects[i]->Mposition.x;
			objects[i]->fastMovePos.y = objects[i]->Mposition.y;
			objects[i]->fastMovePos.z = 0;
			return;
		}
	}
}


//初期化
void cHorizontalMoveGround::Init()
{
	float t = 0;
	t += 0.1f;
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		objects[i] = new cHorizontalMoveGround;


		// 使用
		objects[i]->use = false;

		// サイズ
		objects[i]->size = D3DXVECTOR2(1, 1);

		// 行列
		objects[i]->Mposition = D3DXVECTOR3(0, t, 0);
		objects[i]->Mrotation = D3DXVECTOR3(0, 0, 0);
		objects[i]->Mscale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		D3DXMatrixIdentity(&objects[i]->MworldMatrix);
	}

	SetVertex();

}

//終了処理
void cHorizontalMoveGround::Uninit()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		delete objects[i];
	}
}


//ポリゴンの描画
void cHorizontalMoveGround::Draw()
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pMoveDevice = MyDirect3D_GetDevice();

	D3DXMATRIX MovescaleMatrix;			// スケーリング行列
	D3DXMATRIX MoverotationMatrix;		// 回転行列
	D3DXMATRIX MovetranslationMatrix;	// 平行移動行列


	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (objects[i]->use)
		{
			// 行列初期化
			D3DXMatrixIdentity(&objects[i]->MworldMatrix);

			D3DXMatrixScaling(&MovescaleMatrix, objects[i]->Mscale.x, objects[i]->Mscale.y, objects[i]->Mscale.z);
			D3DXMatrixMultiply(&objects[i]->MworldMatrix, &objects[i]->MworldMatrix, &MovescaleMatrix);

			D3DXMatrixRotationYawPitchRoll(&MoverotationMatrix, objects[i]->Mrotation.y, objects[i]->Mrotation.x, objects[i]->Mrotation.z);
			D3DXMatrixMultiply(&objects[i]->MworldMatrix, &objects[i]->MworldMatrix, &MoverotationMatrix);

			D3DXMatrixTranslation(&MovetranslationMatrix, objects[i]->Mposition.x, objects[i]->Mposition.y, objects[i]->Mposition.z);
			D3DXMatrixMultiply(&objects[i]->MworldMatrix, &objects[i]->MworldMatrix, &MovetranslationMatrix);

			// ワールドマトリックスを設定
			pMoveDevice->SetTransform(D3DTS_WORLD, &objects[i]->MworldMatrix);

			// 描画したいポリゴンの頂点バッファをデータストリーム(データの通り道)セット
			pMoveDevice->SetStreamSource(0, pMoveVertexBuffer, 0, sizeof(VERTEX_3D));

			// 描画したいポリゴンの頂点フォーマットの設定
			pMoveDevice->SetFVF(FVF_VERTEX_3D);

			// ポリゴンの描画
			pMoveDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_GROUND));
			pMoveDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				2
			);
		}
	}
}

//横移動更新処理
void cHorizontalMoveGround::Update()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (objects[i]->use)
		{
			if (objects[i]->distance.x > 0) {
				objects[i]->Mposition.x += objects[i]->spead;

				if (objects[i]->Mposition.x<objects[i]->fastMovePos.x - objects[i]->distance.x) {
					objects[i]->spead *= -1;
				}
				else if (objects[i]->Mposition.x>objects[i]->fastMovePos.x + objects[i]->distance.x) {
					objects[i]->spead *= -1;
				}
			}


			if (objects[i]->distance.x < 0) {

				objects[i]->Mposition.x -= objects[i]->spead;
				if (objects[i]->Mposition.x<objects[i]->fastMovePos.x - objects[i]->distance.x*-1) {
					objects[i]->spead *= -1;
				}
				else if (objects[i]->Mposition.x>objects[i]->fastMovePos.x + objects[i]->distance.x*-1) {
					objects[i]->spead *= -1;
				}
			}
			// フレームカウンター
			objects[i]->frameCounter++;
		}
	}
}