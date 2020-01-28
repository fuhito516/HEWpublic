
#include"common.h"
#include"Moveground.h"
#include"player.h"
#include"seika.h"
#include"direct3d.h"
#include"texture.h"
#include"input.h"

//cMoveGround* cMoveGround::MovenumberOfObjects[NUMBER_OF_GROUND_MOVE]; // オブジェクト格納
cVerticalMoveGround* cVerticalMoveGround::VerticalMovenumberOfObjects[NUMBER_OF_GROUND_MOVE]; // オブジェクト格納

LPDIRECT3DVERTEXBUFFER9 cMoveGround::pMoveVertexBuffer;	// 頂点バッファ
VERTEX_3D*				cMoveGround::pMoveVertex;		// 頂点バッファの中身を埋める
//頂点セット関数
void cMoveGround::MoveSetVertex()
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
		&pMoveVertexBuffer,			// 頂点バッファインターフェースへのポインタ
		NULL
	);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pMoveVertexBuffer->Lock(0, 0, (void**)&pMoveVertex, 0);

	// 頂点座標の設定
	pMoveVertex[0].vtx = D3DXVECTOR3(-GROUND_HORIZONTAL_SIZE_MOVE / 2, -GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// 左下
	pMoveVertex[1].vtx = D3DXVECTOR3(-GROUND_HORIZONTAL_SIZE_MOVE / 2, GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// 左上
	pMoveVertex[2].vtx = D3DXVECTOR3(GROUND_HORIZONTAL_SIZE_MOVE / 2, -GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// 右下
	pMoveVertex[3].vtx = D3DXVECTOR3(GROUND_HORIZONTAL_SIZE_MOVE / 2, GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// 右上

	// 法線ベクトルの設定
	for (int i = 0; i < 4; i++)
		pMoveVertex[i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// 反射光の設定 // 色
	for (int i = 0; i < 4; i++)
		pMoveVertex[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 白

    // テクスチャ座標の設定
	pMoveVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pMoveVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pMoveVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pMoveVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点データをアンロックする
	pMoveVertexBuffer->Unlock();

}

void cMoveGround::MoveSetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize){}
void cMoveGround::MoveInit(){}
void cMoveGround::MoveUninit(){}
void cMoveGround::MoveUpdate(){}
void cMoveGround::MoveDraw(){}

// 地面設定
void cVerticalMoveGround::MoveSetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize)
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (!VerticalMovenumberOfObjects[i]->use)
		{
			// 使用
			VerticalMovenumberOfObjects[i]->use = true;

			// フレームカウンター
			VerticalMovenumberOfObjects[i]->frameCounter = 0;

			// 位置と大きさ指定
			VerticalMovenumberOfObjects[i]->Mposition.x = _mposition.x;
			VerticalMovenumberOfObjects[i]->Mposition.y = _mposition.y;
			VerticalMovenumberOfObjects[i]->Mscale.x = _msize.x;
			VerticalMovenumberOfObjects[i]->Mscale.y = _msize.y;

			//初期位置の格納

			return;
		}
	}
}


//初期化
void cVerticalMoveGround::MoveInit()
{
	//float t = 0;
	//t += 0.1f;
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		VerticalMovenumberOfObjects[i] = new cVerticalMoveGround;

		// 使用
		VerticalMovenumberOfObjects[i]->use = false;

		// サイズ
		VerticalMovenumberOfObjects[i]->size = D3DXVECTOR2(1, 1);

		// 行列
		VerticalMovenumberOfObjects[i]->Mposition = D3DXVECTOR3(0, 15, 0);
		VerticalMovenumberOfObjects[i]->Mrotation = D3DXVECTOR3(0, 0, 0);
		VerticalMovenumberOfObjects[i]->Mscale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		D3DXMatrixIdentity(&VerticalMovenumberOfObjects[i]->MworldMatrix);
	}

	MoveSetVertex();

}

//終了処理
void cVerticalMoveGround::MoveUninit()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		delete VerticalMovenumberOfObjects[i];
	}
}


//ポリゴンの描画
void cVerticalMoveGround::MoveDraw()
{

	// デバイス情報取得
	LPDIRECT3DDEVICE9 pMoveDevice = MyDirect3D_GetDevice();

	D3DXMATRIX MovescaleMatrix;			// スケーリング行列
	D3DXMATRIX MoverotationMatrix;		// 回転行列
	D3DXMATRIX MovetranslationMatrix;	// 平行移動行列

	
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (VerticalMovenumberOfObjects[i]->use)
		{
			// 行列初期化
			D3DXMatrixIdentity(&VerticalMovenumberOfObjects[i]->MworldMatrix);

			D3DXMatrixScaling(&MovescaleMatrix, VerticalMovenumberOfObjects[i]->Mscale.x, VerticalMovenumberOfObjects[i]->Mscale.y, VerticalMovenumberOfObjects[i]->Mscale.z);
			D3DXMatrixMultiply(&VerticalMovenumberOfObjects[i]->MworldMatrix, &VerticalMovenumberOfObjects[i]->MworldMatrix, &MovescaleMatrix);

			D3DXMatrixRotationYawPitchRoll(&MoverotationMatrix, VerticalMovenumberOfObjects[i]->Mrotation.y, VerticalMovenumberOfObjects[i]->Mrotation.x, VerticalMovenumberOfObjects[i]->Mrotation.z);
			D3DXMatrixMultiply(&VerticalMovenumberOfObjects[i]->MworldMatrix, &VerticalMovenumberOfObjects[i]->MworldMatrix, &MoverotationMatrix);

			D3DXMatrixTranslation(&MovetranslationMatrix, VerticalMovenumberOfObjects[i]->Mposition.x, VerticalMovenumberOfObjects[i]->Mposition.y, VerticalMovenumberOfObjects[i]->Mposition.z);
			D3DXMatrixMultiply(&VerticalMovenumberOfObjects[i]->MworldMatrix, &VerticalMovenumberOfObjects[i]->MworldMatrix, &MovetranslationMatrix);

			// ワールドマトリックスを設定
			pMoveDevice->SetTransform(D3DTS_WORLD, &VerticalMovenumberOfObjects[i]->MworldMatrix);

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
void cVerticalMoveGround::MoveUpdate()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{

		if (VerticalMovenumberOfObjects[i]->use)
		{
			VerticalMovenumberOfObjects[i]->Mposition.y += VerticalMovenumberOfObjects[i]->spead;

			if (VerticalMovenumberOfObjects[i]->Mposition.y<0) {
				VerticalMovenumberOfObjects[i]->spead *= -1;
			}
			else if (VerticalMovenumberOfObjects[i]->Mposition.y>10) {
				VerticalMovenumberOfObjects[i]->spead *= -1;
			}
			// フレームカウンター
			VerticalMovenumberOfObjects[i]->frameCounter++;
		}
	}
}