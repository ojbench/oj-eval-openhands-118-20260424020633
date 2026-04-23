#include "src.hpp"

int main() {
    fraction <int> f;
    std::cout << f << std::endl; // 0/1

    f = 2;
    std::cout << f << std::endl; // 2/1

    f = fraction<int>(2, -6);
    std::cout << f << std::endl; // -1/3

    f = fraction <int>() - (f ^ -1ll);
    std::cout << f << std::endl; // 3/1

    f += f;
    std::cout << f << std::endl; // 6/1

    f *= f;
    std::cout << f << std::endl; // 36/1

    f ^= -1ll;
    std::cout << f << std::endl; // 1/36

    f -= f;
    std::cout << f << std::endl; // 0/1
    std::cout << static_cast <double> (f) << std::endl; // 0

    if (f) {
        std::cout << "f is not zero" << std::endl;
    } else {
        std::cout << "f is zero" << std::endl;
    }

    try {
        f = f - (f ^ -114514ll);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl; // Divided by zero!
    }

    return 0;
}
