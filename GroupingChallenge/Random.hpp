#pragma once
#include <stdint.h>
#include <random>
#include <numeric>
// src : https://martin.ankerl.com/2018/12/08/fast-random-bool/

template <typename U = uint_fast64_t> 
class Randomizer {
private:
    std::mt19937& rng;
public:
    Randomizer(std::mt19937& generator) : rng(generator) {}
    bool operator()() {
        if (1 == m_rand) {
            m_rand = std::uniform_int_distribution<U>{}(rng) | s_mask_left1;
        }
        bool const ret = m_rand & 1;
        m_rand >>= 1;
        return ret;
    }

private:
    static constexpr const U s_mask_left1 = U(1) << (sizeof(U) * 8 - 1);
    U m_rand = 1;
};
