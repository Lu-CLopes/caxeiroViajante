#ifndef _POINT_H_
#define _POINT_H_


#include <cmath>
#include <cstdint>


// constants for Point flags
const double PI = 3.14159265358979323846;


class Point{
public:
    // attributes
    double x;
    double y;
    char name;

    // constructors
    Point(){
        x = 0.0;
        y = 0.0;
        name = 0;
    }

    Point(double X, double Y){
        x = X;
        y = Y;
        name = '0';
    }

    Point(double X, double Y, char NAME){
        x = X;
        y = Y;
        name = NAME;
    }

    // methods
    // (euclidian) distante to other point
    double d2op(Point other)
    {
        return std::hypot(x - other.x, y-other.y);
    }

    // compares to another point
    bool isEqualTo(Point other)
    {
        if(x == other.x && y == other.y /*&& name == other.name*/)  // name is not really important
            return true;

        return false;
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