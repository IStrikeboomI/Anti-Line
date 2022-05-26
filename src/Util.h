#pragma once
#include <random>
namespace Util {
	static int random(int min, int max) {
        std::random_device dev;
        std::mt19937 rng(dev());
        // distribution in range [min, max]
        std::uniform_int_distribution<std::mt19937::result_type> distribution(min, max);

        return distribution(rng);
	}
}
