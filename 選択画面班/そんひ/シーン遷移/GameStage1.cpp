
// ���C��
#include"Game.h"
#include"GameStage1.h"
#include"GameStage2.h"
// ��
#include"camera.h"
#include"debugproc.h"
#include"input.h"
// �v�f
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
// �V�[��
#include"scene.h"
#include"Title.h"

// ��
#include "fog.h"
static Fog FG;

// ������
void cStage1::Init()
{
	LPDIRECT3DDEVICE9	pDevice = MyDirect3D_GetDevice();
	// ��
	cCamera::Init();

	// �v�f
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

	// �z�u

	// �v���C���[
	cPlayer::Set(D3DXVECTOR3(0, 1, 0));
	cSeika::Set();
	cLight::Set();
	// �w�i
	cBackground::SetBackground(TEXTURE_INDEX_BACK1, D3DXVECTOR3(70, 0, 200), D3DXVECTOR3(1200, 300, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK2, D3DXVECTOR3(5, 50, 180), D3DXVECTOR3(20, 20, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK3, D3DXVECTOR3(70, 20, 150), D3DXVECTOR3(600, 150, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK4, D3DXVECTOR3(70, 40, 50), D3DXVECTOR3(600, 150, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK5, D3DXVECTOR3(70, 00, 40), D3DXVECTOR3(20, 20, 1)); // �n�ʂɕύX
	cBackground::SetBackground(TEXTURE_INDEX_BACK6, D3DXVECTOR3(70, 00, 30), D3DXVECTOR3(200, 50, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK7, D3DXVECTOR3(70, 40, 20), D3DXVECTOR3(600, 150, 1));

	// �n��
	//��ӂ̍��W y == -40-------------------------------------------------------------------------
	cGround::SetGround(D3DXVECTOR2(-17.5f, 0), D3DXVECTOR2(5.0f, 80.0f));
	cGround::SetGround(D3DXVECTOR2(38.75f, -20.0f), D3DXVECTOR2(112.5f, 40.0f));  //�O-4.0f,2.0f
	cGround::SetGround(D3DXVECTOR2(20, 0.0f), D3DXVECTOR2(2.0f, 10.0f)); //-0.5,5.0
	cGround::SetGround(D3DXVECTOR2(25, 0.0f), D3DXVECTOR2(2.0f, 20.0f));
	cGround::SetGround(D3DXVECTOR2(30, 0.0f), D3DXVECTOR2(2.0f, 10.0f));
	cGround::SetGround(D3DXVECTOR2(38, 9.0f), D3DXVECTOR2(6.0f, 2.0f));
	cVerticalMoveGround::SetGround(D3DXVECTOR2(56.0, 16.0f), D3DXVECTOR2(20.0f, 2.0f), D3DXVECTOR2(0.0f, 4.0f));

	cGround::SetGround(D3DXVECTOR2(75, -0.0f), D3DXVECTOR2(2.0f, 6.0f));//�����[�g
																		//�����̊ԂɓG���ꂽ���I�I�I
	cGround::SetGround(D3DXVECTOR2(94, 0.0f), D3DXVECTOR2(2.0f, 8.0f));//�����[�g
																	   //�����̊ԂɓG���ꂽ���I�I�I
	cGround::SetGround(D3DXVECTOR2(105, -20.0f), D3DXVECTOR2(2.0f, 40.0f));//�����[�g

	cGround::SetGround(D3DXVECTOR2(118, -22.0f), D3DXVECTOR2(8.0f, 36.0f));//�����[�g
																		   //-12�̏�ɓG�z�u
	cGround::SetGround(D3DXVECTOR2(125, -25.0f), D3DXVECTOR2(6.0f, 30.0f));//�����[�g
	cGround::SetGround(D3DXVECTOR2(132, -23.0f), D3DXVECTOR2(8.0f, 34.0f));//�����[�g
																		   //-12�̏�ɓG�z�u
	cGround::SetGround(D3DXVECTOR2(140, -22.0f), D3DXVECTOR2(8.0f, 36.0f));//�����[�g

	cGround::SetGround(D3DXVECTOR2(135, 6.0f), D3DXVECTOR2(10.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(130, 10.0f), D3DXVECTOR2(2.0f, 6.0f));

	cGround::SetGround(D3DXVECTOR2(119, 6.0f), D3DXVECTOR2(10.0f, 6.0f));//�����[�g
	cGround::SetGround(D3DXVECTOR2(129, 6.0f), D3DXVECTOR2(10.0f, 6.0f));//�����[�g



																		 //--------------------------------
																		 //�ニ�[�g�u���b�N
																		 //--------------------------------
	cGround::SetGround(D3DXVECTOR2(77, 20.0f), D3DXVECTOR2(10.0f, 2.0f));
	cGround::SetGround(D3DXVECTOR2(86, 12.0f), D3DXVECTOR2(2.0f, 12.0f));
	cGround::SetGround(D3DXVECTOR2(95, 20.0f), D3DXVECTOR2(10.0f, 2.0f));
	//�����̊ԂɓG
	cGround::SetGround(D3DXVECTOR2(109, 20.0f), D3DXVECTOR2(12.0f, 2.0f));
	//������ӂɃX�R�A�ɉ��Z�������̂�z�u
	cGround::SetGround(D3DXVECTOR2(97, 22.0f), D3DXVECTOR2(2.0f, 4.0f));
	cGround::SetGround(D3DXVECTOR2(109, 22.0f), D3DXVECTOR2(2.0f, 4.0f));//������щz���ĉ��̏�̃u���b�N�ɓ��B

	cGround::SetGround(D3DXVECTOR2(130, 10.0f), D3DXVECTOR2(2.0f, 6.0f));

	cGround::SetGround(D3DXVECTOR2(139, 6.0f), D3DXVECTOR2(10.0f, 6.0f));

	//----------------------------
	//�S�[���K�i
	//----------------------------
	cGround::SetGround(D3DXVECTOR2(148, -21.0f), D3DXVECTOR2(8.0f, 38.0f));
	cGround::SetGround(D3DXVECTOR2(156, -20.0f), D3DXVECTOR2(8.0f, 40.0f));
	cGround::SetGround(D3DXVECTOR2(159, -19.0f), D3DXVECTOR2(2.0f, 42.0f));
	cGround::SetGround(D3DXVECTOR2(161, -18.0f), D3DXVECTOR2(2.0f, 44.0f));
	cGround::SetGround(D3DXVECTOR2(163, -17.0f), D3DXVECTOR2(2.0f, 46.0f));
	cGround::SetGround(D3DXVECTOR2(165, -16.0f), D3DXVECTOR2(2.0f, 48.0f));
	cGround::SetGround(D3DXVECTOR2(167, -15.0f), D3DXVECTOR2(2.0f, 50.0f));
	cGround::SetGround(D3DXVECTOR2(169, -14.0f), D3DXVECTOR2(2.0f, 52.0f));
	cGround::SetGround(D3DXVECTOR2(172, -13.0f), D3DXVECTOR2(4.0f, 54.0f));//�S�[���̓����ꏊ

																		   //-------------------
																		   //�㔼�̃X�e�[�W��X��172����X�^�[�g
																		   //-------------------
	cGround::SetGround(D3DXVECTOR2(173, -12.0f), D3DXVECTOR2(2.0f, 54.0f));//�S�[���̓����ꏊ

	cGround::SetGround(D3DXVECTOR2(175, -14.0f), D3DXVECTOR2(2.0f, 52.0f));//�ŏ��̒i��
	cGround::SetGround(D3DXVECTOR2(177, -15.0f), D3DXVECTOR2(2.0f, 50.0f));//�߂鎞�p
	cGround::SetGround(D3DXVECTOR2(179, -16.0f), D3DXVECTOR2(2.0f, 48.0f));
	cGround::SetGround(D3DXVECTOR2(181, -17.0f), D3DXVECTOR2(2.0f, 46.0f));
	cGround::SetGround(D3DXVECTOR2(182, -18.0f), D3DXVECTOR2(2.0f, 44.0f));

	cHorizontalMoveGround::SetGround(D3DXVECTOR2(188, 12.0f), D3DXVECTOR2(5.0f, 2.0f), D3DXVECTOR2(4.0f, 0.0f));
	cHorizontalMoveGround::SetGround(D3DXVECTOR2(205, 12.0f), D3DXVECTOR2(5.0f, 2.0f), D3DXVECTOR2(-4.0f, 0.0f));

	cGround::SetGround(D3DXVECTOR2(192, -19.0f), D3DXVECTOR2(35.0f, 42.0f));

	//�����ɉ��Ɉړ�����G��ǉ�
	cGround::SetGround(D3DXVECTOR2(210, -15.0f), D3DXVECTOR2(2.0f, 50.0f));
	cGround::SetGround(D3DXVECTOR2(214, -19.0f), D3DXVECTOR2(8.0f, 42.0f));
	//��������OUT�̓������]�[��
	cHorizontalMoveGround::SetGround(D3DXVECTOR2(228, 6.0f), D3DXVECTOR2(5.0f, 2.0f), D3DXVECTOR2(5.0f, 0.0f));
	cHorizontalMoveGround::SetGround(D3DXVECTOR2(247, 6.0f), D3DXVECTOR2(5.0f, 2.0f), D3DXVECTOR2(-5.0f, 0.0f));
	cVerticalMoveGround::SetGround(D3DXVECTOR2(238.0, -2.0f), D3DXVECTOR2(5.0f, 2.0f), D3DXVECTOR2(0.0f, 5.0f));
	cVerticalMoveGround::SetGround(D3DXVECTOR2(238.0, 15.0f), D3DXVECTOR2(5.0f, 2.0f), D3DXVECTOR2(0.0f, -5.0f));

	cCandle::SetCandle(D3DXVECTOR2(238.0, 10.0f));
	//�����[�g
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


	//�ニ�[�g�i�����邾�����j
	cGround::SetGround(D3DXVECTOR2(248, 22.0f), D3DXVECTOR2(8.0f, 2.0f));
	//��̉��i�j
	cGround::SetGround(D3DXVECTOR2(262, 5.0f), D3DXVECTOR2(10.0f, 2.0f));
	cGround::SetGround(D3DXVECTOR2(271, 8.0f), D3DXVECTOR2(10.0f, 5.0f));

	// �t�H�O
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
}
// �I��
void cStage1::Uninit()
{
	// �v�f
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

	// ��
	cCamera::Uninit();
}
// �X�V
void cStage1::Update()
{
	// �V�[��
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

	// �t�H�O
	FG.ChangeSize(FG.GetBACEKESU() - 0.001f);
	FG.Update();

	// ��
	cCamera::Update();

	// �I������
	if (cGhost::collision)
	{

	}
	else if (cGoal::collision)
	{

	}
	//SATGE2�J��
	if (GetKeyboardPress(DIK_RETURN))
	{
		cScene::Fade(STAGE_TWO);
	}
}
// �`��
void cStage1::Draw()
{
	LPDIRECT3DDEVICE9	pD3DDevice = MyDirect3D_GetDevice();

	// ��
	cCamera::SetCamera();

	// ���u�����h
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	pD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	// �v�f
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
	/*if (cBridge::objects[0]->collision)
	{
		FG.setL(i, cBridge::objects[0]->gimmickPosition.x, cBridge::objects[0]->gimmickPosition.y);
		i++;
	}*/
	FG.setLC(i);
	FG.Draw();
}