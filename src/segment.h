#ifndef PATH_FINDER_CPP_SEGMENT_H
#define PATH_FINDER_CPP_SEGMENT_H

#include "helpers.h"
#include "line.h"

class Segment : Line {
    Point start;
    Point end;

public:
    Segment(Point start, Point end);

    bool ContainsPoint(Point point);

    bool IntersectsWithCircle(Circle circle);
};

#endif //PATH_FINDER_CPP_SEGMENT_H
