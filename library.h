#ifndef PATH_FINDER_CPP_SHARED_LIBRARY_H
#define PATH_FINDER_CPP_SHARED_LIBRARY_H

#include "src/solver.h"

#define DLLEXPORT __declspec(dllexport)

extern "C" {

DLLEXPORT double ArcLength(Arc *arc);
DLLEXPORT bool ArcIntersectsWithCircle(Arc *arc, Circle *circle);

// Helpers
DLLEXPORT double DistanceBetween(Point *a, Point *b);
DLLEXPORT double DifferenceOfSquares_Internal(double operand1, double operand2);
DLLEXPORT size_t QuadraticEquation(double a, double b, double c, double **result);
DLLEXPORT bool SamePoint(Point *a, Point *b);
DLLEXPORT Point *RelativePoint(Point *start, double ratio, Point *end);
DLLEXPORT double Angle(Point *a, Point *b, Point *c);
DLLEXPORT Direction GetDirection(Point *point, Point *resolver, Point *center, bool inverse);
DLLEXPORT bool CircleContainsPoint(Circle *circle, Point *point);

#if INCLUDE_POINT_ON_CIRCLE_EDGE

DLLEXPORT bool PointOnCircleEdge(Circle *circle, Point *point);

#endif

// Line
DLLEXPORT Point *PointOfTangency(Circle *circle);
DLLEXPORT Line *IntersectionLineOfTwoCircles(Circle *a, Circle *b);
DLLEXPORT size_t Tangents(Point *point, Circle *circle, Line **result);
DLLEXPORT size_t CommonTangents(Circle *a, Circle *b, Line **result);

DLLEXPORT double Solve(Point *start, Point *end, Circle *circles, int count);

DLLEXPORT void FreePoint(Point *point);
DLLEXPORT void FreeCircle(Circle *circle);
DLLEXPORT void FreeLine(Line *line);

}

#endif //PATH_FINDER_CPP_SHARED_LIBRARY_H
