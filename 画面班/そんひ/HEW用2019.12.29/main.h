#pragma once

#define CLASS_NAME     "GameWindow"       // ウインドウクラスの名前
#define WINDOW_CAPTION "ゲームウィンドウ" // ウィンドウの名前

// ウィンドウプロシージャ(コールバック関数)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// 基本関数
static bool Initialize(HINSTANCE hInstance);	// 戻り値:初期化に失敗したときfalse
static void Update(void);
static void Draw(void);
static void Finalize(void);