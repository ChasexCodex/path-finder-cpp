#include <iostream>
#include "src/solver.h"

int main() {
    Solver solver({-2, 0}, {2, 0}, {{0,0,1}});
    try {
        auto result = solver.Solve();

        cout << result << endl;
    } catch (...) {
        cout << "Error occurred" << endl;
    }
    return 0;
}
