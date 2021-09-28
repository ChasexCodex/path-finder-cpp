#include "node.h"

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

double Node::EstimatedLength() const { return distance + heuristic; }

void Node::SetDirection(Direction direction) {
    presetDirection = direction;
}
