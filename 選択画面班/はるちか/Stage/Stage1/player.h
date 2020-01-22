#pragma once

#include"direct3d.h"
#include"vertex.h"

// �v���C���[�̈ړ��X�s�[�h
#define PLAYER_MOVEMENT_SPEED (0.2f)
// �v���C���[�̃W�����v�̗�
#define PLAYER_JUMPPOWER (1.5f)
// �v���C���[�̍ō��������x
#define PLAYER_MAXIMUM_FALLSPEED (0.3f)
// �v���C���[�̏����ʒu(x, y)
#define PLAYER_INITIAL_POSITION_X (0.0f)
#define PLAYER_INITIAL_POSITION_Y (8.0f)

// �v���C���[�̐�
#define NUMBER_OF_PLAYER (1)
// �v���C���[�̒��_��
#define NUMBER_OF_PLAYER_VERTEXES (4)
// �v���C���[�̏c���̃T�C�Y
#define PLAYER_VERTICAL_SIZE	(4.0f)
#define PLAYER_HORIZONTAL_SIZE	(4.0f)

class cPlayer
{
// ���ʕ�
public:

	static cPlayer* numberOfObjects[NUMBER_OF_PLAYER]; // �I�u�W�F�N�g�i�[

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

	// �W�����v�\����
	bool jumpPossible;
	// �W�����v������
	bool jumping;
	// �W�����v�Œ��̓V��ւ̓����蔻��
	bool hitCeilingWhileJumping;

	// �d�̓J�E���^�[
	float gravityTimer;

	// �����蔻��(���ɓ������Ă���̂�)
	int collision;

	// ���Εێ�
	bool retention;

	// �`��
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

};