
// メイン
#include"Title.h"
#include"common.h"
#include"direct3d.h"
#include"vertex.h"
// 環境
#include"camera.h"
#include"input.h"
// シーン
#include"scene.h"
#include"Game.h"

LPDIRECT3DTEXTURE9 cTitle::pTextures[NUMBER_OF_TITLE_TEXTURE];
bool cTitle::use = false;

// 初期化
void cTitle::Init()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// 使用
	use = true;

	// テクスチャー
	for (int i = 0; i < NUMBER_OF_TITLE_TEXTURE; i++)
	{
		pTextures[i] = NULL;
	}
	D3DXCreateTextureFromFile(pD3DDevice, "asset/texture/title back.png", &pTextures[0]);
	D3DXCreateTextureFromFile(pD3DDevice, "asset/texture/title name.png", &pTextures[1]);

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
	// 遷移
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		cScene::Fade(SCENE_GAME);
	}
}
// 描画
void cTitle::Draw()
{

}