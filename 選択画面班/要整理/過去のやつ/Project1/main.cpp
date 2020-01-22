
// 基礎
#include<Windows.h>
#include"common.h"
#include"directx.h"
// システム
#include"texture.h"
#include"sprite.h"
#include"input.h"
#include"fade.h"
// オブジェクト
#include"scene.h"
#include"camera.h"
#include"object.h"
#include"fog.h"

// 要整理
// 河野
#include"Caracterselect.h"
// 李
#include"peaple.h"
#include"diffical.h"

//===============================================
//ここを追加　3D用追加コード

// 頂点
typedef struct MyStruct
{
	D3DXVECTOR3	vtx;
	D3DXVECTOR3	nor;
	D3DCOLOR	diffuse;
	D3DXVECTOR2	tex;
}VERTEX_3D;
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// カメラ
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

// 頂点バッファ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuff;
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuff_Grid;

//ここまで3D用追加コード
//===============================================

// プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static bool Initialize(void);	// 戻り値:初期化に失敗したときfalse
static void Update(void);
static void Draw(void);
static void Finalize(void);

// 要整理
// グローバル変数
static HWND		g_hWnd;             // ウィンドウハンドル
static float	g_Rotation = 0.0f; // スプライト回転角度 
static float	g_Move = 0.0f;
static int		k = 0;

static D3DXVECTOR3 Grid_pos = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
static float delta_size = 1.5;
static float size = 90;
static int Grid_i = 0;
D3DXMATRIX  g_gridWorld;
// オブジェクト
int obj_count = 0;
Obj *obj_All[100];

Obj Chara;
Obj Fire;

Obj BG;
Obj Ground;
Obj Grand;

Fog FG;

// メイン関数
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 使用しない一時変数を明示
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // ウィンドウクラス構造体の設定
    WNDCLASS wc			= {};
    wc.lpfnWndProc		= WndProc;							// ウィンドウプロシージャの指定
    wc.lpszClassName	= CLASS_NAME;						// クラス名の設定
    wc.hInstance		= hInstance;						// インスタンスハンドルの指定
    wc.hCursor			= LoadCursor(NULL, IDC_ARROW);		// マウスカーソルを指定
    wc.hbrBackground	= (HBRUSH)(COLOR_BACKGROUND + 1);	// ウインドウのクライアント領域の背景色を設定

    // クラス登録
    RegisterClass(&wc);

    // ウィンドウスタイル
    DWORD window_style = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);

    // 基本矩形座標
	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    // 指定したクライアント領域を確保するために新たな矩形座標を計算
    AdjustWindowRect(&window_rect, window_style, FALSE);
    // 新たなWindowの矩形座標から幅と高さを算出
    int window_width	= window_rect.right - window_rect.left;
    int window_height	= window_rect.bottom - window_rect.top;
    // プライマリモニターの画面解像度取得
    int desktop_width	= GetSystemMetrics(SM_CXSCREEN);
    int desktop_height	= GetSystemMetrics(SM_CYSCREEN);
    // デスクトップの真ん中にウィンドウが生成されるように座標を計算
    // ※ただし万が一、デスクトップよりウィンドウが大きい場合は左上に表示
    int window_x = max((desktop_width - window_width)   / 2, 0);
    int window_y = max((desktop_height - window_height) / 2, 0);

    // ウィンドウの生成
    g_hWnd = CreateWindow
	(
        CLASS_NAME,     // ウィンドウクラス
        WINDOW_CAPTION, // ウィンドウテキスト
        window_style,   // ウィンドウスタイル
        window_x,       // ウィンドウ座標x
        window_y,       // ウィンドウ座標y
        window_width,   // ウィンドウの幅
        window_height,  // ウィンドウの高さ
        NULL,           // 親ウィンドウハンドル
        NULL,           // メニューハンドル
        hInstance,      // インスタンスハンドル
        NULL            // 追加のアプリケーションデータ
    );

    if( g_hWnd == NULL )
	{
        // ウィンドウハンドルが何らかの理由で生成出来なかった
        return -1;
    }

    // 指定のウィンドウハンドルのウィンドウを指定の方法で表示
    ShowWindow(g_hWnd, nCmdShow);

	// ゲームの初期化(Direct3Dの初期化)
	if( !Initialize() )
	{
        // ゲームの初期化に失敗した
		return -1;
	}
	Keyboard_Initialize(hInstance, g_hWnd);

    // Windowsゲーム用メインループ
    MSG msg = {};	// msg.message == WM_NULL
    while( WM_QUIT != msg.message ) {

        if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
		{
            // メッセージがある場合はメッセージ処理を優先
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
		{
			Update();
			Draw();
        }
    }

	// ゲームの終了処理(Direct3Dの終了処理)
	Finalize();

    return (int)msg.wParam;
}
// ウィンドウプロシージャ(コールバック関数)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch( uMsg ) {
        case WM_KEYDOWN:
            if( wParam == VK_ESCAPE ) {
                SendMessage(hWnd, WM_CLOSE, 0, 0); // WM_CLOSEメッセージの送信
            }
            break;

        case WM_CLOSE:
            if( MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK ) {
                DestroyWindow(hWnd); // 指定のウィンドウにWM_DESTROYメッセージを送る
            }
            return 0; // DefWindowProc関数にメッセージを流さず終了することによって何もなかったことにする

        case WM_DESTROY: // ウィンドウの破棄メッセージ
            PostQuitMessage(0); // WM_QUITメッセージの送信
            return 0;
    };

    // 通常メッセージ処理はこの関数に任せる
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// ゲームの初期化関数
bool Initialize(void)
{
	// Direct3Dラッパーモジュールの初期化
	if (!MyDirect3D_Initialize(g_hWnd))
	{
		return false;
	}

	// テクスチャの読み込み
	if (Texture_Load() > 0)
	{
		MessageBox(g_hWnd, "いくつか読み込めなかったテクスチャファイルがあります", "エラー", MB_OK);
	}

	// 要整理
	//================================================================
	//ここを追加　3Dポリゴン用頂点の準備

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

	//ここまで　3Dポリゴン用頂点の準備
	//================================================================

	// 要整理
	// SCENE
	cScene::Initialize_Scene();
	CaracterselectInitialize();

    return true;
}

// ゲームの更新関数
void Update(void)
{
	Keyboard_Update();

	// 要整理
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
		// 河野
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

// ゲームの描画関数
void Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
    if( !pDevice ) return;
     
    // 画面のクリア
    pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 128, 0, 255), 1.0f, 0);

	// 描画バッチ命令の開始
	pDevice->BeginScene();

	//==============================================
	//ここを追加　テスト用カメラ情報を準備

	pDevice->SetTransform(D3DTS_VIEW, &GetCamera_mtx());

	//==============================================
	// ここを追加　テスト用プロジェクション行列の作成

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

	// 描画バッチ命令の終了
	pDevice->EndScene();

    // バックバッファをフリップ（タイミングはD3DPRESENT_PARAMETERSの設定による）
    pDevice->Present(NULL, NULL, NULL, NULL);
}

// ゲームの終了処理
void Finalize(void)
{
	// キー入力の解放
	Keyboard_Finalize();
    // テクスチャの解放
    Texture_Release();
    // Direct3Dラッパーモジュールの終了処理
    MyDirect3D_Finalize();
}
