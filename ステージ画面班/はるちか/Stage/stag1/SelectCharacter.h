#pragma once

#include"direct3d.h"

#define NUMBER_OF_SELECT_CHARACTER_TEXTURE (10)

class cSelectCharacter
{
public:

	static LPDIRECT3DTEXTURE9 pTextures[NUMBER_OF_SELECT_CHARACTER_TEXTURE];

	static bool use;

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};