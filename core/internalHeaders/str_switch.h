#ifndef STR_SWITCH_H
#define STR_SWITCH_H

#include <string>

typedef unsigned char uchar;
typedef unsigned long long ullong;

constexpr ullong FNV_PRIME = 1099511628211ULL;
constexpr ullong FNV_OFFSET_BASIS = 14695981039346656037ULL;

constexpr ullong fnv1a_hash(const char* str, const ullong hash = FNV_OFFSET_BASIS)
{
    return (*str == 0)
        ? hash
        : fnv1a_hash(str + 1, (hash ^ static_cast<uchar>(*str)) * FNV_PRIME);
}


inline ullong str_hash_for_switch(const char* const str)
{
    return str ? fnv1a_hash(str) : 0;
}

inline ullong str_hash_for_switch(const std::string& str)
{
    return fnv1a_hash(str.c_str());
}

constexpr ullong operator""_hash(const char* str, size_t)
{
    return fnv1a_hash(str);
}

#endif  // STR_SWITCH_H