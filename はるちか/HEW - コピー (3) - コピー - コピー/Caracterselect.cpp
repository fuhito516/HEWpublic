
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")

#include <Windows.h>
#include "common.h"
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include <d3dx9.h>
#include"input.h"
#include"Caracterselect.h"

//�O���[�o���ϐ�
float PAD = 3.14 / 360;
float Playercarsolu;//P1�@P2���̃J�[�\�����W
float sx = 1;
float sy = 1;
float a=0;
int count = 0;
int oldcount = 0;
void CaracterselectInitialize() {
	
	//==================================
	//���C�g�ƃJ�[�\���̍��W�̌���
	//==================================
	count += 1 / 6000;

	////�����܂ł����W
}
void CaracterselectUpdate() {

	//==========================================
	//1P�̓���
	//=========================================

	if (Keyboard_IsTrigger(DIK_RETURN)) {
		
	}
	
}

void CaracterselectDraw() {
	//-----------------------------------
	//2D
	//-----------------------------------
	Sprite_Draw(TEXTURE_INDEX_TITLE,
		0, 0, 0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	Sprite_Draw(TEXTURE_INDEX_UNKO,
		FIREPOS_X,FIREPOS_Y,
		0, 0,
		S_KIHONTEXTURE_W, S_KIHONTEXTURE_H);

		if (sx <= 1.5/*&&sx<=1*/) {

			sx += PAD;
			sy += PAD;
		}
		if (sx >= 1.5) {
			sx -= 0.3f;
			sy -= 0.3f;
		}

	
		
	Sprite_animetionDraw(TEXTURE_INDEX_PURESENTER,
		KETTEIPOS_X, KETTEIPOS_Y,
		0, 0,
		256, 256, sx, sy);

}