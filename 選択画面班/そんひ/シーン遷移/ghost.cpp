
// メイン
#include"ghost.h"
#include"common.h"
#include"direct3d.h"
#include<math.h>
// 環境
#include"debugproc.h"
// テクスチャ
#include"texture.h"
// 対象
#include"player.h"

cGhost* cGhost::objects[NUMBER_OF_GHOST];

LPDIRECT3DVERTEXBUFFER9 cGhost::pVertexBuffer;
VERTEX_3D*				cGhost::pVertex;

bool cGhost::collision = false;

// 頂点
void cGhost::SetVertex()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	pD3DDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVertexBuffer,
		NULL
	);

	pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vtx = D3DXVECTOR3(-HORIZONTAL_SIZE_GHOST / 2, -VERTICAL_SIZE_GHOST / 2, 0.0f);	// 左下
	pVertex[1].vtx = D3DXVECTOR3(-HORIZONTAL_SIZE_GHOST / 2,  VERTICAL_SIZE_GHOST / 2, 0.0f);	// 左上
	pVertex[2].vtx = D3DXVECTOR3( HORIZONTAL_SIZE_GHOST / 2, -VERTICAL_SIZE_GHOST / 2, 0.0f);	// 右下
	pVertex[3].vtx = D3DXVECTOR3( HORIZONTAL_SIZE_GHOST / 2,  VERTICAL_SIZE_GHOST / 2, 0.0f);	// 右上
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

// 使用
void cGhost::Set(D3DXVECTOR3 _position, float _width_move)
{
	for (int i = 0; i < NUMBER_OF_GHOST; i++)
	{
		if (objects[i] == NULL)
		{
			objects[i] = new cGhost(_position, _width_move);
			break;
		}
	}
}
cGhost::cGhost(D3DXVECTOR3 _position, float _width_move)
{
	// 使用
	use = true;

	// パラメータ
	width_move = _width_move;
	settingPosition = _position;
	moveDirection = DIRECTION_RIGHT;
	collision = false;

	// 描画
	D3DXMatrixIdentity(&worldMatrix);
	position = settingPosition;
	rotation = D3DXVECTOR3(0, 0, 0);
	scale	 = D3DXVECTOR3(1, 1, 1);
}

// 基本関数
void cGhost::Init()
{
	for (int i = 0; i < NUMBER_OF_GHOST; i++)
	{
		objects[i] = NULL;
	}

	SetVertex();
}
void cGhost::Uninit()
{
	for (int i = 0; i < NUMBER_OF_GHOST; i++)
	{
		if (objects[i] != NULL)
		{
			delete objects[i];
			objects[i] = NULL;
		}
	}
}
void cGhost::Update()
{
	for (int i = 0; i < NUMBER_OF_GHOST; i++)
	{
		if (objects[i] != NULL)
		{
			if (objects[i]->use)
			{
				// 移動
				objects[i]->Move();
				// 衝突チェック
				objects[i]->CollisionInspection();
			}
		}
	}
}
void cGhost::Draw()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_GHOST; i++)
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

				pD3DDevice->SetTransform(D3DTS_WORLD, &objects[i]->worldMatrix);

				pD3DDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));
				pD3DDevice->SetFVF(FVF_VERTEX_3D);

				pD3DDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_GHOST));
				pD3DDevice->DrawPrimitive
				(
					D3DPT_TRIANGLESTRIP,
					0,
					2
				);
			}
		}
	}
}

void cGhost::Move()
{
	if (position.x > settingPosition.x + width_move / 2)
	{
		moveDirection = DIRECTION_LEFT;
	}
	if (position.x < settingPosition.x - width_move / 2)
	{
		moveDirection = DIRECTION_RIGHT;
	}

	if (moveDirection == DIRECTION_RIGHT)
	{
		position.x += SPEED_GHOST;
	}
	if (moveDirection == DIRECTION_LEFT)
	{
		position.x -= SPEED_GHOST;
	}
}
void cGhost::CollisionInspection()
{
	if (pow(position.x - cPlayer::objects[0]->position.x, 2)+ pow(position.y - cPlayer::objects[0]->position.y, 2) <= pow(RADIUS_PLAYER + RADIUS_GHOST, 2))
	{
		collision = true;
	}

	PrintDebugProc("衝突判定　%d\n", (int)collision);
}