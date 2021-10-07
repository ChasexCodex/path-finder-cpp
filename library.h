#ifndef PATH_FINDER_CPP_SHARED_LIBRARY_H
#define PATH_FINDER_CPP_SHARED_LIBRARY_H

#include "src/solver.h"

#define DLLEXPORT __declspec(dllexport)

extern "C" {

DLLEXPORT double ArcLength_External(Arc arc);
DLLEXPORT bool ArcIntersectsWithCircle_External(Arc arc, Circle circle);

// Helpers
DLLEXPORT double DistanceBetween_External(Point a, Point b);
DLLEXPORT double DifferenceOfSquares_External(double operand1, double operand2);
DLLEXPORT size_t QuadraticEquation_External(double a, double b, double c, double **result);
DLLEXPORT bool SamePoint_External(Point a, Point b);
DLLEXPORT Point* RelativePoint_External(Point start, double ratio, Point end);
DLLEXPORT double Angle_External(Point a, Point b, Point c);
DLLEXPORT Direction GetDirection_External(Point point, Point resolver, Point center, bool inverse);
DLLEXPORT bool CircleContainsPoint_External(Circle circle, Point point);

#if INCLUDE_POINT_ON_CIRCLE_EDGE

DLLEXPORT bool PointOnCircleEdge_External(Circle circle, Point point);

#endif

// Line
DLLEXPORT Point *PointOfTangency_External(Line line, Circle circle);
DLLEXPORT Line *IntersectionLineOfTwoCircles_External(Circle a, Circle b);
DLLEXPORT size_t Tangents_External(Point point, Circle circle, Line **result);
DLLEXPORT size_t CommonTangents_External(Circle a, Circle b, Line **result);

DLLEXPORT double solve_External(Point start, Point end, double* xs, double* ys, double* rs, int count);

DLLEXPORT void FreePoint_External(Point *point);
DLLEXPORT void FreeCircle_External(Circle *circle);
DLLEXPORT void FreeLine_External(Line *line);

}

#endif //PATH_FINDER_CPP_SHARED_LIBRARY_H
