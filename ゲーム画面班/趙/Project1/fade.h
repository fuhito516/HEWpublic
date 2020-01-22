#pragma once

#include"common.h"

#include"sprite.h"
#include"texture.h"

#include"scene.h"

#define FADE_COUNT (60)	// 遷移時間(フレーム)

enum FadeState	// フェードの状態
{
	FADESTATE_NONE,
	FADESTATE_IN,
	FADESTATE_OUT,
};

class cFade
{
private:
protected:
public:
	static int		fadeState;	// フェード状態
	static int		fadeAlpha;	// アルファ値
	static eScene	nextScene;	// 次のシーン

	static void Fade(eScene _nextScene);
	// usingFade = true時
	static void UpdateFade();
	static void DrawFade();
};