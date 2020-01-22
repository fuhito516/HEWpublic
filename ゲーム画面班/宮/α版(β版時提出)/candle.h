#pragma once

#include"direct3d.h"
#include"vertex.h"

// �낤�����̐�
#define NUMBER_OF_CANDLE (1)
// �낤�����̏c���̃T�C�Y
#define CANDLE_VERTICAL_SIZE	(4.0f)
#define CANDLE_HORIZONTAL_SIZE	(4.0f)

class cCandle
{
// ���ʕ�
public:

	static cCandle* numberOfObjects[NUMBER_OF_CANDLE];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;

	// �֐�
	static void SetVertex();
	static void SetCandle(D3DXVECTOR2 _position);
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// �v�f��
public:

	// �g�p
	bool use;
	// ����
	bool turnOn;

	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;
};