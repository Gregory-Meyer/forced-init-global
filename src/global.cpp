#include "global.h"

#include <atomic>
#include <fstream>

static std::atomic<int> refcount{ 0 };

namespace global::detail {

[[gnu::constructor]] static void _init() {
    if (refcount.fetch_add(1) == 0) {
        std::ofstream ofs{ "output.txt" };
        ofs << "ctor\n";
    }
}

[[gnu::destructor]] static void _deinit() {
    if (refcount.fetch_sub(1) == 1) {
        std::ofstream ofs{ "output.txt", std::ios_base::app };
        ofs << "dtor\n";
    }
}

} // namespace global::detail
