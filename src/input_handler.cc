/*
 * input_handler.cc
 *
 * Strictly handles input and outputs an action for main thread
 * to tackle.
 */

#include "input_handler.hpp"

// global constants
const char kEscape = 27; 
const char kInsert = 'i'; 
const char kSpecialAction = ':'; 
const char kQuit   = 'q'; 
const char kUp     = 'k'; 
const char kDown   = 'j'; 
const char kLeft   = 'h'; 
const char kRight  = 'l'; 

static int gMaxRow;
static int gMaxCol;

enum class IHMode 
{
    kModeNavigate = 0,
    kModeInsert   = 1,
}; 

typedef struct 
{
    IHMode mode;
    bool special_action;
} handler_t;

static handler_t gIH;

void input_handler_init(void)
{
    gIH.mode   = IHMode::kModeNavigate;
    gIH.special_action     = false;

    // TODO remove these constants
    gMaxRow = 100;
    gMaxCol = 100;
}

// terminal controls
//  esc: escape insert mode (nav mode) 
//  i: insert mode (ins mode)
//
// nav mode
//  special keys move cursor (h/l/k/j arrow keys
//  :s save, :q quit)
//
// ins mode
//  inserts any character entered
IHAction input_handler_process(char ch, cursor_t& cursor)
{
    if (IHMode::kModeInsert == gIH.mode)
    {
        switch (ch)
        {
            case kEscape:
                gIH.mode = IHMode::kModeNavigate;
                break;
            default:
                cursor.col++;
                if (cursor.col > gMaxCol)
                {
                    cursor.col = 0;
                    cursor.row++;
                }
                if (cursor.row > gMaxRow)
                {
                    cursor.row = gMaxRow;
                }
                return IHAction::kActionInsert;
        }
    }
    else
    {
        switch (ch) 
        {

            case kSpecialAction:
                gIH.special_action = true;
                break;

            case kQuit:
                if (gIH.special_action)
                {
                    return IHAction::kActionQuit;
                }
                break;

            case kDown:
                cursor.row++;
                gIH.special_action = false;
                break;

            case kUp:
                cursor.row--;
                gIH.special_action = false;
                break;

            case kLeft:
                cursor.col--;
                gIH.special_action = false;
                break;

            case kRight:
                cursor.col++; 
                gIH.special_action = false;
                break;

            case kInsert:
                gIH.mode = IHMode::kModeInsert;
                gIH.special_action = false;
                break;
                
            default:
                gIH.special_action = false;
                break;
        }

        if (cursor.row > gMaxRow)
            cursor.row = gMaxRow;

        if (cursor.row < 0)
            cursor.row = 0;

        if (cursor.col > gMaxCol)
            cursor.col = gMaxCol;

        if (cursor.col < 0)
            cursor.col = 0;


        return IHAction::kActionNavigate;
    }

    return IHAction::kActionNone;
}
