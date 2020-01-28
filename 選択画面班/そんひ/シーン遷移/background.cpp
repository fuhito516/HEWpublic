
#include"common.h"
#include"background.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"ground.h"

#include"debugproc.h"

cBackground* cBackground::objects[NUMBER_OF_BACKLAYER];

// 配置
void cBackground::SetBackground(TextureIndex _textureIndex, D3DXVECTOR3 _position, D3DXVECTOR3 _scale)
{
	for (int i = 0; i < NUMBER_OF_BACKLAYER; i++)
	{
		if ( !objects[i]->use )
		{
			objects[i]->use = true;

			// 情報
			objects[i]->textureIndex = _textureIndex;
			objects[i]->position = _position;
			objects[i]->scale = _scale;

			return;
		}
	}
}

//初期化
void cBackground::Init()
{
	for (int i = 0; i < NUMBER_OF_BACKLAYER; i++)
	{
		objects[i] = new cBackground;

		objects[i]->use = false;
		objects[i]->textureIndex = TEXTURE_INDEX_MAX;

		D3DXMatrixIdentity(&objects[i]->worldMatrix);
		objects[i]->position = D3DXVECTOR3(0, 0, 0);
		objects[i]->rotation = D3DXVECTOR3(0, 0, 0);
		objects[i]->scale = D3DXVECTOR3(1, 1, 1);
	}
}
//終了処理
void cBackground::Uninit()
{
	for (int i = 0; i < NUMBER_OF_BACKLAYER; i++)
	{
		delete objects[i];
	}
}
//更新処理
void cBackground::Update()
{

}

//ポリゴンの描画
void cBackground::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_BACKLAYER; i++)
	{
		if ( objects[i]->use )
		{
			D3DXMatrixIdentity(&objects[i]->worldMatrix);
			D3DXMatrixIdentity(&scaleMatrix);
			D3DXMatrixIdentity(&rotationMatrix);
			D3DXMatrixIdentity(&translationMatrix);

			D3DXMatrixScaling(&scaleMatrix, objects[i]->scale.x, objects[i]->scale.y, objects[i]->scale.z);
			D3DXMatrixMultiply(&objects[i]->worldMatrix, &objects[i]->worldMatrix, &scaleMatrix);
			D3DXMatrixRotationYawPitchRoll(&rotationMatrix, objects[i]->rotation.y, objects[i]->rotation.x, objects[i]->rotation.z);
			D3DXMatrixMultiply(&objects[i]->worldMatrix, &objects[i]->worldMatrix, &rotationMatrix);
			D3DXMatrixTranslation(&translationMatrix, objects[i]->position.x, objects[i]->position.y, objects[i]->position.z);
			D3DXMatrixMultiply(&objects[i]->worldMatrix, &objects[i]->worldMatrix, &translationMatrix);

			pDevice->SetTransform(D3DTS_WORLD, &objects[i]->worldMatrix);

			pDevice->SetStreamSource(0, cGround::pVertexBuffer, 0, sizeof(VERTEX_3D));
			pDevice->SetFVF(FVF_VERTEX_3D);

			pDevice->SetTexture(0, Texture_GetTexture(objects[i]->textureIndex));
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				2
			);
		}
	}
}