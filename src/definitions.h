#ifndef PATH_FINDER_CPP_SHARED_DEFINITIONS_H
#define PATH_FINDER_CPP_SHARED_DEFINITIONS_H

#if DEFAULT_MSVC
#define SAFE_THROW(message) (throw std::exception((message)))
#elif WSL_GCC
#define SAFE_THROW(message) (throw std::exception())
#endif

#endif //PATH_FINDER_CPP_SHARED_DEFINITIONS_H
