//==================================================
//AT12b345川野敏慎
//2019/11/12
//Draw関数の中のカメラの情報の初期化関数の初期化部分を移動したもの
//
//==================================================

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")

#include <Windows.h>
#include "common.h"
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include <d3dx9.h>
#include"input.h"
#include"Caracterselect.h"


//===============================================
//ここを追加　3D用追加コード

typedef struct 
{
	D3DXVECTOR3 vtx;//頂点座標
	D3DXVECTOR3 nor;//法線ベクトル
	D3DCOLOR diffuse;//反射光
	D3DXVECTOR2 tex;//テクスチャ座標

}VERTEX_3D;

//3Dポリゴン頂点フォーマット
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//プロジェクション用パラメーター
#define VIEW_ANGLE		(D3DXToRadian(45.0f))
#define VIEW_ASPECT		((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT)
#define VIEW_NEAR_Z		(1.0f)
#define VIEW_FAR_Z		(1000.0f)
//カメラ用パラメータ
D3DXVECTOR3		g_posCamerEye;
D3DXVECTOR3		g_posCameraAt;
D3DXVECTOR3		g_vecCameraUp;

D3DXMATRIX		g_mtxView;
D3DXMATRIX		g_mtxProjection;

D3DXVECTOR3		g_pos;
D3DXVECTOR3		g_rot;
D3DXVECTOR3		g_scl;
D3DXMATRIX		g_mtxWorld;


LPDIRECT3DVERTEXBUFFER9		g_pD3DVtxBuff;
LPDIRECT3DVERTEXBUFFER9		g_pD3DVtxBord;




//ここまで3D用追加コード
//===============================================



/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/
#define CLASS_NAME     "GameWindow"       // ウインドウクラスの名前
#define WINDOW_CAPTION "ゲームウィンドウ" // ウィンドウの名前
#define MAX_GURID (50)
#define bordten 4

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/
// ウィンドウプロシージャ(コールバック関数)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// ゲームの初期化関数
// 戻り値:初期化に失敗したときfalse
static bool Initialize(void);
// ゲームの更新関数
static void Update(void);
// ゲームの描画関数
static void Draw(void);
// ゲームの終了処理
static void Finalize(void);


/*------------------------------------------------------------------------------
   グローバル変数宣言
------------------------------------------------------------------------------*/
static HWND g_hWnd;             // ウィンドウハンドル
static float g_Rotation = 0.0f; // スプライト回転角度 
float Rad = 90.0f;
static float g_Pos = 0.0f;
float s = 1;
float i = 0;


D3DLIGHT9 g_Light;//ライトの構造体
LPDIRECT3DINDEXBUFFER9 g_pD3DIdxBuff;//インターフェースの入れ物
LPDIRECT3DINDEXBUFFER9 g_pD3DIdxBord;//インターフェースの入れ物

/*------------------------------------------------------------------------------
   関数定義
------------------------------------------------------------------------------*/

//#######################################################################
// メイン関数
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 使用しない一時変数を明示
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	//=============================================================
	//bool Keyboard_Initialize(HINSTANCE hInstance, HWND hWnd);
	//=============================================================
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
    g_hWnd = CreateWindow(
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

    if( g_hWnd == NULL ) {
        // ウィンドウハンドルが何らかの理由で生成出来なかった
        return -1;
    }
	//初期化場所
	Keyboard_Initialize(hInstance, g_hWnd);
    // 指定のウィンドウハンドルのウィンドウを指定の方法で表示
	
    ShowWindow(g_hWnd, nCmdShow);

	// ゲームの初期化(Direct3Dの初期化)
	if( !Initialize() ) {
        // ゲームの初期化に失敗した
		return -1;
	}

    // Windowsゲーム用メインループ
    MSG msg = {}; // msg.message == WM_NULL
    while( WM_QUIT != msg.message ) {

        if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
            // メッセージがある場合はメッセージ処理を優先
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // ゲームの更新
			Keyboard_Update();

			Update();
			
			// ゲームの描画
			Draw();
        }
    }
		

	// ゲームの終了処理(Direct3Dの終了処理)
	Keyboard_Finalize();
	Finalize();



    return (int)msg.wParam;
}

//#######################################################################
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


//#######################################################################
// ゲームの初期化関数
bool Initialize(void)
{
	CaracterselectInitialize();

    // Direct3Dラッパーモジュールの初期化
    if( !MyDirect3D_Initialize(g_hWnd) ) {
        return false;
    }

    // テクスチャの読み込み
    if( Texture_Load() > 0 ) {
        MessageBox(g_hWnd, "いくつか読み込めなかったテクスチャファイルがあります", "エラー", MB_OK);
    }

	
	//================================================================
	//ここを追加　3Dポリゴン用頂点の準備
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();


	//オブジェクトの頂点バッファを生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 36,//サイズ
		D3DUSAGE_WRITEONLY,//使用法
		FVF_VERTEX_3D,//使用する頂点フォーマット
		D3DPOOL_MANAGED,//リソースのバッファを保持するメモリクラスタを指定
		&g_pD3DVtxBuff, NULL);//頂点バッファをインターフェースへのポインタ




 //光の初期化ーーーーーーーーーー
	ZeroMemory(&g_Light,sizeof(D3DLIGHT9));
	g_Light.Type = D3DLIGHT_DIRECTIONAL;//ライトの種類
	g_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//光の色RGBA０～１
	g_Light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//環境光の色

	D3DXVECTOR3 vecDin = D3DXVECTOR3(0.0f, -0.6f, 1.0f);//光のさすベクトル
	D3DXVec3Normalize(&vecDin, &vecDin);
	g_Light.Direction = vecDin;//正規化してセット

	pDevice->SetLight(0, &g_Light);//0番のライトへデータをセット
	pDevice->LightEnable(0, TRUE);//０番のライトを有効果　例（ダメージ貰ったら光らせたいとか場面ごとに使い分けれるようにする）
	 //ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

	pDevice->CreateIndexBuffer(sizeof(WORD) * 3,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pD3DIdxBord,
		NULL);
	//----------------------------------------------------------
	//
	//インターフェースを作成
	//
	//----------------------------------------------------------




	//今回の例

	//ここまで
//	g_pD3DIdxBuff->Unlock();//アンロック忘れないように注意！！！

	//ここまでがインターフェース初期化＊＊＊＊＊＊＊


		//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;
		
	
		g_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//グリッド線の描画

		//頂点座標の設定
	
		g_pD3DVtxBuff->Unlock();

	//ここまで　3Dポリゴン用頂点の準備
	//================================================================
		g_posCamerEye = D3DXVECTOR3(0, 4, -8.0f);
		g_posCameraAt = D3DXVECTOR3(0, 0, 0);
		g_vecCameraUp = D3DXVECTOR3(0.0f, 10.0f, 0.0f);


    return true;
}

//#######################################################################
// ゲームの更新関数
void Update(void)
{
	CaracterselectUpdate();

}

//#######################################################################
// ゲームの描画関数
void Draw(void)
{
	
    LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)  return ;
	
	//光のドロー

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);//光源処理ON
	//=========================================================================
	//TRUEにしてから光を当てたいポリゴンをDrawする
	//FALSEにしてから光をあてないポリゴンをDrawする
	//Draw～を１回ずつでTRUE↔FALSEを切り替えないでなるべくまとめてDrawする。
	//=========================================================================
    // 画面のクリア
    pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(10, 40, 20, 255), 1.0f, 0);

    // 描画バッチ命令の開始
    pDevice->BeginScene();

	//==============================================
	//ここを追加　テスト用カメラ情報を準備

	//ビュー行列
	D3DXMatrixLookAtLH(&g_mtxView,
		&g_posCamerEye,//カメラの視点
		&g_posCameraAt,//カメラの注視点
		&g_vecCameraUp);//カメラの上方向


	//ビュー行列の設定
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);

	//==============================================
	// ここを追加　テスト用プロジェクション行列の作成
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
		VIEW_ANGLE,//視野角
		VIEW_ASPECT,//アスペクト比
		VIEW_NEAR_Z,//Near値
		VIEW_FAR_Z);//Far値

	//プロジェクション行列の設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);



	CaracterselectDraw();


	//=============================================================
	//ここを追加　ポリゴンのワールド行列の作成
	D3DXMATRIX	mtxScl;//スケーリング行列
	D3DXMATRIX	mtxRot;//回転行列
	D3DXMATRIX	mtxTrs;//平行移動行列


	


	//ここまでを追加　
	//=============================================================  

    // 描画バッチ命令の終了
    pDevice->EndScene();

    // バックバッファをフリップ（タイミングはD3DPRESENT_PARAMETERSの設定による）
    pDevice->Present(NULL, NULL, NULL, NULL);
}

//#######################################################################
// ゲームの終了処理
void Finalize(void)
{
    // テクスチャの解放
    Texture_Release();

	if (g_pD3DIdxBuff != NULL) {
		g_pD3DIdxBuff->Release();//インターフェース解放
		g_pD3DIdxBuff = NULL;
	}

	//if (g_pD3DIdxBord != NULL) {
	//	g_pD3DIdxBord->Release();//インターフェース解放
	//	g_pD3DIdxBord = NULL;
	//}

    // Direct3Dラッパーモジュールの終了処理
    MyDirect3D_Finalize();





}
