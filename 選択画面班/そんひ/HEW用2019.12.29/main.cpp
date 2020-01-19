
// ����
// Sprite_Draw���傫���ύX����

// �V�X�e��
#include<Windows.h>	// WindowsMain�̏��̂�
#include"directx.h"	// DirectX�̋@�\�����鏊�ɓ����
// �`��
#include"texture.h"
#include"sprite.h"
#include"debugproc.h"
#include"fade.h"
// �L�[����
#include"input.h"
#include<dinput.h>
// ��v
#include"common.h"
#include"main.h"
#include"scene.h"
// �v�f
#include"vertex.h"	// ���_�Ɋւ�����
#include"camera.h"	// �J�����A�r���[�s��A�v���W�F�N�V�����s��Ɋւ�����
#include"grid.h"

// �V�[��
static cFade* gcFade = GetFade();

// �V�X�e��
static HWND g_hWnd;             // �E�B���h�E�n���h��
// ���C�g
D3DLIGHT9 gLight;//���C�g�\����


// ���C���֐�
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �g�p���Ȃ��ꎞ�ϐ��𖾎�
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// �E�B���h�E�N���X�\���̂̐ݒ�
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;                          // �E�B���h�E�v���V�[�W���̎w��
	wc.lpszClassName = CLASS_NAME;                     // �N���X���̐ݒ�
	wc.hInstance = hInstance;                          // �C���X�^���X�n���h���̎w��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);          // �}�E�X�J�[�\�����w��
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1); // �E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�

	// �N���X�o�^
	RegisterClass(&wc);

	// �E�B���h�E�X�^�C��
	DWORD window_style = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);

	// ��{��`���W
	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɐV���ȋ�`���W���v�Z
	AdjustWindowRect(&window_rect, window_style, FALSE);

	// �V����Window�̋�`���W���畝�ƍ������Z�o
	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	// �v���C�}�����j�^�[�̉�ʉ𑜓x�擾
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	// �f�X�N�g�b�v�̐^�񒆂ɃE�B���h�E�����������悤�ɍ��W���v�Z
	// ��������������A�f�X�N�g�b�v���E�B���h�E���傫���ꍇ�͍���ɕ\��
	int window_x = max((desktop_width - window_width) / 2, 0);
	int window_y = max((desktop_height - window_height) / 2, 0);

	// �E�B���h�E�̐���
	g_hWnd = CreateWindow
	(
		CLASS_NAME,     // �E�B���h�E�N���X
		WINDOW_CAPTION, // �E�B���h�E�e�L�X�g
		window_style,   // �E�B���h�E�X�^�C��
		window_x,       // �E�B���h�E���Wx
		window_y,       // �E�B���h�E���Wy
		window_width,   // �E�B���h�E�̕�
		window_height,  // �E�B���h�E�̍���
		NULL,           // �e�E�B���h�E�n���h��
		NULL,           // ���j���[�n���h��
		hInstance,      // �C���X�^���X�n���h��
		NULL            // �ǉ��̃A�v���P�[�V�����f�[�^
	);

	if (g_hWnd == NULL)
		return -1;	// �E�B���h�E�n���h�������炩�̗��R�Ő����o���Ȃ�����

	// �w��̃E�B���h�E�n���h���̃E�B���h�E���w��̕��@�ŕ\��
	ShowWindow(g_hWnd, nCmdShow);

	// �Q�[���̏�����(Direct3D�̏�����)
	if (!Initialize(hInstance))
	{
		return -1;
	}

	// Windows�Q�[���p���C�����[�v
	MSG msg = {}; // msg.message == WM_NULL
	while (WM_QUIT != msg.message) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// ���b�Z�[�W������ꍇ�̓��b�Z�[�W������D��
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// �X�V
			Update();
			// �`��
			Draw();
		}
	}
	// �Q�[���̏I������(Direct3D�̏I������)
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
			SendMessage(hWnd, WM_CLOSE, 0, 0); // WM_CLOSE���b�Z�[�W�̑��M
		}
		break;
	case WM_CLOSE:
		if (MessageBox
				(
				hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F",
				MB_OKCANCEL | MB_DEFBUTTON2
				)
			== IDOK)
		{
			DestroyWindow(hWnd);				// �w��̃E�B���h�E��WM_DESTROY���b�Z�[�W�𑗂�
		}
		return 0;
		/* DefWindowProc�֐��Ƀ��b�Z�[�W�𗬂����I�����邱�Ƃɂ���ĉ����Ȃ��������Ƃɂ��� */
	case WM_DESTROY:
		PostQuitMessage(0);						// WM_QUIT���b�Z�[�W�̑��M
		return 0;
	};

	// �ʏ탁�b�Z�[�W�����͂��̊֐��ɔC����
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// �Q�[���̏������֐�
bool Initialize(HINSTANCE hInstance)
{

	// Direct3D���b�p�[���W���[���̏�����
	if (!MyDirect3D_Initialize(g_hWnd)) return false;

	// �e�N�X�`���̓ǂݍ���
	if (Texture_Load() > 0)
		MessageBox(g_hWnd, "�������ǂݍ��߂Ȃ������e�N�X�`���t�@�C��������܂�", "�G���[", MB_OK);

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return false;

	// �V�X�e��������
	// �f�o�b�N�`��
	InitDebugProc();
	// �L�[�{�[�h������
	InitInput(hInstance, g_hWnd);
	//���C�g������
	ZeroMemory(&gLight, sizeof(D3DLIGHT9));						//�\���̂��[���N���A(�K�{)
	gLight.Type = D3DLIGHT_DIRECTIONAL;							//���C�g�̎��
	gLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//���̐FRGBA(0.0f�`1.0f)
	gLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//�����̐F
	D3DXVECTOR3 vecDir = D3DXVECTOR3(50.0f, -100.0f, 20.0f);	//���̍��������x�N�g��
	D3DXVec3Normalize(&vecDir, &vecDir);
	gLight.Direction = vecDir;									//���K�����ăZ�b�g
	gLight.Range = 1000.0f;
	pDevice->SetLight(0, &gLight);	//0�ԃ��C�g�փf�[�^���Z�b�g
	pDevice->LightEnable(0, TRUE);	//0�ԃ��C�g��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �e�V�[���̏�����
	gcFade->Init_Fade();

	return true;

}

// �Q�[���̍X�V�֐�
void Update(void)
{

	//�L�[�{�[�h�̍X�V
	UpdateInput();

	// �e�V�[���̍X�V
	switch (gcFade->currentScene)
	{
	case TITLE:
		Update_TITLE();
		break;
	case NUMBER_OF_PEOPLE:
		Update_NUMBER_OF_PEOPLE();
		break;
	case CHARACTER:
		Update_CHARACTER();
		break;
	case NAME:
		Update_NAME();
		break;
	case DIFFICULTY:
		Update_DIFFICULTY();
		break;
	case STAGE:
		Update_STAGE();
		break;
	case GAME:
		Update_GAME();
		break;
	case GAMEOVER:
		Update_GAMEOVER();
		break;
	case AREARANKING:
		Update_AREARANKING();
		break;
	case STAGECLEAR:
		Update_STAGECLEAR();
		break;
	case STAGERANKING:
		Update_STAGERANKING();
		break;
	case SCORETABLE:
		Update_SCORETABLE();
		break;
	case RETURN:
		Update_RETURN();
		break;
	}

	// �t�F�[�h�̍X�V
	gcFade->Update_Fade();

}
void Draw(void)
{

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	// ��ʂ̃N���A
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(123, 104, 238, 255), 1.0f, 0);
	/*pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);*/
	// �`��o�b�`���߂̊J�n
	pDevice->BeginScene();

	// �e�V�[���̕`��
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	switch (gcFade->currentScene)
	{
	case TITLE:
		Draw_TITLE();
		break;
	case NUMBER_OF_PEOPLE:
		Draw_NUMBER_OF_PEOPLE();
		break;
	case CHARACTER:
		Draw_CHARACTER();
		break;
	case NAME:
		Draw_NAME();
		break;
	case DIFFICULTY:
		Draw_DIFFICULTY();
		break;
	case STAGE:
		Draw_STAGE();
		break;
	case GAME:
		Draw_GAME();
		break;
	case GAMEOVER:
		Draw_GAMEOVER();
		break;
	case AREARANKING:
		Draw_AREARANKING();
		break;
	case STAGECLEAR:
		Draw_STAGECLEAR();
		break;
	case STAGERANKING:
		Draw_STAGERANKING();
		break;
	case SCORETABLE:
		Draw_SCORETABLE();
		break;
	case RETURN:
		Draw_RETURN();
		break;
	}

	// �t�F�[�h�̕`��
	gcFade->Draw_Fade();
	// �f�o�b�O�̕`��
	DrawDebugProc();

	// �`��o�b�`���߂̏I��
	pDevice->EndScene();
	// �o�b�N�o�b�t�@���t���b�v�i�^�C�~���O��D3DPRESENT_PARAMETERS�̐ݒ�ɂ��j
	pDevice->Present(NULL, NULL, NULL, NULL);

}

// �Q�[���̏I������
void Finalize(void)
{

	// �e�V�[���̉��

	// �V�X�e�����
	UninitInput();	// �L�[�{�[�h�I��
	UninitDebugProc();		// �f�o�b�O�`��I��
	Texture_Release();		// �e�N�X�`���̉��
	MyDirect3D_Finalize();	// Direct3D���b�p�[���W���[���̏I��

}