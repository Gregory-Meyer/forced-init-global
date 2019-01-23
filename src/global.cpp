#include "global.h"

#include <atomic>
#include <fstream>

static std::atomic<int> refcount{ 0 };

namespace global::detail {

class Init {
public:
    Init() {
        if (refcount.fetch_add(1) == 0) {
            std::ofstream ofs{ "output.txt" };
            ofs << "Init() invoked for the first time\n";
        }
    }

    ~Init() {
        if (refcount.fetch_sub(1) == 1) {
            std::ofstream ofs{ "output.txt", std::ios_base::app };
            ofs << "~Init() invoked for the last time\n";
        }
    }
};

static Init init_instance;

} // namespace global::detail
