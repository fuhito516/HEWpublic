
// メイン
#include"scene.h"
#include"common.h"
#include"direct3d.h"
#include"vertex.h"
// 環境
#include"debugproc.h"
// シーン
#include"Title.h"
#include"SelectPlayer.h"
#include"SelectCharacter.h"
#include"SelectDifficulty.h"
#include"SelectStage.h"
#include"Game.h"

cScene* cScene::object;

// コンストラクタ
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

// 初期化
void cScene::Init()
{
	object = new cScene;
}
void cScene::Init(int _currentScene)
{
	object = new cScene(_currentScene);
}
// 解放
void cScene::Uninit()
{
	delete object;
}
// 更新
void cScene::Update()
{
	switch (object->fadeState)
	{
	case FADE_NONE:
		break;

	case FADE_OUT:
		object->fadeAlpha += 255 / FRAME_FOR_FADE;

		if (object->fadeAlpha > 255)
		{
			object->fadeAlpha = 255;
			object->fadeState = FADE_IN;

			switch (cScene::object->currentScene)
			{
			case SCENE_TITLE:
				cTitle::Uninit();
				cSelectPlayer::Init();
				break;
			case SCENE_SELECT_NUMBER_OF_PLAYER:
				cSelectPlayer::Uninit();
				cSelectCharacter::Init();
				break;
			case SCENE_SELECT_CHARACTER:
				cSelectCharacter::Uninit();
				cSelectDifficulty::Init();
				break;
			case SCENE_SELECT_DIFFICULTY:
				cSelectDifficulty::Uninit();
				cSelectStage::Init();
				break;
			case SCENE_SELECT_STAGE:
				cSelectStage::Uninit();
				cGame::Init();
				break;
			// ゲーム
			case SCENE_GAME:
				cGame::Uninit();
				break;
			case SCENE_GAMEOVER:
				break;
			case SCENE_STAGECLEAR:
				break;
			case SCENE_RETURN:
				break;

			default: break;
			}

			object->currentScene = object->nextScene;
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

	PrintDebugProc("フェードα値　%d\n", (int)object->fadeAlpha);
}
// 描画
void cScene::Draw()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// ズレがある場合(-0.5f)を各成分に付ける
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

// フェード
void cScene::Fade(int _nextScene)
{
	object->nextScene = _nextScene;
	object->fadeState = FADE_OUT;
	object->fadeAlpha = 0;
}