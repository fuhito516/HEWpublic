#pragma once

#include"direct3d.h"
#include"vertex.h"

// �{�[�h�̐�(���)
#define NUMBER_OF_GROUND (120)
// �{�[�h�̏c���̃T�C�Y(�����l)
#define GROUND_VERTICAL_SIZE	(1.0f)
#define GROUND_HORIZONTAL_SIZE	(1.0f)

class cGround
{
public:

	static cGround*				objects[NUMBER_OF_GROUND];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;

	// �g�p
	bool use;

	// �`��
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

	// �R���X�g���N�^
	cGround(D3DXVECTOR2 _position, D3DXVECTOR2 _size);

	// ���_
	static void SetVertex();

	// ��{�֐�
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// �z�u
	static void SetGround(D3DXVECTOR2 _position, D3DXVECTOR2 _size);
};