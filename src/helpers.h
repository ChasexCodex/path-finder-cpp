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

#define pow2(x) pow(x, 2)

bool DoubleEquals(double x, double y);

double Limit(double x);

bool Infinity(double x);

double DistanceBetween(Point a, Point b);

double DifferenceOfSquares(double operand1, double operand2);

vector<double> QuadraticEquation(double a, double b, double c);

bool SamePoint(Point a, Point b);

Point RelativePoint(Point start, double ratio, Point end);

bool InRangeInclusive(double min, double target, double max);

bool InRangeExclusive(double min, double target, double max);

double NormalizeAngle(double rad);

double Angle(Point a, Point b, Point c);

double NormalizedAngle(Point a, Point b, Point c);

Direction GetDirection(Point point, Point resolver, Point center, bool inverse = false);

bool CircleContainsPoint(Circle circle, Point point);

bool PointOnCircleEdge(Circle circle, Point point);

#endif //PATH_FINDER_CPP_HELPERS_H
