
#include"common.h"
#include"bridge.h"
#include"candle.h"
#include"ground.h"
#include"seika.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"debugproc.h"

cBridge* cBridge::numberOfObjects[NUMBER_OF_BRIDGE];

// 地面設定
void cBridge::SetBridge(D3DXVECTOR2 _gimmickPosition, D3DXVECTOR2 _bridgePosition, D3DXVECTOR2 _bridgeSize)
{
	for (int i = 0; i < NUMBER_OF_BRIDGE; i++)
	{
		if (!numberOfObjects[i]->use)
		{
			// 使用
			numberOfObjects[i]->use = true;

			// 仕掛け
			numberOfObjects[i]->gimmickPosition.x = _gimmickPosition.x;
			numberOfObjects[i]->gimmickPosition.y = _gimmickPosition.y;

			// 橋
			numberOfObjects[i]->bridgePosition.x = _bridgePosition.x;
			numberOfObjects[i]->bridgePosition.y = _bridgePosition.y;
			numberOfObjects[i]->bridgeScale.x = _bridgeSize.x;
			numberOfObjects[i]->bridgeScale.y = _bridgeSize.y;

			return;
		}
	}
}

//初期化
void cBridge::Init()
{
	InitDebugProc();

	for (int i = 0; i < NUMBER_OF_BRIDGE; i++)
	{
		numberOfObjects[i] = new cBridge;

		// 使用
		numberOfObjects[i]->use = false;
		// 灯る
		numberOfObjects[i]->turnOn = false;

		D3DXMatrixIdentity(&numberOfObjects[i]->gimmickWorldMatrix);
		numberOfObjects[i]->gimmickPosition = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->gimmickRotation = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->gimmickScale = D3DXVECTOR3(1, 1, 1);

		D3DXMatrixIdentity(&numberOfObjects[i]->bridgeWorldMatrix);
		numberOfObjects[i]->bridgePosition = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->bridgeRotation = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->bridgeScale = D3DXVECTOR3(1, 1, 1);
	}
}

//終了処理
void cBridge::Uninit()
{
	UninitDebugProc();

	for (int i = 0; i < NUMBER_OF_BRIDGE; i++)
	{
		delete numberOfObjects[i];
	}
}

//更新処理
void cBridge::Update()
{
	UpdateDebugProc();

	for (int i = 0; i < NUMBER_OF_BRIDGE; i++)
	{
		// 聖火との当たり判定
		if (cBridge::numberOfObjects[i]->use)
		{
			for (int j = 0; j < NUMBER_OF_SEIKA; j++)
			{
				// 聖火がnumberOfObjects[i]の範囲にめり込んでいる時
				if (
					// 聖火の下が上にめり込む
					(cSeika::numberOfObjects[j]->position.y - SEIKA_VERTICAL_SIZE / 2 < cBridge::numberOfObjects[i]->gimmickPosition.y + BRIDGE_VERTICAL_SIZE / 2)
					&&
					// 聖火の上が下にめり込む
					(cSeika::numberOfObjects[j]->position.y + SEIKA_VERTICAL_SIZE / 2 > cBridge::numberOfObjects[i]->gimmickPosition.y - BRIDGE_VERTICAL_SIZE / 2)
					&&
					// 聖火の右端が左端にめり込む
					(cSeika::numberOfObjects[j]->position.x + SEIKA_HORIZONTAL_SIZE / 2 > cBridge::numberOfObjects[i]->gimmickPosition.x - BRIDGE_HORIZONTAL_SIZE / 2)
					&&
					// 聖火の左端が右端にめり込む
					(cSeika::numberOfObjects[j]->position.x - SEIKA_HORIZONTAL_SIZE / 2 < cBridge::numberOfObjects[i]->gimmickPosition.x + BRIDGE_HORIZONTAL_SIZE / 2)
					)
				{
					cBridge::numberOfObjects[i]->turnOn = true;
				}
			}

			//PrintDebugProc("仕掛けの点灯状態[%d]　%d\n", i, cBridge::numberOfObjects[i]->turnOn);
		}
	}
}

//ポリゴンの描画
void cBridge::Draw()
{
	DrawDebugProc();

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_BRIDGE; i++)
	{
		if (cBridge::numberOfObjects[i]->use)
		{
			D3DXMatrixIdentity(&numberOfObjects[i]->gimmickWorldMatrix);

			D3DXMatrixScaling(&scaleMatrix, numberOfObjects[i]->gimmickScale.x, numberOfObjects[i]->gimmickScale.y, numberOfObjects[i]->gimmickScale.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->gimmickWorldMatrix, &numberOfObjects[i]->gimmickWorldMatrix, &scaleMatrix);
			D3DXMatrixRotationYawPitchRoll(&rotationMatrix, numberOfObjects[i]->gimmickRotation.y, numberOfObjects[i]->gimmickRotation.x, numberOfObjects[i]->gimmickRotation.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->gimmickWorldMatrix, &numberOfObjects[i]->gimmickWorldMatrix, &rotationMatrix);
			D3DXMatrixTranslation(&translationMatrix, numberOfObjects[i]->gimmickPosition.x, numberOfObjects[i]->gimmickPosition.y, numberOfObjects[i]->gimmickPosition.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->gimmickWorldMatrix, &numberOfObjects[i]->gimmickWorldMatrix, &translationMatrix);

			pDevice->SetTransform(D3DTS_WORLD, &numberOfObjects[i]->gimmickWorldMatrix);

			pDevice->SetStreamSource(0, cCandle::pVertexBuffer, 0, sizeof(VERTEX_3D));
			pDevice->SetFVF(FVF_VERTEX_3D);

			// 点灯状態による切替
			if (numberOfObjects[i]->turnOn)
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

			if ( numberOfObjects[i]->turnOn )
			{
				D3DXMatrixIdentity(&scaleMatrix);
				D3DXMatrixIdentity(&rotationMatrix);
				D3DXMatrixIdentity(&translationMatrix);

				D3DXMatrixIdentity(&numberOfObjects[i]->bridgeWorldMatrix);

				D3DXMatrixScaling(&scaleMatrix, numberOfObjects[i]->bridgeScale.x, numberOfObjects[i]->bridgeScale.y, numberOfObjects[i]->bridgeScale.z);
				D3DXMatrixMultiply(&numberOfObjects[i]->bridgeWorldMatrix, &numberOfObjects[i]->bridgeWorldMatrix, &scaleMatrix);
				D3DXMatrixRotationYawPitchRoll(&rotationMatrix, numberOfObjects[i]->bridgeRotation.y, numberOfObjects[i]->bridgeRotation.x, numberOfObjects[i]->bridgeRotation.z);
				D3DXMatrixMultiply(&numberOfObjects[i]->bridgeWorldMatrix, &numberOfObjects[i]->bridgeWorldMatrix, &rotationMatrix);
				D3DXMatrixTranslation(&translationMatrix, numberOfObjects[i]->bridgePosition.x, numberOfObjects[i]->bridgePosition.y, numberOfObjects[i]->bridgePosition.z);
				D3DXMatrixMultiply(&numberOfObjects[i]->bridgeWorldMatrix, &numberOfObjects[i]->bridgeWorldMatrix, &translationMatrix);

				pDevice->SetTransform(D3DTS_WORLD, &numberOfObjects[i]->bridgeWorldMatrix);

				pDevice->SetStreamSource(0, cGround::pVertexBuffer, 0, sizeof(VERTEX_3D));
				pDevice->SetFVF(FVF_VERTEX_3D);

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
}