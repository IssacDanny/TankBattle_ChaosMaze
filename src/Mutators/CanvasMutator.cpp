#include "Mutators/CanvasMutator.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

/**
 * @brief Binds the mutator to the hardware display ledger.
 */
CanvasMutator::CanvasMutator(DisplayLedger& ledger) : display(ledger) {}

void CanvasMutator::clear() 
{
    auto* renderer = static_cast<SDL_Renderer*>(display.renderContext);
    if (!renderer) return;

    // Clear to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void CanvasMutator::present() 
{
    auto* renderer = static_cast<SDL_Renderer*>(display.renderContext);
    if (!renderer) return;

    SDL_RenderPresent(renderer);
}

void CanvasMutator::drawSprite(void* texture, const AABB& destination, float angleDegrees, const Vector2D& centre) 
{
    auto* renderer = static_cast<SDL_Renderer*>(display.renderContext);
    auto* tex = static_cast<SDL_Texture*>(texture);

    if (!renderer || !tex) return;

    SDL_Rect destRect{
        static_cast<int>(destination.x),
        static_cast<int>(destination.y),
        static_cast<int>(destination.width),
        static_cast<int>(destination.height)
    };

    SDL_Point pivot{
        static_cast<int>(centre.x),
        static_cast<int>(centre.y)
    };

    SDL_RenderCopyEx(
        renderer,
        tex,
        nullptr,          // srcRect: nullptr = full texture
        &destRect,
        static_cast<double>(angleDegrees),
        &pivot,
        SDL_FLIP_NONE
    );
}

void CanvasMutator::drawText(const std::string& text, int x, int y) 
{
    auto* renderer = static_cast<SDL_Renderer*>(display.renderContext);
    auto* font = static_cast<TTF_Font*>(display.fontAsset); // from DisplayLedger :contentReference[oaicite:1]{index=1}

    if (!renderer || !font) return;
    if (text.empty()) return;

    SDL_Color color{ 255, 255, 255, 255 }; // white

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) return;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    if (!tex) {
        SDL_FreeSurface(surface);
        return;
    }

    int w = 0, h = 0;
    SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);

    SDL_Rect destRect{ x, y, w, h };
    SDL_RenderCopy(renderer, tex, nullptr, &destRect);

    // Cleanup (crucial: avoid leaks every frame)
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surface);
}