
#include"common.h"
#include"background.h"

#include"direct3d.h"
#include"texture.h"
#include"input.h"

#include"ground.h"

#include"debugproc.h"

cBackground* cBackground::numberOfObjects[NUMBER_OF_BACKLAYER];

// �n�ʐݒ�
void cBackground::SetBackground(TextureIndex _textureIndex, D3DXVECTOR3 _position, D3DXVECTOR3 _scale)
{
	for (int i = 0; i < NUMBER_OF_BACKLAYER; i++)
	{
		if ( !numberOfObjects[i]->use )
		{
			numberOfObjects[i]->use = true;

			// ���
			numberOfObjects[i]->textureIndex = _textureIndex;
			numberOfObjects[i]->position = _position;
			numberOfObjects[i]->scale = _scale;

			return;
		}
	}
}

//������
void cBackground::Init()
{
	for (int i = 0; i < NUMBER_OF_BACKLAYER; i++)
	{
		numberOfObjects[i] = new cBackground;

		numberOfObjects[i]->use = false;
		numberOfObjects[i]->textureIndex = TEXTURE_INDEX_MAX;

		D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);
		numberOfObjects[i]->position = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->rotation = D3DXVECTOR3(0, 0, 0);
		numberOfObjects[i]->scale = D3DXVECTOR3(1, 1, 1);
	}
}
//�I������
void cBackground::Uninit()
{
	for (int i = 0; i < NUMBER_OF_BACKLAYER; i++)
	{
		delete numberOfObjects[i];
	}
}
//�X�V����
void cBackground::Update()
{

}

//�|���S���̕`��
void cBackground::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX translationMatrix;

	int i = 0;
	for (int i = 0; i < NUMBER_OF_BACKLAYER; i++)
	{
		if ( numberOfObjects[i]->use )
		{
			D3DXMatrixIdentity(&numberOfObjects[i]->worldMatrix);
			D3DXMatrixIdentity(&scaleMatrix);
			D3DXMatrixIdentity(&rotationMatrix);
			D3DXMatrixIdentity(&translationMatrix);

			D3DXMatrixScaling(&scaleMatrix, numberOfObjects[i]->scale.x, numberOfObjects[i]->scale.y, numberOfObjects[i]->scale.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &scaleMatrix);
			D3DXMatrixRotationYawPitchRoll(&rotationMatrix, numberOfObjects[i]->rotation.y, numberOfObjects[i]->rotation.x, numberOfObjects[i]->rotation.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &rotationMatrix);
			D3DXMatrixTranslation(&translationMatrix, numberOfObjects[i]->position.x, numberOfObjects[i]->position.y, numberOfObjects[i]->position.z);
			D3DXMatrixMultiply(&numberOfObjects[i]->worldMatrix, &numberOfObjects[i]->worldMatrix, &translationMatrix);

			pDevice->SetTransform(D3DTS_WORLD, &numberOfObjects[i]->worldMatrix);

			pDevice->SetStreamSource(0, cGround::pVertexBuffer, 0, sizeof(VERTEX_3D));
			pDevice->SetFVF(FVF_VERTEX_3D);

			pDevice->SetTexture(0, Texture_GetTexture(numberOfObjects[i]->textureIndex));
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,
				0,
				2
			);
		}
	}
}