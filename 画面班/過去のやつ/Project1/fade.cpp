
#include"common.h"
#include"fade.h"
#include"scene.h"

int		cFade::fadeState = FADESTATE_NONE;	// フェード状態
int		cFade::fadeAlpha = 0;				// アルファ値
eScene	cFade::nextScene = NONE;			// 次のシーン

void cFade::Fade(eScene _nextScene)
{
	fadeState = FADESTATE_OUT;
	fadeAlpha = 0;
	nextScene = _nextScene;
}
void cFade::UpdateFade()
{
	switch (fadeState)
	{
	case FADESTATE_OUT:
		fadeAlpha += 255 / FADE_COUNT;	// FADE_COUNTフレームで真っ暗へ
		if (fadeAlpha > 255)
		{
			fadeAlpha = 255;
			cScene::scene = nextScene;
			fadeState = FADESTATE_IN;
		}
		break;
	case FADESTATE_IN:
		fadeAlpha -= 255 / FADE_COUNT;	// FADE_COUNTフレームで画面へ
		if (fadeAlpha < 0)
		{
			fadeAlpha = 0;
			fadeState = FADESTATE_NONE;
		}
		break;
	default:
		break;
	}
}
void cFade::DrawFade()
{
	Sprite_SetColor(D3DCOLOR_RGBA(0, 0, 0, fadeAlpha));
	Sprite_Draw
	(
		TEXTURE_INDEX_BLACK,
		0, 0,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);
}