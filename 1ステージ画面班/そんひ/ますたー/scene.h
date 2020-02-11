#pragma once

#define FRAME_FOR_FADE	(120)	// ëJà⁄èäóvÉtÉåÅ[ÉÄ
#define FIRST_SCENE		SCENE_TITLE

enum SCENE_NAME
{
	SCENE_NONE,
	SCENE_TITLE,
	SCENE_SELECT_NUMBER_OF_PLAYER,
	SCENE_SELECT_CHARACTER,
	SCENE_SELECT_DIFFICULTY,
	SCENE_SELECT_STAGE,
	SCENE_GAME,
	STAGE_ONE,
	STAGE_TWO,
	STAGE_THREE,
	SCENE_GAMEOVER,
	SCENE_STAGECLEAR,
	SCENE_SCORETABLE,
	SCENE_RETURN
};
enum FADE_STATE
{
	FADE_NONE,
	FADE_IN,
	FADE_OUT,
};

class cScene
{
public:

	static cScene* object;

	cScene();
	cScene(int _currentScene);

	static void Init();
	static void Init(int _currentScene);
	static void Uninit();
	static void Update();
	static void Draw();

	static void Fade(int nextScene);

	int currentScene;
	int nextScene;
	int fadeState;
	int fadeAlpha;
};