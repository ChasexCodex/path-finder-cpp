#ifndef PATH_FINDER_CPP_CIRCLE_NODE_H
#define PATH_FINDER_CPP_CIRCLE_NODE_H

#include <vector>
#include "node.h"
#include "circle.h"

using namespace std;

typedef Connection pair<Node*, Node*>

struct CircleNode : public Circle {
    bool generated = false;
    vector<Connection> connections{};
    void AddConnection(Connection connection) {
        connections.push_back(connection);
    }
    CircleNode(Circle circle) : Circle(circle) {}
};


#endif //PATH_FINDER_CPP_CIRCLE_NODE_H
