#include"Koumeitou.h"
#include"texture.h"
#include"sprite.h"
KOUMEI koumei;
void koumeiInit(){
	koumei.s = 1;
	koumei.koumeipos.x = -20;
	koumei.koumeipos.y = 20;
}
void koumeiUpdate() {
	koumei.koumeipos.x += 0.5f;
	if (koumei.koumeipos.x > SCREEN_WIDTH + 256) {
		koumei.koumeipos.x = SCREEN_WIDTH - 240;
	}
}

void koumeiDraw() {
	Sprite_KoumeiDraw(TEXTURE_INDEX_KOUMEI, koumei.koumeipos.x, koumei.koumeipos.y,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);


}