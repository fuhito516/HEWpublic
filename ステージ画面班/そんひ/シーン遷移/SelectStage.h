#pragma once

#include"direct3d.h"

#define NUMBER_OF_SELECT_STAGE_TEXTURE (6)

#define NUMBER_OF_STAGE (3)

class cSelectStage
{
public:

	static LPDIRECT3DTEXTURE9 pTextures[NUMBER_OF_SELECT_STAGE_TEXTURE];

	static bool use;

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};