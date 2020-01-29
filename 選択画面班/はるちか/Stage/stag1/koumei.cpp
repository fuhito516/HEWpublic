#include"koumei.h"
#include"texture.h"
#include"sprite.h"
KOUMEI koumei;
void KOUMEI::Init() {
	koumei.s = 1;
	koumei.koumeipos.x = -20;
	koumei.koumeipos.y = 20;
}
void KOUMEI::Update() {
	koumei.koumeipos.x += 0.5f;
	if (koumei.koumeipos.x > SCREEN_WIDTH + 256) {
		koumei.koumeipos.x = SCREEN_WIDTH - 240;
	}
}

void KOUMEI::Draw() {
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();
	if (!pD3DDevice) return;

	pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	sprite_draw(TEXTURE_INDEX_KOUMEI, koumei.koumeipos.x, koumei.koumeipos.y, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


}