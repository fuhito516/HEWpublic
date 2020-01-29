#pragma once

#include"common.h"
#include"direct3d.h"

// �t�F�[�h�|���S�����_�t�H�[�}�b�g(���_���W(2D)/���ˌ�)
#define FVF_VERTEX_FADE (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
// 3D�|���S�����_�t�H�[�}�b�g(���_���W[3D]/�@��/���ˌ�/�e�N�X�`�����W)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// �t�F�[�h�|���S�����_
typedef struct
{
	D3DXVECTOR4 vertex;		// ���_���W
	D3DCOLOR	diffuse;	// ���ˌ�
} Vertex_Fade;
typedef struct
{
	D3DXVECTOR3 vtx;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR diffuse;	// ���ˌ�
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;