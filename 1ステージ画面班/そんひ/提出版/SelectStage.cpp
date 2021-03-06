
// メイン
#include"common.h"
#include"direct3d.h"
#include"vertex.h"
#include"debugproc.h"
// 環境
#include"camera.h"
#include"input.h"
#include"sprite.h"
// シーン
#include"scene.h"
#include"GameStage1.h"
#include"SelectStage.h"

// シーン遷移
static bool fade = false;

LPDIRECT3DTEXTURE9 cSelectStage::pTextures[NUMBER_OF_SELECT_STAGE_TEXTURE];
bool cSelectStage::use = false;

static int gStage = 1;	//ステージ

// 初期化
void cSelectStage::Init()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	fade = false;
	gStage = 1;

	// テクスチャー
	for (int i = 0; i < NUMBER_OF_SELECT_STAGE_TEXTURE; i++)
	{
		pTextures[i] = NULL;
	}
	// 環境
	cCamera::Init();
	/* デバッグ機能の追加 */
}
// 終了
void cSelectStage::Uninit()
{
	// 使用
	use = false;

	// 環境
	cCamera::Uninit();

	// テクスチャ
	for (int i = 0; i < NUMBER_OF_SELECT_STAGE_TEXTURE; i++)
	{
		if (pTextures[i] != NULL)
		{
			pTextures[i]->Release();
			pTextures[i] = NULL;
		}
	}
}
// 更新
void cSelectStage::Update()
{
	//PrintDebugProc("SELECT_STAGE\n");

	if (GetKeyboardRelease(DIK_LEFT) || GetKeyboardRelease(DIK_A)) {
		gStage--;
	}
	if (GetKeyboardRelease(DIK_RIGHT) || GetKeyboardRelease(DIK_D)) {
		gStage++;
	}
	// 制御
	if (gStage < 1)
		gStage = 1;
	if (gStage > NUMBER_OF_STAGE)
		gStage = NUMBER_OF_STAGE;


	//PrintDebugProc("ステージ　%d\n", gStage);

	// 遷移
	if (GetKeyboardTrigger(DIK_RETURN) && !fade)
	{
		switch (gStage)
		{
		case 1:
			cScene::Fade(STAGE_ONE);
			break;
		case 2:
			cScene::Fade(STAGE_TWO);
			break;
		case 3:
			cScene::Fade(STAGE_THREE);
			break;

		default:
			break;
		}

		fade = true;
	}
}
// 描画
void cSelectStage::Draw()
{
	//共通
	Sprite_Draw
	(
		TEXTURE_INDEX_BLACK,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_BACK,
		(float)SCREEN_WIDTH / 10, (float)SCREEN_HEIGHT / 10,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_DECISION,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT * (9.0f / 10.0f),
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);

	// シーン名
	Sprite_Draw
	(
		TEXTURE_INDEX_STAGE_HEADING,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 10,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);

	// ステージ数
	for (int i = 1; i <= NUMBER_OF_STAGE; i++)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_STAGE_ROPE,
			(float)SCREEN_WIDTH * ((float)i / (NUMBER_OF_STAGE + 1)), (float)SCREEN_HEIGHT / 2,
			1.2f, 1.2f,
			0, 0, 1.0f, 1.0f
		);
		Sprite_Draw
		(
			TEXTURE_INDEX_BLACKNUMBER,
			(float)SCREEN_WIDTH * ((float)i / (NUMBER_OF_STAGE + 1)), (float)SCREEN_HEIGHT / 2 - 118,
			0.8f, 0.8f,
			1.0f / 8 * (i - 1), 0, 1.0f / 8 * i, 0.5f
		);
	}

	// キャラクター
	Sprite_Draw
	(
		TEXTURE_INDEX_PLAYER_L4,
		(float)SCREEN_WIDTH * ((float)gStage / (NUMBER_OF_STAGE + 1)) - 36, (float)SCREEN_HEIGHT * (2.0f / 3.0f),
		1.0f, 1.0f,
		0, 0, 1.0f, 1.0f
	);

}