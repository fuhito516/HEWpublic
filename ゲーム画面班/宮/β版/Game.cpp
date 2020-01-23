
// ���C��
#include"Game.h"
// ��
#include"camera.h"
// �v�f
#include"background.h"
#include"ground.h"
#include"player.h"
#include"seika.h"
#include"bridge.h"
#include"candle.h"
#include"goal.h"
#include"light.h"
// �V�[��
#include"scene.h"
#include"Title.h"

// ������
void cGame::Init()
{
	// ��
	cCamera::Init();

	// �v�f
	cBackground::Init();
	cGround::Init();
	cPlayer::Init();
	cSeika::Init();
	cBridge::Init();
	cCandle::Init();
	cGoal::Init();
	cLight::Init();

	// �w�i
	cBackground::SetBackground(TEXTURE_INDEX_BACK1, D3DXVECTOR3(70, 0, 200), D3DXVECTOR3(1200, 300, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK2, D3DXVECTOR3(5, 50, 180), D3DXVECTOR3(20, 20, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK3, D3DXVECTOR3(70, 20, 150), D3DXVECTOR3(600, 150, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK4, D3DXVECTOR3(70, 40, 50), D3DXVECTOR3(600, 150, 1));
	//cBackground::SetBackground(TEXTURE_INDEX_BACK5, D3DXVECTOR3(70, 00, 40), D3DXVECTOR3(20, 20, 1)); // �n�ʂɕύX
	cBackground::SetBackground(TEXTURE_INDEX_BACK6, D3DXVECTOR3(70, 00, 30), D3DXVECTOR3(200, 50, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK7, D3DXVECTOR3(70, 40, 20), D3DXVECTOR3(600, 150, 1));
	// �n��
	cGround::SetGround(D3DXVECTOR2(-17.5f, 0), D3DXVECTOR2(5.0f, 80.0f));
	cGround::SetGround(D3DXVECTOR2(0, -20.0f), D3DXVECTOR2(30.0f, 40.0f));
	cGround::SetGround(D3DXVECTOR2(30, -22.5f), D3DXVECTOR2(30.0f, 35.0f));
	cGround::SetGround(D3DXVECTOR2(52.5f, -22.5f), D3DXVECTOR2(5.0f, 35.0f));
	cGround::SetGround(D3DXVECTOR2(62.5f, -25.0f), D3DXVECTOR2(5.0f, 30.0f));
	cGround::SetGround(D3DXVECTOR2(85.0f, -27.5f), D3DXVECTOR2(30.0f, 25.0f));
	cGround::SetGround(D3DXVECTOR2(130.0f, -27.5f), D3DXVECTOR2(20.0f, 25.0f)); // �S��x=140,y=80
	// �M�~�b�N
	cCandle::SetCandle(D3DXVECTOR2(30.0f, 3.0f));
	cBridge::SetBridge(D3DXVECTOR2(95.0f, -2.0f), D3DXVECTOR2(110.0f, -16.0f), D3DXVECTOR2(20.0f, 2.0f));
	cGoal::SetGoal(D3DXVECTOR2(145, -10));
}
// �I��
void cGame::Uninit()
{
	// �v�f
	cBridge::Uninit();
	cCandle::Uninit();
	cGoal::Uninit();
	cPlayer::Uninit();
	cSeika::Uninit();
	cBackground::Uninit();
	cGround::Uninit();
	cLight::Uninit();

	// ��
	cCamera::Uninit();
}
// �X�V
void cGame::Update()
{
	// ��
	cCamera::Update();

	// �V�[��
	cGround::Update();
	cPlayer::Update();
	cSeika::Update();
	cBridge::Update();
	cCandle::Update();
	cGoal::Update();
	cLight::Update();
}
// �`��
void cGame::Draw()
{
	// ��
	cCamera::SetCamera();

	// �v�f
	cBackground::Draw();
	cGround::Draw();
	cBridge::Draw();
	cCandle::Draw();
	cSeika::Draw();
	cPlayer::Draw();
	cGoal::Draw();
	cLight::Draw();
}