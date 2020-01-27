
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
#include"Game.h"
#include"SelectPlayer.h"
#include"SelectCharacter.h"
#include"SelectDifficulty.h"
#include"SelectStage.h"

LPDIRECT3DTEXTURE9 cSelectDifficulty::pTextures[NUMBER_OF_SELECT_DIFFICULTY_TEXTURE];
bool cSelectDifficulty::use = false;

float dwaku_x = SCREEN_WIDTH / 4;                              //難易度枠x
float dwaku_y = SCREEN_HEIGHT / 2;                             //難易度枠y
int nannido;

// 初期化
void cSelectDifficulty::Init()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// 使用
	use = true;

	nannido = 1;

	// テクスチャー
	for (int i = 0; i < NUMBER_OF_SELECT_DIFFICULTY_TEXTURE; i++)
	{
		pTextures[i] = NULL;
	}

	// 環境
	cCamera::Init();
	/* デバッグ機能の追加 */
}
// 終了
void cSelectDifficulty::Uninit()
{
	// 使用
	use = false;

	// 環境
	cCamera::Uninit();

	// テクスチャ
	for (int i = 0; i < NUMBER_OF_SELECT_DIFFICULTY_TEXTURE; i++)
	{
		if (pTextures[i] != NULL)
		{
			pTextures[i]->Release();
			pTextures[i] = NULL;
		}
	}
}
// 更新
void cSelectDifficulty::Update()
{
	PrintDebugProc("SELECT_DIFFICULTY\n");

	if (nannido >= 1 && nannido < 3) {
		if (GetKeyboardRelease(DIK_RIGHT) || GetKeyboardRelease(DIK_D)) {
			dwaku_x += (float)SCREEN_WIDTH / 4;   //右に移動
			nannido += 1;
		}
	}
	if (nannido > 1 && nannido <= 3) {
		if (GetKeyboardRelease(DIK_LEFT) || GetKeyboardRelease(DIK_A))
		{
			dwaku_x -= (float)SCREEN_WIDTH / 4;  //左に移動
			nannido -= 1;
		}
	}

	// 遷移------------------------------------------------------
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		cScene::Fade(SCENE_SELECT_STAGE);
	}
}
// 描画
void cSelectDifficulty::Draw()
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
	//シーン------------------------------------------------------------------------
	Sprite_Draw
	(
		TEXTURE_INDEX_DIFFICULTY_HEADING,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 10,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_DIFFICULTY_LIGHT,
		dwaku_x, dwaku_y,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_DIFFICULTY_EASY,
		(float)SCREEN_WIDTH / 4, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_DIFFICULTY_NORMAL,
		(float)SCREEN_WIDTH / 4 * 2, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_DIFFICULTY_HARD,
		(float)SCREEN_WIDTH / 4 * 3, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
}