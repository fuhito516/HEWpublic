
// メイン
#include"goal.h"
#include"common.h"
#include"direct3d.h"
#include"texture.h"
#include"input.h"
#include"debugproc.h"
#include<math.h>
// 対象
#include"seika.h"

cGoal* cGoal::objects[NUMBER_OF_GOAL];

LPDIRECT3DVERTEXBUFFER9 cGoal::pVertexBuffer;
VERTEX_3D*				cGoal::pVertex;

bool cGoal::collision = false;

// コンストラクタ
cGoal::cGoal(D3DXVECTOR3 _position)
{
	// 使用
	use = true;

	// 位置
	position = _position;

	// 描画
	D3DXMatrixIdentity(&worldMatrix);
	rotation = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(1, 1, 1);
}

// 頂点
void cGoal::SetVertex()
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

	pVertex[0].vtx = D3DXVECTOR3(-GOAL_HORIZONTAL_SIZE / 2, -GOAL_VERTICAL_SIZE / 2, 0.0f);
	pVertex[1].vtx = D3DXVECTOR3(-GOAL_HORIZONTAL_SIZE / 2, GOAL_VERTICAL_SIZE / 2, 0.0f);
	pVertex[2].vtx = D3DXVECTOR3(GOAL_HORIZONTAL_SIZE / 2, -GOAL_VERTICAL_SIZE / 2, 0.0f);
	pVertex[3].vtx = D3DXVECTOR3(GOAL_HORIZONTAL_SIZE / 2, GOAL_VERTICAL_SIZE / 2, 0.0f);
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
void cGoal::Init()
{
	for (int i = 0; i < NUMBER_OF_GOAL; i++)
	{
		objects[i] = NULL;
	}

	// 灯る
	collision = false;

	// 頂点
	SetVertex();
}
// 終了
void cGoal::Uninit()
{
	for (int i = 0; i < NUMBER_OF_GOAL; i++)
	{
		if (objects[i] != NULL)
		{
			delete objects[i];
			objects[i] = NULL;
		}
	}
}
// 更新
void cGoal::Update()
{
	for (int i = 0; i < NUMBER_OF_GOAL; i++)
	{
		// 聖火との当たり判定
		if (objects[i] != NULL)
		{
			if (objects[i]->use)
			{
				for (int j = 0; j < NUMBER_OF_SEIKA; j++)
				{
					// 聖火がobjects[i]の範囲にめり込んでいる時
					if (pow(objects[i]->position.x - cSeika::objects[0]->position.x, 2) + pow(objects[i]->position.y - cSeika::objects[0]->position.y, 2) <= pow(RADIUS_SEIKA + RADIUS_GOAL, 2))
					{
						collision = true;
					}
						//// 聖火の下が上にめり込む
						//(cSeika::objects[j]->position.y - SEIKA_VERTICAL_SIZE / 2 < cGoal::objects[i]->position.y + GOAL_VERTICAL_SIZE / 2)
						//&&
						//// 聖火の上が下にめり込む
						//(cSeika::objects[j]->position.y + SEIKA_VERTICAL_SIZE / 2 > cGoal::objects[i]->position.y - GOAL_VERTICAL_SIZE / 2)
						//&&
						//// 聖火の右端が左端にめり込む
						//(cSeika::objects[j]->position.x + SEIKA_HORIZONTAL_SIZE / 2 - 2 > cGoal::objects[i]->position.x - GOAL_HORIZONTAL_SIZE / 2)
						//&&
						//// 聖火の左端が右端にめり込む
						//(cSeika::objects[j]->position.x - SEIKA_HORIZONTAL_SIZE / 2 + 2 < cGoal::objects[i]->position.x + GOAL_HORIZONTAL_SIZE / 2)
						//)
				}
			}

			//PrintDebugProc("ロウソクの点灯状態[%d]　%d\n", i, cGoal::objects[i]->collision);
		}
	}
}
// 描画
void cGoal::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_GOAL; i++)
	{
		if (objects[i] != NULL)
		{
			if (objects[i]->use)
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

				// 点灯状態による切替
				if (objects[i]->collision)
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_GOAL2));
				}
				else
				{
					pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_GOAL1));
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
}

// 配置
void cGoal::Set(D3DXVECTOR3 _position)
{
	for (int i = 0; i < NUMBER_OF_GOAL; i++)
	{
		if (objects[i] == NULL)
		{
			objects[i] = new cGoal(_position);
			break;
		}
	}
}