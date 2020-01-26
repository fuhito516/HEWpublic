
// メイン
#include"light.h"
#include"common.h"
#include"direct3d.h"
// 環境
#include"texture.h"
#include"input.h"
#include"debugproc.h"
// ターゲット
#include"seika.h"
#include"player.h"

cLight* cLight::objects[NUMBER_OF_SEIKA];

LPDIRECT3DVERTEXBUFFER9 cLight::pVertexBuffer;
VERTEX_3D*				cLight::pVertex;

// コンストラクタ
cLight::cLight()
{
	// 描画
	D3DXMatrixIdentity(&worldMatrix);
	position = D3DXVECTOR3(cSeika::objects[0]->position.x, cSeika::objects[0]->position.y, 0);
	rotation = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(1, 1, 1);
}

// 頂点
void cLight::SetVertex()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	// light
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

	pVertex[0].vtx = D3DXVECTOR3(-LIGHT_HORIZONTAL_SIZE / 2, -LIGHT_VERTICAL_SIZE / 2, 0.0f);
	pVertex[1].vtx = D3DXVECTOR3(-LIGHT_HORIZONTAL_SIZE / 2, LIGHT_VERTICAL_SIZE / 2, 0.0f);
	pVertex[2].vtx = D3DXVECTOR3(LIGHT_HORIZONTAL_SIZE / 2, -LIGHT_VERTICAL_SIZE / 2, 0.0f);
	pVertex[3].vtx = D3DXVECTOR3(LIGHT_HORIZONTAL_SIZE / 2, LIGHT_VERTICAL_SIZE / 2, 0.0f);
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

// 初期化
void cLight::Init()
{
	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		objects[i] = NULL;
	}

	SetVertex();
}
// 終了
void cLight::Uninit()
{
	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		if (objects[i] != NULL)
		{
			delete objects[i];
			objects[i] = NULL;
		}
		
	}
}
// 更新
void cLight::Update()
{
	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		if (objects[i] != NULL)
		{
			objects[i]->position = D3DXVECTOR3(cSeika::objects[i]->position.x, cSeika::objects[i]->position.y, -1);
		}
	}
}
// 描画
void cLight::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		if (objects[i] != NULL)
		{
			D3DXMatrixIdentity(&objects[i]->worldMatrix);

			D3DXMatrixScaling(&scaleMatrix, objects[i]->scale.x, objects[i]->scale.y, objects[i]->scale.z);
			D3DXMatrixMultiply(&objects[i]->worldMatrix, &objects[i]->worldMatrix, &scaleMatrix);

			D3DXMatrixRotationYawPitchRoll(&rotationMatrix, objects[i]->rotation.y, objects[i]->rotation.x, objects[i]->rotation.z);
			D3DXMatrixMultiply(&objects[i]->worldMatrix, &objects[i]->worldMatrix, &rotationMatrix);

			D3DXMatrixTranslation(&translationMatrix, objects[i]->position.x, objects[i]->position.y, objects[i]->position.z);
			D3DXMatrixMultiply(&objects[i]->worldMatrix, &objects[i]->worldMatrix, &translationMatrix);

			pDevice->SetTransform(D3DTS_WORLD, &objects[i]->worldMatrix);

			pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));
			pDevice->SetFVF(FVF_VERTEX_3D);

			pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_TEST1));
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				2
			);
		}
	}
}

// 配置
void cLight::Set()
{
	for (int i = 0; i < NUMBER_OF_SEIKA; i++)
	{
		if (objects[i] == NULL)
		{
			objects[i] = new cLight;
			break;
		}
	}
}