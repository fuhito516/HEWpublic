
// ���C��
#include"Game.h"
// ��
#include"camera.h"
#include"debugproc.h"
// �v�f
#include"background.h"
#include"ground.h"
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
#include"object.h"

// ���ΐ�
#include "fuse.h"
Fuse fuse_all[100];
int fuse_count=0;

#include "fog.h"
Fog FG;

// ������
void cGame::Init()
{
	LPDIRECT3DDEVICE9	pDevice = MyDirect3D_GetDevice();
	// ��
	cCamera::Init();

	// �v�f
	cBackground::Init();
	cGround::Init();
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
	cGoal::Set(D3DXVECTOR3(145, -10, 0));
	cGhost::Set(D3DXVECTOR3(110, -15, 0), 20);

	LPDIRECT3DTEXTURE9	g_p;
	FG.Init(pDevice, 800, 200, 1);
	FG.Move(0, 0, -0.5);
	D3DXCreateTextureFromFile(pDevice, "asset/texture/Fog_ex.png", &g_p);
	FG.setT(g_p);

	// ���ΐ�
	// ��Q�����E�E�E���Sx���W
	// ��R�����E�E�E���Sy���W
	// ��S�����E�E�E��(�����Ƃ͂��ƂȂ�̂Œ����K�v)
	// ��T�����E�E�E��������(0������1���E��2�����3������)
	fuse_all[fuse_count].Init(pDevice, 10, 0, 100, 0); // fuse_count 0 ����
	fuse_all[fuse_count].setTime(5000);	// �T�b�����Ē���
	fuse_count++;


	fuse_all[fuse_count].Init(pDevice, 20, 10, 100, 2);
	fuse_all[fuse_count].setTime(5000);
	fuse_count++;

	fuse_all[fuse_count].Init(pDevice, 30, 0, 100, 0);
	fuse_all[fuse_count].setTime(5000);

	fuse_count++;
	/*fuse_all[fuse_count].Init(pDevice, 20, -10, 100, 3);
	fuse_all[fuse_count].setTime(5000);
	fuse_count++;*/

	


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
	cGhost::Uninit();
	cLight::Uninit();

	// ��
	cCamera::Uninit();
}
// �X�V
void cGame::Update()
{
	// �V�[��
	cGround::Update();
	cPlayer::Update();
	cSeika::Update();
	cBridge::Update();
	cCandle::Update();
	cGoal::Update();
	cGhost::Update();
	cLight::Update();

	for (int i = 0; i < fuse_count; i++)
	{
		// ���΂Ƃ����
		if (pow(fuse_all[i].Block[0].getXY().x - cSeika::objects[0]->position.x, 2) + pow(fuse_all[i].Block[0].getXY().y - cSeika::objects[0]->position.y, 2) <= pow(BLOCK_SIZE + RADIUS_SEIKA, 2))
		{
			fuse_all[i].setStartTime(GetTickCount());	// ���ΐ�����
		}

		if (fuse_all[i].getState() == 1)
		{
			fuse_all[i].Update();
			for (int j = 0; j < fuse_count; j++)
			{
				if ((j != i) && (fuse_all[j].getState() == 0) && 
					(fuse_all[i].tail->getType() == 6)&&
					(pow(fuse_all[i].Block[fuse_all[i].length - 1].getXY().x - fuse_all[j].Block[0].getXY().x, 2) +
						pow(fuse_all[i].Block[fuse_all[i].length - 1].getXY().y - fuse_all[j].Block[0].getXY().y, 2)
						<= pow(BLOCK_SIZE*2, 2)
						)
					)
				{
					fuse_all[j].setStartTime(GetTickCount());
				}
			}
		}
	}

	/*
	if (fuse_all[���Ԗ�].tail->getTye() == 7 && !finished_���Ԗ�)	// �Y���Ԗڂ̍Ō���̏�Ԃ��V�ԂȂ�
	{
		Set(�M�~�b�N);
		finished_���Ԗ� = true;
	}
	*/

	// �ǉ�
	FG.ChangeSize(FG.GetBACEKESU() - 0.001f);
	FG.Update();

	// ��
	cCamera::Update();

	// �I������
	if (cGhost::collision)
	{
		// �Q�[���I�[�o�[
	}
	else if (cGoal::collision)
	{
		// �Q�[���N���A
	}
}
// �`��
void cGame::Draw()
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
	
	// ���ΐ�
	for (int i = 0; i < fuse_count; i++)
	{
		fuse_all[i].Draw();
	}

	cGround::Draw();
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