#ifndef PATH_FINDER_CPP_POINT_H
#define PATH_FINDER_CPP_POINT_H

struct Point
{
    double x,y;

    Point() : x(0.0), y(0.0) {}
    Point(double x, double y) : x(x), y(y) {}
};

#endif //PATH_FINDER_CPP_POINT_H