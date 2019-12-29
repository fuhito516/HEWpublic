#pragma once

#include"direct3d.h"
#include"vertex.h"

// �{�[�h�̃X�s�[�h
#define GROUND_MOVE_SPEED (0.05f)

// �{�[�h�̐�(���)
#define NUMBER_OF_GROUND_MOVE (10)
// �{�[�h�̒��_��
#define NUMBER_OF_GROUND_VERTEXES_MOVE (4)
// �{�[�h�̏c���̃T�C�Y(�����l)
#define GROUND_VERTICAL_SIZE_MOVE	(1.0f)
#define GROUND_HORIZONTAL_SIZE_MOVE	(1.0f)

class cMoveGround
{
	// ���ʕ�
public:

	static cMoveGround* numberOfObjects[NUMBER_OF_GROUND_MOVE]; // �I�u�W�F�N�g�i�[

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;	// ���_�o�b�t�@
	static VERTEX_3D*				pVertex;		// ���_�o�b�t�@�̒��g�𖄂߂�

	// �֐�
	static void SetVertex();
	static void SetGround(D3DXVECTOR2 _position, D3DXVECTOR2 _size, float _moveWidth);
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

// �v�f��
public:

	// �ǉ��p�����[�^
	float speed;
	float moveWidth;

	// �g�p
	bool use;

	// �T�C�Y
	D3DXVECTOR2 size;

	// �s��
	D3DXVECTOR3	position;
	D3DXVECTOR3 pastPosition;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;
};