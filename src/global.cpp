#include "global.h"

#include <atomic>
#include <fstream>

static std::atomic<int> refcount{ 0 };

global::Init::Init() {
    if (refcount.fetch_add(1) == 0) {
        std::ofstream ofs{ "output.txt" };
        ofs << "ctor " << this << '\n';
    }
}

global::Init::~Init() {
    if (refcount.fetch_sub(1) == 1) {
        std::ofstream ofs{ "output.txt", std::ios_base::app };
        ofs << "dtor " << this << '\n';
    }
}
