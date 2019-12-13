
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

//グローバル変数
float PAD = 3.14 / 360;
float Playercarsolu;//P1　P2等のカーソル座標
float sx = 1;
float sy = 1;
float a=0;
int i;
float count;
float count2;
int flg;
void CaracterselectInitialize() {
	
	//==================================
	//ライトとカーソルの座標の決定
	//==================================
	i = 192;

	count = 0.0f;

	////ここまでが座標
}
void CaracterselectUpdate() {

	//==========================================
	//1Pの動き
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
	//pressエンターの拡大
	//伸び縮み
	if (sx <= 1) {
		flg = 1;
	}
	if (sx >= 1.5) {
		flg = 0;

	}
	//size変更
	if (flg == 1) {
		sx += PAD;
		sy += PAD;
	}
	if (flg == 0) {
		sx -= PAD;
		sy -= PAD;
	}


		

	if (Keyboard_IsTrigger(DIK_RETURN)) {
		//遷移処理記入
	}
}
void CaracterselectDraw() {
	//-----------------------------------
	//2D
	//-----------------------------------
	//背景を黒くするための物
	Sprite_Draw(TEXTURE_INDEX_BG,
		0, 0, 0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT);
	//タイトルの描画
	Sprite_Draw(TEXTURE_INDEX_TITLE,
		0, 0, 0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT);
	//全体的の明暗表現

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