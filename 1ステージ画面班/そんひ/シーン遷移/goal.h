#pragma once

#include"direct3d.h"
#include"vertex.h"

// �낤�����̐�
#define NUMBER_OF_GOAL (1)
// �낤�����̏c���̃T�C�Y
#define GOAL_HORIZONTAL_SIZE	(16.0f)
#define GOAL_VERTICAL_SIZE		(8.0f)
// �Փ˔��a
#define RADIUS_GOAL (GOAL_HORIZONTAL_SIZE / 2)

class cGoal
{
public:

	static cGoal* objects[NUMBER_OF_GOAL];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;

	// �g�p
	bool use;

	// �Փ�
	static bool collision;

	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

	// �R���X�g���N�^
	cGoal(D3DXVECTOR3 _position);

	// ���_
	static void SetVertex();

	// ��{�֐�
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// �z�u
	static void Set(D3DXVECTOR3 _position);
};