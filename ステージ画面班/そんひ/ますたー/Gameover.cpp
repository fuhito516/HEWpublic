
// メイン
#include"Gameover.h"
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

// アニメーション
static int frame = 0;
static float second = 0;

// 初期化
void cGameover::Init()
{
	// アニメーション
	frame = 0;
	second = 0;

	// 環境
	cCamera::Init();
}
// 終了
void cGameover::Uninit()
{
	// 環境
	cCamera::Uninit();
}
// 更新
void cGameover::Update()
{
	// PrintDebugProc("GAMECLEAR\n");

	// 遷移
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		//cScene::Fade(SCENE_);
	}
}
// 描画
void cGameover::Draw()
{
	// アニメーション
	frame++;
	second = (float)frame / FRAME_PER_SECOND;

	if (second < 1.8f)
	{
		sprite_draw
		(
			TEXTURE_INDEX_GAMEOVER1,
			0, 0,
			0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
		);
	}
	else if (second < 2.6f)
	{
		sprite_draw
		(
			TEXTURE_INDEX_GAMEOVER2,
			0, 0,
			0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
		);
	}
	else if (second < 4.0f)
	{
		sprite_draw
		(
			TEXTURE_INDEX_GAMEOVER3,
			0, 0,
			0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
		);
	}
	else
	{
		sprite_draw
		(
			TEXTURE_INDEX_GAMEOVER4,
			0, 0,
			0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
		);
	}
}