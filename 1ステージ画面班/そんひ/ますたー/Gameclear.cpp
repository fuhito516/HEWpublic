
// メイン
#include"Gameclear.h"
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

// 初期化
void cGameclear::Init()
{
	fade = false;

	// 環境
	cCamera::Init();
}
// 終了
void cGameclear::Uninit()
{
	// 環境
	cCamera::Uninit();
}
// 更新
void cGameclear::Update()
{
	// PrintDebugProc("GAMECLEAR\n");

	// 遷移
	if (GetKeyboardTrigger(DIK_RETURN) && !fade)
	{
		cScene::Fade(SCENE_RETURN);
		fade = true;
	}
}
// 描画
void cGameclear::Draw()
{
	sprite_draw
	(
		TEXTURE_INDEX_GAMECLEAR,
		0, 0,
		0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
	);
}