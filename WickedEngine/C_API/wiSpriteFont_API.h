#pragma once
#include "wiC_API.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wiSpriteFont_t *wiSpriteFont;

wiSpriteFont wiSpriteFont_Create(const char *text);
void wiSpriteFont_Destroy(wiSpriteFont font);

void wiSpriteFont_SetText(wiSpriteFont font, const char *text);
void wiSpriteFont_SetSize(wiSpriteFont font, int size);
void wiSpriteFont_SetPos(wiSpriteFont font, wiVector pos);
void wiSpriteFont_SetColor(wiSpriteFont font, wiColor color);

// Draw the font immediately (requires internal CommandList)
void wiSpriteFont_Draw(wiSpriteFont font);

#ifdef __cplusplus
}
#endif
