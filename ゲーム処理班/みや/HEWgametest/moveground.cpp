
#include"common.h"
#include"moveground.h"
#include"player.h"
#include"seika.h"
#include"direct3d.h"
#include"texture.h"
#include"input.h"

cMoveGround* cMoveGround::numberOfObjects[NUMBER_OF_GROUND_MOVE]; // オブジェクト格納

LPDIRECT3DVERTEXBUFFER9 cMoveGround::pVertexBuffer;	// 頂点バッファ
VERTEX_3D*				cMoveGround::pVertex;		// 頂点バッファの中身を埋める

//頂点セット関数
void cMoveGround::SetVertex()
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
	pVertex[0].vtx = D3DXVECTOR3(-GROUND_HORIZONTAL_SIZE_MOVE / 2, -GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// 左下
	pVertex[1].vtx = D3DXVECTOR3(-GROUND_HORIZONTAL_SIZE_MOVE / 2, GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// 左上
	pVertex[2].vtx = D3DXVECTOR3(GROUND_HORIZONTAL_SIZE_MOVE / 2, -GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// 右下
	pVertex[3].vtx = D3DXVECTOR3(GROUND_HORIZONTAL_SIZE_MOVE / 2, GROUND_HORIZONTAL_SIZE_MOVE / 2, 0.0f);	// 右上

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

// 地面設定
void cMoveGround::SetGround(D3DXVECTOR2 _position, D3DXVECTOR2 _size, float _moveWidth)
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (!numberOfObjects[i]->use)
		{
			// 追加設定
			numberOfObjects[i]->moveWidth = _moveWidth;

			// 使用
			numberOfObjects[i]->use = true;

			// 位置と大きさ指定
			numberOfObjects[i]->pastPosition.x = numberOfObjects[i]->position.x = _position.x;
			numberOfObjects[i]->pastPosition.y = numberOfObjects[i]->position.y = _position.y;
			numberOfObjects[i]->scale.x = _size.x;
			numberOfObjects[i]->scale.y = _size.y;

			return;
		}
	}
}

//初期化
void cMoveGround::Init()
{
	SetVertex();

	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		numberOfObjects[i] = new cMoveGround;

		// 追加パラメータ
		numberOfObjects[i]->speed = GROUND_MOVE_SPEED;
		numberOfObjects[i]->moveWidth = 0;

		// 使用
		numberOfObjects[i]->use = false;

		// サイズ
		numberOfObjects[i]->size = D3DXVECTOR2(1, 1);

		// 行列
		numberOfObjects[i]->pastPosition = numberOfObjects[i]->position = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->rotation = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);
	}
}

//終了処理
void cMoveGround::Uninit()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		delete numberOfObjects[i];
	}
}

//更新処理
void cMoveGround::Update()
{
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (numberOfObjects[i]->use)
		{
			numberOfObjects[i]->position.y += numberOfObjects[i]->speed;

			if (
				numberOfObjects[i]->position.y < numberOfObjects[i]->pastPosition.y - numberOfObjects[i]->moveWidth / 2
				||
				numberOfObjects[i]->position.y > numberOfObjects[i]->pastPosition.y + numberOfObjects[i]->moveWidth / 2
				)
			{
				numberOfObjects[i]->speed *= -1;
			}
		}
	}
}

//ポリゴンの描画
void cMoveGround::Draw()
{

	// デバイス情報取得
	LPDIRECT3DDEVICE9 pMoveDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;			// スケーリング行列
	D3DXMATRIX rotationMatrix;		// 回転行列
	D3DXMATRIX translationMatrix;	// 平行移動行列

	
	for (int i = 0; i < NUMBER_OF_GROUND_MOVE; i++)
	{
		if (numberOfObjects[i]->use)
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
			pMoveDevice->SetTransform(D3DTS_WORLD, &numberOfObjects[i]->worldMatrix);

			// 描画したいポリゴンの頂点バッファをデータストリーム(データの通り道)セット
			pMoveDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));

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