#pragma once

#include"direct3d.h"

#define NUMBER_OF_TITLE_TEXTURE (2)

#define FIREPOS_X	(800)
#define FIREPOS_Y	(80)
#define KETTEIPOS_X (SCREEN_WIDTH/2)
#define KETTEIPOS_Y	(SCREEN_HEIGHT/2+200)

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