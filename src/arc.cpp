#include "arc.h"

Arc::Arc(Point start, Point end, Direction direction, Circle circle)
        : start(direction == Clockwise ? start : end),
          end(direction == Clockwise ? end : start),
          circle(circle) {}

double Arc::Length() const {
    return NormalizedAngle(start, circle.ctr, end) * circle.r;
}

bool Arc::IntersectsWithCircle(Circle other) const {
    const auto intersectionLine = Line::IntersectionLineOfTwoCircles(circle, other);
    if (intersectionLine == nullptr)
        return false;

    const auto &result = intersectionLine->IntersectionWithCircle(circle);

    auto ret = !result.empty() && any_of(result.begin(), result.end(), [this](const Point &point) {
        return ContainsPointUnchecked(point);
    });

    delete intersectionLine;
    return ret;
}

bool Arc::ContainsPointUnchecked(Point point) const {
    const auto angle = NormalizeAngle(atan2(point.y - circle.ctr.y, point.x - circle.ctr.x));
    const auto startAngle = NormalizeAngle(atan2(start.y - circle.ctr.y, start.x - circle.ctr.x));
    const auto endAngle = NormalizeAngle(atan2(end.y - circle.ctr.y, end.x - circle.ctr.x));

    if (DoubleEquals(angle, startAngle)) return true;
    if (DoubleEquals(angle, endAngle)) return true;

    if (startAngle > endAngle)
        return InRangeExclusive(endAngle, angle, startAngle);
    return !InRangeExclusive(startAngle, angle, endAngle);
}
