#pragma once

#include <d3dx9.h>

struct Camera
{
	D3DXVECTOR3 Eye;
	D3DXVECTOR3 At;
	D3DXVECTOR3 Up;
};

void InitializeCamera();
void UpdateCamera();

D3DXMATRIX GetCamera_mtx();