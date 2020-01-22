
// ����
#include"common.h"
#include"main.h"
// �V�X�e��
#include<Windows.h>
#include"direct3d.h"
// �`��
#include"texture.h"
#include"sprite.h"
#include"vertex.h"
#include"camera.h"
#include"grid.h"
// �L�[�{�[�h
#include"input.h"
#include<dinput.h>
// �v�f
// �w�i
#include"background.h"
#include"ground.h"
// �L�����N�^�[
#include"player.h"
#include"seika.h"
// �M�~�b�N
#include"candle.h"
#include"bridge.h"

#include"goal.h"

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

	// �J����
	cCamera::Init();

	// �v�f
	// �w�i
	cBackground::Init();
	cGround::Init();
	// �L�����N�^�[
	cPlayer::Init();
	cSeika::Init();
	// �M�~�b�N
	cBridge::Init();
	cCandle::Init();

	cGoal::Init();

	// �w�i����
	cBackground::SetBackground(TEXTURE_INDEX_BACK1, D3DXVECTOR3(70, 0, 200), D3DXVECTOR3(1200, 300, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK2, D3DXVECTOR3(5, 50, 180), D3DXVECTOR3(20, 20, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK3, D3DXVECTOR3(70, 20, 150), D3DXVECTOR3(600, 150, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK4, D3DXVECTOR3(70, 40, 50), D3DXVECTOR3(600, 150, 1));
	//cBackground::SetBackground(TEXTURE_INDEX_BACK5, D3DXVECTOR3(70, 00, 40), D3DXVECTOR3(20, 20, 1)); // �n�ʂɕύX
	cBackground::SetBackground(TEXTURE_INDEX_BACK6, D3DXVECTOR3(70, 00, 30), D3DXVECTOR3(200, 50, 1));
	cBackground::SetBackground(TEXTURE_INDEX_BACK7, D3DXVECTOR3(70, 40, 20), D3DXVECTOR3(600, 150, 1));
	// �n�ʐ���
	cGround::SetGround(D3DXVECTOR2(-17.5f, 0), D3DXVECTOR2(5.0f, 80.0f));
	cGround::SetGround(D3DXVECTOR2(0, -20.0f), D3DXVECTOR2(30.0f, 40.0f));
	cGround::SetGround(D3DXVECTOR2(30, -22.5f), D3DXVECTOR2(30.0f, 35.0f));
	cGround::SetGround(D3DXVECTOR2(52.5f, -22.5f), D3DXVECTOR2(5.0f, 35.0f));
	cGround::SetGround(D3DXVECTOR2(62.5f, -25.0f), D3DXVECTOR2(5.0f, 30.0f));
	cGround::SetGround(D3DXVECTOR2(85.0f, -27.5f), D3DXVECTOR2(30.0f, 25.0f));
	cGround::SetGround(D3DXVECTOR2(130.0f, -27.5f), D3DXVECTOR2(20.0f, 25.0f)); // �S��x=140,y=80
	// ���E�\�N����
	cCandle::SetCandle(D3DXVECTOR2(30.0f, 3.0f));
	// ������
	cBridge::SetBridge(D3DXVECTOR2(95.0f, -2.0f), D3DXVECTOR2(110.0f, -16.0f), D3DXVECTOR2(20.0f, 2.0f));

	cGoal::SetGoal(D3DXVECTOR2(145, -10));

	return true;
}

// �Q�[���̏I������
void Finalize(void)
{
	cGoal::Uninit();

	// �v�f
	// �M�~�b�N
	cBridge::Uninit();
	cCandle::Uninit();
	// �L�����N�^�[
	cPlayer::Uninit();
	cSeika::Uninit();
	// �w�i
	cBackground::Uninit();
	cGround::Uninit();

	// �J����
	cCamera::Uninit();

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

	// �J����
	cCamera::Update();

	// �v�f
	// �w�i
	cGround::Update();
	// �L�����N�^�[
	cPlayer::Update();
	cSeika::Update();
	// �M�~�b�N
	cBridge::Update();
	cCandle::Update();

	cGoal::Update();
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

	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	// �J����
	cCamera::SetCamera();

	// �v�f
	// �w�i
	cBackground::Draw();
	cGround::Draw();
	// �M�~�b�N
	cBridge::Draw();
	cCandle::Draw();
	// �L�����N�^�[
	cSeika::Draw();
	cPlayer::Draw();

	cGoal::Draw();

	pD3DDevice->EndScene();
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
}