#ifndef PATH_FINDER_CPP_CIRCLE_H
#define PATH_FINDER_CPP_CIRCLE_H

#include "point.h"

struct Circle
{
    Point ctr;
    double r;

    Circle() : ctr(), r(1.0) {}
    Circle(Point c, double r) : ctr(c), r(r) {}
    Circle(double cx, double cy, double r) : ctr(cx,cy), r(r) {}
};

#endif //PATH_FINDER_CPP_CIRCLE_H