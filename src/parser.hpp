#pragma once
#include "tokenizer.hpp"

enum class OPC {
    CALL_KW= '.',
    PUSH_RAW= 'r',
    PUSH_INT= 'i',
    PUSH_STR= 's',
    ADD, SUB, MUL, DIV,
    POW, SQRT,
    NONE= 0, ERROR=1, UNKNOWN= -1
};

struct Action {
    OPC opcode;
    string lead;
    std::vector<string> args;
};

struct Parser
{
    std::vector<Token> tokens;
    uint idx;
    std::vector<Action> actions;

    Parser (std::vector<Token> v_token_list) {
        tokens = v_token_list;
        idx = 0;
        actions = {};
    }

    bool check(int i=0) {
        return tokens.size() > idx+i;
    }

    void advance() {
        if (check()) {
            ++idx;
        }
    }

    Token get() {
        if (check()) {
            return tokens[idx];
        } else {
            return {TT::ERROR, "<error>"};
        }
    }

    Token next() {
        if (check(1)) {
            return tokens[idx+1];
        } else {
            return {TT::ERROR, "<error>"};
        }
    }

    void push(const Action& action) {
        actions.push_back(action);
    }


    void parse();
};
