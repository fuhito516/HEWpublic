#pragma once

#include"direct3d.h"
#include"vertex.h"

// �{�[�h�̐�(���)
#define NUMBER_OF_GROUND (10)
// �{�[�h�̒��_��
#define NUMBER_OF_GROUND_VERTEXES (4)
// �{�[�h�̏c���̃T�C�Y(�����l)
#define GROUND_VERTICAL_SIZE	(1.0f)
#define GROUND_HORIZONTAL_SIZE	(1.0f)

class cGround
{
// ���ʕ�
public:

	static cGround* numberOfObjects[NUMBER_OF_GROUND]; // �I�u�W�F�N�g�i�[

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;	// ���_�o�b�t�@
	static VERTEX_3D*				pVertex;		// ���_�o�b�t�@�̒��g�𖄂߂�

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