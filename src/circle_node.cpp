#include "circle_node.h"

void CircleNode::AddConnection(Connection connection) {
    connections.push_back(connection);
}

CircleNode::CircleNode(Circle circle) : Circle(circle) {}
