#pragma once

#include"direct3d.h"

#define NUMBER_OF_TITLE_TEXTURE (2)

class cTitle
{
public:

	static LPDIRECT3DTEXTURE9 pTextures[NUMBER_OF_TITLE_TEXTURE];

	static bool use;

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};