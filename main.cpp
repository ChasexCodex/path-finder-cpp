#include <iostream>
#include <chrono>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <csignal>
#include "function.h"
#include "src/circle.h"

using namespace rapidjson;
using namespace std;

int main() {
    signal(SIGABRT, [](int signalCode) {
        cout << "Terminating..." << endl;
    });

//    Solver solver({-1, 0}, {0, 1}, {{0, 0, 1}});

    FILE *fp;

#if DEFAULT_MSVC
    fopen_s(&fp, "data.json", "rb");
#elif WSL_GCC
    fp = fopen("data.json", "rb");
#endif

    if(!fp) {
        cout << "Error reading the file 'data.json'. Terminating" << endl;
        return 1;
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
        printf("Start\n");
        auto capture = std::chrono::high_resolution_clock::now();
        auto result = solve(start, end, obstacles);
        auto elapsed = std::chrono::high_resolution_clock::now() - capture;
        int64_t microseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        printf("Took %lld ms\n", microseconds);
        printf("%.15f\n\n", result);
//        auto res = solver.GetFinishPath();
//        printf("%d\n", res.size());
//        for (const auto &point : res) {
//            printf("(x: %.15f, y: %.15f)\n", point.x, point.y);
//        }
    } catch (...) {
        cout << "An error occurred" << endl;
    }
    return 0;
}
