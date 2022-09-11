#pragma once
#include <random>
namespace Util {
	static inline int random(int min, int max) {
        std::random_device dev;
        std::mt19937 rng(dev());
        // distribution in range [min, max]
        std::uniform_int_distribution<std::mt19937::result_type> distribution(min, max);

        return distribution(rng);
	}
    static inline int signum(double x) {
        if (x > 0) return 1;
        if (x < 0) return -1;
        return 0;
    }
    static inline double degToRad(double deg) {
        //0.0174532925199432957 is pi/180
        return deg * 0.0174532925199432957;
    }
}
