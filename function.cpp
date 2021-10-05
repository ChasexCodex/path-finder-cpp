// SETTINGS
#define USE_BASIC_STRUCTURES 1


#if DEFAULT_MSVC
#define SAFE_THROW(message) (throw std::exception((message)))
#elif WSL_GCC
#define SAFE_THROW(message) (throw std::exception())
#endif


#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class Arc;
struct Circle;
struct CircleNode;
class Line;
struct Node;
struct Point;
class Segment;
class Solver;

enum Direction {
    Clockwise = 1,
    CounterClockwise = -1,
    None = 0
};

const double ZERO_THRESHOLD = 1.0E-10;
const double INFINITY_THRESHOLD = 1.0E+10;
const double PI = 3.14159265358979;

typedef const Point &PointRef;
typedef const Circle &CircleRef;
typedef std::pair<Node *, Node *> Connection;

#if USE_BASIC_STRUCTURES

struct Point {
    double x, y;

    Point() : x(0.0), y(0.0) {}

    Point(double x, double y) : x(x), y(y) {}
};

struct Circle {
    Point ctr;
    double r;

    Circle() : ctr(), r(1.0) {}

    Circle(Point c, double r) : ctr(c), r(r) {}

    Circle(double cx, double cy, double r) : ctr(cx, cy), r(r) {}
};

#endif

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

#if !USE_MACROS

double pow2(double x) { return x * x; }

bool DoubleEquals(double x, double y) {
    return abs(x - y) < ZERO_THRESHOLD;
}

double DifferenceOfSquares(double operand1, double operand2) {
    return (operand1 + operand2) * (operand1 - operand2);
}

bool InRangeInclusive(double min, double target, double max) {
    return min <= target && target <= max;
}

bool InRangeExclusive(double min, double target, double max) {
    return min < target && target < max;
}

double NormalizeAngle(double rad) {
    return rad >= 0 ? rad : 2 * PI + rad;
}

double NormalizedAngle(PointRef a, PointRef b, PointRef c) {
    return NormalizeAngle(Angle(a, b, c));
}

#else

#if USE_LIMIT

double Limit(double x) {
    if (abs(x) < ZERO_THRESHOLD) return 0;
    if (abs(x) > INFINITY_THRESHOLD) return INFINITY;
    return x;
}

#endif

double DistanceBetween(PointRef a, PointRef b) {
    return sqrt(pow2(a.x - b.x) + pow2(a.y - b.y));
}

bool SamePoint(PointRef a, PointRef b) {
    return DoubleEquals(a.x, b.x) && DoubleEquals(a.y, b.y);
}

double Angle(PointRef a, PointRef b, PointRef c) {
    return atan2(a.y - b.y, a.x - b.x) - atan2(c.y - b.y, c.x - b.x);
}

vector<double> QuadraticEquation(double a, double b, double c) {
    auto delta = pow2(b) - 4 * a * c;
    if (delta < 0)
        return {};
    if (DoubleEquals(delta, 0))
        return {-b / (2 * a)};
    delta = sqrt(delta);
    return {(-b + delta) / (2 * a), (-b - delta) / (2 * a)};
}

Point RelativePoint(PointRef start, double ratio, PointRef end) {
    return {start.x * (1 - ratio) + end.x * ratio, start.y * (1 - ratio) + end.y * ratio};
}

Direction GetDirection(PointRef point, PointRef resolver, PointRef center, bool inverse) {
    if (SamePoint(point, resolver))
#if DEFAULT_MSVC
        throw exception("None Occurred");
#elif WSL_GCC
    throw exception();
#endif

    auto i = inverse ? -1 : 1;

    if (DoubleEquals(point.y, center.y)) {
        if (point.x < resolver.x)
            i *= -1;
    } else {
        if (point.y < center.y)
            i *= -1;
        if (point.x < resolver.x)
            i *= -1;
    }

    return (Direction) i;
}

#if INCLUDE_POINT_ON_CIRCLE_EDGE

bool PointOnCircleEdge(CircleRef circle, PointRef point) {
    return DoubleEquals(pow2(circle.ctr.x - point.x) + pow2(circle.ctr.y - point.y), pow2(circle.r));
}

#endif

bool CircleContainsPoint(CircleRef circle, PointRef point) {
    return pow2(circle.ctr.x - point.x) + pow2(circle.ctr.y - point.y) < pow2(circle.r);
}

#endif // !USE_MACROS

class Arc {
    const Point start;
    const Point end;
    const Circle circle;

private:
    [[nodiscard]] bool ContainsPointUnchecked(Point point) const;

public:
    Arc(Point start, Point end, Direction direction, Circle circle);

    [[nodiscard]] double Length() const;

    [[nodiscard]] bool IntersectsWithCircle(Circle other) const;
};

struct CircleNode {
    bool generated = false;
    const Circle circle;
    std::vector<Connection> connections{};

    void AddConnection(Connection connection);

    explicit CircleNode(Circle circle);
};

class Line {
    double slope;
    double offset;

    [[nodiscard]] double DistanceFrom(PointRef point) const;

    [[nodiscard]] double GetY(double x) const;

public:
    Line(double slope, double offset);

    Line(PointRef a, PointRef b);

    Line(double slope, PointRef has);

    [[nodiscard]] bool PassesByPoint(PointRef point) const;

public:
    [[nodiscard]] Point PointOfTangency(CircleRef circle) const;

    [[nodiscard]] vector<Point> IntersectionWithCircle(CircleRef circle) const;

    static Line *IntersectionLineOfTwoCircles(CircleRef a, CircleRef b);

    static vector<Line> Tangents(PointRef point, CircleRef circle);

    static vector<Line> CommonTangents(CircleRef a, CircleRef b);
};

struct Node {
    double distance = INFINITY;
    double heuristic = 0;
    bool visited = false;
    CircleNode *container = nullptr;
    Node *parent = nullptr;
    Direction presetDirection = None;
    Point point;

    Node(Point point, CircleNode *container, Point end);

    bool SetNewDistance(double newDistance);

    [[nodiscard]] Direction GetDirection(Point resolver, bool inverse = false) const;

    [[nodiscard]] Direction GetDirectionParent() const;;

    [[nodiscard]] Arc MakeArc(Point end) const;

#if ASTAR

    [[nodiscard]] double EstimatedLength() const;

#endif

    void SetDirection(Direction direction);
};

class Segment : Line {
    Point start;
    Point end;

public:
    Segment(Point start, Point end);

    bool ContainsPoint(Point point);

    bool IntersectsWithCircle(Circle circle);
};

class Solver {
    Node *begin;
    Node *finish;

    vector<CircleNode *> obstacles{};
    vector<Node *> nodes{};
    vector<Node *> beginConnections{};

    pair<double, bool> StartSolving();

    void GenerateMap();

    void GenerateCircleNodeConnections(CircleNode *circleNode);

    vector<Node *> Search(Node *node);

    Node *CreateNode(Point point, CircleNode *container, Point end);

public:
    Solver(Point start, Point end, vector<Circle> obstacles);

    double Solve();

    ~Solver();
};

Arc::Arc(Point start, Point end, Direction direction, Circle circle)
        : start(direction == Clockwise ? start : end),
          end(direction == Clockwise ? end : start),
          circle(circle) {}

double Arc::Length() const {
    return NormalizedAngle(start, circle.ctr, end) * circle.r;
}

bool Arc::IntersectsWithCircle(Circle other) const {
    auto intersectionLine = Line::IntersectionLineOfTwoCircles(circle, other);
    if (intersectionLine == nullptr)
        return false;

    auto result = intersectionLine->IntersectionWithCircle(circle);
    delete intersectionLine;

    return any_of(result.begin(), result.end(), [this](const Point &point) {
        return ContainsPointUnchecked(point);
    });
}

bool Arc::ContainsPointUnchecked(Point point) const {
    const auto angle = NormalizeAngle(atan2(point.y - circle.ctr.y, point.x - circle.ctr.x));
    const auto startAngle = NormalizeAngle(atan2(start.y - circle.ctr.y, start.x - circle.ctr.x));
    const auto endAngle = NormalizeAngle(atan2(end.y - circle.ctr.y, end.x - circle.ctr.x));

    if (DoubleEquals(angle, startAngle)) return true;
    if (DoubleEquals(angle, endAngle)) return true;

    if (startAngle > endAngle)
        return InRangeExclusive(endAngle, angle, startAngle);
    return !InRangeExclusive(startAngle, angle, endAngle);
}

void CircleNode::AddConnection(Connection connection) {
    connections.push_back(connection);
}

CircleNode::CircleNode(Circle circle) : circle(circle) {}

Line::Line(double slope, double offset) : slope(Limit(slope)), offset(offset) {}

Line::Line(PointRef a, PointRef b) {
    if (SamePoint(a, b))
        throw exception();
    slope = Limit(((a.y - b.y) / (a.x - b.x)));
    if (isinf(slope))
        offset = a.x;
    else
        offset = a.y - slope * a.x;
}

Line::Line(double slope, PointRef has) : slope(Limit(slope)) {
    if (isinf(slope))
        offset = has.x;
    else
        offset = has.y - slope * has.x;
}

double Line::DistanceFrom(PointRef point) const {
    if (isinf(slope))
        return abs(point.x - offset);
    return abs(slope * point.x - point.y + offset) / sqrt(pow2(slope) + 1);
}

double Line::GetY(double x) const {
    if (isinf(slope))
        SAFE_THROW("NaN occurred");
    return x * slope + offset;
}

bool Line::PassesByPoint(PointRef point) const {
    if (isinf(slope))
        return DoubleEquals(point.x, offset);
    return DoubleEquals(point.x * slope + offset, point.y);
}

Point Line::PointOfTangency(CircleRef circle) const {
    if (isinf(slope))
        return {offset, circle.ctr.y};
    auto x = (circle.ctr.x - slope * (offset - circle.ctr.y)) / (1 + pow2(slope));
    return {x, GetY(x)};
}

vector<Point> Line::IntersectionWithCircle(CircleRef circle) const {
    double distance = DistanceFrom(circle.ctr);
    if (isnan(distance))
        throw exception();
    if (distance > circle.r)
        return {};
    if (DoubleEquals(distance, circle.r))
        return {PointOfTangency(circle)};

    vector<double> axis;
    vector<Point> ret;

    if (isinf(slope)) {
        axis = QuadraticEquation(
                1,
                -2 * circle.ctr.y,
                pow2(circle.ctr.y) + DifferenceOfSquares(offset - circle.ctr.x, circle.r));
        transform(axis.begin(), axis.end(), back_inserter(ret), [this](double y) {
            return Point(offset, y);
        });
    } else {
        axis = QuadraticEquation(
                1 + pow2(slope),
                2 * (-circle.ctr.x + slope * (offset - circle.ctr.y)),
                pow2(circle.ctr.x) + DifferenceOfSquares(offset - circle.ctr.y, circle.r));
        transform(axis.begin(), axis.end(), back_inserter(ret), [this](double x) {
            return Point(x, GetY(x));
        });
    }


    return ret;
}

Line *Line::IntersectionLineOfTwoCircles(CircleRef a, CircleRef b) {
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

vector<Line> Line::Tangents(PointRef point, CircleRef circle) {
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

vector<Line> Line::CommonTangents(CircleRef a, CircleRef b) {
    auto distance = DistanceBetween(a.ctr, b.ctr);

    if (DoubleEquals(distance, 0))
        return {};

    CircleRef biggest = a.r > b.r ? a : b;
    CircleRef smallest = a.r < b.r ? a : b;

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
            for (const auto _offset: result) {
                ret.emplace_back(cross.slope, _offset);
            }
        }
    } else {
        double r1 = smallest.r / biggest.r;
        double r2 = 1 - r1;
        Point point((smallest.ctr.x - biggest.ctr.x * r1) / r2, (smallest.ctr.y - biggest.ctr.y * r1) / r2);
        auto result = Tangents(point, a);
        ret.insert(ret.end(), result.begin(), result.end());
    }

    if (distance < radii || DoubleEquals(distance, radii))
        return ret;

//    if (DoubleEquals(distance, radii))
//        ret.emplace_back(-(a.ctr.x - b.ctr.x) / (a.ctr.y - b.ctr.y), RelativePoint(a.ctr, a.r / radii, b.ctr));
//    else {
    auto result = Tangents(RelativePoint(a.ctr, a.r / radii, b.ctr), smallest);
    ret.insert(ret.end(), result.begin(), result.end());
//    }

    return ret;
}

Node::Node(Point point, CircleNode *container, Point end)
        : point(point.x, point.y), container(container) {
    heuristic = DistanceBetween(point, end);
}

bool Node::SetNewDistance(double newDistance) {
    if (distance > newDistance) {
        distance = newDistance;
        return true;
    }

    return false;
}

Direction Node::GetDirection(Point resolver, bool inverse) const {
    return presetDirection ? presetDirection : ::GetDirection(point, resolver, container->circle.ctr, inverse);
}

Direction Node::GetDirectionParent() const {
    return presetDirection ? presetDirection : ::GetDirection(point, parent->point, container->circle.ctr);
}

Arc Node::MakeArc(Point end) const {
    return Arc{point, end, GetDirectionParent(), container->circle};
}

#if ASTAR

double Node::EstimatedLength() const { return distance + heuristic; }

#endif

void Node::SetDirection(Direction direction) {
    presetDirection = direction;
}

Segment::Segment(Point start, Point end) : Line(start, end), start(start), end(end) {}

bool Segment::ContainsPoint(Point point) {
    return PassesByPoint(point) &&
           InRangeInclusive(min(start.x, end.x), point.x, max(start.x, end.x)) &&
           InRangeInclusive(min(start.y, end.y), point.y, max(start.y, end.y));
}

bool Segment::IntersectsWithCircle(Circle circle) {
    if (CircleContainsPoint(circle, start))
        return true;
    if (CircleContainsPoint(circle, end))
        return true;
    const auto &result = IntersectionWithCircle(circle);

    return !result.empty() && any_of(result.begin(), result.end(), [this](Point point) {
        return ContainsPoint(point);
    });
}

Solver::Solver(Point start, Point end, vector<Circle> _obstacles) {
    begin = new Node(start, nullptr, end);
    finish = new Node(end, nullptr, end);
    transform(_obstacles.begin(), _obstacles.end(), back_inserter(obstacles), [](const Circle &circle) {
        return new CircleNode(circle);
    });
}

double Solver::Solve() {
    const auto result = StartSolving();
    if (result.second)
        return result.first;

    auto comparer = [](const Node *const lhs, const Node *const rhs) {
#if ASTAR
        return lhs->EstimatedLength() < rhs->EstimatedLength();
#elif DIJKSTRA
        return lhs->distance < rhs->distance;
#endif
    };
    bool found;
#if ASTAR
    vector<Node *> paths(beginConnections.begin(), beginConnections.end());
    while (!paths.empty()) {
        sort(paths.begin(), paths.end(), comparer);
        auto newNodes = Search(paths[0]);
        paths.erase(paths.begin());
        found = !isinf(finish->distance);
        for (auto &item: newNodes) {
            paths.push_back(item);
        }
        if (!found) continue;
        auto pend = remove_if(paths.begin(), paths.end(), [this](const Node *const node) {
            return node->EstimatedLength() >= finish->distance;
        });
        paths.erase(pend, paths.end());
    }
#elif DIJKSTRA
    while(true) {
        sort(nodes.begin(),  nodes.end(), comparer);
        auto first = find_if(nodes.begin(),  nodes.end(), [this](Node * node){
            return !node->visited && node->distance < finish->distance;
        });
        if(first == nodes.end())
            break;
        Search(*first);
        found = !isinf(finish->distance);
    }
#endif

    return found ? finish->distance : -1;
}

pair<double, bool> Solver::StartSolving() {
    auto illegalPoint = [](Point point) {
        return [point](CircleNode *circleNode) {
            return CircleContainsPoint(circleNode->circle, point);
        };
    };

    if (any_of(obstacles.begin(), obstacles.end(), illegalPoint(begin->point)))
        return {-1, true};
    if (any_of(obstacles.begin(), obstacles.end(), illegalPoint(finish->point)))
        return {-1, true};


    Segment cross(begin->point, finish->point);
    auto crossIntersect = [&cross](CircleNode *circleNode) {
        return cross.IntersectsWithCircle(circleNode->circle);
    };

    if (!any_of(obstacles.begin(), obstacles.end(), crossIntersect)) {
        return {DistanceBetween(begin->point, finish->point), true};
    }

    GenerateMap();
    return {0, false};
}

void Solver::GenerateMap() {
    auto size = obstacles.size();
    for (int i = 0; i < size; i++) {
        auto obstacle = obstacles[i];
        // begin connections

#if INCLUDE_POINT_ON_CIRCLE_EDGE
        if (PointOnCircleEdge(obstacle->circle, begin->point)) {
            for (auto direction: {Clockwise, CounterClockwise}) {
                auto node = CreateNode(begin->point, obstacle, finish->point);
                node->SetDirection(direction);
                node->SetNewDistance(0);
                beginConnections.push_back(node);
            }
        } else
#endif

            for (auto tangent: Line::Tangents(begin->point, obstacle->circle)) {
                auto pointOfTangency = tangent.PointOfTangency(obstacle->circle);
                Segment segment(begin->point, pointOfTangency);

                bool skip = false;
                for (int j = 0; j < size; j++) {
                    if (i == j) continue;
                    if (segment.IntersectsWithCircle(obstacles[j]->circle)) {
                        skip = true;
                        break;
                    }
                }

                if (skip) continue;

                auto node = CreateNode(pointOfTangency, obstacles[i], finish->point);
                node->SetNewDistance(DistanceBetween(begin->point, pointOfTangency));
                node->parent = begin;
                beginConnections.push_back(node);
            }

        // finish connections
#if INCLUDE_POINT_ON_CIRCLE_EDGE
        if (PointOnCircleEdge(obstacle->circle, finish->point)) {
            for (auto direction: {Clockwise, CounterClockwise}) {
                auto node = CreateNode(finish->point, obstacle, finish->point);
                node->SetDirection(direction);
                obstacle->AddConnection({node, finish});
            }
        } else
#endif

            for (auto tangent: Line::Tangents(finish->point, obstacle->circle)) {
                auto pointOfTangency = tangent.PointOfTangency(obstacle->circle);
                Segment segment(pointOfTangency, finish->point);

                bool skip = false;
                for (int j = 0; j < size; j++) {
                    if (i == j) continue;
                    if (segment.IntersectsWithCircle(obstacles[j]->circle)) {
                        skip = true;
                        break;
                    }
                }

                if (skip) continue;

                auto node = CreateNode(pointOfTangency, obstacles[i], finish->point);
                obstacles[i]->AddConnection({node, finish});
            }
    }
}

void Solver::GenerateCircleNodeConnections(CircleNode *circleNode) {
    circleNode->generated = true;
    for (auto obstacle: obstacles) {
        if (obstacle->generated)
            continue;
        for (auto tangent: Line::CommonTangents(circleNode->circle, obstacle->circle)) {
            auto pot1 = tangent.PointOfTangency(circleNode->circle);
            auto pot2 = tangent.PointOfTangency(obstacle->circle);
            Segment segment(pot1, pot2);

            bool skip = false;
            for (const auto other: obstacles) {
                if (other == circleNode || other == obstacle)
                    continue;
                if (segment.IntersectsWithCircle(other->circle)) {
                    skip = true;
                    break;
                }
            }

            if (skip) continue;

            auto node1 = CreateNode(pot1, circleNode, finish->point);
            auto node2 = CreateNode(pot2, obstacle, finish->point);
            circleNode->AddConnection({node1, node2});
            obstacle->AddConnection({node2, node1});
        }
    }
}

vector<Node *> Solver::Search(Node *node) {
    vector<Node *> ret;
    if (node->visited)
        return ret;

    node->visited = true;
    if (!node->container->generated)
        GenerateCircleNodeConnections(node->container);
    auto connections = node->container->connections;
    vector<Connection> connectionsFiltered;
    copy_if(connections.begin(), connections.end(), back_inserter(connectionsFiltered), [](Connection conn) {
        return !(conn.first->visited || conn.second->visited);
    });
    Point target{2.0853057149744103, -7.4292004868520394};
    for (auto tuple: connectionsFiltered) {
        auto item1 = tuple.first;
        auto item2 = tuple.second;

        if (node->GetDirectionParent() != item1->GetDirection(item2->point, true))
            continue;

        Arc arc = node->MakeArc(item1->point);
        bool skip = false;
        for (const auto obstacle: obstacles) {
            if (obstacle == node->container)
                continue;
            if (arc.IntersectsWithCircle(obstacle->circle)) {
                skip = true;
                break;
            }
        }

        if (skip) continue;

        auto length = arc.Length() + node->distance;

        if (item1->SetNewDistance(length)) {
            item1->parent = node;
            if (item2->SetNewDistance(DistanceBetween(item1->point, item2->point) + length)) {
                item2->parent = item1;
                ret.push_back(item2);
            }
        }
    }

    return ret;
}

Node *Solver::CreateNode(Point point, CircleNode *container, Point end) {
    auto node = new Node(point, container, end);
    nodes.push_back(node);
    return node;
}

Solver::~Solver() {
    delete begin;
    delete finish;
    for (auto obstacle: obstacles)
        delete obstacle;
    for (auto node: nodes)
        delete node;
}

double solve(Point start, Point end, vector<Circle> obstacle) {
    return Solver(start, end, move(obstacle)).Solve();
}