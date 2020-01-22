#pragma once

#include"vertex.h"

#define GRID_NUMBER				(13)
#define GRID_INTERVALLENGTH		(5.0f)
#define GRID_HALF_OF_LINELENGTH	(GRID_NUMBER * GRID_INTERVALLENGTH / 2 - GRID_INTERVALLENGTH / 2)
#define GRID_NUMBER_OF_VERTEX	(GRID_NUMBER * 2 * 2)
#define GRID_NUMBER_OF_LINE		(GRID_NUMBER * 2)

class cGrid
{
public:

	LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;	// ���_�o�b�t�@
	VERTEX_3D				*pVertex;

	D3DXVECTOR3 pos;		// �n�ʂ̈ʒu(�l�p�`�̒������W)
	D3DXVECTOR3 rot;		// �n�ʂ̌���(��])
	D3DXVECTOR3 scl;		// �n�ʂ̑傫��(�X�P�[��)
	D3DXMATRIX worldMtx;	// ���[���h�}�g���b�N�X

	void Init_Grid();		// ������
	void Uninit_Grid();		// �I��
	void Update_Grid();		// �X�V
	void Draw_Grid();		// �`��

};

cGrid* GetGrid();