#pragma once

#include"direct3d.h"
#include"vertex.h"
#include"common.h"
#include"seika.h"

// ÉTÉCÉY
#define LIGHT_HORIZONTAL_SIZE	(SCREEN_WIDTH / 5)
#define LIGHT_VERTICAL_SIZE		(LIGHT_HORIZONTAL_SIZE / 2)

class cLight
{
public:

	static cLight* numberOfObjects[NUMBER_OF_SEIKA];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;

	// ï`âÊ
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

	static void SetVertex();
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};