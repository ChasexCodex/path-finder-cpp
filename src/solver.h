#ifndef PATH_FINDER_CPP_SOLVER_H
#define PATH_FINDER_CPP_SOLVER_H

#include <vector>
#include <algorithm>
#include <functional>
#include <queue>

#include "node.h"
#include "segment.h"

using namespace std;

class Solver {
    Node *begin;
    Node *finish;

    vector<CircleNode *> obstacles;
    vector<Node *> beginConnections;

    pair<double, bool> StartSolving();

    void GenerateMap();

    void GenerateCircleNodeConnections(CircleNode *circleNode);

    vector<Node *> Search(Node *node);

public:
    Solver(Point start, Point end, vector<Circle> obstacles);

    double Solve();
};

#endif //PATH_FINDER_CPP_SOLVER_H
