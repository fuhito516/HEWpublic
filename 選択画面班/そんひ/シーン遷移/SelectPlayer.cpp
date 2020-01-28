
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

LPDIRECT3DTEXTURE9 cSelectPlayer::pTextures[NUMBER_OF_SELECT_PLAYER_TEXTURE];
bool cSelectPlayer::use = false;

//グローバル変数
float pwaku_x = SCREEN_WIDTH / 5;                              //人数枠x
float pwaku_y = SCREEN_HEIGHT / 2;                             //人数枠y
extern int people;                                                       //人数

// 初期化
void cSelectPlayer::Init()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// 使用
	use = true;

	people = 1;

	// テクスチャー
	for (int i = 0; i < NUMBER_OF_SELECT_PLAYER_TEXTURE; i++)
	{
		pTextures[i] = NULL;
	}

	// 環境
	cCamera::Init();
	/* デバッグ機能の追加 */
}
// 終了
void cSelectPlayer::Uninit()
{
	// 使用
	use = false;

	// 環境
	cCamera::Uninit();

	// テクスチャ
	for (int i = 0; i < NUMBER_OF_SELECT_PLAYER_TEXTURE; i++)
	{
		if (pTextures[i] != NULL)
		{
			pTextures[i]->Release();
			pTextures[i] = NULL;
		}
	}
}
// 更新
void cSelectPlayer::Update()
{
	PrintDebugProc("SELECT_PLAYER\n");

	if (people >= 1 && people < 4) {
		if (GetKeyboardRelease(DIK_RIGHT) || GetKeyboardRelease(DIK_D)) 
		{
			pwaku_x += (float)SCREEN_WIDTH / 5;   //右移動
			people++;
		}
	}
	if (people > 1 && people <= 4) {
		if (GetKeyboardRelease(DIK_LEFT) || GetKeyboardRelease(DIK_A))
		{
			pwaku_x -= (float)SCREEN_WIDTH / 5;  //左移動
			people--;
		}
	}

	// 遷移
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		cScene::Fade(SCENE_SELECT_CHARACTER);
	}
}
// 描画
void cSelectPlayer::Draw()
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

	//シーン----------------------------------------------------------------------
	Sprite_Draw
	(
		TEXTURE_INDEX_PEOPLE_HEADING,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 10,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_PEOPLE_LIGHT,
		pwaku_x, pwaku_y,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_PEOPLE_ONE,
		(float)SCREEN_WIDTH / 5, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_PEOPLE_TWO,
		(float)SCREEN_WIDTH / 5 * 2, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_PEOPLE_THREE,
		(float)SCREEN_WIDTH / 5 * 3, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_PEOPLE_FOUR,
		(float)SCREEN_WIDTH / 5 * 4, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);

}