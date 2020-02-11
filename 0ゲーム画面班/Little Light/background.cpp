
#include"common.h"
#include"background.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"ground.h"

#include"debugproc.h"

cBackground* cBackground::objects[NUMBER_OF_BACKLAYER];

// コンストラクタ
cBackground::cBackground(TextureIndex _textureIndex, D3DXVECTOR3 _position, D3DXVECTOR3 _scale)
{
	// 使用
	use = true;

	// 描画
	D3DXMatrixIdentity(&worldMatrix);
	textureIndex = _textureIndex;
	position = _position;
	rotation = D3DXVECTOR3(0, 0, 0);
	scale = _scale;
}

// 初期化
void cBackground::Init()
{
	for (int i = 0; i < NUMBER_OF_BACKLAYER; i++)
	{
		objects[i] = NULL;
	}
}
// 終了
void cBackground::Uninit()
{
	for (int i = 0; i < NUMBER_OF_BACKLAYER; i++)
	{
		if (objects[i] != NULL)
		{
			delete objects[i];
			objects[i] = NULL;
		}
	}
}
// 更新
void cBackground::Update()
{

}
// 描画
void cBackground::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_BACKLAYER; i++)
	{
		if (objects[i] != NULL)
		{
			if (objects[i]->use)
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
}

// 配置
void cBackground::SetBackground(TextureIndex _textureIndex, D3DXVECTOR3 _position, D3DXVECTOR3 _scale)
{
	for (int i = 0; i < NUMBER_OF_BACKLAYER; i++)
	{
		if (objects[i] == NULL)
		{
			objects[i] = new cBackground(_textureIndex, _position, _scale);
			break;
		}
	}
}