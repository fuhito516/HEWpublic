
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

LPDIRECT3DTEXTURE9 cSelectCharacter::pTextures[NUMBER_OF_SELECT_CHARACTER_TEXTURE];
bool cSelectCharacter::use = false;

//グローバル変数
float Playercarsolu = (float)SCREEN_WIDTH / 32 * 4;                                      //カーソル座標の決定
float Playercarsolu2 = (float)SCREEN_WIDTH / 32 * 4;                                    //カーソル座標の決定
float Playercarsolu3 = (float)SCREEN_WIDTH / 32 * 4;                                      //カーソル座標の決定
float Playercarsolu4 = (float)SCREEN_WIDTH / 32 * 4;                                   //カーソル座標の決定
int Character1P = 1;                                                  //１Pの選択キャラクター
int Character2P = 1;                                                  //２Pの選択キャラクター
int Character3P = 1;                                                  //３Pの選択キャラクタ-
int Character4P = 1;                                                  //４Pの選択キャラクター
int people;                                                       //人数

// 初期化
void cSelectCharacter::Init()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// 使用
	use = true;

	// テクスチャー
	for (int i = 0; i < NUMBER_OF_SELECT_CHARACTER_TEXTURE; i++)
	{
		pTextures[i] = NULL;
	}
	
	// 環境
	cCamera::Init();
	/* デバッグ機能の追加 */
}
// 終了
void cSelectCharacter::Uninit()
{
	// 使用
	use = false;

	// 環境
	cCamera::Uninit();

	// テクスチャ
	for (int i = 0; i < NUMBER_OF_SELECT_CHARACTER_TEXTURE; i++)
	{
		if (pTextures[i] != NULL)
		{
			pTextures[i]->Release();
			pTextures[i] = NULL;
		}
	}
}
// 更新
void cSelectCharacter::Update()
{
	//PrintDebugProc("SELECT_PLAYER\n");

	//1Pの動き-------------------------------------------------------
	if (Character1P >= 1 && Character1P < 5) {
		if (GetKeyboardRelease(DIK_D)) {
			Playercarsolu += (float)SCREEN_WIDTH / 32 * 6;  //右移動
			Character1P++;
		}
	}
	if (Character1P > 1 && Character1P <= 5) {
		if (GetKeyboardRelease(DIK_A)) {
			Playercarsolu -= (float)SCREEN_WIDTH / 32 * 6;   //左移動
			Character1P--;
		}
	}
	//２P動き----------------------------------------------------------
	if (Character2P >= 1 && Character2P < 5) {
		if (GetKeyboardRelease(DIK_RIGHT)) {
			Playercarsolu2 += (float)SCREEN_WIDTH / 32 * 6;   //右移動
			Character2P++;
		}
	}
	if (Character2P > 1 && Character2P <= 5) {
		if (GetKeyboardRelease(DIK_LEFT)) {
			Playercarsolu2 -= (float)SCREEN_WIDTH / 32 * 6;   //左移動
			Character2P--;
		}
	}
	//３P動き------------------------------------------------------------
	if (Character3P >= 1 && Character3P < 5) {
		if (GetKeyboardRelease(DIK_H)) {
			Playercarsolu3 += (float)SCREEN_WIDTH / 32 * 6;    //右移動
			Character3P++;
		}
	}
	if (Character3P > 1 && Character3P <= 5) {
		if (GetKeyboardRelease(DIK_F)) {
			Playercarsolu3 -= (float)SCREEN_WIDTH / 32 * 6;    //左移動
			Character3P--;
		}
	}
	//4P動く処理---------------------------------------------------------------
	if (Character4P >= 1 && Character4P < 5) {
		if (GetKeyboardRelease(DIK_L)) {
			Playercarsolu4 += (float)SCREEN_WIDTH / 32 * 6;    //右移動
			Character4P++;
		}
	}
	if (Character4P > 1 && Character4P <= 5) {
		if (GetKeyboardRelease(DIK_J)) {
			Playercarsolu4 -= (float)SCREEN_WIDTH / 32 * 6;    //左移動
			Character4P--;
		}
	}

	// 遷移---------------------------------------------------------------------
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		cScene::Fade(SCENE_SELECT_DIFFICULTY);
	}
}
// 描画
void cSelectCharacter::Draw()
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
	//シーン-----------------------------------------------------------------
	Sprite_Draw
	(
		TEXTURE_INDEX_CHARACTER_HEADING,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 10,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);

	for (int charaselect = 0; charaselect <= 4; charaselect++) {
		Sprite_Draw
		(
			TEXTURE_INDEX_CHARACTER_SELECT,
			((float)SCREEN_WIDTH / 32 * (4 + 6 * charaselect)), (float)SCREEN_HEIGHT / 2,
			1.0f, 1.0f, 0, 0, 1.0f, 1.0f
		);
	}

	if (people >= 1)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_CHARACTER_ONE,
			Playercarsolu, (float)SCREEN_HEIGHT / 2,
			1.0f, 1.0f, 0, 0, 1.0f, 1.0f
		);
	}
	if (people >= 2)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_CHARACTER_TWO,
			Playercarsolu2, (float)SCREEN_HEIGHT / 2,
			1.0f, 1.0f, 0, 0, 1.0f, 1.0f
		);
	}
	if (people >= 3)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_CHARACTER_THREE,
			Playercarsolu3, (float)SCREEN_HEIGHT / 2,
			1.0f, 1.0f, 0, 0, 1.0f, 1.0f
		);

	}
	if (people >= 4)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_CHARACTER_FOUR,
			Playercarsolu4, (float)SCREEN_HEIGHT / 2,
			1.0f, 1.0f, 0, 0, 1.0f, 1.0f
		);
	}

}