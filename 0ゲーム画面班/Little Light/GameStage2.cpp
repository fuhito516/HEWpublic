// メイン
#include"GameStage1.h"
#include"GameStage3.h"
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
// シーン
#include"scene.h"
#include"Title.h"

// スプライト
#include"texture.h"
#include"sprite.h"

#include"sound.h"

// シーン遷移
static bool fade = false;

// 趙
#include "fog.h"
static Fog FG;
// 追加
// 導火線
#include "fuse.h"
static Fuse fuse_all[100];
static int fuse_count = 0;
static bool finished_1 = false;

// 初期化
void cStage2::Init()
{
	LPDIRECT3DDEVICE9	pDevice = MyDirect3D_GetDevice();

	// シーン遷移
	fade = false;

	// 環境
	cCamera::Init();

	// 要素
	cBackground::Init();
	cGround::Init();
	cVerticalMoveGround::Init();
	cHorizontalMoveGround::Init();
	cPlayer::Init();
	cSeika::Init();
	cBridge::Init();
	cCandle::Init();
	cGoal::Init();
	cGhost::Init();

	// 配置

	// プレイヤー
	cPlayer::Set(D3DXVECTOR3(0, 1, 0));
	cSeika::Set();
	// 背景
	cBackground::SetBackground(TEXTURE_INDEX_BACK1, D3DXVECTOR3(70, 0, 200), D3DXVECTOR3(1200, 300, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK2, D3DXVECTOR3(5, 10, 80), D3DXVECTOR3(20, 20, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK3, D3DXVECTOR3(70, 20, 150), D3DXVECTOR3(600, 150, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK4, D3DXVECTOR3(70, 40, 50), D3DXVECTOR3(600, 150, 1));
	//cBackground::SetBackground(TEXTURE_INDEX_BACK5, D3DXVECTOR3(70, 00, 40), D3DXVECTOR3(20, 20, 1)); // 地面に変更
	cBackground::SetBackground(TEXTURE_INDEX_BACK6, D3DXVECTOR3(70, 00, 30), D3DXVECTOR3(200, 50, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK7, D3DXVECTOR3(70, 40, 20), D3DXVECTOR3(600, 150, 1));
	
	// 地面
	// グラウンド設定(オススメはサイズは変更できるがバランスを考えると固定ブロックを基に要素を付け加えていく方がよい)
	// 地面
	cGround::SetGround(D3DXVECTOR2(-17.5f, 0.0f), D3DXVECTOR2(5.0f, 80.0f));
	cGround::SetGround(D3DXVECTOR2(0.0f, -20.0f), D3DXVECTOR2(30.0f, 40.0f));

	cGround::SetGround(D3DXVECTOR2(42.0f, -20.0f), D3DXVECTOR2(46.0f, 40.0f)); //床
	cGround::SetGround(D3DXVECTOR2(45.0f, 2.0f), D3DXVECTOR2(2.0f, 4.0f)); //でこ
	cGround::SetGround(D3DXVECTOR2(60.0f, 5.0f), D3DXVECTOR2(2.0f, 2.0f)); //穴上床を上るためのブロック
	cGround::SetGround(D3DXVECTOR2(70.0f, 8.0f), D3DXVECTOR2(10.0f, 2.0f)); //１つ目穴の上
	cGround::SetGround(D3DXVECTOR2(100.0f, -20.0f), D3DXVECTOR2(50.0f, 40.0f)); //1つ目穴次の床(2つめの床)
	cGround::SetGround(D3DXVECTOR2(100.0f, 5.0f), D3DXVECTOR2(20.0f, 2.0f)); //敵を避けるための上床
	cGhost::Set(D3DXVECTOR3(100, 2, 0), 20); //2つめの床の敵
	cGround::SetGround(D3DXVECTOR2(160.0f, -20.0f), D3DXVECTOR2(60.0f, 40.0f)); //3つ目の床
	cGround::SetGround(D3DXVECTOR2(134.0f, 2.0f), D3DXVECTOR2(2.0f, 4.0f)); //上るためのやつ
	cGround::SetGround(D3DXVECTOR2(145.0f, 8.0f), D3DXVECTOR2(20.0f, 2.0f)); //間があいてる床
	cGround::SetGround(D3DXVECTOR2(136.0f, 3.5f), D3DXVECTOR2(2.0f, 7.0f)); //穴開いてる床の左壁
	cGround::SetGround(D3DXVECTOR2(156.5f, 6.0f), D3DXVECTOR2(7.0f, 2.0f)); //穴開いてる床の終着点の段差
	cGround::SetGround(D3DXVECTOR2(188.0f, 17.0f), D3DXVECTOR2(4.0f, 34.0f)); //聖火台の下
	cGoal::Set(D3DXVECTOR3(188, 36, 0)); //聖火台

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
	fuse_all[fuse_count].Init(pDevice, 160.0f, 3.0f, 100, 0);
	fuse_all[fuse_count].setTime(10000);
	fuse_count++;
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
	cVerticalMoveGround::Uninit();
	cHorizontalMoveGround::Uninit();
	cGhost::Uninit();

	// 環境
	cCamera::Uninit();
}
// 更新
void cStage2::Update()
{
	PrintDebugProc("Hキーで操作方法\n");

	// シーン
	cGround::Update();
	cVerticalMoveGround::Update();
	cHorizontalMoveGround::Update();
	if (!fade)
	{
		cPlayer::Update();
	}
	cSeika::Update();
	cBridge::Update();
	cCandle::Update();
	cGoal::Update();
	cGhost::Update();

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

	// 導火線が終わったら追加
	if (fuse_all[0].tail->getType() == 7 && !finished_1)	// 該当番目の最後尾の状態が７番なら
	{
		cGround::SetGround(D3DXVECTOR2(179.0f, 5.0f), D3DXVECTOR2(2.0f, 2.0f));
		cVerticalMoveGround::SetGround(D3DXVECTOR2(183.0f, 17.0f), D3DXVECTOR2(4.0f, 2.0f), D3DXVECTOR2(0.0f, -9.0f));
		finished_1 = true;
	}

	// 環境
	cCamera::Update();

	// 終了判定
	if (cGhost::collision && !fade)
	{
		cScene::Fade(SCENE_GAMEOVER);
		fade = true;
		// サウンド
		StopSound(SOUND_LABEL_WALK);
	}
	else if (cGoal::collision && !fade)
	{
		cScene::Fade(SCENE_STAGECLEAR);
		fade = true;
		// サウンド
		StopSound(SOUND_LABEL_WALK);
	}
	else if (cPlayer::objects[0]->position.y < -40 && !fade)
	{
		cScene::Fade(SCENE_GAMEOVER);
		fade = true;
		// サウンド
		StopSound(SOUND_LABEL_WALK);
	}
	else if (cSeika::objects[0]->position.y < -40 && !fade)
	{
		cScene::Fade(SCENE_GAMEOVER);
		fade = true;
		// サウンド
		StopSound(SOUND_LABEL_WALK);
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
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	pD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	// 操作方法
	if (GetKeyboardPress(DIK_H))
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_CONTROL,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
			2, 2,
			0, 0,
			1, 1
		);
	}

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
	/*if (cCandle::objects[0]->collision)
	{
		FG.setL(i, cCandle::objects[0]->position.x, cCandle::objects[0]->position.y);
		i++;
	}
	if (cBridge::objects[0]->collision)
	{
		FG.setL(i, cBridge::objects[0]->gimmickPosition.x, cBridge::objects[0]->gimmickPosition.y);
		i++;
	}*/
	FG.setLC(i);
	FG.Draw();
}