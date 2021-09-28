#include "solver.h"
#include "segment.h"

#include <vector>
#include <algorithm>
#include <queue>

Solver::Solver(Point start, Point end, vector<Circle> _obstacles) {
    begin = new Node(start, nullptr, end);
    finish = new Node(end, nullptr, end);
    finish->isEnd = true;
    transform(_obstacles.begin(), _obstacles.end(), back_inserter(obstacles), [](Circle circle) {
        return new CircleNode(circle);
    });
}

double Solver::Solve() {
    auto result = StartSolving();
    if (result.second)
        return result.first;

    auto comparer = [](Node *const lhs, Node *const rhs) {
        return lhs->EstimatedLength() > rhs->EstimatedLength();
    };
    priority_queue<Node *, vector<Node *>, decltype(comparer)> paths(comparer);
    for(auto path : beginConnections) {
        paths.push(path);
    }
    while (!paths.empty()) {
        auto newNodes = Search(paths.top());
        paths.pop();
        bool found = !Infinity(finish->distance);
        for (const auto newNode: newNodes) {
            if (found) {
                if (newNode->EstimatedLength() >= finish->distance)
                    continue;
            }
            paths.push(newNode);
        }
    }

    return Infinity(finish->distance) ? -1 : finish->distance;
}

pair<double, bool> Solver::StartSolving() {
    auto illegalPoint = [](Point point) {
        return [point](CircleNode* circle) {
            return CircleContainsPoint(*circle, point);
        };
    };

    if (find_if(obstacles.begin(), obstacles.end(), illegalPoint(*begin)) != obstacles.end())
        return {-1, true};
    if (find_if(obstacles.begin(), obstacles.end(), illegalPoint(*begin)) != obstacles.end())
        return {-1, true};


    Segment cross(*begin, *finish);
    auto crossIntersect = [&cross](CircleNode *circleNode) {
        return cross.IntersectsWithCircle(*circleNode);
    };

    if (find_if(obstacles.begin(), obstacles.end(), crossIntersect) == obstacles.end()) {
        return {DistanceBetween(*begin, *finish), true};
    }

    GenerateMap();
    return {0, false};
}

void Solver::GenerateMap() {
    auto size = obstacles.size();
    for (int i = 0; i < size; i++) {
        auto obstacle = obstacles[i];
        // begin connections
        for (auto tangent: Line::Tangents(*begin, *obstacle)) {
            auto pointOfTangency = tangent.PointOfTangency(*obstacle);
            Segment segment(*begin, pointOfTangency);

            bool skip = false;
            for (int j = 0; j < size; j++) {
                if (i == j) continue;
                if (segment.IntersectsWithCircle(*obstacles[j])) {
                    skip = true;
                    break;
                }
            }

            if (skip) continue;

            auto node = new Node(pointOfTangency, obstacles[i], *finish);
            node->SetNewDistance(DistanceBetween(*begin, pointOfTangency));
            node->parent = begin;
            beginConnections.push_back(node);
        }

        // finish connections
        for (auto tangent: Line::Tangents(*finish, *obstacle)) {
            auto pointOfTangency = tangent.PointOfTangency(*obstacle);
            Segment segment(pointOfTangency, *finish);

            bool skip = false;
            for (int j = 0; j < size; j++) {
                if (i == j) continue;
                if (segment.IntersectsWithCircle(*obstacles[j])) {
                    skip = true;
                    break;
                }
            }

            if (skip) continue;

            auto node = new Node(pointOfTangency, obstacles[i], *finish);
            obstacles[i]->AddConnection({node, finish});
        }
    }
}

void Solver::GenerateCircleNodeConnections(CircleNode *circleNode) {
    circleNode->generated = true;
    for (auto obstacle: obstacles) {
        if (obstacle->generated)
            continue;
        for (auto tangent: Line::CommonTangents(*circleNode, *obstacle)) {
            auto pot1 = tangent.PointOfTangency(*circleNode);
            auto pot2 = tangent.PointOfTangency(*obstacle);
            Segment segment(pot1, pot2);

            bool skip = false;
            for (auto other: obstacles) {
                if (other == circleNode || other == obstacle)
                    continue;
                if (segment.IntersectsWithCircle(*other)) {
                    skip = true;
                    break;
                }
            }

            if (skip) continue;

            auto node1 = new Node(pot1, circleNode, *finish);
            auto node2 = new Node(pot2, obstacle, *finish);
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

        if (node->GetDirectionParent() != item1->GetDirection(*item2, true))
            continue;

        Arc arc = node->MakeArc(*item1);
        bool skip = false;
        for (auto obstacle: obstacles) {
            if (obstacle == node->container)
                continue;
            if (arc.IntersectsWithCircle(*obstacle)) {
                skip = true;
                break;
            }
        }

        if (skip) continue;

        auto length = arc.Length() + node->distance;

        if (item1->SetNewDistance(length)) {
            item1->parent = node;
            if (item2->SetNewDistance(DistanceBetween(*item1, *item2) + length)) {
                item2->parent = item1;
                ret.push_back(item2);
            }
        }
    }

    return ret;
}
