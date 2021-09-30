#ifndef PATH_FINDER_CPP_ARC_H
#define PATH_FINDER_CPP_ARC_H

#include "point.h"
#include "line.h"

class Arc {
    const Point start;
    const Point end;
    const Circle circle;
    const Direction direction;

private:
    [[nodiscard]] bool ContainsPointUnchecked(Point point) const;

public:
    Arc(Point start, Point end, Direction direction, Circle circle);

    [[nodiscard]] double Length() const;

    [[nodiscard]] bool IntersectsWithCircle(Circle other) const;
};

#endif //PATH_FINDER_CPP_ARC_H
