#ifndef PATH_FINDER_CPP_SOLVER_H
#define PATH_FINDER_CPP_SOLVER_H

#include "node.h"

using namespace std;

class Solver {
    Node *begin;
    Node *finish;


    vector<CircleNode *> obstacles{};
    vector<Node *> nodes{};
    vector<Node *> beginConnections{};

    pair<double, bool> StartSolving();

    void GenerateMap();

    void GenerateCircleNodeConnections(CircleNode *circleNode);

    vector<Node *> Search(Node *node);

    Node *CreateNode(Point point, CircleNode *container, Point end);

public:
    Solver(Point start, Point end, vector<Circle> obstacles);

    double Solve();

    vector<Point> GetFinishPath();

    ~Solver();
};

#endif //PATH_FINDER_CPP_SOLVER_H
