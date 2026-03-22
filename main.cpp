#include "core.h"
#include "src/eval.hpp"

int main()
{
    string source = {};

    while (true)
    {
        log(PROMPT, CLR);

        if(
            !std::getline(std::cin, source)
            || si::is_any_of(source, "quit!")
        ) break;

        Tokenizer tokenizer(source);
        tokenizer.tokenize();

        Parser parser(tokenizer.tokens);
        parser.parse();

        Eval eval(parser.actions);
        eval.exec();
    }
    
}
