
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
#include "fog.h"
static Fog FG;
// 追加
// 導火線
#include "fuse.h"
Fuse fuse_all[100];
int fuse_count = 0;
bool finished_1 = false;

// シーン遷移
static bool fade = false;

// 初期化
void cGame::Init()
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
	cBackground::SetBackground(TEXTURE_INDEX_BACK2, D3DXVECTOR3(5, 10, 80), D3DXVECTOR3(20, 20, 1));
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

	// フォグ
	LPDIRECT3DTEXTURE9	g_p;
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
	}

	// 導火線
	// 第２引数・・・中心x座標
	// 第３引数・・・中心y座標
	// 第４引数・・・幅(長さとはことなるので調整必要)
	// 第５引数・・・流れる方向(0が左へ1が右へ2が上へ3が下へ)
	// 要素0
	fuse_all[fuse_count].Init(pDevice, 10, 5, 50, 0); // fuse_count 0 から
	fuse_all[fuse_count].setTime(5000);	// ５秒かけて鎮火(変更可)
	fuse_count++;
	// 要素1
	fuse_all[fuse_count].Init(pDevice, 17.5f, 8.5f, 25, 2);
	fuse_all[fuse_count].setTime(2500);	// 時間も調整しよう※相対速度を変えると、描画がかわるから、％は同じように
	fuse_count++;
	// 要素2

	// 設定を調整するのは大変になるから、50個のブロックだと7.5fずつずらすことできれいに配置できることを意識しよう。
	// 25個ならその半分の3.75f
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
	cVerticalMoveGround::Uninit();
	cHorizontalMoveGround::Uninit();
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
	cVerticalMoveGround::Update();
	cHorizontalMoveGround::Update();
	cPlayer::Update();
	cSeika::Update();
	cBridge::Update();
	cCandle::Update();
	cGoal::Update();
	cGhost::Update();
	cLight::Update();
	
	// フォグ
	FG.ChangeSize(FG.GetBACEKESU() - 0.001f);
	FG.Update();

	// 導火線
	for (int i = 0; i < fuse_count; i++)
	{
		// 聖火との趙突
		if (
			(pow(fuse_all[i].Block[0].getXY().x - cSeika::objects[0]->position.x, 2) + pow(fuse_all[i].Block[0].getXY().y - cSeika::objects[0]->position.y, 2) <= pow(BLOCK_SIZE + 1 + RADIUS_SEIKA, 2))
			&& (fuse_all[i].Block[0].getType() == 5)
			)
		{
			fuse_all[i].setStartTime(GetTickCount());	// 導火線着火
		}

		if (fuse_all[i].getState() == 1)
		{
			fuse_all[i].Update();
			for (int j = 0; j < fuse_count; j++)
			{
				if ((j != i) && (fuse_all[j].getState() == 0) &&
					(fuse_all[i].tail->getType() == 6) &&
					(pow(fuse_all[i].Block[fuse_all[i].length - 1].getXY().x - fuse_all[j].Block[0].getXY().x, 2) +
						pow(fuse_all[i].Block[fuse_all[i].length - 1].getXY().y - fuse_all[j].Block[0].getXY().y, 2)
						<= pow(BLOCK_SIZE * 2, 2)
						)
					)
				{
					fuse_all[j].setStartTime(GetTickCount());
				}
			}
		}
	}

	// 要素1が終わったら地面を配置、宮追加
	if (fuse_all[1].tail->getType() == 7 && !finished_1)	// 該当番目の最後尾の状態が７番なら
	{
		cGround::SetGround(D3DXVECTOR2(20, 4), D3DXVECTOR2(5, 1));
		cGround::SetGround(D3DXVECTOR2(25, 8), D3DXVECTOR2(5, 1));
		finished_1 = true;
	}
	

	// 環境
	cCamera::Update();

	// 終了判定
	if (cGhost::collision && !fade)
	{
		cScene::Fade(SCENE_GAMEOVER);
		fade = true;
	}
	else if (cGoal::collision && !fade)
	{
		cScene::Fade(SCENE_STAGECLEAR);
		fade = true;
	}

	//SATGE1遷移
	if (GetKeyboardPress(DIK_RETURN))
	{
		cScene::Fade(STAGE_ONE);
	}
}
// 描画
void cGame::Draw()
{
	LPDIRECT3DDEVICE9	pD3DDevice = MyDirect3D_GetDevice();

	// 環境
	cCamera::SetCamera();

	// αブレンド
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	pD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	

	// 要素
	cBackground::Draw();

	// 導火線
	for (int i = 0; i < fuse_count; i++)
	{
		fuse_all[i].Draw();
	}

	cGround::Draw();
	cVerticalMoveGround::Draw();;
	cHorizontalMoveGround::Draw();
	cBridge::Draw();
	cCandle::Draw();
	cPlayer::Draw();
	cSeika::Draw();
	cGoal::Draw();
	cGhost::Draw();
	//cLight::Draw();

	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
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
	FG.Draw();
}