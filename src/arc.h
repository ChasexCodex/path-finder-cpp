#ifndef PATH_FINDER_CPP_ARC_H
#define PATH_FINDER_CPP_ARC_H

#include "point.h"
#include "line.h"

class Arc {
    Point start;
    Point end;
    Circle circle;
    Direction direction;

public:
    Arc(Point start, Point end, Direction direction, Circle circle);

    double Length();

    bool IntersectsWithCircle(Circle other);

    bool ContainsPointUnchecked(Point point);
};

#endif //PATH_FINDER_CPP_ARC_H
