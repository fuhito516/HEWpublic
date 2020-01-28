
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
#include"player.h"
#include"ground.h"
#include"seika.h"
#include"Moveground.h"

// システム
static HWND g_hWnd;	// ウィンドウハンドル
// ライト
D3DLIGHT9 gLight;
//UpDownField

int change;
float t = 0;
// メイン関数
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	// 使用しない一時変数を明示
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// ウィンドウクラス構造体の設定
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;                          // ウィンドウプロシージャの指定
	wc.lpszClassName = CLASS_NAME;                     // クラス名の設定
	wc.hInstance = hInstance;                          // インスタンスハンドルの指定
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);          // マウスカーソルを指定
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1); // ウインドウのクライアント領域の背景色を設定

	// クラス登録
	RegisterClass(&wc);

	// ウィンドウスタイル
	DWORD window_style = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);

	// 基本矩形座標
	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// 指定したクライアント領域を確保するために新たな矩形座標を計算
	AdjustWindowRect(&window_rect, window_style, FALSE);

	// 新たなWindowの矩形座標から幅と高さを算出
	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	// プライマリモニターの画面解像度取得
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	// デスクトップの真ん中にウィンドウが生成されるように座標を計算
	// ※ただし万が一、デスクトップよりウィンドウが大きい場合は左上に表示
	int window_x = max((desktop_width - window_width) / 2, 0);
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

	if (g_hWnd == NULL)
		return -1;	// ウィンドウハンドルが何らかの理由で生成出来なかった

	// 指定のウィンドウハンドルのウィンドウを指定の方法で表示
	ShowWindow(g_hWnd, nCmdShow);

	// ゲームの初期化(Direct3Dの初期化)
	if (!Initialize(hInstance))
		return -1;	// ゲームの初期化に失敗した

	// Windowsゲーム用メインループ
	MSG msg = {}; // msg.message == WM_NULL
	while (WM_QUIT != msg.message) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
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
	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0); // WM_CLOSEメッセージの送信
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
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
	// Direct3Dラッパーモジュールの初期化
	if (!MyDirect3D_Initialize(g_hWnd))
		return false;

	// テクスチャの読み込み
	if (Texture_Load() > 0)
		MessageBox(g_hWnd, "いくつか読み込めなかったテクスチャファイルがあります", "エラー", MB_OK);

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return false;

	// キーボード
	InitInput(hInstance, g_hWnd);

	ZeroMemory(&gLight, sizeof(D3DLIGHT9));						//構造体をゼロクリア(必須)
	gLight.Type = D3DLIGHT_DIRECTIONAL;							//ライトの種類
	gLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//光の色RGBA(0.0f～1.0f)
	gLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//環境光の色
	D3DXVECTOR3 vecDir = D3DXVECTOR3(50.0f, -100.0f, 20.0f);	//光の差す方向ベクトル
	D3DXVec3Normalize(&vecDir, &vecDir);
	gLight.Direction = vecDir;									//正規化してセット
	gLight.Range = 1000.0f;

	pDevice->SetLight(0, &gLight);	//0番ライトへデータをセット
	pDevice->LightEnable(0, TRUE);	//0番ライトを有効化

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// カメラ
	cCamera::Init();
	//cGrid::Init();

	// 要素
	cPlayer::Init();
	cSeika::Init();
	cGround::Init();
	cVerticalMoveGround::MoveInit();
	cHorizontalMoveGround::MoveInit();

	// グラウンド設定(オススメはサイズは変更できるがバランスを考えると固定ブロックを基に要素を付け加えていく方がよい)
	cGround::SetGround(D3DXVECTOR2(45, -4.0f), D3DXVECTOR2(100.0f, 2.0f));
	cGround::SetGround(D3DXVECTOR2(30, -0.5f), D3DXVECTOR2(2.0f, 5.0f));
	cGround::SetGround(D3DXVECTOR2(35, -0.5f), D3DXVECTOR2(2.0f, 8.0f));
	cGround::SetGround(D3DXVECTOR2(40, -0.5f), D3DXVECTOR2(2.0f, 5.0f));
	cGround::SetGround(D3DXVECTOR2(40, -0.5f), D3DXVECTOR2(2.0f, 5.0f));

	cVerticalMoveGround::MoveSetGround(D3DXVECTOR2(60, 0.0f), D3DXVECTOR2(20.0f, 2.0f));
	cHorizontalMoveGround::MoveSetGround(D3DXVECTOR2(80, 10.0f), D3DXVECTOR2(10.0f, 2.0f));

	cGround::SetGround(D3DXVECTOR2(75, -0.5f), D3DXVECTOR2(2.0f, 5.0f));//下ルート
	//ここの間に敵入れたい！！！
	cGround::SetGround(D3DXVECTOR2(85, -0.5f), D3DXVECTOR2(2.0f, 7.0f));//下ルート
	//ここの間に敵入れたい！！！
	cGround::SetGround(D3DXVECTOR2(94, -1.0f), D3DXVECTOR2(2.0f, 4.0f));//下ルート
	//ここの間に敵入れたい！！！
	cGround::SetGround(D3DXVECTOR2(105, -8.0f), D3DXVECTOR2(2.0f, 16.0f));//下ルート

	cGround::SetGround(D3DXVECTOR2(119, -12.0f), D3DXVECTOR2(10.0f, 16.0f));//下ルート

	cGround::SetGround(D3DXVECTOR2(119, 6.0f), D3DXVECTOR2(10.0f, 6.0f));//下ルート

	cGround::SetGround(D3DXVECTOR2(129, 6.0f), D3DXVECTOR2(10.0f, 6.0f));//下ルート
	//-12の上に敵配置
	cGround::SetGround(D3DXVECTOR2(129, -12.0f), D3DXVECTOR2(10.0f, 6.0f));//下ルート


	cGround::SetGround(D3DXVECTOR2(135, -8.0f), D3DXVECTOR2(10.0f, 8.0f));//下ルート
	cGround::SetGround(D3DXVECTOR2(135, 6.0f), D3DXVECTOR2(10.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(130, 10.0f), D3DXVECTOR2(2.0f, 6.0f));



	//--------------------------------
	//上ルートブロック
	//--------------------------------
	cGround::SetGround(D3DXVECTOR2(77, 20.0f), D3DXVECTOR2(6.0f, 2.0f));
	cGround::SetGround(D3DXVECTOR2(95, 20.0f), D3DXVECTOR2(6.0f, 2.0f));
	//ここの間に敵
	cGround::SetGround(D3DXVECTOR2(103, 20.0f), D3DXVECTOR2(10.0f, 2.0f));
	//ここら辺にスコアに加算されるものを配置
	cGround::SetGround(D3DXVECTOR2(97, 22.0f), D3DXVECTOR2(2.0f, 4.0f));
	cGround::SetGround(D3DXVECTOR2(109, 22.0f), D3DXVECTOR2(2.0f, 4.0f));//ここ飛び越えて下の上のブロックに到達
	
	
	cGround::SetGround(D3DXVECTOR2(130, 10.0f), D3DXVECTOR2(2.0f, 6.0f));

	cGround::SetGround(D3DXVECTOR2(139, 6.0f), D3DXVECTOR2(10.0f, 6.0f));

	//----------------------------
	//ゴール階段
	//----------------------------
	cGround::SetGround(D3DXVECTOR2(145, -5.0f), D3DXVECTOR2(10.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(155, -3.0f), D3DXVECTOR2(10.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(159, 0.0f), D3DXVECTOR2(2.0f, 6.0f));
	cGround::SetGround(D3DXVECTOR2(161, 1.0f), D3DXVECTOR2(2.0f, 8.0f));
	cGround::SetGround(D3DXVECTOR2(163, 2.0f), D3DXVECTOR2(2.0f, 10.0f));
	cGround::SetGround(D3DXVECTOR2(165, 3.0f), D3DXVECTOR2(2.0f, 12.0f));
	cGround::SetGround(D3DXVECTOR2(167, 4.0f), D3DXVECTOR2(2.0f, 14.0f));
	cGround::SetGround(D3DXVECTOR2(169, 5.0f), D3DXVECTOR2(2.0f, 16.0f));
	cGround::SetGround(D3DXVECTOR2(172, 6.0f), D3DXVECTOR2(4.0f, 16.0f));//ゴールの灯す場所

	return true;

}

// 更新
void Update(void)
{
	// キーボード
	UpdateInput();

	// カメラ
	cCamera::Update();
	//cGrid::Update();

	// 要素
	cPlayer::Update();
	cSeika::Update();
	cGround::Update();
	cVerticalMoveGround::MoveUpdate();
	cHorizontalMoveGround::MoveUpdate();
}

// 描画
void Draw(void)
{

	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();
	if (!pD3DDevice) return;

	// 画面のクリア
	/*pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(123, 104, 238, 255), 1.0f, 0);*/
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	// 描画バッチ命令の開始
	pD3DDevice->BeginScene();
	Sprite_SetColor(D3DCOLOR_RGBA(0, 255, 255, 255));

	// カメラ
	cCamera::SetCamera();
	//cGrid::Draw();

	// 要素
	cSeika::Draw();
	cPlayer::Draw();
	cGround::Draw();
	cVerticalMoveGround::MoveDraw();
	cHorizontalMoveGround::MoveDraw();
	// 描画バッチ命令の終了
	pD3DDevice->EndScene();
	// バックバッファをフリップ（タイミングはD3DPRESENT_PARAMETERSの設定による）
	pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

// ゲームの終了処理
void Finalize(void)
{

	// 要素
	cSeika::Uninit();
	cPlayer::Uninit();
	cGround::Uninit();
	cVerticalMoveGround::MoveUninit();
	cHorizontalMoveGround::MoveUninit();
	// カメラ
	//cGrid::Uninit();
	cCamera::Uninit();

	// キーボード
	UninitInput();
	// システム解放
	Texture_Release();		// テクスチャの解放
	MyDirect3D_Finalize();	// Direct3Dラッパーモジュールの終了

}