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

    [[nodiscard]] Direction GetDirection(Point resolver, bool inverse = false) const;

    [[nodiscard]] Direction GetDirectionParent() const;;

    [[nodiscard]] Arc MakeArc(Point end) const;

    [[nodiscard]] double EstimatedLength() const;

    void SetDirection(Direction direction);
};

#endif //PATH_FINDER_CPP_NODE_H
