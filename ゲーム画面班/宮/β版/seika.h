#pragma once

#include"direct3d.h"
#include"vertex.h"

// ���΂̈ړ��X�s�[�h
#define SEIKA_MOVEMENT_SPEED (1.0f)
// ���΂̍ō��������x
#define SEIKA_MAXSPEED (1.0f)

// ���΂̐�
#define NUMBER_OF_SEIKA (1)
// ���΂̏c���̃T�C�Y
#define SEIKA_VERTICAL_SIZE		(2.0f)
#define SEIKA_HORIZONTAL_SIZE	(2.0f)

class cSeika
{
// ���ʕ�
public:

	static cSeika* numberOfObjects[NUMBER_OF_SEIKA];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;
	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer_light;
	static VERTEX_3D*				pVertex_light;

	// �ȑO�̎���
	int owner;

	// �ړ�����
	int directionVertical;
	int directionHorizontal;

	// �W�����v������
	bool jumping;
	// �W�����v�Œ��̓V��ւ̓����蔻��
	bool hitCeilingWhileJumping;
	// �W�����v�ϔ���
	bool jumped;

	// �d�̓J�E���^�[
	float gravityTimer;

	// �����蔻��(���ɓ������Ă���̂�)
	int collision;

	// �O�t���[���̈ʒu
	D3DXVECTOR2 pastPosition;

	// �`��
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

	D3DXVECTOR3	position_light;
	D3DXVECTOR3	rotation_light;
	D3DXVECTOR3	scale_light;
	D3DXMATRIX	worldMatrix_light;

	static void SetVertex();
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};