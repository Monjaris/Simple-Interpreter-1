#pragma once
#include <cstddef>
// #include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <unordered_map>
// #include <algorithm>
#include <functional>
#include <sstream>
#include <mutex>
// #include <expected>

using isize = std::ptrdiff_t;
using f32 = float;
using f64 = double;
using string = std::string;
template<class K, class V> using hash_map = std::unordered_map<K, V>;
using Strvec = std::vector<string>;
using KWAction = std::function<void(Strvec)>;


// Simple Interpreter - namespace(root) of project
namespace si {};

#define CLR "\033[37m"
#define PROMPT "\033[32m$: "

namespace si
{
    template <class... Args>
    void log(Args... args) {
        using Osstream = std::ostringstream;
        static std::once_flag flag;
        std::call_once(flag,
            [] {
                std::ios::sync_with_stdio(false);
            }
        );

        thread_local Osstream ss;


        ss.str({});
        (ss << ... << args);
        std::cout << std::move(ss).str();
    }

    template <const char* clr="\033[31m", class... Args>
    void logerr(Args... args) {
        log((clr, ..., args));
    }

    template <bool _terminate=true, class... Args>
    void logerr(int ec, Args... args) {
        log((..., args));
        if constexpr(_terminate) {
            std::exit(ec);
        }
    }

    template <class T>
    bool is_any_of(const T& val, auto... values) {
        return ((val == values) || ...);
    }
};

using si::log;

