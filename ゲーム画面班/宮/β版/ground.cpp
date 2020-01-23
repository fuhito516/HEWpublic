
#include"common.h"
#include"ground.h"
#include"player.h"
#include"seika.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

cGround* cGround::numberOfObjects[NUMBER_OF_GROUND]; // オブジェクト格納

LPDIRECT3DVERTEXBUFFER9 cGround::pVertexBuffer;	// 頂点バッファ
VERTEX_3D*				cGround::pVertex;		// 頂点バッファの中身を埋める

//頂点セット関数
void cGround::SetVertex()
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

	pVertex[0].vtx = D3DXVECTOR3(-GROUND_HORIZONTAL_SIZE / 2, -GROUND_VERTICAL_SIZE / 2, 0.0f);
	pVertex[1].vtx = D3DXVECTOR3(-GROUND_HORIZONTAL_SIZE / 2,  GROUND_VERTICAL_SIZE / 2, 0.0f);
	pVertex[2].vtx = D3DXVECTOR3( GROUND_HORIZONTAL_SIZE / 2, -GROUND_VERTICAL_SIZE / 2, 0.0f);
	pVertex[3].vtx = D3DXVECTOR3( GROUND_HORIZONTAL_SIZE / 2,  GROUND_VERTICAL_SIZE / 2, 0.0f);
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

// 地面設定
void cGround::SetGround(D3DXVECTOR2 _position, D3DXVECTOR2 _size)
{
	for (int i = 0; i < NUMBER_OF_GROUND; i++)
	{
		if ( !numberOfObjects[i]->use )
		{
			// 使用
			numberOfObjects[i]->use = true;

			// 位置と大きさ指定
			numberOfObjects[i]->position.x = _position.x;
			numberOfObjects[i]->position.y = _position.y;
			numberOfObjects[i]->scale.x = _size.x;
			numberOfObjects[i]->scale.y = _size.y;

			return;
		}
	}
}

//初期化
void cGround::Init()
{

	for (int i = 0; i < NUMBER_OF_GROUND; i++)
	{
		numberOfObjects[i] = new cGround;

		// 使用
		numberOfObjects[i]->use = false;

		// サイズ
		numberOfObjects[i]->size = D3DXVECTOR2(1, 1);

		// 行列
		numberOfObjects[i]->position = D3DXVECTOR3(0, 0.0f, 0);
		numberOfObjects[i]->rotation = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);
	}

	SetVertex();

}

//終了処理
void cGround::Uninit()
{
	for (int i = 0; i < NUMBER_OF_GROUND; i++)
	{
		delete numberOfObjects[i];
	}
}

//更新処理
void cGround::Update()
{
	
}

//ポリゴンの描画
void cGround::Draw()
{

	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_GROUND; i++)
	{
		if ( numberOfObjects[i]->use )
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
			pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_GROUND));
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				2
			);
		}
	}
}