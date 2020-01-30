
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
int koumei, koumei1, koumei2;
float count;
int flg;
void CaracterselectInitialize() {
	//================================================
	//初期化
	//================================================
	i = 192;
	koumei = 0;
	koumei1 = 0;
	koumei2 = 0;
	count = 0.0f;

	////ここまでが座標
}
void CaracterselectUpdate() {

	//==========================================
	//1Pの動き
	//==========================================
	koumei++;
	koumei1++;
	koumei2++;
	count++;
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

	//================================================
	//孔明灯の移動
	//==================================================
	if (koumei >= SCREEN_WIDTH+256){
		koumei = -256;
	}
	if (koumei1 >= SCREEN_WIDTH + 256) {
		koumei1 = -256;
	}
	if (koumei2 >= SCREEN_WIDTH + 256) {
		koumei2 = -256;
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
	//孔明灯
	Sprite_Draw(TEXTURE_INDEX_KOUMEITOU,
		koumei- SCREEN_WIDTH, FIREPOS_Y,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	//パターン２
	//Sprite_Draw(TEXTURE_INDEX_KOUMEITOU,
	//	koumei1+256, FIREPOS_Y + 30,
	//	0, 0,
	//	256, 256);

	////パターン３
	//Sprite_Draw(TEXTURE_INDEX_KOUMEITOU,
	//	koumei2 + 521, FIREPOS_Y + 20,
	//	0, 0,
	//	256, 256);

	//火のアニメーション
	Sprite_Draw(TEXTURE_INDEX_UNKO,
		FIREPOS_X,FIREPOS_Y,
		i, 0,
		S_KIHONTEXTURE_W, S_KIHONTEXTURE_H);
	
	//プッシュエンター
	Sprite_animetion_Alpha_Draw(TEXTURE_INDEX_PURESENTER,
		KETTEIPOS_X, KETTEIPOS_Y,
		0, 0,
		256, 256, sx, sy);
	
}