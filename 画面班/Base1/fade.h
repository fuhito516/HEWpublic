#pragma once

#include"common.h"

#include"sprite.h"
#include"texture.h"

#define FADE_COUNT (60)	// 遷移時間(フレーム)
#define NUMBER_OF_STAGE (3)

// シーンの種類
enum eScene
{
	TITLE,
	NUMBER_OF_PEOPLE,
	CHARACTER,
	NAME,
	DIFFICULTY,
	STAGE,
	GAME,
	GAMEOVER,
	AREARANKING,
	STAGECLEAR,
	STAGERANKING,
	SCORETABLE,
	RETURN
};
#define FIRST_SCENE STAGE
// フェードの状態
enum eFadeState
{
	FADE_STATE_NONE,
	FADE_STATE_IN,
	FADE_STATE_OUT,
};

class cFade
{
public:

	int currentScene;	// 現在のシーン
	int	nextScene;		// 次のシーン
	int	fadeState;	// フェード状態
	int	fadeAlpha;	// アルファ値

	void Init_Fade();
	void Update_Fade();
	void Draw_Fade();

};

cFade* GetFade();
void Fade(int nextScene);	// 次のシーンへ移動