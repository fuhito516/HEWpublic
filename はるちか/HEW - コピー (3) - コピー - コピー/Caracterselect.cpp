
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
int i;
float count;
float count2;
int flg;
void CaracterselectInitialize() {
	
	//==================================
	//���C�g�ƃJ�[�\���̍��W�̌���
	//==================================
	i = 192;

	count = 0.0f;

	////�����܂ł����W
}
void CaracterselectUpdate() {

	//==========================================
	//1P�̓���
	//==========================================

	count++;
	count2++;
	//honoo
	if (count >3.5f) {
		if (i > 2304) {
			i = 128 - 64;	
		}
		i+=256;
		count = 0;
	}	
	//press�G���^�[�̊g��
	//�L�яk��
	if (sx <= 1) {
		flg = 1;
	}
	if (sx >= 1.5) {
		flg = 0;

	}
	//size�ύX
	if (flg == 1) {
		sx += PAD;
		sy += PAD;
	}
	if (flg == 0) {
		sx -= PAD;
		sy -= PAD;
	}


		

	if (Keyboard_IsTrigger(DIK_RETURN)) {
		//�J�ڏ����L��
	}
}
void CaracterselectDraw() {
	//-----------------------------------
	//2D
	//-----------------------------------
	//�w�i���������邽�߂̕�
	Sprite_Draw(TEXTURE_INDEX_BG,
		0, 0, 0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT);
	//�^�C�g���̕`��
	Sprite_Draw(TEXTURE_INDEX_TITLE,
		0, 0, 0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT);
	//�S�̓I�̖��Õ\��

	Sprite_Alpha_Draw(TEXTURE_INDEX_LIGHT,
		KETTEIPOS_X, SCREEN_HEIGHT/2,
		0, 0,
		1024, 576, 1,1);


	Sprite_Draw(TEXTURE_INDEX_UNKO,
		FIREPOS_X,FIREPOS_Y,
		i, 0,
		S_KIHONTEXTURE_W, S_KIHONTEXTURE_H);
	
	
	Sprite_animetion_Alpha_Draw(TEXTURE_INDEX_PURESENTER,
		KETTEIPOS_X, KETTEIPOS_Y,
		0, 0,
		256, 256, sx, sy);
	
}