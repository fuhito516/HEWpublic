#pragma once

#include"directx.h"

typedef struct
{
	D3DXVECTOR3 vtx;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR diffuse;	// 反射光
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_3D;