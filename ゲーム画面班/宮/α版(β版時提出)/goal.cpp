
#include"common.h"
#include"goal.h"
#include"seika.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"debugproc.h"

cGoal* cGoal::numberOfObjects[NUMBER_OF_GOAL];

LPDIRECT3DVERTEXBUFFER9 cGoal::pVertexBuffer;
VERTEX_3D*				cGoal::pVertex;

//���_�Z�b�g�֐�
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

// �n�ʐݒ�
void cGoal::SetGoal(D3DXVECTOR2 _position)
{
	for (int i = 0; i < NUMBER_OF_GOAL; i++)
	{
		if (!numberOfObjects[i]->use)
		{
			// �g�p
			numberOfObjects[i]->use = true;

			// �ʒu�w��
			numberOfObjects[i]->position.x = _position.x;
			numberOfObjects[i]->position.y = _position.y;

			return;
		}
	}
}

//������
void cGoal::Init()
{
	InitDebugProc();

	for (int i = 0; i < NUMBER_OF_GOAL; i++)
	{
		numberOfObjects[i] = new cGoal;

		// �g�p
		numberOfObjects[i]->use = false;
		// ����
		numberOfObjects[i]->turnOn = false;

		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);
		numberOfObjects[i]->position = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->rotation = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->scale = D3DXVECTOR3(1, 1, 1);
	}

	SetVertex();
}

//�I������
void cGoal::Uninit()
{
	UninitDebugProc();

	for (int i = 0; i < NUMBER_OF_GOAL; i++)
	{
		delete numberOfObjects[i];
	}
}

//�X�V����
void cGoal::Update()
{
	UpdateDebugProc();

	for (int i = 0; i < NUMBER_OF_GOAL; i++)
	{
		// ���΂Ƃ̓����蔻��
		if (cGoal::numberOfObjects[i]->use)
		{
			for (int j = 0; j < NUMBER_OF_SEIKA; j++)
			{
				// ���΂�numberOfObjects[i]�͈̔͂ɂ߂荞��ł��鎞
				if (
					// ���΂̉�����ɂ߂荞��
					(cSeika::numberOfObjects[j]->position.y - SEIKA_VERTICAL_SIZE / 2 < cGoal::numberOfObjects[i]->position.y + GOAL_VERTICAL_SIZE / 2)
					&&
					// ���΂̏オ���ɂ߂荞��
					(cSeika::numberOfObjects[j]->position.y + SEIKA_VERTICAL_SIZE / 2 > cGoal::numberOfObjects[i]->position.y - GOAL_VERTICAL_SIZE / 2)
					&&
					// ���΂̉E�[�����[�ɂ߂荞��
					(cSeika::numberOfObjects[j]->position.x + SEIKA_HORIZONTAL_SIZE / 2 - 2 > cGoal::numberOfObjects[i]->position.x - GOAL_HORIZONTAL_SIZE / 2)
					&&
					// ���΂̍��[���E�[�ɂ߂荞��
					(cSeika::numberOfObjects[j]->position.x - SEIKA_HORIZONTAL_SIZE / 2 + 2 < cGoal::numberOfObjects[i]->position.x + GOAL_HORIZONTAL_SIZE / 2)
					)
				{
					cGoal::numberOfObjects[i]->turnOn = true;
				}
			}

			//PrintDebugProc("���E�\�N�̓_�����[%d]�@%d\n", i, cGoal::numberOfObjects[i]->turnOn);
		}
	}
}

//�|���S���̕`��
void cGoal::Draw()
{
	DrawDebugProc();

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_GOAL; i++)
	{
		if (cGoal::numberOfObjects[i]->use)
		{
			D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);

			D3DXMatrixScaling(&scaleMatrix, numberOfObjects[i]->scale.x, numberOfObjects[i]->scale.y, numberOfObjects[i]->scale.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &scaleMatrix);
			D3DXMatrixRotationYawPitchRoll(&rotationMatrix, numberOfObjects[i]->rotation.y, numberOfObjects[i]->rotation.x, numberOfObjects[i]->rotation.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &rotationMatrix);
			D3DXMatrixTranslation(&translationMatrix, numberOfObjects[i]->position.x, numberOfObjects[i]->position.y, numberOfObjects[i]->position.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &translationMatrix);

			pDevice->SetTransform(D3DTS_WORLD, &numberOfObjects[i]->worldMatrix);

			pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �_����Ԃɂ��ؑ�
			if (numberOfObjects[i]->turnOn)
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