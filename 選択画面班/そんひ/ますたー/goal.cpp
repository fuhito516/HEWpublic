
// ���C��
#include"goal.h"
#include"common.h"
#include"direct3d.h"
#include"texture.h"
#include"input.h"
#include"debugproc.h"
#include<math.h>
// �Ώ�
#include"seika.h"

cGoal* cGoal::objects[NUMBER_OF_GOAL];

LPDIRECT3DVERTEXBUFFER9 cGoal::pVertexBuffer;
VERTEX_3D*				cGoal::pVertex;

bool cGoal::collision = false;

// �R���X�g���N�^
cGoal::cGoal(D3DXVECTOR3 _position)
{
	// �g�p
	use = true;

	// �ʒu
	position = _position;

	// �`��
	D3DXMatrixIdentity(&worldMatrix);
	rotation = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(1, 1, 1);
}

// ���_
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

// ������
void cGoal::Init()
{
	for (int i = 0; i < NUMBER_OF_GOAL; i++)
	{
		objects[i] = NULL;
	}

	// ����
	collision = false;

	// ���_
	SetVertex();
}
// �I��
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
// �X�V
void cGoal::Update()
{
	for (int i = 0; i < NUMBER_OF_GOAL; i++)
	{
		// ���΂Ƃ̓����蔻��
		if (objects[i] != NULL)
		{
			if (objects[i]->use)
			{
				for (int j = 0; j < NUMBER_OF_SEIKA; j++)
				{
					// ���΂�objects[i]�͈̔͂ɂ߂荞��ł��鎞
					if (pow(objects[i]->position.x - cSeika::objects[0]->position.x, 2) + pow(objects[i]->position.y - cSeika::objects[0]->position.y, 2) <= pow(RADIUS_SEIKA + RADIUS_GOAL, 2))
					{
						collision = true;
					}
						//// ���΂̉�����ɂ߂荞��
						//(cSeika::objects[j]->position.y - SEIKA_VERTICAL_SIZE / 2 < cGoal::objects[i]->position.y + GOAL_VERTICAL_SIZE / 2)
						//&&
						//// ���΂̏オ���ɂ߂荞��
						//(cSeika::objects[j]->position.y + SEIKA_VERTICAL_SIZE / 2 > cGoal::objects[i]->position.y - GOAL_VERTICAL_SIZE / 2)
						//&&
						//// ���΂̉E�[�����[�ɂ߂荞��
						//(cSeika::objects[j]->position.x + SEIKA_HORIZONTAL_SIZE / 2 - 2 > cGoal::objects[i]->position.x - GOAL_HORIZONTAL_SIZE / 2)
						//&&
						//// ���΂̍��[���E�[�ɂ߂荞��
						//(cSeika::objects[j]->position.x - SEIKA_HORIZONTAL_SIZE / 2 + 2 < cGoal::objects[i]->position.x + GOAL_HORIZONTAL_SIZE / 2)
						//)
				}
			}

			//PrintDebugProc("���E�\�N�̓_�����[%d]�@%d\n", i, cGoal::objects[i]->collision);
		}
	}
}
// �`��
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

				// �_����Ԃɂ��ؑ�
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

// �z�u
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