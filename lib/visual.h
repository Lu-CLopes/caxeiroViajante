#ifndef _VISUAL_H_
#define _VISUAL_H_


#include <cstdint>
#include <cmath>


// constants for Point flags
const uint8_t POINT_EMPTY = 0x0;
const uint8_t POINT_FULL = 0x1;


class Point{
public:
    // attributes
    double x;
    double y;
    uint8_t flags;

    // constructors
    Point(){
        x = 0.0;
        y = 0.0;
        flags = POINT_EMPTY;
    }

    Point(double X, double Y){
        x = X;
        y = Y;
        flags = POINT_EMPTY;
    }

    Point(double X, double Y, bool isFull){
        x = X;
        y = Y;
        if(isFull)
            flags = POINT_FULL;
        else
            flags = POINT_EMPTY;
    }

    // methods
    // (euclidian) distante to other point
    double d2op(Point other)
    {
        return std::hypot(x - other.x, y-other.y);
    }

    void fillStatus(bool isFull)
    {
        if(isFull)
            flags = flags | POINT_FULL;
        else
            flags = flags & (~POINT_FULL);
    }
};


// SCREEN
#include <iostream>
#include <SDL.h>
const double centerX = 500.0;
const double centerY = 375.0;
const int RADIUS = 7;
const double PI = 3.14159265358979323846;


inline int SDL_initialize(SDL_Window** window, SDL_Renderer** renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    (*window) = SDL_CreateWindow("Screen Test",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     1000, 750,
                                     SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    (*renderer) = SDL_CreateRenderer((*window), -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 1;
    }

    return 0;
}


inline void line(SDL_Renderer* renderer, Point FROM, Point TO)
{
    double dx = TO.x - FROM.x;
    double dy = TO.y - FROM.y;
    double len = sqrt(dx*dx + dy*dy);

    if (len == 0) return; // avoid division by zero

    // Normalize direction
    dx /= len;
    dy /= len;

    // Arrow parameters
    double arrowLength = 7.0;  // length of arrowhead
    double arrowWidth  = 5.0;  // half width

    // main line endpoints
    Point perifONE( FROM.x + RADIUS * dx, FROM.y + RADIUS * dy);
    Point tip(TO.x - RADIUS * dx, TO.y - RADIUS * dy);    // tip == perifTWO

    // arrowhead points
    Point base(tip.x - arrowLength * dx, tip.y - arrowLength * dy);
    Point left(base.x + arrowWidth * dy, base.y - arrowWidth * dx);
    Point right(base.x - arrowWidth * dy, base.y + arrowWidth * dx);

    // Draw main line
    SDL_RenderDrawLine(renderer,
        centerX + perifONE.x, centerY - perifONE.y,
        centerX + base.x, centerY - base.y);

    // drawing triangle arrowhead
    SDL_RenderDrawLine(renderer,
        centerX + tip.x, centerY - tip.y,
        centerX + left.x, centerY - left.y);
    SDL_RenderDrawLine(renderer,
        centerX + tip.x, centerY - tip.y,
        centerX + right.x, centerY - right.y);
    SDL_RenderDrawLine(renderer,
        centerX + left.x, centerY - left.y,
        centerX + right.x, centerY - right.y);
}

inline void showAxis(SDL_Renderer* renderer, bool showMarkers)
{
    const int x1 = centerX-5;
    const int x2 = centerX+5;
    const int y1 = centerY-5;
    const int y2 = centerY+5;
    int i;

    SDL_SetRenderDrawColor(renderer, 255, 80, 80, 255); // Red
    SDL_RenderDrawLine(renderer, centerX, 0, centerX, 2*centerY);
    if(showMarkers)
    {
        for(i=0; i<2*centerY; i+=50)
            if(i != centerY)
                SDL_RenderDrawLine(renderer, x1, i, x2, i);
    }

    SDL_SetRenderDrawColor(renderer, 80, 80, 255, 255); // Blue
    SDL_RenderDrawLine(renderer, 0, centerY, 2*centerX, centerY);
    if(showMarkers)
    {
        for(i=0; i<2*centerX; i+=50)
            if(i != centerX)
                SDL_RenderDrawLine(renderer, i, y1, i, y2);
    }
}

inline void emptyCircle(SDL_Renderer* renderer, Point target)
{
    int cX = centerX + round(target.x);
    int cY = centerY - round(target.y);
    int x = RADIUS-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (RADIUS << 1);

    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, cX + x, cY + y);
        SDL_RenderDrawPoint(renderer, cX + y, cY + x);
        SDL_RenderDrawPoint(renderer, cX - y, cY + x);
        SDL_RenderDrawPoint(renderer, cX - x, cY + y);
        SDL_RenderDrawPoint(renderer, cX - x, cY - y);
        SDL_RenderDrawPoint(renderer, cX - y, cY - x);
        SDL_RenderDrawPoint(renderer, cX + y, cY - x);
        SDL_RenderDrawPoint(renderer, cX + x, cY - y);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (RADIUS << 1);
        }
    }
}

inline void fullCircle(SDL_Renderer* renderer, Point target)
{
    int cX = centerX + round(target.x);
    int cY = centerY - round(target.y);

    for (int w = 0; w < RADIUS * 2; w++)
    {
        for (int h = 0; h < RADIUS * 2; h++)
        {
            int dx = RADIUS - w; // horizontal offset
            int dy = RADIUS - h; // vertical offset
            if ((dx*dx + dy*dy) <= (49))
            {
                SDL_RenderDrawPoint(renderer, cX + dx, cY + dy);
            }
        }
    }
}

inline void drawCircle(SDL_Renderer* renderer, Point target)
{
    if(target.flags & POINT_FULL)
        fullCircle(renderer, target);
    else
        emptyCircle(renderer, target);
}

#endif