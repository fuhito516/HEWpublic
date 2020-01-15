#pragma once

#include"direct3d.h"
#include"vertex.h"

// ���΂̈ړ��X�s�[�h
#define SEIKA_MOVEMENT_SPEED (0.3f)
// ���΂̃W�����v�̗�
#define SEIKA_JUMPPOWER (2.0f)
// ���΂̍ō��������x
#define SEIKA_MAXIMUM_FALLSPEED (0.5f)

// ���΂̐�
#define NUMBER_OF_SEIKA (1)
// ���΂̒��_��
#define NUMBER_OF_SEIKA_VERTEXES (4)
// ���΂̏c���̃T�C�Y
#define SEIKA_VERTICAL_SIZE		(2.0f)
#define SEIKA_HORIZONTAL_SIZE	(2.0f)

class cSeika
{
	// ���ʕ�
public:

	static cSeika* numberOfObjects[NUMBER_OF_SEIKA]; // �I�u�W�F�N�g�i�[

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;	// ���_�o�b�t�@
	static VERTEX_3D*				pVertex;		// ���_�o�b�t�@�̒��g�𖄂߂�

	// �֐�
	static void SetVertex();
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// �v�f��
public:

	// �O�t���[���̈ʒu
	D3DXVECTOR2 pastPosition;

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

	// �`��
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

};