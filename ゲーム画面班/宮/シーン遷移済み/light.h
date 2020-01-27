#pragma once

#include"direct3d.h"
#include"vertex.h"
#include"common.h"
#include"seika.h"

// �T�C�Y
#define LIGHT_HORIZONTAL_SIZE	(SCREEN_WIDTH / 5)
#define LIGHT_VERTICAL_SIZE		(LIGHT_HORIZONTAL_SIZE / 2)
// ���C�t(GAMEOVER�܂ł̐�������)
#define SECONDS_FOR_DEAD (10.0f)

class cLight
{
public:

	static cLight* objects[NUMBER_OF_SEIKA];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;

	// �p�����[�^
	float life;
	static bool dead;

	// �`��
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

	// �R���X�g���N�^
	cLight();

	// ���_
	static void SetVertex();

	// ��{�֐�
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// �z�u
	static void Set();
};