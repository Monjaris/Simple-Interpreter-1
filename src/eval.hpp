#pragma once
#include "parser.hpp"

struct Eval
{
    std::vector<Action> actions;
    uint idx;

    Eval (std::vector<Action> v_action_list) {
        actions = v_action_list;
        idx = 0;
    }

    bool check() {
        return actions.size() > idx;
    }

    void next() {
        if (check()) {
            ++idx;
        }
    }

    Action get() {
        if (check()) {
            return actions[idx];
        }
        log(1, "Evaluator vector out of bounds\n");
        return Action{};
    }

    int exec();
};
