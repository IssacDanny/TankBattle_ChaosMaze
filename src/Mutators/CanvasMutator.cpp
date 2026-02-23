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
    // TODO: Cast display.renderContext to (SDL_Renderer*).
    // TODO: Call SDL_SetRenderDrawColor (usually to black).
    // TODO: Call SDL_RenderClear.
}

void CanvasMutator::present() 
{
    // TODO: Call SDL_RenderPresent using the renderContext.
}

void CanvasMutator::drawSprite(void* texture, const AABB& destination, float angleDegrees, const Vector2D& centre) 
{
    // TODO: Prepare an SDL_Rect using the destination AABB data.
    // TODO: Prepare an SDL_Point using the centre Vector2D data.
    // TODO: Call SDL_RenderCopyEx to draw the texture with rotation.
    // Note: Cast texture to (SDL_Texture*) and renderContext to (SDL_Renderer*).
}

void CanvasMutator::drawText(const std::string& text, int x, int y) 
{
    // TODO: Use TTF_RenderText_Solid to create an SDL_Surface.
    // TODO: Convert the surface to an SDL_Texture.
    // TODO: Query the texture for width/height and create a destination SDL_Rect.
    // TODO: Call SDL_RenderCopy to paint the text.
    // TODO: Crucial: Clean up the temporary surface and texture to avoid memory leaks!
}