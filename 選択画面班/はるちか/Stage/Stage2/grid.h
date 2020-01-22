#pragma once

#include"direct3d.h"
#include"vertex.h"

// �ؖڂ̐�(�c������)
#define NUMBER_OF_GRAIN (5)
// �O���b�h���̐�
#define NUMBER_OF_LINE_OF_GRID (NUMBER_OF_GRAIN * 2)
// �O���b�h�̒��_��
#define NUMBER_OF_VERTEX_OF_GRID (NUMBER_OF_LINE_OF_GRID * 2)
// �O���b�h�����m�̊Ԋu
#define SPACEING_BETWEEN_GRID_LINES (10.0f)
// �O���b�h�̔����̒���
#define HALF_LENGTH_OF_GRID	((NUMBER_OF_GRAIN * SPACEING_BETWEEN_GRID_LINES - SPACEING_BETWEEN_GRID_LINES) / 2)

class cGrid
{
// ���ʕ�
public:

	static cGrid* numberOfGrid;	// �I�u�W�F�N�g�i�[

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;	// ���_�o�b�t�@
	static VERTEX_3D				*pVertex;		// ���_�o�b�t�@�̒��g�𖄂߂�

	static D3DXVECTOR3 position;	// �ʒu(�������W)
	static D3DXVECTOR3 rotation;	// ��]
	static D3DXVECTOR3 scale;		// �傫��
	static D3DXMATRIX worldMatrix;	// ���[���h�}�g���b�N�X

	static void SetVertex_Grid();	// ���_�Z�b�g�֐�
	static void Init();				// ������
	static void Uninit();			// �I������
	static void Update();			// �X�V
	static void Draw();				// �`��

};