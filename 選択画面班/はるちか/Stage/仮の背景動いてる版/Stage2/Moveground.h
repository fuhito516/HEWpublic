#pragma once

#include"direct3d.h"
#include"vertex.h"

// �{�[�h�̐�(���)
#define NUMBER_OF_GROUND_MOVE (10)
// �{�[�h�̒��_��
#define NUMBER_OF_GROUND_VERTEXES_MOVE (4)
// �{�[�h�̏c���̃T�C�Y(�����l)
#define GROUND_VERTICAL_SIZE_MOVE	(1.0f)
#define GROUND_HORIZONTAL_SIZE_MOVE	(1.0f)

class cMoveGround
{
	// ���ʕ�
public:

	static cMoveGround* MovenumberOfObjects[NUMBER_OF_GROUND_MOVE]; // �I�u�W�F�N�g�i�[

	static LPDIRECT3DVERTEXBUFFER9	pMoveVertexBuffer;	// ���_�o�b�t�@
	static VERTEX_3D*				pMoveVertex;		// ���_�o�b�t�@�̒��g�𖄂߂�

													// �֐�
	static void MoveSetVertex();
	static void MoveSetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize);
	static void MoveInit();
	static void MoveUninit();
	static void MoveUpdate();
	static void MoveDraw();

	//static void GetMovegroundpos(float GetPos);
	
	// �v�f��
public:

	// �g�p
	bool use;

	// �t���[���J�E���^�[
	int frameCounter;

	// �T�C�Y
	D3DXVECTOR2 size;

	D3DXVECTOR3 fastMovePos;

	// �s��
	D3DXVECTOR3	Mposition;
	D3DXVECTOR3	Mrotation;
	D3DXVECTOR3	Mscale;
	D3DXMATRIX	MworldMatrix;
	D3DXVECTOR3	Nposition;

};