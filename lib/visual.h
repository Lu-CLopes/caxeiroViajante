#ifndef _VISUAL_H_
#define _VISUAL_H_


#include "genetic.h"    // should I remove this?


// SCREEN
#include <iostream>
#include <SDL.h>
const double centerX = 500.0;
const double centerY = 375.0;
const int RADIUS = 7;


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


inline void line(SDL_Renderer* renderer, Point FROM, Point TO, bool hasArrowhead)
{
    double dx = TO.x - FROM.x;
    double dy = TO.y - FROM.y;
    double len = sqrt(dx*dx + dy*dy);

    if (len == 0) return; // avoid division by zero

    // Normalize direction
    dx /= len;
    dy /= len;

    // main line endpoints
    Point perifONE( FROM.x + RADIUS * dx, FROM.y + RADIUS * dy);
    Point tip(TO.x - RADIUS * dx, TO.y - RADIUS * dy);    // tip == perifTWO

    if(hasArrowhead)
    {
        // Arrow parameters
        double arrowLength = 7.0;  // length of arrowhead
        double arrowWidth  = 5.0;  // half width

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
    else
    {
        // Draw main line
        SDL_RenderDrawLine(renderer,
            centerX + perifONE.x, centerY - perifONE.y,
            centerX + tip.x, centerY - tip.y);
    }
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

inline void drawPoints(SDL_Renderer* renderer, Point points[AMOUNT_POINTS], int n)
{
    int i;

    for(i=0; i<AMOUNT_POINTS; i++)
    {
        if(i<n)
        {
            fullCircle(renderer, points[i]);
            line(renderer, points[i], i==AMOUNT_POINTS-1? points[0] : points[i+1], true);
        }
        else
            emptyCircle(renderer, points[i]);
    }

    return;
}

#endif