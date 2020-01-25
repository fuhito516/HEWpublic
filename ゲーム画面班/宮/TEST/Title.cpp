
// ���C��
#include"Title.h"
#include"common.h"
#include"direct3d.h"
#include"vertex.h"
// ��
#include"camera.h"
#include"input.h"
// �V�[��
#include"scene.h"
#include"Game.h"

LPDIRECT3DTEXTURE9 cTitle::pTextures[NUMBER_OF_TITLE_TEXTURE];
bool cTitle::use = false;

// ������
void cTitle::Init()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// �g�p
	use = true;

	// �e�N�X�`���[
	for (int i = 0; i < NUMBER_OF_TITLE_TEXTURE; i++)
	{
		pTextures[i] = NULL;
	}
	D3DXCreateTextureFromFile(pD3DDevice, "asset/texture/title back.png", &pTextures[0]);
	D3DXCreateTextureFromFile(pD3DDevice, "asset/texture/title name.png", &pTextures[1]);

	// ��
	cCamera::Init();
	/* �f�o�b�O�@�\�̒ǉ� */
}
// �I��
void cTitle::Uninit()
{
	// �g�p
	use = false;

	// ��
	cCamera::Uninit();

	// �e�N�X�`��
	for (int i = 0; i < NUMBER_OF_TITLE_TEXTURE; i++)
	{
		if (pTextures[i] != NULL)
		{
			pTextures[i]->Release();
			pTextures[i] = NULL;
		}
	}
}
// �X�V
void cTitle::Update()
{
	// �J��
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		cScene::Fade(SCENE_GAME);
	}
}
// �`��
void cTitle::Draw()
{

}