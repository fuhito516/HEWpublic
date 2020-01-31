
// メイン
#include"Return.h"
#include"common.h"
#include"direct3d.h"
#include"vertex.h"
// 環境
#include"debugproc.h"
#include"camera.h"
#include"input.h"
#include"sprite.h"
// シーン
#include"scene.h"

// シーン遷移
static bool fade = false;

// アニメーション
static int frame = 0;
static float second = 0;

// 選択
static int returnScene = 0;

// 初期化
void cReturn::Init()
{
	// シーン遷移
	fade = false;

	// アニメーション
	frame = 0;
	second = 0;

	// 環境
	cCamera::Init();
}
// 終了
void cReturn::Uninit()
{
	// 環境
	cCamera::Uninit();
}
// 更新
void cReturn::Update()
{
	//PrintDebugProc("SCENE_RETURN\n");

	// 選択移動
	if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S))
	{
		returnScene++;
	}
	else if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W))
	{
		returnScene--;
	}
	if (returnScene < 0)
	{
		returnScene = 0;
	}
	else if (returnScene > 1)
	{
		returnScene = 1;
	}

	PrintDebugProc("シーン遷移　%d\n", returnScene);
	// 遷移
	if (GetKeyboardTrigger(DIK_RETURN) && !fade)
	{
		switch (returnScene)
		{
		case 0:
			cScene::Fade(SCENE_TITLE);
			break;
		case 1:
			cScene::Fade(SCENE_SELECT_STAGE);
			break;

		default:
			break;
		}
		fade = true;
	}
}
// 描画
void cReturn::Draw()
{
	// 見出し
	Sprite_Draw
	(
		TEXTURE_INDEX_RETURN,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 10,
		0.8f, 0.8f,
		0, 0, 1, 1
	);

	// 項目
	Sprite_Draw
	(
		TEXTURE_INDEX_TOTITLE,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50,
		0.8f, 0.8f,
		0, 0, 1, 1
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_TOSTAGE,
		SCREEN_WIDTH / 2 + 128 * 0.8f, SCREEN_HEIGHT / 2 + 50,
		0.8f, 0.8f,
		0, 0, 1, 1
	);

	// 矢印
	if (returnScene == 0)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_RETURNSELECT,
			SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT / 2 - 50,
			1, 1,
			0, 0, 1, 1
		);
	}
	else if (returnScene == 1)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_RETURNSELECT,
			SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT / 2 + 50,
			1, 1,
			0, 0, 1, 1
		);
	}
}