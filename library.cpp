#include "library.h"

double ArcLength(Arc *arc) {
    return arc->Length();
}

bool ArcIntersectsWithCircle(Arc *arc, Circle *circle) {
    return arc->IntersectsWithCircle(*circle);
}


double DistanceBetween(Point *a, Point *b) {
    return DistanceBetween(*a, *b);
}

double DifferenceOfSquares_Internal(double operand1, double operand2) {
    return DifferenceOfSquares(operand1, operand2);
}

size_t QuadraticEquation(double a, double b, double c, double **result) {
    auto res = QuadraticEquation(a, b, c);
    *result = new double[res.size()];
    for (int i = 0; i < res.size(); ++i) {
        (*result)[i] = res[i];
    }
    return res.size();
}

bool SamePoint(Point *a, Point *b) {
    return SamePoint(*a, *b);
}

Point* RelativePoint(Point *start, double ratio, Point *end) {
    auto res = RelativePoint(*start, ratio, *end);
    auto ref = new Point;
    *ref = res;
    return ref;
}

double Angle(Point *a, Point *b, Point *c) {
    return Angle(*a, *b, *b);
}

Direction GetDirection(Point *point, Point *resolver, Point *center, bool inverse) {
    return GetDirection(*point, *resolver, *center, inverse);
}

bool CircleContainsPoint(Circle *circle, Point *point) {
    return CircleContainsPoint(*circle, *point);
}

#if INCLUDE_POINT_ON_CIRCLE_EDGE

bool PointOnCircleEdge(Circle *circle, Point *point) {
    return PointOnCircleEdge(*circle, *point);
}

#endif

double Solve(Point *start, Point *end, Circle **circles, int count) {
    vector<Circle> obstacles(*circles, *circles + count);
    return Solver(*start, *end, obstacles).Solve();
}

Point *PointOfTangency(Line* line, Circle *circle) {
    auto ref = new Point;
    *ref = line->PointOfTangency(*circle);
    return ref;
}

Line *IntersectionLineOfTwoCircles(Circle *a, Circle *b) {
    return Line::IntersectionLineOfTwoCircles(*a, *b);
}

size_t Tangents(Point *point, Circle *circle, Line **result) {
    auto res = Line::Tangents(*point, *circle);
    *result = res.data();
    return res.size();
}

size_t CommonTangents(Circle *a, Circle *b, Line **result) {
    auto res = Line::CommonTangents(*a, *b);
    *result = res.data();
    return res.size();
}

void FreePoint(Point *point) {
    delete point;
}

void FreeCircle(Circle *circle) {
    delete circle;
}

void FreeLine(Line *line) {
    delete line;
}
