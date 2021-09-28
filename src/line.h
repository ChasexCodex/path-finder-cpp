#ifndef PATH_FINDER_CPP_LINE_H
#define PATH_FINDER_CPP_LINE_H

#include <algorithm>
#include <iterator>
#include "helpers.h"

struct Line {
    double slope;
    double offset;

//    double PerpendicularSlope();

    Line(double slope, double offset);

    Line(PointRef a, PointRef b);

    Line(double slope, PointRef has);

//    Line PerpendicularAt(Point point);

    [[nodiscard]] double DistanceFrom(PointRef point) const;

//    double GetX(double y);

    [[nodiscard]] double GetY(double x) const;

    [[nodiscard]] bool PassesByPoint(PointRef point) const;

//    Point *IntersectionWithLine(Line line);

    [[nodiscard]] Point PointOfTangency(CircleRef circle) const;

    [[nodiscard]] vector<Point> IntersectionWithCircle(CircleRef circle) const;

    static Line *IntersectionLineOfTwoCircles(CircleRef a, CircleRef b);

    static vector<Line> Tangents(PointRef point, CircleRef circle);

    static vector<Line> CommonTangents(CircleRef a, CircleRef b);
};

#endif //PATH_FINDER_CPP_LINE_H
