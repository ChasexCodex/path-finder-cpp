#include "segment.h"

Segment::Segment(Point start, Point end) : Line(start, end), start(start), end(end) {}

bool Segment::ContainsPoint(Point point) {
    return PassesByPoint(point) &&
           InRangeInclusive(min(start.x, end.x), point.x, max(start.x, end.x)) &&
           InRangeInclusive(min(start.y, end.y), point.y, max(start.y, end.y));
}

bool Segment::IntersectsWithCircle(Circle circle) {
    if (CircleContainsPoint(circle, start))
        return true;
    if (CircleContainsPoint(circle, end))
        return true;
    auto result = IntersectionWithCircle(circle);
    if (result.empty())
        return false;
    return find_if(result.begin(), result.end(), [this](Point point) {
        return ContainsPoint(point);
    }) != result.end();
}
