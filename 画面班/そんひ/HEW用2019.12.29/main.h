#pragma once

#define CLASS_NAME     "GameWindow"       // �E�C���h�E�N���X�̖��O
#define WINDOW_CAPTION "�Q�[���E�B���h�E" // �E�B���h�E�̖��O

// �E�B���h�E�v���V�[�W��(�R�[���o�b�N�֐�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// ��{�֐�
static bool Initialize(HINSTANCE hInstance);	// �߂�l:�������Ɏ��s�����Ƃ�false
static void Update(void);
static void Draw(void);
static void Finalize(void);