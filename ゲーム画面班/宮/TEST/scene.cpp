
// ���C��
#include"scene.h"
#include"common.h"
#include"direct3d.h"
#include"vertex.h"
// ��
#include"debugproc.h"
// �V�[��
#include"Title.h"
#include"Game.h"

cScene* cScene::object;

// �R���X�g���N�^
cScene::cScene()
{
	currentScene = FIRST_SCENE;
	nextScene = SCENE_NONE;
	fadeState = FADE_NONE;
	fadeAlpha = 0;
}
cScene::cScene(int _currentScene)
{
	currentScene = _currentScene;
	nextScene = SCENE_NONE;
	fadeState = FADE_NONE;
	fadeAlpha = 0;
}

// ������
void cScene::Init()
{
	object = new cScene;
}
void cScene::Init(int _currentScene)
{
	object = new cScene(_currentScene);
}
// ���
void cScene::Uninit()
{
	delete object;
}
// �X�V
void cScene::Update()
{
	switch (cScene::object->currentScene)
	{
	case SCENE_TITLE:
		cTitle::Update();
		break;
	case SCENE_GAME:
		cGame::Update();
		break;

	default: break;
	}

	switch (object->fadeState)
	{
	case FADE_NONE:
		break;

	case FADE_OUT:
		object->fadeAlpha += 255 / FRAME_FOR_FADE;
		if (object->fadeAlpha > 255)
		{
			object->fadeAlpha = 255;
			object->currentScene = object->nextScene;
			object->fadeState = FADE_IN;

			switch (cScene::object->currentScene)
			{
			case SCENE_TITLE:
				cTitle::Uninit();
				cGame::Init();
				break;
			case SCENE_GAME:
				cGame::Uninit();
				break;

			default: break;
			}
		}
		break;

	case FADE_IN:
		object->fadeAlpha -= 255 / FRAME_FOR_FADE;
		if (object->fadeAlpha < 0)
		{
			object->fadeAlpha = 0;
			object->fadeState = FADE_NONE;
		}
		break;

	default:
		break;
	}

	//PrintDebugProc("�t�F�[�h���l�@%d\n", (int)object->fadeAlpha);
}
// �`��
void cScene::Draw()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// �V�[��
	switch (cScene::object->currentScene)
	{
	case SCENE_TITLE:
		cTitle::Draw();
		break;
	case SCENE_GAME:
		cGame::Draw();
		break;

	default: break;
	}

	// �Y��������ꍇ(-0.5f)���e�����ɕt����
	Vertex_Fade vertexes[] =
	{
		{ D3DXVECTOR4(0, 0, 0, 1.0f),							D3DCOLOR_RGBA(0, 0, 0, object->fadeAlpha) },
		{ D3DXVECTOR4(SCREEN_WIDTH, 0, 0, 1.0f),				D3DCOLOR_RGBA(0, 0, 0, object->fadeAlpha) },
		{ D3DXVECTOR4(0, SCREEN_HEIGHT, 0, 1.0f),				D3DCOLOR_RGBA(0, 0, 0, object->fadeAlpha) },
		{ D3DXVECTOR4(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1.0f),	D3DCOLOR_RGBA(0, 0, 0, object->fadeAlpha) }
	};

	pD3DDevice->SetFVF(FVF_VERTEX_FADE);
	pD3DDevice->SetTexture(0, NULL);
	pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(Vertex_Fade));
}

// �t�F�[�h
void cScene::Fade(int _nextScene)
{
	object->nextScene = _nextScene;
	object->fadeState = FADE_OUT;
	object->fadeAlpha = 0;
}