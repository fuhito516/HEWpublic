
// メイン
#include"Game.h"
#include"GameStage1.h"
#include"GameStage2.h"
// 環境
#include"camera.h"
#include"debugproc.h"
#include"input.h"
// 要素
#include"background.h"
#include"ground.h"
#include"Moveground.h"
#include"player.h"
#include"seika.h"
#include"bridge.h"
#include"candle.h"
#include"goal.h"
#include"ghost.h"
#include"light.h"
// シーン
#include"scene.h"
#include"Title.h"

// 趙
/*#include"object.h"
static Obj obj;
#include "fog.h"
static Fog FG;*/

// 初期化
void cStage1::Init()
{
	LPDIRECT3DDEVICE9	pDevice = MyDirect3D_GetDevice();
	// 環境
	cCamera::Init();

	// 要素
	cBackground::Init();
	cGround::Init();
	cVerticalMoveGround::Init();
	cHorizontalMoveGround::Init();
	cPlayer::Init();
	cSeika::Init();
	cLight::Init();
	cBridge::Init();
	cCandle::Init();
	cGoal::Init();
	cGhost::Init();

	// 配置

	// プレイヤー
	cPlayer::Set(D3DXVECTOR3(0, 1, 0));
	cSeika::Set();
	cLight::Set();
	// 背景
	cBackground::SetBackground(TEXTURE_INDEX_BACK1, D3DXVECTOR3(70, 0, 200), D3DXVECTOR3(1200, 300, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK2, D3DXVECTOR3(5, 50, 180), D3DXVECTOR3(20, 20, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK3, D3DXVECTOR3(70, 20, 150), D3DXVECTOR3(600, 150, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK4, D3DXVECTOR3(70, 40, 50), D3DXVECTOR3(600, 150, 1));
	//cBackground::SetBackground(TEXTURE_INDEX_BACK5, D3DXVECTOR3(70, 00, 40), D3DXVECTOR3(20, 20, 1)); // 地面に変更
	cBackground::SetBackground(TEXTURE_INDEX_BACK6, D3DXVECTOR3(70, 00, 30), D3DXVECTOR3(200, 50, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK7, D3DXVECTOR3(70, 40, 20), D3DXVECTOR3(600, 150, 1));

	// 地面
	cGround::SetGround(D3DXVECTOR2(45, -4.0f), D3DXVECTOR2(100.0f, 2.0f));
	cGround::SetGround(D3DXVECTOR2(30, -0.5f), D3DXVECTOR2(2.0f, 5.0f));
	cGround::SetGround(D3DXVECTOR2(35, -0.5f), D3DXVECTOR2(2.0f, 8.0f));
	cGround::SetGround(D3DXVECTOR2(40, -0.5f), D3DXVECTOR2(2.0f, 5.0f));
	cGround::SetGround(D3DXVECTOR2(40, -0.5f), D3DXVECTOR2(2.0f, 5.0f));
	cVerticalMoveGround::SetGround(D3DXVECTOR2(60, 0.0f), D3DXVECTOR2(20.0f, 2.0f));

	cGround::SetGround(D3DXVECTOR2(75, -0.5f), D3DXVECTOR2(2.0f, 5.0f));//下ルート
																		//ここの間に敵入れたい！！！
	cGround::SetGround(D3DXVECTOR2(85, -0.5f), D3DXVECTOR2(2.0f, 6.0f));//下ルート
																		//ここの間に敵入れたい！！！
	cGround::SetGround(D3DXVECTOR2(94, -1.0f), D3DXVECTOR2(2.0f, 4.0f));//下ルート
																		//ここの間に敵入れたい！！！
	cGround::SetGround(D3DXVECTOR2(105, -8.0f), D3DXVECTOR2(2.0f, 16.0f));//下ルート

	cGround::SetGround(D3DXVECTOR2(119, -12.0f), D3DXVECTOR2(10.0f, 16.0f));//下ルート

	cGround::SetGround(D3DXVECTOR2(119, 6.0f), D3DXVECTOR2(10.0f, 6.0f));//下ルート

	cGround::SetGround(D3DXVECTOR2(129, 6.0f), D3DXVECTOR2(10.0f, 6.0f));//下ルート
																		 //-12の上に敵配置
	cGround::SetGround(D3DXVECTOR2(129, -12.0f), D3DXVECTOR2(10.0f, 6.0f));//下ルート


	cGround::SetGround(D3DXVECTOR2(135, -8.0f), D3DXVECTOR2(10.0f, 8.0f));//下ルート
	cGround::SetGround(D3DXVECTOR2(135, 6.0f), D3DXVECTOR2(10.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(130, 10.0f), D3DXVECTOR2(2.0f, 6.0f));



	//--------------------------------
	//上ルートブロック
	//--------------------------------
	cGround::SetGround(D3DXVECTOR2(77, 20.0f), D3DXVECTOR2(6.0f, 2.0f));
	cGround::SetGround(D3DXVECTOR2(95, 20.0f), D3DXVECTOR2(6.0f, 2.0f));
	//ここの間に敵
	cGround::SetGround(D3DXVECTOR2(103, 20.0f), D3DXVECTOR2(10.0f, 2.0f));
	//ここら辺にスコアに加算されるものを配置
	cGround::SetGround(D3DXVECTOR2(97, 22.0f), D3DXVECTOR2(2.0f, 4.0f));
	cGround::SetGround(D3DXVECTOR2(109, 22.0f), D3DXVECTOR2(2.0f, 4.0f));//ここ飛び越えて下の上のブロックに到達


	cGround::SetGround(D3DXVECTOR2(130, 10.0f), D3DXVECTOR2(2.0f, 6.0f));

	cGround::SetGround(D3DXVECTOR2(139, 6.0f), D3DXVECTOR2(10.0f, 6.0f));

	//----------------------------
	//ゴール階段
	//----------------------------
	cGround::SetGround(D3DXVECTOR2(145, -5.0f), D3DXVECTOR2(10.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(155, -3.0f), D3DXVECTOR2(10.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(159, 0.0f), D3DXVECTOR2(2.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(161, 1.0f), D3DXVECTOR2(2.0f, 8.0f));
	cGround::SetGround(D3DXVECTOR2(163, 2.0f), D3DXVECTOR2(2.0f, 10.0f));
	cGround::SetGround(D3DXVECTOR2(165, 3.0f), D3DXVECTOR2(2.0f, 12.0f));
	cGround::SetGround(D3DXVECTOR2(167, 4.0f), D3DXVECTOR2(2.0f, 14.0f));
	cGround::SetGround(D3DXVECTOR2(169, 5.0f), D3DXVECTOR2(2.0f, 16.0f));
	cGround::SetGround(D3DXVECTOR2(172, 6.0f), D3DXVECTOR2(4.0f, 16.0f));//ゴールの灯す場所

	//LPDIRECT3DTEXTURE9	g_p;
	//FG.Init(pDevice, 800, 200, 1);
	//FG.Move(0, 0, -0.5);
	//D3DXCreateTextureFromFile(pDevice, "asset/texture/Fog_ex.png", &g_p);
	//FG.setT(g_p);


	/*pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	for (int i = 1; i <= 7; i++)
	{
		pDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		pDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		pDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}

	for (int i = 0; i <= 7; i++)
	{
		pDevice->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		pDevice->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	}*/
}
// 終了
void cStage1::Uninit()
{
	// 要素
	cBridge::Uninit();
	cCandle::Uninit();
	cGoal::Uninit();
	cPlayer::Uninit();
	cSeika::Uninit();
	cBackground::Uninit();
	cGround::Uninit();
	cVerticalMoveGround::Uninit();
	cHorizontalMoveGround::Uninit();
	cGhost::Uninit();
	cLight::Uninit();

	// 環境
	cCamera::Uninit();
}
// 更新
void cStage1::Update()
{
	// シーン
	cGround::Update();
	cVerticalMoveGround::Update();
	cHorizontalMoveGround::Update();
	cPlayer::Update();
	cSeika::Update();
	cBridge::Update();
	cCandle::Update();
	cGoal::Update();
	cGhost::Update();
	cLight::Update();

	//FG.Update();

	// 環境
	cCamera::Update();

	// 終了判定
	if (cGhost::collision)
	{

	}
	else if (cGoal::collision)
	{

	}
	//SATGE2遷移
	if (GetKeyboardPress(DIK_RETURN))
	{
		cScene::Fade(STAGE_TWO);
	}
}
// 描画
void cStage1::Draw()
{
	LPDIRECT3DDEVICE9	pD3DDevice = MyDirect3D_GetDevice();

	// 環境
	cCamera::SetCamera();

	// αブレンド
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	pD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	// 要素
	cBackground::Draw();
	cGround::Draw();
	cVerticalMoveGround::Draw();;
	cHorizontalMoveGround::Draw();
	cBridge::Draw();
	cCandle::Draw();
	cSeika::Draw();
	cPlayer::Draw();
	cGoal::Draw();
	cGhost::Draw();
	//cLight::Draw();

	/*pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	for (int i = 1; i <= 7; i++)
	{
		pD3DDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		pD3DDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		pD3DDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}

	for (int i = 0; i <= 7; i++)
	{
		pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	}
	int i = 0;
	FG.setL(0, cSeika::objects[0]->position.x, cSeika::objects[0]->position.y);
	i++;
	if (cCandle::objects[0]->collision)
	{
		FG.setL(i, cCandle::objects[0]->position.x, cCandle::objects[0]->position.y);
		i++;
	}
	if (cBridge::objects[0]->collision)
	{
		FG.setL(i, cBridge::objects[0]->gimmickPosition.x, cBridge::objects[0]->gimmickPosition.y);
		i++;
	}
	FG.setLC(i);
	FG.Draw();*/
}