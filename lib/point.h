#ifndef _POINT_H_
#define _POINT_H_


#include <cmath>
#include <cstdint>


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

    bool isFull()
    {
        return (flags & POINT_FULL);
    }
};

#endif