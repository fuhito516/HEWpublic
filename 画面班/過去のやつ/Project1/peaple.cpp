
#include"common.h"
#include"peaple.h"
#include"sprite.h"
#include"texture.h"
#include"input.h"

static float	waku_x	= 50.0f;
static float	waku_y	= 225.0f;
static int		ninzu	= 1;

void UpdatePeaple(void)
{
	// 右に移動
	if (ninzu >= 1 && ninzu < 4)
	{
		if (Keyboard_IsTrigger(DIK_RIGHT))
		{
			waku_x += 235;
			ninzu += 1;
		}
	}
	// 左に移動
	if(ninzu > 1 && ninzu <= 4){
		if (Keyboard_IsTrigger(DIK_LEFT))
		{
			waku_x -= 235;
			ninzu -= 1;
		}
	}
	// 決定
	if (Keyboard_IsTrigger(DIK_A))
	{
		// キャラクター選択へ
	}
	// 戻る
	if (Keyboard_IsTrigger(DIK_Z))
	{
		// モード選択へ
	}
}

void DrawPeaple(void)
{
	// スプライト描画
	Sprite_Draw
	(
		TEXTURE_INDEX_HAIKEI,
		0.0f, 0.0f,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	); // 1024 576

	Sprite_Draw
	(
		TEXTURE_INDEX_WAKU,
		waku_x, waku_y,
		0, 0,
		WAKU_WIDTH_P, WAKU_HEIGHT_P
	);
}