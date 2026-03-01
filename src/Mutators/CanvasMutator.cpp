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

void CanvasMutator::drawSprite(void* texture, const AABB& destination, float angleDegrees, const Vector2D& /*unused*/) 
{
    SDL_Texture* tex = static_cast<SDL_Texture*>(texture);
    SDL_Renderer* ren = static_cast<SDL_Renderer*>(display.renderContext);
    
    if (!tex || !ren) return;

    // 1. Query the native proportions of the asset
    int nativeW, nativeH;
    SDL_QueryTexture(tex, NULL, NULL, &nativeW, &nativeH);

    // 2. Calculate the "Aspect Fit" Scale
    // We find the ratio required to fit the width and the height
    float scaleX = destination.width / static_cast<float>(nativeW);
    float scaleY = destination.height / static_cast<float>(nativeH);

    // We use the smaller of the two scales to ensure the sprite 
    // fits entirely within the physical AABB without stretching.
    float finalScale = (scaleX < scaleY) ? scaleX : scaleY;

    // 3. Calculate the final visual dimensions
    float finalW = static_cast<float>(nativeW) * finalScale;
    float finalH = static_cast<float>(nativeH) * finalScale;

    // 4. Centre the sprite perfectly over the physical AABB
    float centerX = destination.x + (destination.width / 2.0f);
    float centerY = destination.y + (destination.height / 2.0f);

    SDL_FRect renderRect;
    renderRect.x = centerX - (finalW / 2.0f);
    renderRect.y = centerY - (finalH / 2.0f);
    renderRect.w = finalW;
    renderRect.h = finalH;

    // 5. Define the pivot point (the centre of the scaled sprite)
    SDL_FPoint pivot = { finalW / 2.0f, finalH / 2.0f };

    // 6. Exhibit the sprite
    SDL_RenderCopyExF(ren, tex, NULL, &renderRect, angleDegrees, &pivot, SDL_FLIP_NONE);
}

void CanvasMutator::drawText(const std::string& text, int x, int y) 
{
    // 1. Retrieve the font and renderer from the ledger
    TTF_Font* font = static_cast<TTF_Font*>(display.fontAsset);
    SDL_Renderer* ren = static_cast<SDL_Renderer*>(display.renderContext);

    if (!font || !ren) return;

    // 2. Define the ink colour (Crisp White)
    SDL_Color textColour = { 255, 255, 255, 255 };

    // 3. Commission a temporary painting (Surface)
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColour);
    if (!textSurface) return;

    // 4. Convert the painting into a hardware-accelerated texture
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
    if (!textTexture) {
        SDL_FreeSurface(textSurface);
        return;
    }

    // 5. Define where it should hang on the screen
    SDL_Rect destRect = { x, y, textSurface->w, textSurface->h };

    // 6. Stamp it onto the back-buffer
    SDL_RenderCopy(ren, textTexture, NULL, &destRect);

    // 7. Clean up the temporary materials! A tidy workshop is a happy workshop.
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}