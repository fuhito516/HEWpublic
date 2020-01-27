
#include"common.h"
#include"candle.h"
#include"seika.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"debugproc.h"

cCandle* cCandle::objects[NUMBER_OF_CANDLE];

LPDIRECT3DVERTEXBUFFER9 cCandle::pVertexBuffer;
VERTEX_3D*				cCandle::pVertex;

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

// �n�ʐݒ�
void cCandle::SetCandle(D3DXVECTOR2 _position)
{
	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		if (!objects[i]->use)
		{
			// �g�p
			objects[i]->use = true;

			// �ʒu�w��
			objects[i]->position.x = _position.x;
			objects[i]->position.y = _position.y;

			return;
		}
	}
}

//������
void cCandle::Init()
{
	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		objects[i] = new cCandle;

		// �g�p
		objects[i]->use = false;
		// ����
		objects[i]->collision = false;

		D3DXMatrixIdentity(&objects[i]->worldMatrix);
		objects[i]->position = D3DXVECTOR3(0, 0, 0);
		objects[i]->rotation = D3DXVECTOR3(0, 0, 0);
		objects[i]->scale = D3DXVECTOR3(1, 1, 1);
	}

	SetVertex();
}

//�I������
void cCandle::Uninit()
{
	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		delete objects[i];
	}
}

//�X�V����
void cCandle::Update()
{
	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		// ���΂Ƃ̓����蔻��
		if (cCandle::objects[i]->use)
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
					cCandle::objects[i]->collision = true;
				}
			}

			//PrintDebugProc("���E�\�N�̓_�����[%d]�@%d\n", i, cCandle::objects[i]->collision);
		}
	}
}

//�|���S���̕`��
void cCandle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_CANDLE; i++)
	{
		if (cCandle::objects[i]->use)
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
			if ( objects[i]->collision )
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