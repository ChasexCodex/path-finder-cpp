#ifndef PATH_FINDER_CPP_HELPERS_H
#define PATH_FINDER_CPP_HELPERS_H

#include <cmath>
#include <vector>
#include "circle.h"
#include "direction.h"

using namespace std;

// CONSTANTS
const double ZERO_THRESHOLD = 1.0E-10;
const double INFINITY_THRESHOLD = 1.0E+10;
const double PI = 3.14159265358979;

typedef const Point &PointRef;
typedef const Circle &CircleRef;

#if USE_MACROS

#define pow2(x) ((x)*(x))
#define DoubleEquals(x, y) (abs((x) - (y)) < ZERO_THRESHOLD)
#define DifferenceOfSquares(operand1, operand2) (((operand1) + (operand2)) * ((operand1) - (operand2)))
#define InRangeInclusive(min, target, max) ((min) <= (target) && (target) <= (max))
#define InRangeExclusive(min, target, max) ((min) < (target) && (target) < (max))
#define NormalizeAngle(rad) ((rad) >= 0 ? (rad) : 2 * PI + (rad))
#define NormalizedAngle(a, b, c) (NormalizeAngle(Angle(a, b, c)))

#else

double pow2(double x);
bool DoubleEquals(double x, double y);
double DifferenceOfSquares(double operand1, double operand2);
bool InRangeInclusive(double min, double target, double max);
bool InRangeExclusive(double min, double target, double max);
double NormalizeAngle(double rad);
double NormalizedAngle(PointRef a, PointRef b, PointRef c);

#endif

#if USE_LIMIT

double Limit(double x);

#else
#define Limit(x) (x)
#endif //USE_LIMIT

#if INCLUDE_POINT_ON_CIRCLE_EDGE

bool PointOnCircleEdge(CircleRef circle, PointRef point);

#endif //INCLUDE_POINT_ON_CIRCLE_EDGE

double DistanceBetween(PointRef a, PointRef b);

bool SamePoint(PointRef a, PointRef b);

bool CircleContainsPoint(CircleRef circle, PointRef point);

double Angle(PointRef a, PointRef b, PointRef c);

vector<double> QuadraticEquation(double a, double b, double c);

Point RelativePoint(PointRef start, double ratio, PointRef end);

Direction GetDirection(PointRef point, PointRef resolver, PointRef center, bool inverse = false);

#endif //PATH_FINDER_CPP_HELPERS_H
