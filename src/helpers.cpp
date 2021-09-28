#include "helpers.h"

bool DoubleEquals(double x, double y) { return abs(x - y) < ZERO_THRESHOLD; }

double Limit(double x) {
    if (abs(x) < ZERO_THRESHOLD) return 0;
    if (abs(x) > INFINITY_THRESHOLD) return INFINITY;
    return x;
}

bool Infinity(double x) { return isinf(x); }

double DistanceBetween(Point a, Point b) { return sqrt(pow2(a.x - b.x) + pow2(a.y - b.y)); }

double DifferenceOfSquares(double operand1, double operand2) { return (operand1 + operand2) * (operand1 - operand2); }

vector<double> QuadraticEquation(double a, double b, double c) {
    auto delta = pow2(b) - 4 * a * c;
    if (delta < 0)
        return {};
    if (DoubleEquals(delta, 0))
        return {-b / (2 * a)};
    delta = sqrt(delta);
    return {(-b + delta) / (2 * a), (-b - delta) / (2 * a)};
}

bool SamePoint(Point a, Point b) { return DoubleEquals(a.x, b.x) && DoubleEquals(a.y, b.y); }

Point RelativePoint(Point start, double ratio, Point end) {
    return {start.x * (1 - ratio) + end.x * ratio, start.y * (1 - ratio) + end.y * ratio};
}

bool InRangeInclusive(double min, double target, double max) { return min <= target && target <= max; }

bool InRangeExclusive(double min, double target, double max) { return min < target && target < max; }

double NormalizeAngle(double rad) { return rad >= 0 ? rad : 2 * PI + rad; }

double Angle(Point a, Point b, Point c) {
    return atan2(a.y - b.y, a.x - b.x) - atan2(c.y - b.y, c.x - b.x);
}

double NormalizedAngle(Point a, Point b, Point c) {
    return NormalizeAngle(Angle(a, b, c));
}

Direction GetDirection(Point point, Point resolver, Point center, bool inverse) {
    if (SamePoint(point, resolver))
        throw exception("Can't determine the direction");

    auto i = inverse ? -1 : 1;

    if (DoubleEquals(point.y, center.y)) {
        if (point.x < resolver.x)
            i *= -1;
    } else {
        if (point.y < center.y)
            i *= -1;
        if (point.x < resolver.x)
            i *= -1;
    }

    return (Direction) i;
}

bool PointOnCircleEdge(Circle circle, Point point) {
    return DoubleEquals(DistanceBetween(point, circle.ctr), pow2(circle.r));
}

bool CircleContainsPoint(Circle circle, Point point) {
    return pow2(circle.ctr.x - point.x) + pow2(circle.ctr.y - point.y) < pow2(circle.r);
}
