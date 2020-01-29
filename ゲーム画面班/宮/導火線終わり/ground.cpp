
#include"common.h"
#include"ground.h"
#include"player.h"
#include"seika.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

cGround* cGround::objects[NUMBER_OF_GROUND];

LPDIRECT3DVERTEXBUFFER9 cGround::pVertexBuffer;
VERTEX_3D*				cGround::pVertex;

// コンストラクタ
cGround::cGround(D3DXVECTOR2 _position, D3DXVECTOR2 _size)
{
	// 使用
	use = true;

	// 描画
	D3DXMatrixIdentity(&worldMatrix);
	position.x = _position.x;
	position.y = _position.y;
	position.z = 0;
	rotation = D3DXVECTOR3(0, 0, 0);
	scale.x = _size.x;
	scale.y = _size.y;
	scale.z = 1;
}

// 頂点
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

// 配置
void cGround::SetGround(D3DXVECTOR2 _position, D3DXVECTOR2 _size)
{
	for (int i = 0; i < NUMBER_OF_GROUND; i++)
	{
		if (objects[i] == NULL)
		{
			objects[i] = new cGround(_position, _size);
			break;
		}
	}
}

// 初期化
void cGround::Init()
{
	for (int i = 0; i < NUMBER_OF_GROUND; i++)
	{
		objects[i] = NULL;
	}

	SetVertex();
}
// 終了
void cGround::Uninit()
{
	for (int i = 0; i < NUMBER_OF_GROUND; i++)
	{
		if (objects[i] != NULL)
		{
			delete objects[i];
			objects[i] = NULL;
		}
	}
}
// 更新
void cGround::Update()
{
	
}
// 描画
void cGround::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_GROUND; i++)
	{
		if (objects[i] != NULL)
		{
			if (objects[i]->use)
			{
				// 行列初期化
				D3DXMatrixIdentity(&objects[i]->worldMatrix);

				D3DXMatrixScaling(&scaleMatrix, objects[i]->scale.x, objects[i]->scale.y, objects[i]->scale.z);
				D3DXMatrixMultiply(&objects[i]->worldMatrix, &objects[i]->worldMatrix, &scaleMatrix);

				D3DXMatrixRotationYawPitchRoll(&rotationMatrix, objects[i]->rotation.y, objects[i]->rotation.x, objects[i]->rotation.z);
				D3DXMatrixMultiply(&objects[i]->worldMatrix, &objects[i]->worldMatrix, &rotationMatrix);

				D3DXMatrixTranslation(&translationMatrix, objects[i]->position.x, objects[i]->position.y, objects[i]->position.z);
				D3DXMatrixMultiply(&objects[i]->worldMatrix, &objects[i]->worldMatrix, &translationMatrix);

				// ワールドマトリックスを設定
				pDevice->SetTransform(D3DTS_WORLD, &objects[i]->worldMatrix);

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
}