[system]
    [window]
        width = 1200
        height = 840
        name = 'system window'
        flags = {RESIZABLE, NO-BORDERS,}
    ;  -- idk if i should add semicolons at the end, it either \
    should be yes or no, optional features usually get 
    [user]
        width = 1000
        height =
        680
        name = 'user
        window'
        flags = {
            RESIZABLE,
        }
    ;
;

-- or we can also just do short names via:

[system: window]  -- or should i make it dot or colon+space?
<<
    *that stuff*
>>

-- even shorter options via:
[system: window].width = 1000  -- should be on one line, also this \
get a warning because it is redefined, first definition is on above

DEF SIZE (1000)  -- macros, constants but preprocessed
-- cant use it on above because parser doesnt pre-read internally
-- but referencing a constant is like that:
[global: theme: overrides].bg-color = $(SIZE)

%(SIZE == 1000)  -- if size is non-zero
    -- like if constexpr,
    -- it decides to skip if not-true
    -- or keep if true
    -- and define/set things
%

