#include "node.h"

Node::Node(Point point, CircleNode *container, Point end)
        : Point(point.x, point.y), container(container) {
    heuristic = DistanceBetween(point, end);
}

bool Node::SetNewDistance(double newDistance) {
    if (distance > newDistance) {
        distance = newDistance;
        return true;
    }

    return false;
}

Direction Node::GetDirection(Point resolver, bool inverse) {
    return ::GetDirection(*this, resolver, container->ctr, inverse);
}

Direction Node::GetDirectionParent() {
    return ::GetDirection(*this, *parent, container->ctr);
}

Arc Node::MakeArc(Point end) {
    return Arc{*this, end, GetDirectionParent(), *container};
}

double Node::EstimatedLength() { return distance + heuristic; }
