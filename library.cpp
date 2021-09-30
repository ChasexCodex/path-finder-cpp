#include "src/arc.h"

extern "C" __declspec(dllexport) double ArcLength(Arc* arc);

double ArcLength(Arc *arc) {
    return arc->Length();
}
