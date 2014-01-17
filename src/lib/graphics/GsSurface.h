
#ifndef __GS_SURFACE__
#define __GS_SURFACE__

#include <base/utils/Geometry.h>
#include <memory>


class GsSurface
{
public:

    GsSurface() :
        mpSurface(nullptr) {}

    GsSurface(SDL_Surface *sfc) :
        mpSurface(sfc) {}

    GsSurface(GsSurface *sfc) :
        mpSurface(sfc->getSDLSurface())
    {
        sfc->disownSfc();
    }

    void set(GsSurface *surface)
    {
        if(mpSurface != nullptr)
            SDL_FreeSurface(mpSurface);

        surface->disownSfc();

        mpSurface = surface->getSDLSurface();
    }

    ~GsSurface()
    {
        if(mpSurface != nullptr)
            SDL_FreeSurface(mpSurface);
    }



    /**
     * \brief Draws rect different than the SDL_Fillrect, because it has a contour and is filled
     * \param sfc Surface where to draw it
     * \param rect pointer to the given rect in which it has to be drawn. If it's NULL, than the dimensions
     * 			   of sfc is used
     * \param thickness Thickness of the contour
     * \param ContourColor Color of the contour
     */
    void drawRect(const GsRect<Uint16> &rect,
                  const int thickness,
                  const Uint32 contourColor );


    /**
     * \brief Draws rect different than the SDL_Fillrect, because it has a contour and is filled
     * \param sfc Surface where to draw it
     * \param rect pointer to the given rect in which it has to be drawn. If it's NULL, than the dimensions
     * 			   of sfc is used
     * \param thickness Thickness of the contour
     * \param ContourColor Color of the contour
     * \param FillColor Fill-color of the rect
     */
    void drawRect(const GsRect<Uint16> &rect,
                  const int thickness,
                  const Uint32 contourColor,
                  const Uint32 fillColor );


    GsRect<Uint16> calcBlitRect(const GsRect<float> &rect);

    int blitTo(GsSurface &sfc)
    {
        return SDL_BlitSurface( mpSurface, nullptr, sfc.mpSurface, nullptr );
    }

    int blitTo(GsSurface &sfc, GsRect<Uint16> &dstRect)
    {
        SDL_Rect sdlRect = dstRect.SDLRect();
        return SDL_BlitSurface( mpSurface, nullptr, sfc.mpSurface, &sdlRect );
    }

    int blitTo(GsSurface &sfc, const SDL_Rect &sdlRect)
    {
        return SDL_BlitSurface( mpSurface, nullptr, sfc.mpSurface, const_cast<SDL_Rect*>(&sdlRect) );
    }

    int setVideoMode(const int width,
                 const int height,
                 const int bpp,
                 const Uint32 flags)
    {
        if(mpSurface)
            SDL_FreeSurface(mpSurface);

        mpSurface = SDL_SetVideoMode(width, height, bpp, flags);
        return 0;
    }

    void create(Uint32 flags, int width, int height, int depth,
                Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
    {
        if(mpSurface)
            SDL_FreeSurface(mpSurface);

        mpSurface = SDL_CreateRGBSurface(flags, width, height, depth,
                                         Rmask, Gmask, Bmask, Amask);
    }

    Uint32 mapRGB(const Uint8 r, const Uint8 g, const Uint8 b)
    {
        return SDL_MapRGB( mpSurface->format, r, g, b );
    }

    Uint32 mapRGBA(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
    {
        return SDL_MapRGBA( mpSurface->format, r, g, b, a );
    }


    void fillRGB(const Uint8 r, const Uint8 g, const Uint8 b)
    {
        SDL_FillRect( mpSurface, &mpSurface->clip_rect, SDL_MapRGB( mpSurface->format, r, g, b ) );
    }

    void fillRGB(const GsRect<Uint16> &rect, const Uint8 r, const Uint8 g, const Uint8 b)
    {
        fill( rect, mapRGB(r,g,b) );
    }

    void fillRGBA(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
    {
        SDL_FillRect( mpSurface, &mpSurface->clip_rect, SDL_MapRGBA( mpSurface->format, r, g, b, a ) );
    }

    void fillRGBA(const GsRect<Uint16> &rect, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
    {
        fill( rect, mapRGBA(r,g,b,a) );
    }

    void fill(const GsRect<Uint16> &rect, const Uint32 color)
    {
        SDL_Rect sdlRect = rect.SDLRect();
        SDL_FillRect( mpSurface, &sdlRect, color );
    }

    bool flip()
    {
        return (SDL_Flip(mpSurface)!=-1);
    }

    // bool operator
    operator bool() const
    {
        return (mpSurface!=nullptr);
    }


    // Use this, if you don't need to access the surface and another process
    // will free it. If you used setVideoMode(...)
    // please call this before you call SDL_Quit and exit the program.
    void disownSfc()
    {
        mpSurface = nullptr;
    }

    SDL_Surface *getSDLSurface()
    {
        return mpSurface;
    }


private:

    SDL_Surface *mpSurface;
};

#endif // __GS_SURFACE__
