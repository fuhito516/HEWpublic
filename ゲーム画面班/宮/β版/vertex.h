#pragma once

#include"common.h"
#include"direct3d.h"

// フェードポリゴン頂点フォーマット(頂点座標(2D)/反射光)
#define FVF_VERTEX_FADE (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
// 3Dポリゴン頂点フォーマット(頂点座標[3D]/法線/反射光/テクスチャ座標)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// フェードポリゴン頂点
typedef struct
{
	D3DXVECTOR4 vertex;		// 頂点座標
	D3DCOLOR	diffuse;	// 反射光
} Vertex_Fade;
typedef struct
{
	D3DXVECTOR3 vtx;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR diffuse;	// 反射光
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_3D;