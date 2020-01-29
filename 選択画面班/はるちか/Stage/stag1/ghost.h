#pragma once

#include"direct3d.h"
#include"vertex.h"

// �I�u�W�F�N�g��
#define NUMBER_OF_GHOST (1)
// �T�C�Y
#define HORIZONTAL_SIZE_GHOST	(4.0f)
#define VERTICAL_SIZE_GHOST		(4.0f)
// �X�s�[�h
#define SPEED_GHOST (0.1f)
// �Փ˔��a
#define RADIUS_GHOST (HORIZONTAL_SIZE_GHOST / 2)

class cGhost
{
public:

	// �I�u�W�F�N�g
	static cGhost* objects[NUMBER_OF_GHOST];

	// ���_
	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;
	static void SetVertex();

	// �g�p
	bool use;
	static void Set(D3DXVECTOR3 _position, float _width_move);
	cGhost(D3DXVECTOR3 _position, float _width_move);

	// �p�����[�^
	float width_move;
	D3DXVECTOR3 settingPosition;
	int moveDirection;
	static bool collision;

	// �`��
	D3DXMATRIX	worldMatrix;
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;

	// ��{�֐�
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	void Move();
	void CollisionInspection();
};