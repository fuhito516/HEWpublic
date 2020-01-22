
// 共通
#include"common.h"
#include"main.h"
// システム
#include<Windows.h>
#include"direct3d.h"
// 描画
#include"texture.h"
#include"sprite.h"
#include"vertex.h"
#include"camera.h"
#include"grid.h"
// キーボード
#include"input.h"
#include<dinput.h>
// 要素
// 背景
#include"background.h"
#include"ground.h"
// キャラクター
#include"player.h"
#include"seika.h"
// ギミック
#include"candle.h"
#include"bridge.h"

#include"goal.h"

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

	// カメラ
	cCamera::Init();

	// 要素
	// 背景
	cBackground::Init();
	cGround::Init();
	// キャラクター
	cPlayer::Init();
	cSeika::Init();
	// ギミック
	cBridge::Init();
	cCandle::Init();

	cGoal::Init();

	// 背景生成
	cBackground::SetBackground(TEXTURE_INDEX_BACK1, D3DXVECTOR3(70, 0, 200), D3DXVECTOR3(1200, 300, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK2, D3DXVECTOR3(5, 50, 180), D3DXVECTOR3(20, 20, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK3, D3DXVECTOR3(70, 20, 150), D3DXVECTOR3(600, 150, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK4, D3DXVECTOR3(70, 40, 50), D3DXVECTOR3(600, 150, 1));
	//cBackground::SetBackground(TEXTURE_INDEX_BACK5, D3DXVECTOR3(70, 00, 40), D3DXVECTOR3(20, 20, 1)); // 地面に変更
	cBackground::SetBackground(TEXTURE_INDEX_BACK6, D3DXVECTOR3(70, 00, 30), D3DXVECTOR3(200, 50, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK7, D3DXVECTOR3(70, 40, 20), D3DXVECTOR3(600, 150, 1));
	// 地面生成
	cGround::SetGround(D3DXVECTOR2(-17.5f, 0), D3DXVECTOR2(5.0f, 80.0f));
	cGround::SetGround(D3DXVECTOR2(0, -20.0f), D3DXVECTOR2(30.0f, 40.0f));
	cGround::SetGround(D3DXVECTOR2(30, -22.5f), D3DXVECTOR2(30.0f, 35.0f));
	cGround::SetGround(D3DXVECTOR2(52.5f, -22.5f), D3DXVECTOR2(5.0f, 35.0f));
	cGround::SetGround(D3DXVECTOR2(62.5f, -25.0f), D3DXVECTOR2(5.0f, 30.0f));
	cGround::SetGround(D3DXVECTOR2(85.0f, -27.5f), D3DXVECTOR2(30.0f, 25.0f));
	cGround::SetGround(D3DXVECTOR2(130.0f, -27.5f), D3DXVECTOR2(20.0f, 25.0f)); // 全長x=140,y=80
	// ロウソク生成
	cCandle::SetCandle(D3DXVECTOR2(30.0f, 3.0f));
	// 橋生成
	cBridge::SetBridge(D3DXVECTOR2(95.0f, -2.0f), D3DXVECTOR2(110.0f, -16.0f), D3DXVECTOR2(20.0f, 2.0f));

	cGoal::SetGoal(D3DXVECTOR2(145, -10));

	return true;
}

// ゲームの終了処理
void Finalize(void)
{
	cGoal::Uninit();

	// 要素
	// ギミック
	cBridge::Uninit();
	cCandle::Uninit();
	// キャラクター
	cPlayer::Uninit();
	cSeika::Uninit();
	// 背景
	cBackground::Uninit();
	cGround::Uninit();

	// カメラ
	cCamera::Uninit();

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

	// カメラ
	cCamera::Update();

	// 要素
	// 背景
	cGround::Update();
	// キャラクター
	cPlayer::Update();
	cSeika::Update();
	// ギミック
	cBridge::Update();
	cCandle::Update();

	cGoal::Update();
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

	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	// カメラ
	cCamera::SetCamera();

	// 要素
	// 背景
	cBackground::Draw();
	cGround::Draw();
	// ギミック
	cBridge::Draw();
	cCandle::Draw();
	// キャラクター
	cSeika::Draw();
	cPlayer::Draw();

	cGoal::Draw();

	pD3DDevice->EndScene();
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
}