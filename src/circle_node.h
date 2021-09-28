#ifndef PATH_FINDER_CPP_CIRCLE_NODE_H
#define PATH_FINDER_CPP_CIRCLE_NODE_H

#include <vector>
#include "circle.h"

struct Node;
typedef std::pair<Node *, Node *> Connection;

struct CircleNode {
    bool generated = false;
    const Circle circle;
    std::vector<Connection> connections{};

    void AddConnection(Connection connection);

    explicit CircleNode(Circle circle);
};


#endif //PATH_FINDER_CPP_CIRCLE_NODE_H
