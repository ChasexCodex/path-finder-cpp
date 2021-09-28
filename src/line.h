#ifndef PATH_FINDER_CPP_LINE_H
#define PATH_FINDER_CPP_LINE_H

#include <algorithm>
#include <iterator>
#include "helpers.h"

struct Line {
    double slope;
    double offset;

    double PerpendicularSlope();

    Line(double slope, double offset);

    Line(Point a, Point b);

    Line(double slope, Point has);

    Line PerpendicularAt(Point point);

    double DistanceFrom(Point point);

    double GetX(double y);

    double GetY(double x);

    bool PassesByPoint(Point point);

    Point *IntersectionWithLine(Line line);

    static Line *IntersectionLineOfTwoCircles(Circle a, Circle b);

    Point PointOfTangency(Circle circle);

    vector<Point> IntersectionWithCircle(Circle circle);

    static vector<Line> Tangents(Point point, Circle circle);

    static vector<Line> CommonTangents(Circle a, Circle b);
};

#endif //PATH_FINDER_CPP_LINE_H
