/*
 * main.cc
 */

#include <ncurses.h>
#include "input_handler.hpp"

cursor_t gCursor;

int main(void)
{
    IHAction action;
    gCursor.row = 0;                                                                  
    gCursor.col = 0;                                                                  

    input_handler_init();
    
    // TODO use windows
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

    do 
    {
        char ch = getch();
        // outputs action so that main (or something else)
        // can do the action (e.g. draw to window)
        action = input_handler_process(ch, gCursor);

        switch(action)
        {
            case IHAction::kActionSave     :
            case IHAction::kActionInsert   :
                addch(ch);
                break;
            case IHAction::kActionNavigate :
                move(gCursor.row, gCursor.col);
                break;
            case IHAction::kActionQuit     :
            case IHAction::kActionNone     :
            default:
                continue;
        }
        refresh();
    } while( IHAction::kActionQuit != action ); 

    endwin();
    return 0;
}
