#include "siphash.h"

constexpr uint64_t SIPHASH_KEY1 = 0x0706050403020100;
constexpr uint64_t SIPHASH_KEY2 = 0x0f0e0d0c0b0a0908;

uint64_t siphash(const std::string& input) {
    uint64_t v0 = 0x736f6d6570736575ULL;
    uint64_t v1 = 0x646f72616e646f6dULL;
    uint64_t v2 = 0x6c7967656e657261ULL;
    uint64_t v3 = 0x7465646279746573ULL;

    v0 ^= SIPHASH_KEY1;
    v1 ^= SIPHASH_KEY2;
    v2 ^= SIPHASH_KEY1;
    v3 ^= SIPHASH_KEY2;

    uint64_t m = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        m |= static_cast<uint64_t>(input[i]) << (8 * (i % 8));
        if (i % 8 == 7 || i == input.size() - 1) {
            v3 ^= m;
            for (int i = 0; i < 2; ++i) { 
                v0 += v1; v1 = (v1 << 13) | (v1 >> (64 - 13)); v1 ^= v0; v0 = (v0 << 32) | (v0 >> (64 - 32));
                v2 += v3; v3 = (v3 << 16) | (v3 >> (64 - 16)); v3 ^= v2;
                v0 += v3; v3 = (v3 << 21) | (v3 >> (64 - 21)); v3 ^= v0;
                v2 += v1; v1 = (v1 << 17) | (v1 >> (64 - 17)); v1 ^= v2; v2 = (v2 << 32) | (v2 >> (64 - 32));
            }
            v0 ^= m;
            m = 0;
        }
    }

    v2 ^= 0xff;
    for (int i = 0; i < 4; ++i) {  
        v0 += v1; v1 = (v1 << 13) | (v1 >> (64 - 13)); v1 ^= v0; v0 = (v0 << 32) | (v0 >> (64 - 32));
        v2 += v3; v3 = (v3 << 16) | (v3 >> (64 - 16)); v3 ^= v2;
        v0 += v3; v3 = (v3 << 21) | (v3 >> (64 - 21)); v3 ^= v0;
        v2 += v1; v1 = (v1 << 17) | (v1 >> (64 - 17)); v1 ^= v2; v2 = (v2 << 32) | (v2 >> (64 - 32));
    }

    return v0 ^ v1 ^ v2 ^ v3;
}
