#include "client_a.h"
#include "client_b.h"

#include <iostream>

int main() {
    std::cout << "foo(): " << client::foo() << "\n"
                 "bar(): " << client::bar() << '\n';
}
