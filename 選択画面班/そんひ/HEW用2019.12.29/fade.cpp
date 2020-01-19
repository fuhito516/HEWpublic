
#include"common.h"
#include"fade.h"

static cFade gcFade;

void cFade::Init_Fade()
{
	currentScene = FIRST_SCENE;		// ���݂̃V�[��
	fadeState = FADE_STATE_NONE;	// �t�F�[�h���
	fadeAlpha = 0;					// �A���t�@�l
}
void cFade::Update_Fade()
{
	switch (fadeState)
	{
	case FADE_STATE_NONE:
		break;
	case FADE_STATE_OUT:
		fadeAlpha += 255 / FADE_COUNT;	// FADE_COUNT�t���[���ňÓ]
		if (fadeAlpha > 255)
		{
			fadeAlpha = 255;
			currentScene = nextScene;
			fadeState = FADE_STATE_IN;
		}
		break;
	case FADE_STATE_IN:
		fadeAlpha -= 255 / FADE_COUNT;	// FADE_COUNT�t���[���œ_��
		if (fadeAlpha < 0)
		{
			fadeAlpha = 0;
			fadeState = FADE_STATE_NONE;
		}
		break;
	default:
		break;
	}
}
void cFade::Draw_Fade()
{
	Sprite_SetColor(D3DCOLOR_RGBA(0, 0, 0, fadeAlpha));
	Sprite_Draw
	(
		TEXTURE_INDEX_FADE,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2,
		0, 0, 1.0f, 1.0f
	);
}

void Fade(int nextScene)
{
	gcFade.fadeState = FADE_STATE_OUT;
	gcFade.fadeAlpha = 0;
	gcFade.nextScene = nextScene;
}
cFade* GetFade()
{
	return &gcFade;
}