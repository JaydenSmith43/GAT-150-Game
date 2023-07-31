#pragma once
#include <random>

namespace kiko
{
	inline void seed_random(unsigned int seed) { srand(seed); }

	inline int random() { return rand(); }
	inline int random(unsigned int max) { return rand() % max; } // 0 to (max - 1)
	inline int random(unsigned int min, unsigned int max) { return min + random((max - min) + 1) ; } // min to max

	inline float randomf() { return random() / (float)RAND_MAX; } // inline will instead of calling will place at place called in code
	inline float randomf(float max) { return randomf() * max; }
	inline float randomf(float min, float max) { return min + randomf() * (max - min); }
}