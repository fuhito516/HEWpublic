
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
#include"player.h"
#include"ground.h"
#include"seika.h"
#include"Moveground.h"

// �V�X�e��
static HWND g_hWnd;	// �E�B���h�E�n���h��
// ���C�g
D3DLIGHT9 gLight;
//UpDownField

int change;
float t = 0;
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
		return -1;	// �Q�[���̏������Ɏ��s����

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
			Update();
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
	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0); // WM_CLOSE���b�Z�[�W�̑��M
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd); // �w��̃E�B���h�E��WM_DESTROY���b�Z�[�W�𑗂�
		}
		return 0; // DefWindowProc�֐��Ƀ��b�Z�[�W�𗬂����I�����邱�Ƃɂ���ĉ����Ȃ��������Ƃɂ���

	case WM_DESTROY: // �E�B���h�E�̔j�����b�Z�[�W
		PostQuitMessage(0); // WM_QUIT���b�Z�[�W�̑��M
		return 0;
	};

	// �ʏ탁�b�Z�[�W�����͂��̊֐��ɔC����
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


// �Q�[���̏������֐�
bool Initialize(HINSTANCE hInstance)
{
	t += 4.0f;
	change = 0;
	//if (t <= 1.0) {
	//	change = 1;
	//}
	//if (t >= 5.0) {
	//	change = 0;
	//}
	//if (change == 1) {
	//	t += 0.1;
	//}
	//if (change == 0) {
	//	t -= 0.1;
	//}
	// Direct3D���b�p�[���W���[���̏�����
	if (!MyDirect3D_Initialize(g_hWnd))
		return false;

	// �e�N�X�`���̓ǂݍ���
	if (Texture_Load() > 0)
		MessageBox(g_hWnd, "�������ǂݍ��߂Ȃ������e�N�X�`���t�@�C��������܂�", "�G���[", MB_OK);

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return false;

	// �L�[�{�[�h
	InitInput(hInstance, g_hWnd);

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

	// �J����
	cCamera::Init();
	//cGrid::Init();

	// �v�f
	cPlayer::Init();
	cSeika::Init();
	cGround::Init();
	cVerticalMoveGround::MoveInit();
	cHorizontalMoveGround::MoveInit();

	// �O���E���h�ݒ�(�I�X�X���̓T�C�Y�͕ύX�ł��邪�o�����X���l����ƌŒ�u���b�N����ɗv�f��t�������Ă��������悢)
	cGround::SetGround(D3DXVECTOR2(45, -4.0f), D3DXVECTOR2(100.0f, 2.0f));
	cGround::SetGround(D3DXVECTOR2(30, -0.5f), D3DXVECTOR2(2.0f, 5.0f));
	cGround::SetGround(D3DXVECTOR2(35, -0.5f), D3DXVECTOR2(2.0f, 8.0f));
	cGround::SetGround(D3DXVECTOR2(40, -0.5f), D3DXVECTOR2(2.0f, 5.0f));
	cGround::SetGround(D3DXVECTOR2(40, -0.5f), D3DXVECTOR2(2.0f, 5.0f));

	cVerticalMoveGround::MoveSetGround(D3DXVECTOR2(60, 0.0f), D3DXVECTOR2(20.0f, 2.0f));
	cHorizontalMoveGround::MoveSetGround(D3DXVECTOR2(80, 10.0f), D3DXVECTOR2(10.0f, 2.0f));

	cGround::SetGround(D3DXVECTOR2(75, -0.5f), D3DXVECTOR2(2.0f, 5.0f));//�����[�g
	//�����̊ԂɓG���ꂽ���I�I�I
	cGround::SetGround(D3DXVECTOR2(85, -0.5f), D3DXVECTOR2(2.0f, 7.0f));//�����[�g
	//�����̊ԂɓG���ꂽ���I�I�I
	cGround::SetGround(D3DXVECTOR2(94, -1.0f), D3DXVECTOR2(2.0f, 4.0f));//�����[�g
	//�����̊ԂɓG���ꂽ���I�I�I
	cGround::SetGround(D3DXVECTOR2(105, -8.0f), D3DXVECTOR2(2.0f, 16.0f));//�����[�g

	cGround::SetGround(D3DXVECTOR2(119, -12.0f), D3DXVECTOR2(10.0f, 16.0f));//�����[�g

	cGround::SetGround(D3DXVECTOR2(119, 6.0f), D3DXVECTOR2(10.0f, 6.0f));//�����[�g

	cGround::SetGround(D3DXVECTOR2(129, 6.0f), D3DXVECTOR2(10.0f, 6.0f));//�����[�g
	//-12�̏�ɓG�z�u
	cGround::SetGround(D3DXVECTOR2(129, -12.0f), D3DXVECTOR2(10.0f, 6.0f));//�����[�g


	cGround::SetGround(D3DXVECTOR2(135, -8.0f), D3DXVECTOR2(10.0f, 8.0f));//�����[�g
	cGround::SetGround(D3DXVECTOR2(135, 6.0f), D3DXVECTOR2(10.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(130, 10.0f), D3DXVECTOR2(2.0f, 6.0f));



	//--------------------------------
	//�ニ�[�g�u���b�N
	//--------------------------------
	cGround::SetGround(D3DXVECTOR2(77, 20.0f), D3DXVECTOR2(6.0f, 2.0f));
	cGround::SetGround(D3DXVECTOR2(95, 20.0f), D3DXVECTOR2(6.0f, 2.0f));
	//�����̊ԂɓG
	cGround::SetGround(D3DXVECTOR2(103, 20.0f), D3DXVECTOR2(10.0f, 2.0f));
	//������ӂɃX�R�A�ɉ��Z�������̂�z�u
	cGround::SetGround(D3DXVECTOR2(97, 22.0f), D3DXVECTOR2(2.0f, 4.0f));
	cGround::SetGround(D3DXVECTOR2(109, 22.0f), D3DXVECTOR2(2.0f, 4.0f));//������щz���ĉ��̏�̃u���b�N�ɓ��B
	
	
	cGround::SetGround(D3DXVECTOR2(130, 10.0f), D3DXVECTOR2(2.0f, 6.0f));

	cGround::SetGround(D3DXVECTOR2(139, 6.0f), D3DXVECTOR2(10.0f, 6.0f));

	//----------------------------
	//�S�[���K�i
	//----------------------------
	cGround::SetGround(D3DXVECTOR2(145, -5.0f), D3DXVECTOR2(10.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(155, -3.0f), D3DXVECTOR2(10.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(159, 0.0f), D3DXVECTOR2(2.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(161, 1.0f), D3DXVECTOR2(2.0f, 8.0f));
	cGround::SetGround(D3DXVECTOR2(163, 2.0f), D3DXVECTOR2(2.0f, 10.0f));
	cGround::SetGround(D3DXVECTOR2(165, 3.0f), D3DXVECTOR2(2.0f, 12.0f));
	cGround::SetGround(D3DXVECTOR2(167, 4.0f), D3DXVECTOR2(2.0f, 14.0f));
	cGround::SetGround(D3DXVECTOR2(169, 5.0f), D3DXVECTOR2(2.0f, 16.0f));
	cGround::SetGround(D3DXVECTOR2(172, 6.0f), D3DXVECTOR2(4.0f, 16.0f));//�S�[���̓����ꏊ

	return true;

}

// �X�V
void Update(void)
{
	// �L�[�{�[�h
	UpdateInput();

	// �J����
	cCamera::Update();
	//cGrid::Update();

	// �v�f
	cPlayer::Update();
	cSeika::Update();
	cGround::Update();
	cVerticalMoveGround::MoveUpdate();
	cHorizontalMoveGround::MoveUpdate();
}

// �`��
void Draw(void)
{

	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();
	if (!pD3DDevice) return;

	// ��ʂ̃N���A
	/*pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(123, 104, 238, 255), 1.0f, 0);*/
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	// �`��o�b�`���߂̊J�n
	pD3DDevice->BeginScene();
	Sprite_SetColor(D3DCOLOR_RGBA(0, 255, 255, 255));

	// �J����
	cCamera::SetCamera();
	//cGrid::Draw();

	// �v�f
	cSeika::Draw();
	cPlayer::Draw();
	cGround::Draw();
	cVerticalMoveGround::MoveDraw();
	cHorizontalMoveGround::MoveDraw();
	// �`��o�b�`���߂̏I��
	pD3DDevice->EndScene();
	// �o�b�N�o�b�t�@���t���b�v�i�^�C�~���O��D3DPRESENT_PARAMETERS�̐ݒ�ɂ��j
	pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

// �Q�[���̏I������
void Finalize(void)
{

	// �v�f
	cSeika::Uninit();
	cPlayer::Uninit();
	cGround::Uninit();
	cVerticalMoveGround::MoveUninit();
	cHorizontalMoveGround::MoveUninit();
	// �J����
	//cGrid::Uninit();
	cCamera::Uninit();

	// �L�[�{�[�h
	UninitInput();
	// �V�X�e�����
	Texture_Release();		// �e�N�X�`���̉��
	MyDirect3D_Finalize();	// Direct3D���b�p�[���W���[���̏I��

}