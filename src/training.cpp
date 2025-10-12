#include "../lib/genetic.h"
#include <iostream>


void print_points(Point points[AMOUNT_POINTS])
{
    int i;

    for(i=0; i<AMOUNT_POINTS; i++)
        std::cout << points[i].name << ": ("  << points[i].x << ", " << points[i].y << ")" << std::endl;

    std::cout << "\n\n" << std::endl;

    return;
}

void print_order(Point points[AMOUNT_POINTS])
{
    int i;

    std::cout << "[";
    for(i=0; i<AMOUNT_POINTS; i++)
        std::cout << points[i].name << ((i==AMOUNT_POINTS-1)? "" : ", ");
    std::cout << "]" << std::endl;

    return;
}

int main()
{
    Point points[AMOUNT_POINTS];
    init_benchmark(points);

    print_order(points);
    print_points(points);

    return 0;
}