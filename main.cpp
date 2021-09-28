#include <iostream>
#include "src/solver.h"

int main() {
//    Solver solver({-10, 0}, {10, 0}, {
//            {-6, 0, 2},
//            {6,  0, 2},
//            {0,  0, 3},
//    });

    Solver solver({-1, 0}, {0, 1}, {{0, 0, 1}});

    try {
        auto result = solver.Solve();
        printf("%.15f", result);
    } catch (...) {
        cout << "An error occurred" << endl;
    }
    return 0;
}
