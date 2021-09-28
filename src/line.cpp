#include "line.h"

//double Line::PerpendicularSlope() {
//    return -1 / slope;
//}

Line::Line(double slope, double offset)
        : slope(Limit(slope)), offset(offset) {}

Line::Line(Point a, Point b) {
    if (SamePoint(a, b))
        throw exception("Same Point");
    slope = Limit(((a.y - b.y) / (a.x - b.x)));
    if (isinf(slope))
        offset = a.x;
    else
        offset = a.y - slope * a.x;
}

Line::Line(double slope, Point has) : slope(Limit(slope)) {
    if (isinf(slope))
        offset = has.x;
    else
        offset = has.y - slope * has.x;
}

//Line Line::PerpendicularAt(Point point) {
//    return {PerpendicularSlope(), point};
//}

double Line::DistanceFrom(Point point) {
    return abs(slope * point.x - point.y + offset) / sqrt(pow2(slope) + 1);
}

//double Line::GetX(double y) {
//    if (slope == 0)
//        return NAN;
//    return (y - offset) / slope;
//}

double Line::GetY(double x) {
    if (isinf(slope))
        return NAN;
    return x * slope + offset;
}

bool Line::PassesByPoint(Point point) {
    if (isinf(slope))
        return DoubleEquals(point.x, offset);
    return DoubleEquals(point.x * slope + offset, point.y);
}

//Point *Line::IntersectionWithLine(Line line) {
//    if (DoubleEquals(slope, line.slope))
//        return nullptr;
//    if (slope == 0)
//        return new Point(line.GetX(offset), offset);
//    if (isinf(slope))
//        return new Point(offset, line.GetY(offset));
//    double x = -(offset - line.offset) / (slope - line.slope);
//    return new Point(x, GetY(x));
//}

Line *Line::IntersectionLineOfTwoCircles(Circle a, Circle b) {
    auto distance = DistanceBetween(a.ctr, b.ctr);
    if (DoubleEquals(distance, 0))
        return nullptr;
    auto radii = a.r + b.r;
    if (distance > radii)
        return nullptr;
    if (DoubleEquals(distance, radii)) {
        return new Line(
                -(a.ctr.x - b.ctr.x) / (a.ctr.y - b.ctr.y),
                RelativePoint(a.ctr, a.r / (radii), b.ctr));
    }

    if (DoubleEquals(a.ctr.y, b.ctr.y))
        return new Line(INFINITY, ((b.ctr.x + a.ctr.x) + DifferenceOfSquares(a.r, b.r) / (b.ctr.x - a.ctr.x)) / 2);
    return new Line((a.ctr.x - b.ctr.x) / (a.ctr.y - b.ctr.y),
                    (DifferenceOfSquares(b.ctr.x, a.ctr.x) + DifferenceOfSquares(b.ctr.y, a.ctr.y) +
                     DifferenceOfSquares(a.r, b.r))
                    / (2 * (b.ctr.y - a.ctr.y)));
}

Point Line::PointOfTangency(Circle circle) {
    if (isinf(slope))
        return {offset, circle.ctr.y};
    auto x = (circle.ctr.x - slope * (offset - circle.ctr.y)) / (1 + pow2(slope));
    return {x, GetY(x)};
}

vector<Point> Line::IntersectionWithCircle(Circle circle) {
    double distance = DistanceFrom(circle.ctr);
    if (distance > circle.r)
        return {};
    if (DoubleEquals(distance, circle.r))
        return {PointOfTangency(circle)};

    vector<double> xs;

    if (isinf(slope)) {
        xs = QuadraticEquation(
                1,
                -2 * circle.ctr.y,
                pow2(circle.ctr.y) + DifferenceOfSquares(offset - circle.ctr.x, circle.r));
    } else {
        xs = QuadraticEquation(
                1 + pow2(slope),
                2 * (-circle.ctr.x + slope * (offset - circle.ctr.y)),
                pow2(circle.ctr.x) + DifferenceOfSquares(offset - circle.ctr.y, circle.r));
    }

    vector<Point> ret;
    transform(xs.begin(), xs.end(), back_inserter(ret), [this](double x) {
        return Point(x, GetY(x));
    });
    return ret;
}

vector<Line> Line::Tangents(Point point, Circle circle) {
    double distance = DistanceBetween(point, circle.ctr);

    if (distance < circle.r)
        return {};

    double angle = atan((point.y - circle.ctr.y) / (point.x - circle.ctr.x));
    double extraAngle = atan(circle.r / sqrt(DifferenceOfSquares(distance, circle.r)));

    return {
            Line(tan(angle + extraAngle), point),
            Line(tan(angle - extraAngle), point),
    };
}

vector<Line> Line::CommonTangents(Circle a, Circle b) {
    auto distance = DistanceBetween(a.ctr, b.ctr);

    if (DoubleEquals(distance, 0))
        return {};

    Circle &biggest = a.r > b.r ? a : b;
    Circle &smallest = a.r < b.r ? a : b;

    if (distance + smallest.r <= biggest.r)
        return {};

    vector<Line> ret;
    double radii = a.r + b.r;

    if (DoubleEquals(a.r, b.r)) {
        if (DoubleEquals(a.ctr.x, b.ctr.x)) {
            ret.emplace_back(INFINITY, a.ctr.x + a.r);
            ret.emplace_back(INFINITY, a.ctr.x - a.r);
        } else {
            Line cross(a.ctr, b.ctr);
            vector<double> result = QuadraticEquation(
                    1,
                    -2 * cross.offset,
                    pow2(cross.offset) - pow2(a.r) * (1 + pow2(cross.slope)));
            vector<Line> add;
            transform(result.begin(), result.end(), back_inserter(add), [cross](double _offset) {
                return Line(cross.slope, _offset);
            });
            ret.insert(ret.end(), add.begin(), add.end());
        }
    } else {
        double r1 = smallest.r / biggest.r;
        double r2 = 1 - r1;
        Point point((smallest.ctr.x - biggest.ctr.x * r1) / r2, (smallest.ctr.y - biggest.ctr.y * r1) / r2);
        auto result = Tangents(point, a);
        ret.insert(ret.end(), result.begin(), result.end());
    }

    if (distance < radii)
        return ret;

    if (DoubleEquals(distance, radii))
        ret.emplace_back(-(a.ctr.x - b.ctr.x) / (a.ctr.y - b.ctr.y), RelativePoint(a.ctr, a.r / radii, b.ctr));
    else {
        auto result = Tangents(RelativePoint(a.ctr, a.r / radii, b.ctr), smallest);
        ret.insert(ret.end(), result.begin(), result.end());
    }

    return ret;
}
