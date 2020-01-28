#pragma once

#include"direct3d.h"
#include"vertex.h"

// �{�[�h�̐�(���)
#define NUMBER_OF_GROUND (10)
// �{�[�h�̏c���̃T�C�Y(�����l)
#define GROUND_VERTICAL_SIZE	(1.0f)
#define GROUND_HORIZONTAL_SIZE	(1.0f)

class cGround
{
// ���ʕ�
public:

	static cGround*				objects[NUMBER_OF_GROUND];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;

	// �֐�
	static void SetVertex();
	static void SetGround(D3DXVECTOR2 _position, D3DXVECTOR2 _size);
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// �v�f��
public:

	// �g�p
	bool use;

	// �T�C�Y
	D3DXVECTOR2 size;

	// �s��
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;
};