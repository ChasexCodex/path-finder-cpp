#include "solver.h"
#include "segment.h"

#include <vector>
#include <algorithm>
#include <queue>

Solver::Solver(Point start, Point end, vector<Circle> _obstacles) {
    begin = new Node(start, nullptr, end);
    finish = new Node(end, nullptr, end);
    transform(_obstacles.begin(), _obstacles.end(), back_inserter(obstacles), [](const Circle& circle) {
        return new CircleNode(circle);
    });
}

double Solver::Solve() {
    const auto result = StartSolving();
    if (result.second)
        return result.first;

    auto comparer = [](Node *const lhs, Node *const rhs) {
        return lhs->EstimatedLength() > rhs->EstimatedLength();
    };
    priority_queue<Node *, vector<Node *>, decltype(comparer)> paths(comparer);
    for (const auto& path: beginConnections) {
        paths.push(path);
    }
    while (!paths.empty()) {
        auto newNodes = Search(paths.top());
        paths.pop();
        bool found = !isinf(finish->distance);
        for (const auto newNode: newNodes) {
            if (found) {
                if (newNode->EstimatedLength() >= finish->distance)
                    continue;
            }
            paths.push(newNode);
        }
    }

    return isinf(finish->distance) ? -1 : finish->distance;
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
                auto node = new Node(begin->point, obstacle, finish->point);
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

                auto node = new Node(pointOfTangency, obstacles[i], finish->point);
                node->SetNewDistance(DistanceBetween(begin->point, pointOfTangency));
                node->parent = begin;
                beginConnections.push_back(node);
            }

        // finish connections
#if INCLUDE_POINT_ON_CIRCLE_EDGE
        if (PointOnCircleEdge(obstacle->circle, finish->point)) {
            for (auto direction: {Clockwise, CounterClockwise}) {
                auto node = new Node(finish->point, obstacle, finish->point);
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

                auto node = new Node(pointOfTangency, obstacles[i], finish->point);
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
            for (auto other: obstacles) {
                if (other == circleNode || other == obstacle)
                    continue;
                if (segment.IntersectsWithCircle(other->circle)) {
                    skip = true;
                    break;
                }
            }

            if (skip) continue;

            auto node1 = new Node(pot1, circleNode, finish->point);
            auto node2 = new Node(pot2, obstacle, finish->point);
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
        return !conn.first->visited && !conn.second->visited;
    });

    for (auto tuple: connections) {
        auto item1 = tuple.first;
        auto item2 = tuple.second;

        if (node->GetDirectionParent() != item1->GetDirection(item2->point, true))
            continue;

        Arc arc = node->MakeArc(item1->point);
        bool skip = false;
        for (auto obstacle: obstacles) {
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

//Solver::~Solver() {
//    delete begin;
//    delete finish;
//    for (auto & obstacle : obstacles)
//        delete obstacle;
//    for (auto & node : beginConnections);
//}
