#ifndef MUSIC_LIBRARY_ACTIONS_H
#define MUSIC_LIBRARY_ACTIONS_H

#include <stack>
#include "Playlist.h"
#include <iostream>

class Actions {
public:
    Actions();
    void add_state(Playlist& p);
    void remove_last_state();
    void undo(Playlist& p);
    void redo(Playlist& p);
    void test();
private:
    std::stack<Playlist> undostack;
    std::stack<Playlist> redostack;
};

#endif
