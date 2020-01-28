#pragma once

#include"direct3d.h"
#include"vertex.h"

// �{�[�h�̐�(���)
#define NUMBER_OF_GROUND_MOVE (50)
// �{�[�h�̒��_��
#define NUMBER_OF_GROUND_VERTEXES_MOVE (4)
// �{�[�h�̏c���̃T�C�Y(�����l)
#define GROUND_VERTICAL_SIZE_MOVE	(1.0f)
#define GROUND_HORIZONTAL_SIZE_MOVE	(1.0f)

class cMoveGround
{
	// ���ʕ�
public:
	static cMoveGround* objects[NUMBER_OF_GROUND_MOVE]; // �I�u�W�F�N�g�i�[

	static LPDIRECT3DVERTEXBUFFER9	pMoveVertexBuffer;	// ���_�o�b�t�@
	static VERTEX_3D*				pMoveVertex;		// ���_�o�b�t�@�̒��g�𖄂߂�

													// �֐�
	static void SetVertex();
	virtual void SetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize, D3DXVECTOR2 _distance);
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	// �v�f��
public:

	// �g�p
	bool use;

	// �t���[���J�E���^�[
	int frameCounter;

	//�ړ����x
	float spead = 0.05f;

	// �O�t���[���̈ʒu
	//D3DXVECTOR3 pastMposition;

	// �T�C�Y
	D3DXVECTOR2 size;
	//�ړ�����
	D3DXVECTOR2 distance;

	//�ŏ��̈ʒu
	D3DXVECTOR3 fastMovePos;

	// �s��
	D3DXVECTOR3	Mposition;
	D3DXVECTOR3	Mrotation;
	D3DXVECTOR3	Mscale;
	D3DXMATRIX	MworldMatrix;
	
};

//�c�ړ���
class cVerticalMoveGround : public cMoveGround
{

public:
	static cVerticalMoveGround* objects[NUMBER_OF_GROUND_MOVE]; // �I�u�W�F�N�g�i�[

	static void SetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize, D3DXVECTOR2 _distance);
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};

//���ړ���
class cHorizontalMoveGround : public cMoveGround
{

public:
	static cHorizontalMoveGround* objects[NUMBER_OF_GROUND_MOVE]; // �I�u�W�F�N�g�i�[

	static void SetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize, D3DXVECTOR2 _distance);
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};