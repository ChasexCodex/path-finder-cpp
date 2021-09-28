#ifndef PATH_FINDER_CPP_NODE_H
#define PATH_FINDER_CPP_NODE_H

#include "circle_node.h"
#include "helpers.h"
#include "arc.h"

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

    Direction GetDirection(Point resolver, bool inverse = false);

    Direction GetDirectionParent();;

    Arc MakeArc(Point end);

    double EstimatedLength();

    void SetDirection(Direction direction);
};

#endif //PATH_FINDER_CPP_NODE_H
