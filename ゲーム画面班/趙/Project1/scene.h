#pragma once
// オブジェクトからの使用、不対応

// 基礎
#include"common.h"
#include"directx.h"
// システム
#include"texture.h"
#include"sprite.h"
#include"input.h"

// 河野
#include"Caracterselect.h"
// 李
#include"peaple.h"
#include"diffical.h"

// シーン列挙
enum eScene
{
	NONE,
	TITLE,
	PLAYER,
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
// ステージ列挙
enum eStage
{
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE5,
	
	STAGEMAX
};

class cScene
{
private:
protected:
public:
	static eScene	scene;
	static int		stage;
	static bool		checkPastPressed;

	static void Initialize_Scene();

	// 要整理(GAME)
	static void Update_TITLE();
	static void Update_PLAYER();
	static void Update_CHARACTER();
	static void Update_NAME();
	static void Update_DIFFICULTY();
	static void Update_STAGE();
	static void Update_GAME();
	static void Update_GAMEOVER();
	static void Update_AREARANKING();
	static void Update_STAGECLEAR();
	static void Update_STAGERANKING();
	static void Update_SCORETABLE();
	static void Update_RETURN();

	static void Draw_TITLE();
	static void Draw_PLAYER();
	static void Draw_CHARACTER();
	static void Draw_NAME();
	static void Draw_DIFFICULTY();
	static void Draw_STAGE();
	static void Draw_GAME();
	static void Draw_GAMEOVER();
	static void Draw_AREARANKING();
	static void Draw_STAGECLEAR();
	static void Draw_STAGERANKING();
	static void Draw_SCORETABLE();
	static void Draw_RETURN();

	/* 分担のために細分化 */
};