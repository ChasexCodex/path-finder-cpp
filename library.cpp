#include "library.h"

double ArcLength_External(Arc arc) {
    return arc.Length();
}

bool ArcIntersectsWithCircle_External(Arc arc, Circle circle) {
    return arc.IntersectsWithCircle(circle);
}


//double DistanceBetween(Point *a, Point *b) {
//    return DistanceBetween(*a, *b);
//}

double DistanceBetween_External(Point a, Point b) {
    return DistanceBetween(a, b);
}

double DifferenceOfSquares_External(double operand1, double operand2) {
    return DifferenceOfSquares(operand1, operand2);
}

size_t QuadraticEquation_External(double a, double b, double c, double **result) {
    auto res = QuadraticEquation(a, b, c);
    *result = new double[res.size()];
    for (int i = 0; i < res.size(); ++i) {
        (*result)[i] = res[i];
    }
    return res.size();
}

//bool SamePoint(Point *a, Point *b) {
//    return SamePoint(*a, *b);
//}

bool SamePoint_External(Point a, Point b) {
    return SamePoint(a, b);
}

Point* RelativePoint_External(Point start, double ratio, Point end) {
    auto res = RelativePoint(start, ratio, end);
    auto ref = new Point(res);
    return ref;
}

//double Angle(Point *a, Point *b, Point *c) {
//    return Angle(*a, *b, *b);
//}

double Angle_External(Point a, Point b, Point c) {
    return Angle(a, b, c);
}

//Direction GetDirection(Point *point, Point *resolver, Point *center, bool inverse) {
//    return GetDirection(*point, *resolver, *center, inverse);
//}

Direction GetDirection_External(Point point, Point resolver, Point center, bool inverse) {
    return GetDirection(point, resolver, center, inverse);
}

//bool CircleContainsPoint(Circle *circle, Point *point) {
//    return CircleContainsPoint(*circle, *point);
//}

bool CircleContainsPoint_External(Circle circle, Point point) {
    return CircleContainsPoint(circle, point);
}

#if INCLUDE_POINT_ON_CIRCLE_EDGE

//bool PointOnCircleEdge(Circle *circle, Point *point) {
//    return PointOnCircleEdge(*circle, *point);
//}

bool PointOnCircleEdge_External(Circle circle, Point point) {
    return PointOnCircleEdge(circle, point);
}

#endif

//double solve(Point *start, Point *end, Circle **circles, int count) {
//    vector<Circle> obstacles(*circles, *circles + count);
//    return Solver(*start, *end, obstacles).Solve();
//}

// break
double solve_External(Point start, Point end, double* xs, double* ys, double* rs, int count) {
    vector<Circle> obstacles(count);
    for (int i = 0; i < count; ++i) {
        obstacles[i] = Circle(xs[i], ys[i], rs[i]);
    }
    return Solver(start, end, obstacles).Solve();
}

Point *PointOfTangency(Line line, Circle circle) {
    auto ref = new Point;
    *ref = line.PointOfTangency(circle);
    return ref;
}

//Line *IntersectionLineOfTwoCircles(Circle *a, Circle *b) {
//    return Line::IntersectionLineOfTwoCircles(*a, *b);
//}

Line *IntersectionLineOfTwoCircles_External(Circle a, Circle b) {
    return Line::IntersectionLineOfTwoCircles(a, b);
}

//size_t Tangents(Point *point, Circle *circle, Line **result) {
//    auto res = Line::Tangents(*point, *circle);
//    *result = res.data();
//    return res.size();
//}

size_t Tangents_External(Point point, Circle circle, Line **result) {
    auto res = Line::Tangents(point, circle);
    *result = res.data();
    return res.size();
}

//size_t CommonTangents(Circle *a, Circle *b, Line **result) {
//    auto res = Line::CommonTangents(*a, *b);
//    *result = res.data();
//    return res.size();
//}

size_t CommonTangents_External(Circle a, Circle b, Line **result) {
    auto res = Line::CommonTangents(a, b);
    *result = res.data();
    return res.size();
}

void FreePoint_External(Point *point) {
    delete point;
}

void FreeCircle_External(Circle *circle) {
    delete circle;
}

void FreeLine_External(Line *line) {
    delete line;
}
