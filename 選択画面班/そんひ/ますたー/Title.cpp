
// メイン
#include"Title.h"
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

LPDIRECT3DTEXTURE9 cTitle::pTextures[NUMBER_OF_TITLE_TEXTURE];
bool cTitle::use = false;

//グローバル変数
float PAD = 3.14f / 360;
float sx = 1;
float sy = 1;
float a = 0;
int i;
float koumei, koumei1, koumei2;
float count;
int flg;

// 初期化
void cTitle::Init()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// 使用
	use = true;

	//座標
	i = 192;
	koumei = 0.0f;
	koumei1 = 0.0f;
	koumei2 = 0.0f;
	count = 0.0f;

	// テクスチャー
	for (int i = 0; i < NUMBER_OF_TITLE_TEXTURE; i++)
	{
		pTextures[i] = NULL;
	}
	//D3DXCreateTextureFromFile(pD3DDevice, "asset/texture/title back.png", &pTextures[0]);
	//D3DXCreateTextureFromFile(pD3DDevice, "asset/texture/title name.png", &pTextures[1]);

	// 環境
	cCamera::Init();
	/* デバッグ機能の追加 */
}
// 終了
void cTitle::Uninit()
{
	// 使用
	use = false;

	// 環境
	cCamera::Uninit();

	// テクスチャ
	for (int i = 0; i < NUMBER_OF_TITLE_TEXTURE; i++)
	{
		if (pTextures[i] != NULL)
		{
			pTextures[i]->Release();
			pTextures[i] = NULL;
		}
	}
}
// 更新
void cTitle::Update()
{
	//PrintDebugProc("TITLE\n");

	//==========================================
	//1Pの動き
	//==========================================
	koumei++;
	koumei1++;
	koumei2++;
	count++;
	//honoo
	if (count >3.5f) {
		if (i > 2304) {
			i = 128 - 64;
		}
		i += 256;
		count = 0;
	}
	//pressエンターの拡大
	//伸び縮み
	if (sx <= 1) {
		flg = 1;
	}
	if (sx >= 1.5) {
		flg = 0;

	}
	//size変更
	if (flg == 1) {
		sx += PAD;
		sy += PAD;
	}
	if (flg == 0) {
		sx -= PAD;
		sy -= PAD;
	}

	//================================================
	//孔明灯の移動
	//==================================================
	if (koumei >= SCREEN_WIDTH + 256) {
		koumei = -256;
	}
	if (koumei1 >= SCREEN_WIDTH + 256) {
		koumei1 = -256;
	}
	if (koumei2 >= SCREEN_WIDTH + 256) {
		koumei2 = -256;
	}

	// 遷移
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		cScene::Fade(SCENE_SELECT_NUMBER_OF_PLAYER);
	}
}
// 描画
void cTitle::Draw()
{
	//-----------------------------------
	//2D
	//-----------------------------------
	//背景を黒くするための物
	sprite_draw(TEXTURE_INDEX_BG,
		0.0f, 0.0f, 0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT);
	//タイトルの描画
	sprite_draw(TEXTURE_INDEX_TITLE,
		0.0f, 0.0f, 0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT);
	//全体的の明暗表現

	Sprite_Alpha_Draw(TEXTURE_INDEX_LIGHT,
		KETTEIPOS_X, SCREEN_HEIGHT / 2.0f,
		0, 0,
		SIZE_1024, SIZE_576, 1, 1);
	//孔明灯
	sprite_draw(TEXTURE_INDEX_KOUMEITOU,
		koumei - SCREEN_WIDTH, FIREPOS_Y,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	//パターン２
	//Sprite_Draw(TEXTURE_INDEX_KOUMEITOU,
	//	koumei1+256, FIREPOS_Y + 30,
	//	0, 0,
	//	256, 256);

	////パターン３
	//Sprite_Draw(TEXTURE_INDEX_KOUMEITOU,
	//	koumei2 + 521, FIREPOS_Y + 20,
	//	0, 0,
	//	256, 256);

	//火のアニメーション
	sprite_draw(TEXTURE_INDEX_UNKO,
		FIREPOS_X, FIREPOS_Y,
		i, 0,
		SIZE_128, SIZE_128);

	//プッシュエンター
	Sprite_animetion_Alpha_Draw(TEXTURE_INDEX_PURESENTER,
		KETTEIPOS_X, KETTEIPOS_Y,
		0, 0,
		256, 256, sx, sy);

}