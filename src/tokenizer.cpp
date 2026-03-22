#include "tokenizer.hpp"
#include <cctype>

string Tokenizer::parseRaw() {
    string raw;
    while (isalpha(get()) || isdigit(get())) {
        raw += get();
        step();
    }
    return raw;
}

string Tokenizer::parseInt() {
    string integer;
    while (isdigit(get())) {
        integer += get();
        step();
    }
    return integer;
}

string Tokenizer::parseStr() {
    string str = {};
    if (get() != '"') {
        log("\" at the start of the string not found!\n");
    }
    step();

    int len = 0;
    while (check() && (get() != '"'))
    {
        str += get();
        ++len;
        step();

        if (len > MAX_STR_LEN) {
            log("Length of the string is too much: ", len, "\n");
            break;
        }
    }

    if (!check()) {
        log("Unterminated string: ", str, " <-\n");
    }

    step();
    return str;
}


void Tokenizer::tokenize()
{
    tokens.clear();
    const Token token_template = {TT::NONE, "<none>"};
    Token token = token_template;

    while (check())
    {
        token = token_template;
        skipws();

        if (get() == '.') {
            step();
            string keyword = parseRaw();
            token = Token {
                .type = TT::KW,
                .val = keyword
            };
            push(token);
        }

        else if (isalpha(get())) {
            string raw = parseRaw();
            token = Token {
                .type = TT::RAW,
                .val  = raw
            };
            push(token);
        }

        else if (isdigit(get())) {
            string integer = parseInt();
            token = Token {
                .type = TT::INT,
                .val  = integer
            };
            push(token);
        }

        else if (get() == '"') {
            string str = parseStr();
            token = Token {
                .type = TT::STR,
                .val = str
            };
            push(token);
        }

        else if (get() == '?') {
            step();
            pdata();
        }

        else {
            step();
        }
    }
}

