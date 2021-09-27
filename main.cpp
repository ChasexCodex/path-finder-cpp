#include <iostream>
#include "src/solver.h"

int main() {
    Solver solver;
    auto result = solver.Solve();

    std::cout << result << std::endl;
    return 0;
}
