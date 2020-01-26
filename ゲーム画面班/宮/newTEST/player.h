#pragma once

#include"direct3d.h"
#include"vertex.h"

// �v���C���[�̈ړ��X�s�[�h
#define PLAYER_MOVEMENT_SPEED (0.2f)
// �v���C���[�̃W�����v�̗�
#define PLAYER_JUMPPOWER (0.8f)
// �v���C���[�̍ō��������x
#define PLAYER_MAXIMUM_FALLSPEED (1.0f)
// �v���C���[�̏����ʒu(x, y)
#define PLAYER_INITIAL_POSITION_X (0.0f)
#define PLAYER_INITIAL_POSITION_Y (8.0f)

// �v���C���[�̐�
#define NUMBER_OF_PLAYER (1)
// �c���̃T�C�Y
#define PLAYER_HORIZONTAL_SIZE	(4.0f)
#define PLAYER_VERTICAL_SIZE	(4.0f)
// ��̏c���̃T�C�Y
#define YA_VERTICAL_SIZE	(2.0f)
#define YA_HORIZONTAL_SIZE	(4.0f)

// �Փ˔��a
#define RADIUS_PLAYER (PLAYER_HORIZONTAL_SIZE / 2)

class cPlayer
{
public:

	static cPlayer* objects[NUMBER_OF_PLAYER];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;
	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer_ya;
	static VERTEX_3D*				pVertex_ya;

	// �O�t���[���̈ʒu
	D3DXVECTOR2 pastPosition;

	// �ړ�����
	int directionVertical;
	int pastDirectionHorizontal;
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

	// ���΂𓊂��郂�[�h
	bool throwMode;
	// ���Εێ�
	bool retention;
	// ���΂̓��������
	int throwDegree;

	// �`��
	D3DXMATRIX	worldMatrix;
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;

	D3DXMATRIX	worldMatrix_ya;
	D3DXVECTOR3	position_ya;
	D3DXVECTOR3	rotation_ya;
	D3DXVECTOR3	scale_ya;

	// �R���X�g���N�^
	cPlayer(D3DXVECTOR3 _position);

	static void SetVertex();

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static void Set(D3DXVECTOR3 _position);
};