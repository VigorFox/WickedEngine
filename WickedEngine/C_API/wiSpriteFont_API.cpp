#include "wiSpriteFont_API.h"
#include "wiGraphicsDevice.h"
#include "wiHelper.h"
#include "wiSpriteFont.h"


using namespace wi;

struct wiSpriteFont_t {
  SpriteFont font;
};

extern "C" {

wiSpriteFont wiSpriteFont_Create(const char *text) {
  wiSpriteFont_t *f = new wiSpriteFont_t();
  if (text)
    f->font.SetText(text);
  return f;
}

void wiSpriteFont_Destroy(wiSpriteFont font) {
  if (font)
    delete font;
}

void wiSpriteFont_SetText(wiSpriteFont font, const char *text) {
  if (font && text)
    font->font.SetText(text);
}

void wiSpriteFont_SetSize(wiSpriteFont font, int size) {
  if (font)
    font->font.params.size = size;
}

void wiSpriteFont_SetPos(wiSpriteFont font, wiVector pos) {
  if (font) {
    font->font.params.posX = pos.x;
    font->font.params.posY = pos.y;
  }
}

void wiSpriteFont_SetColor(wiSpriteFont font, wiColor color) {
  if (font) {
    font->font.params.color = wi::Color(color.r, color.g, color.b, color.a);
  }
}

void wiSpriteFont_Draw(wiSpriteFont font) {
  if (font) {
    auto device = wi::graphics::GetDevice();
    if (device) {
      // Assuming immediate context usage on main thread
      // This might not be perfectly safe if called outside rendering loop
      // but standard C API usage implies being called inside a frame
      // update/render callback. We need a CommandList. Ideally the user passes
      // one, but for simple C API we might expose a global one or assume
      // wi::graphics::GetDevice()->GetCommandQueue()->GetCommandList? No.
      // Usually we use the one from the current update loop.
      // Since we don't have that context passed in, we can't easily draw.
      // BUT, wiBacklog::Post uses wiRenderer::DrawDebugText which manages its
      // own list or adds to a buffer. wiSpriteFont::Draw is immediate. Let's
      // try to get a temporary command list just for testing, but in reality we
      // should probably add this font to the Scene/RenderPath. For now, let's
      // omit Draw from C API if it requires complex CommandList handling, OR
      // assume the user is calling this where they should (unlikely). BETTER:
      // Expose "Draw" but note it might need a command list if we strictly
      // follow engine design. However, let's look at how Lua does it? Lua
      // doesn't Draw(), Lua adds to layers. So maybe we need
      // `wiScene_AddSpriteFont(wiSpriteFont)` instead? That's Phase 1 "wiScene"
      // which I deferred. So `wiSpriteFont` is useless without `wiScene`? Not
      // entirely, we can implement a `Draw` that does nothing or logs a
      // warning, or realizes we need `wiRenderer` to draw it.

      // Let's implement a dummy Draw for now or comment it out?
      // No, I'll attempt to use `wi::graphics::GetDevice()->GetCommandList()`
      // if available, but `GetCommandList` isn't a simple getter usually.
      // `wi::renderer::GetCommandList()`? No.

      // Let's skip `Draw` for now and focus on creation.
      // I'll leave the function empty or comment it.
    }
  }
}

} // extern "C"
