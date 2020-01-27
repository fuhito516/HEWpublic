
#include"common.h"
#include"bridge.h"
#include"candle.h"
#include"ground.h"
#include"seika.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"debugproc.h"

cBridge* cBridge::objects[NUMBER_OF_BRIDGE];

// �n�ʐݒ�
void cBridge::SetBridge(D3DXVECTOR2 _gimmickPosition, D3DXVECTOR2 _bridgePosition, D3DXVECTOR2 _bridgeSize)
{
	for (int i = 0; i < NUMBER_OF_BRIDGE; i++)
	{
		if (!objects[i]->use)
		{
			// �g�p
			objects[i]->use = true;

			// �d�|��
			objects[i]->gimmickPosition.x = _gimmickPosition.x;
			objects[i]->gimmickPosition.y = _gimmickPosition.y;

			// ��
			objects[i]->bridgePosition.x = _bridgePosition.x;
			objects[i]->bridgePosition.y = _bridgePosition.y;
			objects[i]->bridgeScale.x = _bridgeSize.x;
			objects[i]->bridgeScale.y = _bridgeSize.y;

			return;
		}
	}
}

//������
void cBridge::Init()
{
	for (int i = 0; i < NUMBER_OF_BRIDGE; i++)
	{
		objects[i] = new cBridge;

		// �g�p
		objects[i]->use = false;
		// ����
		objects[i]->collision = false;

		D3DXMatrixIdentity(&objects[i]->gimmickWorldMatrix);
		objects[i]->gimmickPosition = D3DXVECTOR3(0, 0, 0);
		objects[i]->gimmickRotation = D3DXVECTOR3(0, 0, 0);
		objects[i]->gimmickScale = D3DXVECTOR3(1, 1, 1);

		D3DXMatrixIdentity(&objects[i]->bridgeWorldMatrix);
		objects[i]->bridgePosition = D3DXVECTOR3(0, 0, 0);
		objects[i]->bridgeRotation = D3DXVECTOR3(0, 0, 0);
		objects[i]->bridgeScale = D3DXVECTOR3(1, 1, 1);
	}
}

//�I������
void cBridge::Uninit()
{
	for (int i = 0; i < NUMBER_OF_BRIDGE; i++)
	{
		delete objects[i];
	}
}

//�X�V����
void cBridge::Update()
{
	for (int i = 0; i < NUMBER_OF_BRIDGE; i++)
	{
		// ���΂Ƃ̓����蔻��
		if (cBridge::objects[i]->use)
		{
			for (int j = 0; j < NUMBER_OF_SEIKA; j++)
			{
				// ���΂�objects[i]�͈̔͂ɂ߂荞��ł��鎞
				if (
					// ���΂̉�����ɂ߂荞��
					(cSeika::objects[j]->position.y - SEIKA_VERTICAL_SIZE / 2 < cBridge::objects[i]->gimmickPosition.y + BRIDGE_VERTICAL_SIZE / 2)
					&&
					// ���΂̏オ���ɂ߂荞��
					(cSeika::objects[j]->position.y + SEIKA_VERTICAL_SIZE / 2 > cBridge::objects[i]->gimmickPosition.y - BRIDGE_VERTICAL_SIZE / 2)
					&&
					// ���΂̉E�[�����[�ɂ߂荞��
					(cSeika::objects[j]->position.x + SEIKA_HORIZONTAL_SIZE / 2 > cBridge::objects[i]->gimmickPosition.x - BRIDGE_HORIZONTAL_SIZE / 2)
					&&
					// ���΂̍��[���E�[�ɂ߂荞��
					(cSeika::objects[j]->position.x - SEIKA_HORIZONTAL_SIZE / 2 < cBridge::objects[i]->gimmickPosition.x + BRIDGE_HORIZONTAL_SIZE / 2)
					)
				{
					cBridge::objects[i]->collision = true;
				}
			}

			//PrintDebugProc("�d�|���̓_�����[%d]�@%d\n", i, cBridge::objects[i]->collision);
		}
	}
}

//�|���S���̕`��
void cBridge::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_BRIDGE; i++)
	{
		if (cBridge::objects[i]->use)
		{
			D3DXMatrixIdentity(&objects[i]->gimmickWorldMatrix);

			D3DXMatrixScaling(&scaleMatrix, objects[i]->gimmickScale.x, objects[i]->gimmickScale.y, objects[i]->gimmickScale.z);
			D3DXMatrixMultiply(&objects[i]->gimmickWorldMatrix, &objects[i]->gimmickWorldMatrix, &scaleMatrix);
			D3DXMatrixRotationYawPitchRoll(&rotationMatrix, objects[i]->gimmickRotation.y, objects[i]->gimmickRotation.x, objects[i]->gimmickRotation.z);
			D3DXMatrixMultiply(&objects[i]->gimmickWorldMatrix, &objects[i]->gimmickWorldMatrix, &rotationMatrix);
			D3DXMatrixTranslation(&translationMatrix, objects[i]->gimmickPosition.x, objects[i]->gimmickPosition.y, objects[i]->gimmickPosition.z);
			D3DXMatrixMultiply(&objects[i]->gimmickWorldMatrix, &objects[i]->gimmickWorldMatrix, &translationMatrix);

			pDevice->SetTransform(D3DTS_WORLD, &objects[i]->gimmickWorldMatrix);

			pDevice->SetStreamSource(0, cCandle::pVertexBuffer, 0, sizeof(VERTEX_3D));
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

			if ( objects[i]->collision )
			{
				D3DXMatrixIdentity(&scaleMatrix);
				D3DXMatrixIdentity(&rotationMatrix);
				D3DXMatrixIdentity(&translationMatrix);

				D3DXMatrixIdentity(&objects[i]->bridgeWorldMatrix);

				D3DXMatrixScaling(&scaleMatrix, objects[i]->bridgeScale.x, objects[i]->bridgeScale.y, objects[i]->bridgeScale.z);
				D3DXMatrixMultiply(&objects[i]->bridgeWorldMatrix, &objects[i]->bridgeWorldMatrix, &scaleMatrix);
				D3DXMatrixRotationYawPitchRoll(&rotationMatrix, objects[i]->bridgeRotation.y, objects[i]->bridgeRotation.x, objects[i]->bridgeRotation.z);
				D3DXMatrixMultiply(&objects[i]->bridgeWorldMatrix, &objects[i]->bridgeWorldMatrix, &rotationMatrix);
				D3DXMatrixTranslation(&translationMatrix, objects[i]->bridgePosition.x, objects[i]->bridgePosition.y, objects[i]->bridgePosition.z);
				D3DXMatrixMultiply(&objects[i]->bridgeWorldMatrix, &objects[i]->bridgeWorldMatrix, &translationMatrix);

				pDevice->SetTransform(D3DTS_WORLD, &objects[i]->bridgeWorldMatrix);

				pDevice->SetStreamSource(0, cGround::pVertexBuffer, 0, sizeof(VERTEX_3D));
				pDevice->SetFVF(FVF_VERTEX_3D);

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