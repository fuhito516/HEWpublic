
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
void cStage2::Init()
{
	LPDIRECT3DDEVICE9	pDevice = MyDirect3D_GetDevice();
	// 環境
	cCamera::Init();

	// 要素
	cBackground::Init();
	cGround::Init();
	cVerticalMoveGround::MoveInit();
	cHorizontalMoveGround::MoveInit();
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
	// グラウンド設定(オススメはサイズは変更できるがバランスを考えると固定ブロックを基に要素を付け加えていく方がよい)
	cGround::SetGround(D3DXVECTOR2(22, -4.0f), D3DXVECTOR2(50.0f, 2.0f));
	cGround::SetGround(D3DXVECTOR2(22, -6.0f), D3DXVECTOR2(50.0f, 2.0f));
	cGround::SetGround(D3DXVECTOR2(50, -8.0f), D3DXVECTOR2(50.0f, 2.0f));

	//横移動床
	cHorizontalMoveGround::MoveSetGround(D3DXVECTOR2(55, 1.0f), D3DXVECTOR2(10.0f, 2.0f));
	cHorizontalMoveGround::MoveSetGround(D3DXVECTOR2(75, 1.0f), D3DXVECTOR2(10.0f, 2.0f));


	 //LPDIRECT3DTEXTURE9	g_p;
	 //FG.Init(pDevice, 800, 200, 1);
	 //FG.Move(0, 0, -0.5);
	 //D3DXCreateTextureFromFile(pDevice, "asset/texture/Fog_ex.png", &g_p);
	 //FG.setT(g_p);
	 
	 /*pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	 pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA)
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
void cStage2::Uninit()
{
	// 要素
	cBridge::Uninit();
	cCandle::Uninit();
	cGoal::Uninit();
	cPlayer::Uninit();
	cSeika::Uninit();
	cBackground::Uninit();
	cGround::Uninit();
	cVerticalMoveGround::MoveUninit();
	cHorizontalMoveGround::MoveUninit();
	cGhost::Uninit();
	cLight::Uninit();

	// 環境
	cCamera::Uninit();
}
// 更新
void cStage2::Update()
{
	// シーン
	cGround::Update();
	cVerticalMoveGround::MoveUpdate();
	cHorizontalMoveGround::MoveUpdate();
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
}
// 描画
void cStage2::Draw()
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
	cVerticalMoveGround::MoveDraw();
	cHorizontalMoveGround::MoveDraw();
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