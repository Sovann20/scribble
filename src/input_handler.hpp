/*
 * InputHandler is meant to be a singleton module which helps process
 * user input and maintains some cursor related data.
 */

#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

typedef struct
{
    int row;
    int col;
} cursor_t;

enum class IHAction
{
    kActionQuit     = 0,
    kActionNone     = 1,
    kActionSave     = 2,
    kActionInsert   = 3,
    kActionNavigate = 4,
};

// initialize singleton handler
void input_handler_init(void);

// process a single input character 
IHAction input_handler_process(char ch, cursor_t& cursor);

#endif
