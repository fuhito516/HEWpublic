
// メイン
#include"main.h"
#include"common.h"
#include<Windows.h>
#include"direct3d.h"
#include"debugproc.h"
// 環境
#include"texture.h"
#include"sprite.h"
#include"vertex.h"
#include"camera.h"
#include"input.h"
#include<dinput.h>
// シーン
#include"scene.h"
#include"Title.h"
#include"SelectPlayer.h"
#include"SelectCharacter.h"
#include"SelectDifficulty.h"
#include"SelectStage.h"
#include"Game.h"
#include"GameStage1.h"
#include"GameStage2.h"
#include"Gameover.h"
#include"Gameclear.h"

// システム
static HWND g_hWnd;
D3DLIGHT9 gLight;

// メイン関数
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	// クラス登録
	RegisterClass(&wc);
	DWORD window_style = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);
	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&window_rect, window_style, FALSE);
	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);
	int window_x = max((desktop_width - window_width) / 2, 0);
	int window_y = max((desktop_height - window_height) / 2, 0);
	g_hWnd = CreateWindow
	(
		CLASS_NAME,
		WINDOW_CAPTION,
		window_style,
		window_x,
		window_y,
		window_width,
		window_height,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (g_hWnd == NULL)
	{
		return -1;
	}

	ShowWindow(g_hWnd, nCmdShow);

	if (!Initialize(hInstance))
	{
		return -1;
	}

	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
			Draw();
		}
	}

	Finalize();

	return (int)msg.wParam;
}

// ウィンドウプロシージャ(コールバック関数)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
		{
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// ゲームの初期化関数
bool Initialize(HINSTANCE hInstance)
{
	if (!MyDirect3D_Initialize(g_hWnd))
	{
		return false;
	}

	if (Texture_Load() > 0)
	{
		MessageBox(g_hWnd, "いくつか読み込めなかったテクスチャファイルがあります", "エラー", MB_OK);
	}

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return false;
	}

	InitDebugProc();

	InitInput(hInstance, g_hWnd);

	ZeroMemory(&gLight, sizeof(D3DLIGHT9));
	gLight.Type = D3DLIGHT_DIRECTIONAL;
	gLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	gLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 vecDir = D3DXVECTOR3(50.0f, -100.0f, 20.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);
	gLight.Direction = vecDir;
	gLight.Range = 1000.0f;
	pDevice->SetLight(0, &gLight);
	pDevice->LightEnable(0, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// シーン
	cScene::Init(SCENE_GAME);

	switch (cScene::object->currentScene)
	{
	case SCENE_TITLE:
		cTitle::Init();
		break;
	case SCENE_SELECT_NUMBER_OF_PLAYER:
		cSelectPlayer::Init();
		break;
	case SCENE_SELECT_CHARACTER:
		cSelectCharacter::Init();
		break;
	case SCENE_SELECT_DIFFICULTY:
		cSelectDifficulty::Init();
		break;
	case SCENE_SELECT_STAGE:
		cSelectStage::Init();
		break;
	// ゲーム
	case SCENE_GAME:
		cGame::Init();
		break;
	case STAGE_ONE:
		cStage1::Init();
		break;
	case STAGE_TWO:
		cStage2::Init();
		break;
	case SCENE_GAMEOVER:
		cGameover::Init();
		break;
	case SCENE_STAGECLEAR:
		cGameclear::Init();
		break;
	case SCENE_RETURN:
		break;

	default: break;
	}

	return true;
}
// 終了
void Finalize(void)
{
	// シーン
	switch (cScene::object->currentScene)
	{
	case SCENE_TITLE:
		cTitle::Uninit();
		break;
	case SCENE_SELECT_NUMBER_OF_PLAYER:
		cSelectPlayer::Uninit();
		break;
	case SCENE_SELECT_CHARACTER:
		cSelectCharacter::Uninit();
		break;
	case SCENE_SELECT_DIFFICULTY:
		cSelectDifficulty::Uninit();
		break;
	case SCENE_SELECT_STAGE:
		cSelectStage::Uninit();
		break;
	// ゲーム
	case SCENE_GAME:
		cGame::Uninit();
		break;
	case STAGE_ONE:
		cStage1::Uninit();
		break;
	case STAGE_TWO:
		cStage2::Uninit();
		break;
	case SCENE_GAMEOVER:
		cGameover::Uninit();
		break;
	case SCENE_STAGECLEAR:
		cGameclear::Uninit();
		break;
	case SCENE_RETURN:
		break;

	default: break;
	}

	cScene::Uninit();

	// デバッグ
	UninitDebugProc();
	// キーボード
	UninitInput();
	// システム解放
	Texture_Release();
	MyDirect3D_Finalize();
}
// 更新
void Update(void)
{
	// キーボード
	UpdateInput();
	// デバッグ
	UpdateDebugProc();

	switch (cScene::object->currentScene)
	{
	case SCENE_TITLE:
		cTitle::Update();
		break;
	case SCENE_SELECT_NUMBER_OF_PLAYER:
		cSelectPlayer::Update();
		break;
	case SCENE_SELECT_CHARACTER:
		cSelectCharacter::Update();
		break;
	case SCENE_SELECT_DIFFICULTY:
		cSelectDifficulty::Update();
		break;
	case SCENE_SELECT_STAGE:
		cSelectStage::Update();
		break;
	// ゲーム
	case SCENE_GAME:
		cGame::Update();
		break;
	case STAGE_ONE:
		cStage1::Update();
		break;
	case STAGE_TWO:
		cStage2::Update();
		break;
	case SCENE_GAMEOVER:
		cGameover::Update();
		break;
	case SCENE_STAGECLEAR:
		cGameclear::Update();
		break;
	case SCENE_RETURN:
		break;

	default: break;
	}

	// シーン
	cScene::Update();
}

// 描画
void Draw(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();
	if (!pD3DDevice)
	{
		return;
	}

	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	pD3DDevice->BeginScene();

	// 設定
	// スプライト
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	// アルファブレンドの設定
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	switch (cScene::object->currentScene)
	{
	case SCENE_TITLE:
		cTitle::Draw();
		break;
	case SCENE_SELECT_NUMBER_OF_PLAYER:
		cSelectPlayer::Draw();
		break;
	case SCENE_SELECT_CHARACTER:
		cSelectCharacter::Draw();
		break;
	case SCENE_SELECT_DIFFICULTY:
		cSelectDifficulty::Draw();
		break;
	case SCENE_SELECT_STAGE:
		cSelectStage::Draw();
		break;
	case SCENE_GAME:
		cGame::Draw();
		break;
	case STAGE_ONE:
		cStage1::Draw();
		break;
	case STAGE_TWO:
		cStage2::Draw();
		break;
	case SCENE_GAMEOVER:
		cGameover::Draw();
		break;
	case SCENE_STAGECLEAR:
		cGameclear::Draw();
		break;
	case SCENE_RETURN:
		break;

	default: break;
	}

	// シーン
	cScene::Draw();

	// デバッグ
	DrawDebugProc();

	pD3DDevice->EndScene();
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
}