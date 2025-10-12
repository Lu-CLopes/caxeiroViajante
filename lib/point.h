#ifndef _POINT_H_
#define _POINT_H_


#include <cmath>
#include <cstdint>


// constants for Point flags
const uint8_t POINT_EMPTY = 0x0;
const uint8_t POINT_FULL = 0x1;
const double PI = 3.14159265358979323846;


class Point{
public:
    // attributes
    double x;
    double y;
    char name;
    uint8_t flags;

    // constructors
    Point(){
        x = 0.0;
        y = 0.0;
        name = 0;
        flags = POINT_EMPTY;
    }

    Point(double X, double Y){
        x = X;
        y = Y;
        name = '0';
        flags = POINT_EMPTY;
    }

    Point(double X, double Y, char NAME){
        x = X;
        y = Y;
        name = NAME;
        flags = POINT_EMPTY;
    }

    Point(double X, double Y, char NAME, bool isFull){
        x = X;
        y = Y;
        name = NAME;
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

    void setPosition(double X, double Y)
    {
        x = X;
        y = Y;
    }

    void setInfo(double X, double Y, char NAME)
    {
        x = X;
        y = Y;
        name = NAME;
    }
};

#endif