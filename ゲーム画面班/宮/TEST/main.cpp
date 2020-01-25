
// ���C��
#include"main.h"
#include"common.h"
#include<Windows.h>
#include"direct3d.h"
// ��
#include"texture.h"
#include"sprite.h"
#include"vertex.h"
#include"camera.h"
#include"input.h"
#include<dinput.h>
// �V�[��
#include"scene.h"
#include"Title.h"
#include"Game.h"

// �V�X�e��
static HWND g_hWnd;
D3DLIGHT9 gLight;

// ���C���֐�
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

	// �N���X�o�^
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

// �E�B���h�E�v���V�[�W��(�R�[���o�b�N�֐�)
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
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
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

// �Q�[���̏������֐�
bool Initialize(HINSTANCE hInstance)
{
	if (!MyDirect3D_Initialize(g_hWnd))
	{
		return false;
	}

	if (Texture_Load() > 0)
	{
		MessageBox(g_hWnd, "�������ǂݍ��߂Ȃ������e�N�X�`���t�@�C��������܂�", "�G���[", MB_OK);
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

	// �V�[��
	cScene::Init(SCENE_GAME);

	switch (cScene::object->currentScene)
	{
	case SCENE_TITLE:
		cTitle::Init();
		break;
	case SCENE_GAME:
		cGame::Init();
		break;

	default: break;
	}

	return true;
}
// �I��
void Finalize(void)
{
	// �V�[��
	switch (cScene::object->currentScene)
	{
	case SCENE_TITLE:
		cTitle::Uninit();
		break;
	case SCENE_GAME:
		cGame::Uninit();
		break;

	default: break;
	}

	cScene::Uninit();

	// �L�[�{�[�h
	UninitInput();
	// �V�X�e�����
	Texture_Release();
	MyDirect3D_Finalize();
}
// �X�V
void Update(void)
{
	// �L�[�{�[�h
	UpdateInput();

	// �V�[��
	cScene::Update();
}

// �`��
void Draw(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();
	if (!pD3DDevice)
	{
		return;
	}

	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	pD3DDevice->BeginScene();

	// �ݒ�
	// �X�v���C�g
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	// ���u�����h
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �V�[��
	cScene::Draw();

	pD3DDevice->EndScene();
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
}