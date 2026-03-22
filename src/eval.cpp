#include "eval.hpp"
#include "tokenizer.hpp"
#include <functional>

int Eval::exec()
{
    int errc = 0;

    while (check())
    {
        if (get().opcode == OPC::CALL_KW)
        {
            Action action = get();
            next();
            string kw = action.lead;
            Strvec args = action.args;
            si::keywords[kw](args);
        }
        else if (get().opcode == OPC::PUSH_RAW)
        {
            next();
            log("(raw)", si::retval, ", ");
        }
        else if (get().opcode == OPC::PUSH_INT)
        {
            next();
            log("(int)", si::retval, ", ");
        }
        else if (get().opcode == OPC::PUSH_STR)
        {
            next();
            log("(str)", si::retval, ", ");
        }
        else
        {
            switch (get().opcode)
            {
                case OPC::ADD:
                case OPC::SUB:
                case OPC::MUL:
                case OPC::DIV:
                case OPC::POW:
                case OPC::SQRT:
                {
                    next();
                    log("(op)", si::retval, ", ");
                    goto known;
                    break;
                }

                default: {
                    log("Unknown opcode!\n");
                }
            }
            {
                {
                    log("Unknown command!\n");
                    break;
                }
            }
            known:
        }

    }

    log("\n");
    return errc;
}
