#pragma once

#include"direct3d.h"
#include"vertex.h"

// �낤�����̐�
#define NUMBER_OF_CANDLE (10)
// �낤�����̏c���̃T�C�Y
#define CANDLE_VERTICAL_SIZE	(4.0f)
#define CANDLE_HORIZONTAL_SIZE	(4.0f)

class cCandle
{
public:

	static cCandle* objects[NUMBER_OF_CANDLE];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;

	// �g�p
	bool use;

	// �Փ�
	bool collision;

	// �`��
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

	// �R���X�g���N�^
	cCandle(D3DXVECTOR2 _position);

	// ���_
	static void SetVertex();

	// ��{�֐�
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// �z�u
	static void SetCandle(D3DXVECTOR2 _position);
};