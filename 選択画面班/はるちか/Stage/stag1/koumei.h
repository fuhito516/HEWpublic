#pragma once
#include"direct3d.h"
#include"common.h"
class KOUMEI {
public:
	int s;
	D3DXVECTOR3 koumeipos;
	static void Init();
	static void Update();
	static void Draw();
};

