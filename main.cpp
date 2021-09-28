#include <iostream>
#include <chrono>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include "src/solver.h"

using namespace rapidjson;

double solve(Point start, Point end, vector<Circle> obstacle) {
    return Solver(start, end, move(obstacle)).Solve();
}

int main() {
//    Solver solver({-10, 0}, {10, 0}, {
//            {-6, 0, 2},
//            {6,  0, 2},
//            {0,  0, 3},
//    });

//    Solver solver({-1, 0}, {0, 1}, {{0, 0, 1}});

    FILE *fp;
    fopen_s(&fp, "data.json", "rb");

    if(!fp) {
        cout << "Error reading the file 'data.json'. Terminating" << endl;
        return -1;
    }

    char readBuffer[200000];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document data;
    data.ParseStream(is);

    const auto list = data["children"][0]["children"].GetArray();

    vector<Circle> obstacles;
    Point start{2, -9};
    Point end{5, 2};

    for (auto &it: list) {
        if (it["name"] == "size") continue;
        double x = it["children"][0]["children"][0]["val"].GetDouble();
        double y = it["children"][0]["children"][1]["val"].GetDouble();
        double r = it["children"][1]["val"].GetDouble();
        obstacles.emplace_back(x, y, r);
    }

    try {
        printf("Start");
        auto capture = std::chrono::high_resolution_clock::now();
        auto result = solve(start, end, obstacles);
        auto elapsed = std::chrono::high_resolution_clock::now() - capture;
        int64_t microseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        printf("Took %lld ms\n", microseconds);
        printf("%.15f", result);
    } catch (...) {
        cout << "An error occurred" << endl;
    }
    return 0;
}
