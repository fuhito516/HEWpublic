#pragma once

#include"direct3d.h"
#include"vertex.h"

// �낤�����̐�
#define NUMBER_OF_GOAL (1)
// �낤�����̏c���̃T�C�Y
#define GOAL_VERTICAL_SIZE		(8.0f)
#define GOAL_HORIZONTAL_SIZE	(16.0f)

class cGoal
{
	// ���ʕ�
public:

	static cGoal* numberOfObjects[NUMBER_OF_GOAL];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;

	// �֐�
	static void SetVertex();
	static void SetGoal(D3DXVECTOR2 _position);
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