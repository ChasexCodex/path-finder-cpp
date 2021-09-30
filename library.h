#ifndef PATH_FINDER_CPP_SHARED_LIBRARY_H
#define PATH_FINDER_CPP_SHARED_LIBRARY_H

extern "C" {

    __declspec(dllexport) double ArcLength(Arc* arc);
    __declspec(dllexport) int GetCode();

}

#endif //PATH_FINDER_CPP_SHARED_LIBRARY_H
