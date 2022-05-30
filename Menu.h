#ifndef MUSIC_LIBRARY_MENU_H
#define MUSIC_LIBRARY_MENU_H

#include "string"
#include "Playlist.h"
#include "Actions.h"

//namespace menu {
//    enum command {NaC,add,del,update,list,search,listen,undo,redo,save,quit,help,clear};
//}

class menu {
public:
    enum command {NaC,add,del,update,list,search,listen,undo,redo,save,quit,help,clear,load};

    command ParseCommand(std::string cmd);
    command ParseCommand(const char* cmd);

    void DisplayHelpMessage();
    command GetUserCommand();

    void AfisareDeleteOptiuni();

    void AfisareSearchOptiuni();

    void AfisareListenOptiuni();

    void AfisareUpdateOptiuni();

    void StartLoop();

    static menu& GetInstance() {
        // Allocate with `new` in case IO is not trivially destructible.
        static menu* singleton = new menu();
        return *singleton;
    }

    void ClearScreen();

    Playlist playlist;
    Actions actions;
private:
    menu() = default;

    // Delete copy/move so extra instances can't be created/moved.
    menu(const menu&) = delete;
    menu& operator=(const menu&) = delete;
    menu(menu&&) = delete;
    menu& operator=(menu&&) = delete;
};

#endif