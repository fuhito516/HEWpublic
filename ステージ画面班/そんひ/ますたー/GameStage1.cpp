
//メイン
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

// スプライト
#include"texture.h"
#include"sprite.h"

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
static bool finished_3 = false;

// 初期化
void cStage1::Init()
{
	LPDIRECT3DDEVICE9	pDevice = MyDirect3D_GetDevice();

	// シーン遷移
	fade = false;

	finished_1 = false;
	finished_3 = false;

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
	cPlayer::Set(D3DXVECTOR3(100, 30, 0));
	cSeika::Set();
	cLight::Set();
	// 背景
	cBackground::SetBackground(TEXTURE_INDEX_BACK1, D3DXVECTOR3(120, 0, 200), D3DXVECTOR3(1300, 400, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK2, D3DXVECTOR3(5, 50, 180), D3DXVECTOR3(20, 20, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK3, D3DXVECTOR3(70, 20, 150), D3DXVECTOR3(600, 150, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK4, D3DXVECTOR3(70, 40, 50), D3DXVECTOR3(600, 150, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK5, D3DXVECTOR3(70, 00, 40), D3DXVECTOR3(20, 20, 1)); // 地面に変更
	cBackground::SetBackground(TEXTURE_INDEX_BACK6, D3DXVECTOR3(70, 00, 30), D3DXVECTOR3(200, 50, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK7, D3DXVECTOR3(70, 40, 20), D3DXVECTOR3(600, 150, 1));

	// 地面
	//底辺の座標 y == -40-------------------------------------------------------------------------
	cGround::SetGround(D3DXVECTOR2(-17.5f, 0), D3DXVECTOR2(5.0f, 80.0f));
	cGround::SetGround(D3DXVECTOR2(38.75f, -20.0f), D3DXVECTOR2(112.5f, 40.0f));  //前-4.0f,2.0f
	cGround::SetGround(D3DXVECTOR2(20, 0.0f), D3DXVECTOR2(2.0f, 10.0f)); //-0.5,5.0
	cGround::SetGround(D3DXVECTOR2(25, 0.0f), D3DXVECTOR2(2.0f, 20.0f));
	cGround::SetGround(D3DXVECTOR2(30, 0.0f), D3DXVECTOR2(2.0f, 10.0f));
	cGround::SetGround(D3DXVECTOR2(38, 9.0f), D3DXVECTOR2(6.0f, 2.0f));
	cVerticalMoveGround::SetGround(D3DXVECTOR2(56.0, 16.0f), D3DXVECTOR2(20.0f, 2.0f), D3DXVECTOR2(0.0f, 4.0f));

	cGround::SetGround(D3DXVECTOR2(75, -0.0f), D3DXVECTOR2(2.0f, 6.0f));//下ルート
																		//ここの間に敵入れたい！！！
	cGround::SetGround(D3DXVECTOR2(94, 0.0f), D3DXVECTOR2(2.0f, 8.0f));//下ルート
	cGround::SetGround(D3DXVECTOR2(100, -19.0f), D3DXVECTOR2(2.0f, 42.0f));//下ルート
																	   //ここの間に敵入れたい！！！
	cGround::SetGround(D3DXVECTOR2(105, -20.0f), D3DXVECTOR2(2.0f, 40.0f));//下ルート

	cGround::SetGround(D3DXVECTOR2(110, -21.5f), D3DXVECTOR2(2.0f, 37.0f));//下ルート

	cGround::SetGround(D3DXVECTOR2(118, -22.0f), D3DXVECTOR2(8.0f, 36.0f));//下ルート
																		   //-12の上に敵配置
	cGround::SetGround(D3DXVECTOR2(125, -25.0f), D3DXVECTOR2(6.0f, 30.0f));//下ルート
	cGround::SetGround(D3DXVECTOR2(132, -23.0f), D3DXVECTOR2(8.0f, 34.0f));//下ルート
																		   //-12の上に敵配置
	cGround::SetGround(D3DXVECTOR2(140, -22.0f), D3DXVECTOR2(8.0f, 36.0f));//下ルート

	cGround::SetGround(D3DXVECTOR2(135, 6.0f), D3DXVECTOR2(10.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(130, 10.0f), D3DXVECTOR2(2.0f, 6.0f));

	cGround::SetGround(D3DXVECTOR2(119, 6.0f), D3DXVECTOR2(10.0f, 6.0f));//下ルート
	cGround::SetGround(D3DXVECTOR2(129, 6.0f), D3DXVECTOR2(10.0f, 6.0f));//下ルート

																		 //--------------------------------
																		 //上ルートブロック
																		 //--------------------------------
	cGround::SetGround(D3DXVECTOR2(77, 20.0f), D3DXVECTOR2(10.0f, 2.0f));
	cGround::SetGround(D3DXVECTOR2(86, 12.0f), D3DXVECTOR2(2.0f, 12.0f));
	cGround::SetGround(D3DXVECTOR2(95, 20.0f), D3DXVECTOR2(10.0f, 2.0f));
	//ここの間に敵
	cGround::SetGround(D3DXVECTOR2(109, 20.0f), D3DXVECTOR2(12.0f, 2.0f));
	//ここら辺にスコアに加算されるものを配置
	cGround::SetGround(D3DXVECTOR2(97, 22.0f), D3DXVECTOR2(2.0f, 4.0f));
	cGround::SetGround(D3DXVECTOR2(109, 22.0f), D3DXVECTOR2(2.0f, 4.0f));//ここ飛び越えて下の上のブロックに到達


	cGround::SetGround(D3DXVECTOR2(130, 10.0f), D3DXVECTOR2(2.0f, 6.0f));

	//cGround::SetGround(D3DXVECTOR2(139, 6.0f), D3DXVECTOR2(10.0f, 6.0f));

	//----------------------------
	//ゴール階段
	//----------------------------
	cGround::SetGround(D3DXVECTOR2(148, -21.0f), D3DXVECTOR2(8.0f, 38.0f));
	cGround::SetGround(D3DXVECTOR2(156, -20.0f), D3DXVECTOR2(8.0f, 40.0f));
	cGround::SetGround(D3DXVECTOR2(159, -19.0f), D3DXVECTOR2(2.0f, 42.0f));
	cGround::SetGround(D3DXVECTOR2(161, -18.0f), D3DXVECTOR2(2.0f, 44.0f));
	cGround::SetGround(D3DXVECTOR2(163, -17.0f), D3DXVECTOR2(2.0f, 46.0f));
	cGround::SetGround(D3DXVECTOR2(165, -16.0f), D3DXVECTOR2(2.0f, 48.0f));
	cGround::SetGround(D3DXVECTOR2(167, -15.0f), D3DXVECTOR2(2.0f, 50.0f));
	cGround::SetGround(D3DXVECTOR2(169, -14.0f), D3DXVECTOR2(2.0f, 52.0f));
	cGround::SetGround(D3DXVECTOR2(172, -13.0f), D3DXVECTOR2(4.0f, 54.0f));//ゴールの灯す場所

																		   //-------------------
																		   //後半のステージ床X＝172からスタート
																		   //-------------------
	cGround::SetGround(D3DXVECTOR2(173, -12.0f), D3DXVECTOR2(2.0f, 54.0f));//ゴールの灯す場所

	cGround::SetGround(D3DXVECTOR2(175, -14.0f), D3DXVECTOR2(2.0f, 52.0f));//最初の段差
	cGround::SetGround(D3DXVECTOR2(177, -15.0f), D3DXVECTOR2(2.0f, 50.0f));//戻る時用
	cGround::SetGround(D3DXVECTOR2(179, -16.0f), D3DXVECTOR2(2.0f, 48.0f));
	cGround::SetGround(D3DXVECTOR2(181, -17.0f), D3DXVECTOR2(2.0f, 46.0f));
	cGround::SetGround(D3DXVECTOR2(182, -18.0f), D3DXVECTOR2(2.0f, 44.0f));

	cHorizontalMoveGround::SetGround(D3DXVECTOR2(189.0f, 9.0f), D3DXVECTOR2(6.0f, 1.0f), D3DXVECTOR2(3.0f, 0.0f));
	cGhost::Set(D3DXVECTOR3(197.0f, 3.0f, 0.0f), 14.0f);
	cHorizontalMoveGround::SetGround(D3DXVECTOR2(200.0f, 9.0f), D3DXVECTOR2(5.0f, 1.0f), D3DXVECTOR2(-3.0f, 0.0f));

	cGround::SetGround(D3DXVECTOR2(192, -19.0f), D3DXVECTOR2(35.0f, 42.0f));

	//ここに横に移動する敵を追加
	cGround::SetGround(D3DXVECTOR2(210, -15.0f), D3DXVECTOR2(2.0f, 50.0f));
	cGround::SetGround(D3DXVECTOR2(214, -19.0f), D3DXVECTOR2(8.0f, 42.0f));
	//落ちたらOUTの動く床ゾーン
	cHorizontalMoveGround::SetGround(D3DXVECTOR2(228, 6.0f), D3DXVECTOR2(5.0f, 2.0f), D3DXVECTOR2(5.0f, 0.0f));
	cHorizontalMoveGround::SetGround(D3DXVECTOR2(247, 6.0f), D3DXVECTOR2(5.0f, 2.0f), D3DXVECTOR2(-5.0f, 0.0f));
	cVerticalMoveGround::SetGround(D3DXVECTOR2(238.0, -2.0f), D3DXVECTOR2(5.0f, 2.0f), D3DXVECTOR2(0.0f, 5.0f));
	cVerticalMoveGround::SetGround(D3DXVECTOR2(238.0, 15.0f), D3DXVECTOR2(5.0f, 2.0f), D3DXVECTOR2(0.0f, -5.0f));

	//cCandle::SetCandle(D3DXVECTOR2(238.0, 10.0f));
	//下ルート
	cGround::SetGround(D3DXVECTOR2(214, -19.0f), D3DXVECTOR2(8.0f, 42.0f));
	cBridge::SetBridge(D3DXVECTOR2(238.0, 9.0f), D3DXVECTOR2(250, -30.0f), D3DXVECTOR2(10.0f, 20.0f));
	cGround::SetGround(D3DXVECTOR2(260, -33.0f), D3DXVECTOR2(10.0f, 14.0f));
	cGhost::Set(D3DXVECTOR3(260, -25.0f, 0), 5);
	cCandle::SetCandle(D3DXVECTOR2(260, -15.0f));
	cBridge::SetBridge(D3DXVECTOR2(260, -15.0f), D3DXVECTOR2(260, -19.0f), D3DXVECTOR2(10.0f, 2.0f));
	cGround::SetGround(D3DXVECTOR2(275, -30.0f), D3DXVECTOR2(13.0f, 18.0f));
	cGround::SetGround(D3DXVECTOR2(282, -28.0f), D3DXVECTOR2(2.0f, 22.0f));
	cGround::SetGround(D3DXVECTOR2(284, -27.0f), D3DXVECTOR2(2.0f, 24.0f));
	cGround::SetGround(D3DXVECTOR2(286, -26.0f), D3DXVECTOR2(2.0f, 26.0f));
	cGround::SetGround(D3DXVECTOR2(288, -25.0f), D3DXVECTOR2(2.0f, 28.0f));
	cGround::SetGround(D3DXVECTOR2(290, -24.0f), D3DXVECTOR2(2.0f, 30.0f));
	cGround::SetGround(D3DXVECTOR2(292, -23.0f), D3DXVECTOR2(2.0f, 32.0f));
	cGround::SetGround(D3DXVECTOR2(296, -22.0f), D3DXVECTOR2(6.0f, 34.0f));

	cGoal::Set(D3DXVECTOR3(297, -1, 0));

	//上ルート（床あるだけｗ）
	cGround::SetGround(D3DXVECTOR2(248, 22.0f), D3DXVECTOR2(8.0f, 2.0f));
	//上の下（）
	cGround::SetGround(D3DXVECTOR2(262, 5.0f), D3DXVECTOR2(10.0f, 2.0f));
	cGround::SetGround(D3DXVECTOR2(271, 8.0f), D3DXVECTOR2(10.0f, 5.0f));


	// 導火線
	// 第２引数・・・中心x座標
	// 第３引数・・・中心y座標
	// 第４引数・・・幅(長さとはことなるので調整必要)
	// 第５引数・・・流れる方向(0が右へ1が左へ2が上へ3が下へ)
	// 要素0
	fuse_all[fuse_count].Init(pDevice, 120, 25, 50, 0); // fuse_count 0 から
	fuse_all[fuse_count].setTime(1000);	// 秒かけて鎮火(変更可)
	fuse_count++;
	// 要素1
	fuse_all[fuse_count].Init(pDevice, 135, 25, 50, 0);
	fuse_all[fuse_count].setTime(1000);	// 時間も調整しよう※相対速度を変えると、描画がかわるから、％は同じように
	fuse_count++;
	// 要素2
	fuse_all[fuse_count].Init(pDevice, 127.5f, 25.0f - 3.75f, 25, 3);
	fuse_all[fuse_count].setTime(1000);	// 時間も調整しよう※相対速度を変えると、描画がかわるから、％は同じように
	fuse_count++;
	// 要素3
	fuse_all[fuse_count].Init(pDevice, 135, 13.75f + 3.75f, 50, 0);
	fuse_all[fuse_count].setTime(1000);	// 時間も調整しよう※相対速度を変えると、描画がかわるから、％は同じように
	fuse_count++;

	// 設定を調整するのは大変になるから、50個のブロックだと7.5fずつずらすことできれいに配置できることを意識しよう。
	// 25個ならその半分の3.75f

	// フォグ
	LPDIRECT3DTEXTURE9	g_p;
	FG.Init(pDevice, 2400, 600, 1);
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
	PrintDebugProc("Hキーで操作方法\n");

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

	// 導火線(考えなくていい
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
		cGround::SetGround(D3DXVECTOR2(120, 20), D3DXVECTOR2(5, 1));
		cGround::SetGround(D3DXVECTOR2(125, 16), D3DXVECTOR2(5, 1));
		finished_1 = true;
	}
	// 要素3が終わったら地面を配置、宮追加
	if (fuse_all[3].tail->getType() == 7 && !finished_3)	// 該当番目の最後尾の状態が７番なら
	{
		cGhost::Set(D3DXVECTOR3(120, 12, 0), 10);
		finished_3 = true;
	}

	// 環境
	cCamera::Update();

	// 終了判定
	if (cGhost::collision)
	{
		cScene::Fade(SCENE_GAMEOVER);
		fade = true;
	}
	else if (cGoal::collision)
	{
		cScene::Fade(SCENE_STAGECLEAR);
		fade = true;
	}
	else if (cPlayer::objects[0]->position.y < -40 && !fade)
	{
		cScene::Fade(SCENE_GAMEOVER);
		fade = true;
	}
}
// 描画
void cStage1::Draw()
{
	LPDIRECT3DDEVICE9	pD3DDevice = MyDirect3D_GetDevice();

	// 環境
	cCamera::SetCamera();

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

	// αブレンド
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	pD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	// 要素
	cBackground::Draw();

	// 導火線(考えなくていい
	for (int i = 0; i < fuse_count; i++)
	{
		fuse_all[i].Draw();
	}

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

	// 灯
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
	FG.setL(i, cSeika::objects[0]->position.x, cSeika::objects[0]->position.y);
	i++;
	/*if (cCandle::objects[0]->collision)
	{
	FG.setL(i, cCandle::objects[0]->position.x, cCandle::objects[0]->position.y);
	i++;
	}*/
	for (int j = 0; j < 2; j++)
	{
		if (cBridge::objects[j]->collision)
		{
			FG.setL(i, cBridge::objects[j]->gimmickPosition.x, cBridge::objects[j]->gimmickPosition.y);
			i++;
		}
	}
	FG.setLC(i);
	FG.Draw();
}