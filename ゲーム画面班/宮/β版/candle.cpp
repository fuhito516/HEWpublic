
#include"common.h"
#include"candle.h"
#include"seika.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"debugproc.h"

cCandle* cCandle::numberOfObjects[NUMBER_OF_CANDLE];

LPDIRECT3DVERTEXBUFFER9 cCandle::pVertexBuffer;
VERTEX_3D*				cCandle::pVertex;

//頂点セット関数
void cCandle::SetVertex()
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

	pVertex[0].vtx = D3DXVECTOR3(-CANDLE_HORIZONTAL_SIZE / 2, -CANDLE_VERTICAL_SIZE / 2, 0.0f);
	pVertex[1].vtx = D3DXVECTOR3(-CANDLE_HORIZONTAL_SIZE / 2, CANDLE_VERTICAL_SIZE / 2, 0.0f);
	pVertex[2].vtx = D3DXVECTOR3(CANDLE_HORIZONTAL_SIZE / 2, -CANDLE_VERTICAL_SIZE / 2, 0.0f);
	pVertex[3].vtx = D3DXVECTOR3(CANDLE_HORIZONTAL_SIZE / 2, CANDLE_VERTICAL_SIZE / 2, 0.0f);
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
void cCandle::SetCandle(D3DXVECTOR2 _position)
{
	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		if (!numberOfObjects[i]->use)
		{
			// 使用
			numberOfObjects[i]->use = true;

			// 位置指定
			numberOfObjects[i]->position.x = _position.x;
			numberOfObjects[i]->position.y = _position.y;

			return;
		}
	}
}

//初期化
void cCandle::Init()
{
	InitDebugProc();

	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		numberOfObjects[i] = new cCandle;

		// 使用
		numberOfObjects[i]->use = false;
		// 灯る
		numberOfObjects[i]->turnOn = false;

		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);
		numberOfObjects[i]->position = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->rotation = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->scale = D3DXVECTOR3(1, 1, 1);
	}

	SetVertex();
}

//終了処理
void cCandle::Uninit()
{
	UninitDebugProc();

	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		delete numberOfObjects[i];
	}
}

//更新処理
void cCandle::Update()
{
	UpdateDebugProc();

	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		// 聖火との当たり判定
		if (cCandle::numberOfObjects[i]->use)
		{
			for (int j = 0; j < NUMBER_OF_SEIKA; j++)
			{
				// 聖火がnumberOfObjects[i]の範囲にめり込んでいる時
				if (
					// 聖火の下が上にめり込む
					(cSeika::numberOfObjects[j]->position.y - SEIKA_VERTICAL_SIZE / 2 < cCandle::numberOfObjects[i]->position.y + CANDLE_VERTICAL_SIZE / 2)
					&&
					// 聖火の上が下にめり込む
					(cSeika::numberOfObjects[j]->position.y + SEIKA_VERTICAL_SIZE / 2 > cCandle::numberOfObjects[i]->position.y - CANDLE_VERTICAL_SIZE / 2)
					&&
					// 聖火の右端が左端にめり込む
					(cSeika::numberOfObjects[j]->position.x + SEIKA_HORIZONTAL_SIZE / 2 > cCandle::numberOfObjects[i]->position.x - CANDLE_HORIZONTAL_SIZE / 2)
					&&
					// 聖火の左端が右端にめり込む
					(cSeika::numberOfObjects[j]->position.x - SEIKA_VERTICAL_SIZE / 2 < cCandle::numberOfObjects[i]->position.x + CANDLE_HORIZONTAL_SIZE / 2)
					)
				{
					cCandle::numberOfObjects[i]->turnOn = true;
				}
			}

			//PrintDebugProc("ロウソクの点灯状態[%d]　%d\n", i, cCandle::numberOfObjects[i]->turnOn);
		}
	}
}

//ポリゴンの描画
void cCandle::Draw()
{
	DrawDebugProc();

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		if (cCandle::numberOfObjects[i]->use)
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

			// 点灯状態による切替
			if ( numberOfObjects[i]->turnOn )
			{
				pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_CANDLE2));
			}
			else
			{
				pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_CANDLE1));
			}

			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				2
			);
		}
	}
}