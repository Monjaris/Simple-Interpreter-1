#include "parser.hpp"
#include "tokenizer.hpp"
// #include <type_traits>

void Parser::parse()
{
    actions.clear();
    const Action action_template = {
        OPC::NONE, "", {""}
    };
    Action action = action_template;

    while (check())
    {
        action = action_template;

        if (get().type == TT::KW)
        {
            Token tok = get();
            advance();
            action.opcode = OPC::CALL_KW;

            if (tok.val == "exit") {
                action.lead = "exit";
                string arg1;
                if (get().type != TT::ERROR) {
                    arg1 = get().val;
                    advance();
                } else {
                    arg1 = "0";
                }
                action.args = {arg1};
                push(action);
            }

            else if (tok.val == "clear") {
                action.lead = "clear";
                string arg1;
                if (get().type != TT::ERROR) {
                    arg1 = get().val;
                    advance();
                } else {
                    arg1 = "";
                }
                action.args = {arg1};
                push(action);
            }

            else if (tok.val == "print") {
                action.lead = "print";
                string arg1;
                if (get().type != TT::ERROR) {
                    arg1 = get().val;
                    advance();
                } else {
                    arg1 = "";
                }
                action.args = {arg1};
                push(action);
            }


            else if (tok.val == "add") {
                action.lead = "add";
                string arg1, arg2;
                if (get().type != TT::ERROR) {
                    arg1 = get().val;
                    advance();
                    if (get().type != TT::ERROR) {
                        arg2 = get().val;
                    } else {
                        log(".add: 2 arguments expected, got 1");
                        arg2 = "0";
                    }
                } else {
                    arg1 = "0";
                    arg2 = "0";
                }
                action.args = {arg1, arg2};
                push(action);
            }
            else if (tok.val == "sub") {
                action.lead = "sub";
                string arg1, arg2;
                if (get().type != TT::ERROR) {
                    arg1 = get().val;
                    advance();
                    if (get().type != TT::ERROR) {
                        arg2 = get().val;
                    } else {
                        log(".sub: 2 arguments expected, got 1");
                        arg2 = "0";
                    }
                } else {
                    arg1 = "0";
                    arg2 = "0";
                }
                action.args = {arg1, arg2};
                push(action);
            }
            else if (tok.val == "mul") {
                action.lead = "mul";
                string arg1, arg2;
                if (get().type != TT::ERROR) {
                    arg1 = get().val;
                    advance();
                    if (get().type != TT::ERROR) {
                        arg2 = get().val;
                    } else {
                        log(".mul: 2 arguments expected, got 1");
                        arg2 = "0";
                    }
                } else {
                    arg1 = "0";
                    arg2 = "0";
                }
                action.args = {arg1, arg2};
                push(action);
            }
            else if (tok.val == "div") {
                action.lead = "div";
                string arg1, arg2;
                if (get().type != TT::ERROR) {
                    arg1 = get().val;
                    advance();
                    if (get().type != TT::ERROR) {
                        arg2 = get().val;
                    } else {
                        log(".div: 2 arguments expected, got 1");
                        arg2 = "0";
                    }
                } else {
                    arg1 = "0";
                    arg2 = "0";
                }
                action.args = {arg1, arg2};
                push(action);
            }
            else if (tok.val == "pow") {
                action.lead = "pow";
                string arg1, arg2;
                if (get().type != TT::ERROR) {
                    arg1 = get().val;
                    advance();
                    if (get().type != TT::ERROR) {
                        arg2 = get().val;
                    } else {
                        log(".pow: 2 arguments expected, got 1");
                        arg2 = "1";
                    }
                } else {
                    arg1 = "0";
                    arg2 = "1";
                }
                action.args = {arg1, arg2};
                push(action);
            }
            else if (tok.val == "sqrt") {
                action.lead = "sqrt";
                string arg1;
                if (get().type != TT::ERROR) {
                    arg1 = get().val;
                    advance();
                } else {
                    arg1 = "0";
                }
                action.args = {arg1};
                push(action);
            }

            else {
                action.lead = "noop";
                action.args = {""};
                push(action);
            }
        }

        else if (get().type == TT::RAW)
        {
            Token tok = get();
            advance();
            action.opcode = OPC::PUSH_RAW;
            action.lead = tok.val;
            action.args = {""};
            push(action);
        }

        else if (get().type == TT::INT)
        {
            Token tok = get();
            advance();
            action.opcode = OPC::PUSH_INT;
            action.lead = tok.val;
            action.args = {""};
            push(action);
        }

        else if (get().type == TT::STR)
        {
            Token tok = get();
            advance();
            action.opcode = OPC::PUSH_STR;
            action.lead = tok.val;
            action.args = {""};
            push(action);
        }


        else if (get().type == TT::NONE)
        {
            Token tok = get();
            advance();
            action.opcode = OPC::NONE;
            action.lead = "<none>";
            action.args = {""};
            push(action);
        }
        else if (get().type == TT::ERROR) {
            Token tok = get();
            advance();
            action.opcode = OPC::ERROR;
            action.lead = "<error>";
            action.args = {""};
            push(action);
        }
        else if (get().type == TT::UNKNOWN) {
            Token tok = get();
            advance();
            action.opcode = OPC::UNKNOWN;
            action.lead = "<unknown>";
            action.args = {""};
            push(action);
        }
    }
}

