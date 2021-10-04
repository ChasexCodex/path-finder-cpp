#ifndef PATH_FINDER_CPP_HELPERS_H
#define PATH_FINDER_CPP_HELPERS_H

#include <cmath>
#include <vector>
#include "circle.h"
#include "direction.h"

using namespace std;

const double ZERO_THRESHOLD = 1.0E-10;
const double INFINITY_THRESHOLD = 1.0E+10;
const double PI = 3.14159265358979;

typedef const Point &PointRef;
typedef const Circle &CircleRef;

#define pow2(x) ((x)*(x))

bool DoubleEquals(double x, double y);
//#define DoubleEquals(x, y) (abs((x) - (y)) < ZERO_THRESHOLD)

#if USE_LIMIT
double Limit(double x);
#else
#define Limit(x) (x)
#endif
//bool Infinity(double x);

double DistanceBetween(PointRef a, PointRef b);

double DifferenceOfSquares(double operand1, double operand2);

vector<double> QuadraticEquation(double a, double b, double c);

bool SamePoint(PointRef a, PointRef b);

Point RelativePoint(PointRef start, double ratio, PointRef end);

bool InRangeInclusive(double min, double target, double max);
//#define InRangeInclusive(min, target, max) ((min) <= (target) && (target) <= (max))

bool InRangeExclusive(double min, double target, double max);
//#define InRangeExclusive(min, target, max) ((min) < (target) && (target) < (max))

double NormalizeAngle(double rad);
//#define NormalizeAngle(rad) ((rad) >= 0 ? (rad) : 2 * PI + (rad))

double Angle(PointRef a, PointRef b, PointRef c);

double NormalizedAngle(PointRef a, PointRef b, PointRef c);
//#define NormalizedAngle(a, b, c) (NormalizeAngle(Angle(a, b, c)))

Direction GetDirection(PointRef point, PointRef resolver, PointRef center, bool inverse = false);

bool CircleContainsPoint(CircleRef circle, PointRef point);

#if INCLUDE_POINT_ON_CIRCLE_EDGE

bool PointOnCircleEdge(CircleRef circle, PointRef point);

#endif

#endif //PATH_FINDER_CPP_HELPERS_H
