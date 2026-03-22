#pragma once
#include "../core.h"
#include <cmath>
#include <cstdlib>

namespace si
{
    inline f64 retval = 0;

    // keywords comes after '.' in this language
    inline hash_map<string, KWAction> keywords = {
        {"noop", [](Strvec _) {
            retval = _[0][0] = 0;  // used parameter
        }},

        {"exit", [](Strvec exit_code={"0"}) {
            int ec = std::stoi(exit_code[0]);
            retval = 0;
            std::exit(ec);
        }},

        {"clear", [](Strvec full={""}) {
            if (full[0] == "all") {
                log("\033[2J\033[H");
            } else if (full[0].empty()) {
                std::system("clear -x");
            } else {
                log(".clear: wrong argument!\n");
            }
            retval = 0;
        }},

        {"print", [](Strvec msg) {
            log(msg[0], "\n");
            retval = 0;
        }},

        {"add", [](Strvec operands) {
            isize left = std::stol(operands[0]);
            isize right = std::stol(operands[1]);
            retval = left + right;
        }},
        {"sub", [](Strvec operands) {
            isize left = std::stol(operands[0]);
            isize right = std::stol(operands[1]);
            retval = left - right;
        }},
        {"mul", [](Strvec operands) {
            isize left = std::stol(operands[0]);
            isize right = std::stol(operands[1]);
            retval = left * right;
        }},
        {"div", [](Strvec operands) {
            isize left = std::stol(operands[0]);
            isize right = std::stol(operands[1]);
            if (right) retval=(f64)left/right; else retval=1;
        }},
        {"pow", [](Strvec operands) {
            isize left = std::stol(operands[0]);
            isize right = std::stol(operands[1]);
            retval = std::pow(left, right);
        }},
        {"sqrt", [](Strvec operands) {
            isize left = std::stol(operands[0]);
            retval = std::sqrt(left);
        }},
    };
}


enum class TT
{
    KW= 'K',
    RAW= 'R',
    STR= 'S',
    INT= 'N',

    NONE= '_',
    UNKNOWN= '?',
    ERROR= '!'
};

struct Token {
    TT type;
    string val;

    operator string() {
        return
        {
            "T=" + string(1, char(type)) +
            " : " +
            "V=" + val +
            "\n"
        };
    }

    int ival() {
        return std::stoi(
            val
        );
    }
};

#define MAX_STR_LEN 1024
struct Tokenizer
{
    string src;
    uint pos;
    std::vector<Token> tokens;

    inline Tokenizer(string source) {
        src = source;
        pos = 0;
        tokens = {};
    }


    // checks bounds
    inline bool check() {
        return src.size() > pos;
    }

    // steps with bounds checking
    inline void step() {
        if (check()) {
            ++pos;
        }
    }

    // gets current character that tokenizer points to
    inline char get() {
        return src[pos];
    }

    // skip whitespaces
    inline void skipws() {
        while (check() && isspace(get())) {
            step();
        }
    }

    inline void push(const Token& token) {
        tokens.push_back(token);
    }

    inline void pdata() {
        for (uint i=0;  i < tokens.size();  ++i) {
            std::cout << string(tokens[i]);
        }
    }


    string parseRaw();
    string parseInt();
    string parseStr();
    void tokenize();
};
