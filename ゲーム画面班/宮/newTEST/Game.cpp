
// メイン
#include"Game.h"
// 環境
#include"camera.h"
#include"debugproc.h"
// 要素
#include"background.h"
#include"ground.h"
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

//#include "fog.h"
//Fog FG;

// 初期化
void cGame::Init()
{
	LPDIRECT3DDEVICE9	pDevice = MyDirect3D_GetDevice();
	// 環境
	cCamera::Init();

	// 要素
	cBackground::Init();
	cGround::Init();
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
	cGround::SetGround(D3DXVECTOR2(-17.5f, 0), D3DXVECTOR2(5.0f, 80.0f));
	cGround::SetGround(D3DXVECTOR2(0, -20.0f), D3DXVECTOR2(30.0f, 40.0f));
	cGround::SetGround(D3DXVECTOR2(30, -22.5f), D3DXVECTOR2(30.0f, 35.0f));
	cGround::SetGround(D3DXVECTOR2(52.5f, -22.5f), D3DXVECTOR2(5.0f, 35.0f));
	cGround::SetGround(D3DXVECTOR2(62.5f, -25.0f), D3DXVECTOR2(5.0f, 30.0f));
	cGround::SetGround(D3DXVECTOR2(85.0f, -27.5f), D3DXVECTOR2(30.0f, 25.0f));
	cGround::SetGround(D3DXVECTOR2(130.0f, -27.5f), D3DXVECTOR2(20.0f, 25.0f)); // 全長x=140,y=80
	// ギミック
	cCandle::SetCandle(D3DXVECTOR2(30.0f, 3.0f));
	cBridge::SetBridge(D3DXVECTOR2(95.0f, -2.0f), D3DXVECTOR2(110.0f, -16.0f), D3DXVECTOR2(20.0f, 2.0f));
	cGoal::Set(D3DXVECTOR3(145, -10, 0));
	cGhost::Set(D3DXVECTOR3(110, -15, 0), 20);

	/*LPDIRECT3DTEXTURE9	g_p;
	FG.Init(pDevice, 800, 200, 1);
	FG.Move(0, 0, -0.5);
	D3DXCreateTextureFromFile(pDevice, "asset/texture/Fog_ex.png", &g_p);
	FG.setT(g_p);


	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
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
void cGame::Uninit()
{
	// 要素
	cBridge::Uninit();
	cCandle::Uninit();
	cGoal::Uninit();
	cPlayer::Uninit();
	cSeika::Uninit();
	cBackground::Uninit();
	cGround::Uninit();
	cGhost::Uninit();
	cLight::Uninit();

	// 環境
	cCamera::Uninit();
}
// 更新
void cGame::Update()
{
	// シーン
	cGround::Update();
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
void cGame::Draw()
{
	// 環境
	cCamera::SetCamera();

	// 要素
	cBackground::Draw();
	cGround::Draw();
	cBridge::Draw();
	cCandle::Draw();
	cSeika::Draw();
	cPlayer::Draw();
	cGoal::Draw();
	cGhost::Draw();

	cLight::Draw();

	/*int i = 0;
	FG.setL(0, cSeika::objects[0]->position.x, cSeika::objects[0]->position.y);
	i++;
	if (cCandle::objects[0]->collision)
	{
		FG.setL(i, cCandle::objects[0]->position.x, cSeika::objects[0]->position.y);
		i++;
	}
	if (cCandle::objects[1]->collision)
	{
		FG.setL(i, cCandle::objects[0]->position.x, cSeika::objects[0]->position.y);
		i++;
	}
	FG.setLC(i);
	FG.Draw();*/
}