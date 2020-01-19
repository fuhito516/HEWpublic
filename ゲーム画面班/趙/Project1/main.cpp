
// ��b
#include<Windows.h>
#include"common.h"
#include"directx.h"
// �V�X�e��
#include"texture.h"
#include"sprite.h"
#include"input.h"
#include"fade.h"
// �I�u�W�F�N�g
#include"scene.h"
#include"camera.h"
#include"object.h"
#include"fog.h"

// �v����
// �͖�
#include"Caracterselect.h"
// ��
#include"peaple.h"
#include"diffical.h"

//===============================================
//������ǉ��@3D�p�ǉ��R�[�h

// ���_
typedef struct MyStruct
{
	D3DXVECTOR3	vtx;
	D3DXVECTOR3	nor;
	D3DCOLOR	diffuse;
	D3DXVECTOR2	tex;
}VERTEX_3D;
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// �J����
#define VIEW_ANGLE    (D3DXToRadian(45.0f))
#define VIEW_ASPECT   ((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT)
#define VIEW_NEAR_Z   (1.0f)
#define VIEW_FAR_Z    (1000.0f)

D3DXVECTOR3 g_posCameraEye;
D3DXVECTOR3 g_posCameraAt;
D3DXVECTOR3 g_vecCameraUp;

D3DXMATRIX g_mtxView;
D3DXMATRIX g_mtxProjection;

// ?
D3DXVECTOR3 g_pos_1, g_pos_2, g_pos_3;
D3DXVECTOR3 g_rot_1, g_rot_2;
D3DXVECTOR3 g_scl;
D3DXMATRIX  g_mtxWorld[3];

// ���_�o�b�t�@
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuff;
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuff_Grid;

//�����܂�3D�p�ǉ��R�[�h
//===============================================

// �v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static bool Initialize(void);	// �߂�l:�������Ɏ��s�����Ƃ�false
static void Update(void);
static void Draw(void);
static void Finalize(void);

// �v����
// �O���[�o���ϐ�
static HWND		g_hWnd;             // �E�B���h�E�n���h��
static float	g_Rotation = 0.0f; // �X�v���C�g��]�p�x 
static float	g_Move = 0.0f;
static int		k = 0;

static D3DXVECTOR3 Grid_pos = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
static float delta_size = 1.5;
static float size = 90;
static int Grid_i = 0;
D3DXMATRIX  g_gridWorld;
// �I�u�W�F�N�g
int obj_count = 0;
Obj *obj_All[100];

Obj Chara;
Obj Fire;

Obj BG;
Obj Ground;
Obj Grand;

Fog FG;

// ���C���֐�
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // �g�p���Ȃ��ꎞ�ϐ��𖾎�
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // �E�B���h�E�N���X�\���̂̐ݒ�
    WNDCLASS wc			= {};
    wc.lpfnWndProc		= WndProc;							// �E�B���h�E�v���V�[�W���̎w��
    wc.lpszClassName	= CLASS_NAME;						// �N���X���̐ݒ�
    wc.hInstance		= hInstance;						// �C���X�^���X�n���h���̎w��
    wc.hCursor			= LoadCursor(NULL, IDC_ARROW);		// �}�E�X�J�[�\�����w��
    wc.hbrBackground	= (HBRUSH)(COLOR_BACKGROUND + 1);	// �E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�

    // �N���X�o�^
    RegisterClass(&wc);

    // �E�B���h�E�X�^�C��
    DWORD window_style = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);

    // ��{��`���W
	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    // �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɐV���ȋ�`���W���v�Z
    AdjustWindowRect(&window_rect, window_style, FALSE);
    // �V����Window�̋�`���W���畝�ƍ������Z�o
    int window_width	= window_rect.right - window_rect.left;
    int window_height	= window_rect.bottom - window_rect.top;
    // �v���C�}�����j�^�[�̉�ʉ𑜓x�擾
    int desktop_width	= GetSystemMetrics(SM_CXSCREEN);
    int desktop_height	= GetSystemMetrics(SM_CYSCREEN);
    // �f�X�N�g�b�v�̐^�񒆂ɃE�B���h�E�����������悤�ɍ��W���v�Z
    // ��������������A�f�X�N�g�b�v���E�B���h�E���傫���ꍇ�͍���ɕ\��
    int window_x = max((desktop_width - window_width)   / 2, 0);
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

    if( g_hWnd == NULL )
	{
        // �E�B���h�E�n���h�������炩�̗��R�Ő����o���Ȃ�����
        return -1;
    }

    // �w��̃E�B���h�E�n���h���̃E�B���h�E���w��̕��@�ŕ\��
    ShowWindow(g_hWnd, nCmdShow);

	// �Q�[���̏�����(Direct3D�̏�����)
	if( !Initialize() )
	{
        // �Q�[���̏������Ɏ��s����
		return -1;
	}
	Keyboard_Initialize(hInstance, g_hWnd);

    // Windows�Q�[���p���C�����[�v
    MSG msg = {};	// msg.message == WM_NULL
    while( WM_QUIT != msg.message ) {

        if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
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
    switch( uMsg ) {
        case WM_KEYDOWN:
            if( wParam == VK_ESCAPE ) {
                SendMessage(hWnd, WM_CLOSE, 0, 0); // WM_CLOSE���b�Z�[�W�̑��M
            }
            break;

        case WM_CLOSE:
            if( MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK ) {
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
bool Initialize(void)
{
	// Direct3D���b�p�[���W���[���̏�����
	if (!MyDirect3D_Initialize(g_hWnd))
	{
		return false;
	}

	// �e�N�X�`���̓ǂݍ���
	if (Texture_Load() > 0)
	{
		MessageBox(g_hWnd, "�������ǂݍ��߂Ȃ������e�N�X�`���t�@�C��������܂�", "�G���[", MB_OK);
	}

	// �v����
	//================================================================
	//������ǉ��@3D�|���S���p���_�̏���

	LPDIRECT3DDEVICE9	pDevice = MyDirect3D_GetDevice();
	LPDIRECT3DTEXTURE9	g_p;

	//----------------------------------------------------------------------------------------------
	Ground.Init(pDevice, 480, 100, 1);
	Ground.Move(0, -45, 250);
	D3DXCreateTextureFromFile(pDevice, "asset/texture/Ground.png", &g_p);
	Ground.setT(g_p);

	obj_All[obj_count] = &Ground;
	obj_count += 1;

	//----------------------------------------------------------------------------------------------
	BG.Init(pDevice, 480, 125, 1);
	BG.Move(0, 60, 200);
	D3DXCreateTextureFromFile(pDevice, "asset/texture/BG_Beta1.jpg", &g_p);
	BG.setT(g_p);

	obj_All[obj_count] = &BG;
	obj_count += 1;

	//----------------------------------------------------------------------------------------------
	Grand.Init(pDevice, 800, 10, 1);
	Grand.Rotation(D3DX_PI / 2, 0, 0);
	D3DXCreateTextureFromFile(pDevice, "asset/texture/Grand_ex.png", &g_p);
	Grand.setT(g_p);

	obj_All[obj_count] = &Grand;
	obj_count += 1;

	//----------------------------------------------------------------------------------------------
	Chara.Init(pDevice, 7, 7, 1);
	Chara.Move(0, 3, 0);
	D3DXCreateTextureFromFile(pDevice, "asset/texture/Chara_Beta.png", &g_p);
	Chara.setT(g_p);
	Chara.setType(1);
	Chara.setGravity(0.98f);

	obj_All[obj_count] = &Chara;
	obj_count += 1;

	////----------------------------------------------------------------------------------------------
	Fire.Init(pDevice, 7, 10, 1);
	Fire.Move(20, 5, 0);
	D3DXCreateTextureFromFile(pDevice, "asset/texture/Fire.png", &g_p);
	Fire.setT(g_p);
	Fire.setType(3);
	Fire.setGravity(0.98f);

	obj_All[obj_count] = &Fire;
	obj_count += 1;

	//----------------------------------------------------------------------------------------------
	FG.Init(pDevice, 800, 200, 1);
	FG.Move(0, 0, -0.5);
	D3DXCreateTextureFromFile(pDevice, "asset/texture/Fog_ex.png", &g_p);
	FG.setT(g_p);

	//----------------------------------------------------------------------------------------------

	InitializeCamera();

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

	//�����܂Ł@3D�|���S���p���_�̏���
	//================================================================

	// �v����
	// SCENE
	cScene::Initialize_Scene();
	CaracterselectInitialize();

    return true;
}

// �Q�[���̍X�V�֐�
void Update(void)
{
	Keyboard_Update();

	// �v����
	switch (cScene::scene)
	{
	case TITLE:
		cScene::Update_TITLE();
		break;
	case PLAYER:
		UpdatePeaple();
		cScene::Update_PLAYER();
		break;
	case CHARACTER:
		// �͖�
		CaracterselectUpdate();
		cScene::Update_CHARACTER();
		break;
	case NAME:
		cScene::Update_NAME();
		break;
	case DIFFICULTY:
		UpdateDiffical();
		cScene::Update_DIFFICULTY();
		break;
	case STAGE:
		cScene::Update_STAGE();
		break;
	case GAME:
		Chara.Update();
		Fire.Update();
		FG.Update();
		UpdateCamera();
		
		cScene::Update_GAME();
		break;
	case GAMEOVER:
		cScene::Update_GAMEOVER();
		break;
	case AREARANKING:
		cScene::Update_AREARANKING();
		break;
	case STAGECLEAR:
		cScene::Update_STAGECLEAR();
		break;
	case STAGERANKING:
		cScene::Update_STAGERANKING();
		break;
	case SCORETABLE:
		cScene::Update_SCORETABLE();
		break;
	case RETURN:
		cScene::Update_RETURN();
		break;
	}

	if (
		!Keyboard_IsPress(DIK_RETURN) && !Keyboard_IsPress(DIK_LEFT) && !Keyboard_IsPress(DIK_RIGHT)
		&& cFade::fadeState == FADESTATE_NONE
		)
	{
		cScene::checkPastPressed = false;
	}

	cFade::UpdateFade();
}

// �Q�[���̕`��֐�
void Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
    if( !pDevice ) return;
     
    // ��ʂ̃N���A
    pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 128, 0, 255), 1.0f, 0);

	// �`��o�b�`���߂̊J�n
	pDevice->BeginScene();

	//==============================================
	//������ǉ��@�e�X�g�p�J������������

	pDevice->SetTransform(D3DTS_VIEW, &GetCamera_mtx());

	//==============================================
	// ������ǉ��@�e�X�g�p�v���W�F�N�V�����s��̍쐬

	D3DXMatrixPerspectiveFovLH
	(
		&g_mtxProjection, 
		VIEW_ANGLE,
		VIEW_ASPECT,
		VIEW_NEAR_Z,
		VIEW_FAR_Z
	);

	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);

	//=============================================================

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	switch (cScene::scene)
	{
	case TITLE:
		cScene::Draw_TITLE();
		break;
	case PLAYER:
		DrawPeaple();
		break;
	case CHARACTER:
		CaracterselectDraw();
		break;
	case NAME:
		cScene::Draw_NAME();
		break;
	case DIFFICULTY:
		DrawDiffical();
		break;
	case STAGE:
		cScene::Draw_STAGE();
		break;
	case GAME:
		BG.Draw();
		Ground.Draw();
		Grand.Draw();
		Chara.Draw();
		Fire.Draw();
		// FOG
		int k_FG;
		k_FG = 0;
		FG.setLC(0);
		for (int i = 0; i < obj_count; i++)
		{
			if ((obj_All[i]->getType() == 3) || (obj_All[i]->getType() == 1))
			{
				FG.setL(k_FG, obj_All[i]->getXY().x, obj_All[i]->getXY().y);
				k_FG += 1;
			}
		}
		FG.setLC(k_FG);
		FG.Draw();
		break;
	case GAMEOVER:
		cScene::Draw_GAMEOVER();
		break;
	case AREARANKING:
		cScene::Draw_AREARANKING();
		break;
	case STAGECLEAR:
		cScene::Draw_STAGECLEAR();
		break;
	case STAGERANKING:
		cScene::Draw_STAGERANKING();
		break;
	case SCORETABLE:
		cScene::Draw_SCORETABLE();
		break;
	case RETURN:
		cScene::Draw_RETURN();
		break;
	}

	cFade::DrawFade();

	// �`��o�b�`���߂̏I��
	pDevice->EndScene();

    // �o�b�N�o�b�t�@���t���b�v�i�^�C�~���O��D3DPRESENT_PARAMETERS�̐ݒ�ɂ��j
    pDevice->Present(NULL, NULL, NULL, NULL);
}

// �Q�[���̏I������
void Finalize(void)
{
	// �L�[���͂̉��
	Keyboard_Finalize();
    // �e�N�X�`���̉��
    Texture_Release();
    // Direct3D���b�p�[���W���[���̏I������
    MyDirect3D_Finalize();
}
