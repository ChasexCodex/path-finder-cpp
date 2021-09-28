#include "arc.h"

Arc::Arc(Point start, Point end, Direction direction, Circle circle)
        : start(start), end(end), direction(direction), circle(circle) {}

double Arc::Length() {
    switch (direction) {
        case Clockwise:
            return NormalizedAngle(start, circle.ctr, end) * circle.r;
        case CounterClockwise:
            return (2 * PI - NormalizedAngle(start, circle.ctr, end)) * circle.r;
        case None:
            throw exception("None occurred");
    }
}

bool Arc::IntersectsWithCircle(Circle other) {
    auto intersectionLine = Line::IntersectionLineOfTwoCircles(circle, other);
    if (intersectionLine == nullptr)
        return false;

    auto result = intersectionLine->IntersectionWithCircle(circle);
    if(result.empty())
        return false;
    return find_if(result.begin(),  result.end(), [this](Point point){
        return ContainsPointUnchecked(point);
    }) != result.end();
}

bool Arc::ContainsPointUnchecked(Point point) {
    auto angle = NormalizeAngle(atan2(point.y - circle.ctr.y, point.x - circle.ctr.x));
    auto startAngle = NormalizeAngle(atan2(start.y - circle.ctr.y, start.x - circle.ctr.x));
    auto endAngle = NormalizeAngle(atan2(end.y - circle.ctr.y, end.x - circle.ctr.x));

    if (DoubleEquals(angle, startAngle)) return true;
    if (DoubleEquals(angle, endAngle)) return true;

    switch (direction) {
        case Clockwise:
            if(startAngle > endAngle)
                return InRangeExclusive(endAngle, angle, startAngle);
            return !InRangeExclusive(startAngle, angle, endAngle);
        case CounterClockwise:
            if(startAngle < endAngle)
                return InRangeExclusive(startAngle, angle, endAngle);
            return !InRangeExclusive(endAngle, angle, startAngle);
        default:
            throw exception("None occurred");
    }
}
