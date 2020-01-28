
#include"common.h"
#include"Moveground.h"
#include"player.h"
#include"seika.h"
#include"direct3d.h"
#include"texture.h"
#include"input.h"

//cMoveGround* cMoveGround::MovenumberOfObjects[NUMBER_OF_GROUND_MOVE]; // オブジェクト格納
cHorizontalMoveGround* cHorizontalMoveGround::HorizontalMovenumberOfObjects[NUMBER_OF_GROUND_MOVE]; // オブジェクト格納

// 地面設定
void cHorizontalMoveGround::MoveSetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize)
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (!HorizontalMovenumberOfObjects[i]->use)
		{
			// 使用
			HorizontalMovenumberOfObjects[i]->use = true;

			// フレームカウンター
			HorizontalMovenumberOfObjects[i]->frameCounter = 0;

			// 位置と大きさ指定
			HorizontalMovenumberOfObjects[i]->Mposition.x = _mposition.x;
			HorizontalMovenumberOfObjects[i]->Mposition.y = _mposition.y;
			HorizontalMovenumberOfObjects[i]->Mscale.x = _msize.x;
			HorizontalMovenumberOfObjects[i]->Mscale.y = _msize.y;

			//初期位置の格納
			HorizontalMovenumberOfObjects[i]->fastMovePos.x = HorizontalMovenumberOfObjects[i]->Mposition.x;
			HorizontalMovenumberOfObjects[i]->fastMovePos.y = HorizontalMovenumberOfObjects[i]->Mposition.y;
			HorizontalMovenumberOfObjects[i]->fastMovePos.z = 0;
			return;
		}
	}
}


//初期化
void cHorizontalMoveGround::MoveInit()
{
	float t = 0;
	t += 0.1f;
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		HorizontalMovenumberOfObjects[i] = new cHorizontalMoveGround;


		// 使用
		HorizontalMovenumberOfObjects[i]->use = false;

		// サイズ
		HorizontalMovenumberOfObjects[i]->size = D3DXVECTOR2(1, 1);

		// 行列
		HorizontalMovenumberOfObjects[i]->Mposition = D3DXVECTOR3(0, t, 0);
		HorizontalMovenumberOfObjects[i]->Mrotation = D3DXVECTOR3(0, 0, 0);
		HorizontalMovenumberOfObjects[i]->Mscale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		D3DXMatrixIdentity(&HorizontalMovenumberOfObjects[i]->MworldMatrix);
	}

	MoveSetVertex();

}

//終了処理
void cHorizontalMoveGround::MoveUninit()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		delete HorizontalMovenumberOfObjects[i];
	}
}


//ポリゴンの描画
void cHorizontalMoveGround::MoveDraw()
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pMoveDevice = MyDirect3D_GetDevice();

	D3DXMATRIX MovescaleMatrix;			// スケーリング行列
	D3DXMATRIX MoverotationMatrix;		// 回転行列
	D3DXMATRIX MovetranslationMatrix;	// 平行移動行列


	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (HorizontalMovenumberOfObjects[i]->use)
		{
			// 行列初期化
			D3DXMatrixIdentity(&HorizontalMovenumberOfObjects[i]->MworldMatrix);

			D3DXMatrixScaling(&MovescaleMatrix, HorizontalMovenumberOfObjects[i]->Mscale.x, HorizontalMovenumberOfObjects[i]->Mscale.y, HorizontalMovenumberOfObjects[i]->Mscale.z);
			D3DXMatrixMultiply(&HorizontalMovenumberOfObjects[i]->MworldMatrix, &HorizontalMovenumberOfObjects[i]->MworldMatrix, &MovescaleMatrix);

			D3DXMatrixRotationYawPitchRoll(&MoverotationMatrix, HorizontalMovenumberOfObjects[i]->Mrotation.y, HorizontalMovenumberOfObjects[i]->Mrotation.x, HorizontalMovenumberOfObjects[i]->Mrotation.z);
			D3DXMatrixMultiply(&HorizontalMovenumberOfObjects[i]->MworldMatrix, &HorizontalMovenumberOfObjects[i]->MworldMatrix, &MoverotationMatrix);

			D3DXMatrixTranslation(&MovetranslationMatrix, HorizontalMovenumberOfObjects[i]->Mposition.x, HorizontalMovenumberOfObjects[i]->Mposition.y, HorizontalMovenumberOfObjects[i]->Mposition.z);
			D3DXMatrixMultiply(&HorizontalMovenumberOfObjects[i]->MworldMatrix, &HorizontalMovenumberOfObjects[i]->MworldMatrix, &MovetranslationMatrix);

			// ワールドマトリックスを設定
			pMoveDevice->SetTransform(D3DTS_WORLD, &HorizontalMovenumberOfObjects[i]->MworldMatrix);

			// 描画したいポリゴンの頂点バッファをデータストリーム(データの通り道)セット
			pMoveDevice->SetStreamSource(0, pMoveVertexBuffer, 0, sizeof(VERTEX_3D));

			// 描画したいポリゴンの頂点フォーマットの設定
			pMoveDevice->SetFVF(FVF_VERTEX_3D);

			// ポリゴンの描画
			pMoveDevice->SetTexture(0, NULL);
			pMoveDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				2
			);
		}
	}
}

//縦移動更新処理
void cHorizontalMoveGround::MoveUpdate()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (HorizontalMovenumberOfObjects[i]->use)
		{
			HorizontalMovenumberOfObjects[i]->Mposition.x += HorizontalMovenumberOfObjects[i]->spead;

			if (HorizontalMovenumberOfObjects[i]->Mposition.x<HorizontalMovenumberOfObjects[i]->fastMovePos.x) {
				HorizontalMovenumberOfObjects[i]->spead *= -1;
			}
			else if (HorizontalMovenumberOfObjects[i]->Mposition.x>HorizontalMovenumberOfObjects[i]->fastMovePos.x + 5) {
				HorizontalMovenumberOfObjects[i]->spead *= -1;
			}
			// フレームカウンター
			HorizontalMovenumberOfObjects[i]->frameCounter++;
		}
	}
}