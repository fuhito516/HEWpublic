#pragma once

#include"direct3d.h"
#include"vertex.h"
#include"texture.h"

// �w�i���C���[�̐�
#define NUMBER_OF_BACKLAYER (7)

class cBackground
{
public:

	static cBackground* objects[NUMBER_OF_BACKLAYER];

	// �g�p
	bool use;

	TextureIndex textureIndex;

	// �`��
	D3DXMATRIX	worldMatrix;
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;

	// �R���X�g���N�^
	cBackground(TextureIndex _textureIndex, D3DXVECTOR3 _position, D3DXVECTOR3 _scale);

	// ��{�֐�
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// �z�u
	static void SetBackground(TextureIndex _textureIndex, D3DXVECTOR3 _position, D3DXVECTOR3 _scale);
};