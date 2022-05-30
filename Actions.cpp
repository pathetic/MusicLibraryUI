#include "Actions.h"

Actions::Actions()
{

}

void Actions::add_state(Playlist& p)
{
    // if (!undostack.empty())
    //     if(undostack.top().toString() == p.toString()) return;
    undostack.push(p);
}

void Actions::remove_last_state()
{
    if (!undostack.empty())
        undostack.pop();
}

void Actions::undo(Playlist& p)
{
    if(!undostack.empty())
    {
        redostack.push(p);
        p = undostack.top();
        undostack.pop();
    }
}

void Actions::redo(Playlist& p)
{
    if(!redostack.empty())
    {
        undostack.push(p);
        p = redostack.top();
        redostack.pop();
    }
}