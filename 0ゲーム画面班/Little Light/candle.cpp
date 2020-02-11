
#include"common.h"
#include"candle.h"
#include"seika.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"debugproc.h"

#include"sound.h"

cCandle* cCandle::objects[NUMBER_OF_CANDLE];

LPDIRECT3DVERTEXBUFFER9 cCandle::pVertexBuffer;
VERTEX_3D*				cCandle::pVertex;

cCandle::cCandle(D3DXVECTOR2 _position)
{
	// �g�p
	use = true;

	// �Փ�
	collision = false;

	// �`��
	D3DXMatrixIdentity(&worldMatrix);
	position.x = _position.x;
	position.y = _position.y;
	position.z = 1;
	rotation = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(1, 1, 1);
}

// ���_
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

// ������
void cCandle::Init()
{
	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		objects[i] = NULL;
	}

	SetVertex();
}
// �I��
void cCandle::Uninit()
{
	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		if (objects[i] != NULL)
		{
			delete objects[i];
			objects[i] = NULL;
		}
	}
}
// �X�V
void cCandle::Update()
{
	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		if (objects[i] != NULL)
		{
			if (objects[i]->use)
			{
				for (int j = 0; j < NUMBER_OF_SEIKA; j++)
				{
					// ���΂�objects[i]�͈̔͂ɂ߂荞��ł��鎞
					if (
						// ���΂̉�����ɂ߂荞��
						(cSeika::objects[j]->position.y - SEIKA_VERTICAL_SIZE / 2 < cCandle::objects[i]->position.y + CANDLE_VERTICAL_SIZE / 2)
						&&
						// ���΂̏オ���ɂ߂荞��
						(cSeika::objects[j]->position.y + SEIKA_VERTICAL_SIZE / 2 > cCandle::objects[i]->position.y - CANDLE_VERTICAL_SIZE / 2)
						&&
						// ���΂̉E�[�����[�ɂ߂荞��
						(cSeika::objects[j]->position.x + SEIKA_HORIZONTAL_SIZE / 2 > cCandle::objects[i]->position.x - CANDLE_HORIZONTAL_SIZE / 2)
						&&
						// ���΂̍��[���E�[�ɂ߂荞��
						(cSeika::objects[j]->position.x - SEIKA_VERTICAL_SIZE / 2 < cCandle::objects[i]->position.x + CANDLE_HORIZONTAL_SIZE / 2)
						)
					{
						if (!objects[i]->collision)
						{
							cCandle::objects[i]->collision = true;
						}
					}
				}

				//PrintDebugProc("���E�\�N�̓_�����[%d]�@%d\n", i, cCandle::objects[i]->collision);
			}
		}
	}
}
// �`��
void cCandle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
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

				// �_����Ԃɂ��ؑ�
				if (objects[i]->collision)
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
}

// �z�u
void cCandle::SetCandle(D3DXVECTOR2 _position)
{
	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		if (objects[i] == NULL)
		{
			objects[i] = new cCandle(_position);
			break;
		}
	}
}