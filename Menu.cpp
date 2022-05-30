#include <cstring>
#include <iostream>
#include "Menu.h"

void menu::ClearScreen() {
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}

menu::command menu::ParseCommand(std::string cmd) {
    return ParseCommand(cmd.c_str());
}

menu::command menu::ParseCommand(const char *cmd) {
    if (strcmp(cmd,"add")==0)
        return add;
    if (strcmp(cmd,"del")==0)
        return del;
    if (strcmp(cmd,"list")==0)
        return list;
    if (strcmp(cmd,"search")==0)
        return search;
    if (strcmp(cmd,"update")==0)
        return update;
    if (strcmp(cmd,"listen")==0)
        return listen;
    if (strcmp(cmd,"undo")==0)
        return undo;
    if (strcmp(cmd,"redo")==0)
        return redo;
    if (strcmp(cmd,"save")==0)
        return save;
    if (strcmp(cmd,"quit")==0)
        return quit;
    if (strcmp(cmd,"clear")==0)
        return clear;
    if (strcmp(cmd,"load")==0)
        return load;
    if (strcmp(cmd,"help")==0)
        return help;
    return NaC;
}

#define MAX_STR_LEN 100

menu::command menu::GetUserCommand() {
    char inp[MAX_STR_LEN];
    std::cout<<"Introdu comanda ta\n";
    std::cin.getline(inp,MAX_STR_LEN);
    return ParseCommand(inp);
}

void menu::DisplayHelpMessage() {
    std::cout << "Scrie o comanda pentru a interactiona cu programul\n" <<
    "Comenziile prezente momentan sunt:\n" <<
    "add, del, list, search, update, listen, undo, redo, load, save, quit, help\n";
}

void menu::AfisareDeleteOptiuni() {
    int optiune;
    do {
        ClearScreen();
        std::cout << "0. Back\n" <<
        "1. Delete dupa index\n" <<
        "2. Delete dupa ISMN\n";
        std::cin >> optiune;
        ClearScreen();
        std::cin.ignore();
    } while(optiune < 0 || optiune > 2);

    bool ret;
    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            int index;
            std::cout << "Introdu indexul melodiei";
            std::cin >> index;
            std::cin.ignore();
            actions.add_state(playlist);
            ret = playlist.DeleteSongByIndex(index);
        }
            break;
        case 2:
        {
            std::string ismn;
            std::cout << "Introdu ISMN-ul melodiei";
            std::cin >> ismn;
            actions.add_state(playlist);
            ret = playlist.DeleteSongByIsmn(ismn);
        }
    }
    if(!ret)
        std::cout << "Melodia a fost stearsa\n";
    else
        actions.remove_last_state(), std::cout << "Melodia nu a fost gasita\n";
    //TODO: delete dupa ce a selectat userul
}

void menu::AfisareSearchOptiuni() {
    int optiune;
    do {
        ClearScreen();
        std::cout << "0. Back\n" <<
                  "1. Search dupa index\n" <<
                  "2. Search dupa ISMN\n" <<
                  "3. Search dupa Artist\n" <<
                  "4. Search dupa Gen\n" <<
                  "5. Search dupa Album\n";
        std::cin >> optiune;
        ClearScreen();
        std::cin.ignore();
    } while(optiune < 0 || optiune > 5);

    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            int index;
            std::cin>>index;
            std::cin.ignore();
            playlist.DisplaySongByCriteriu([&index](Song& song){
                if (index--==0) return true;
                return false;
            });
        }
            break;
        case 2:
        {
            std::string ismn;
            std::cin >> ismn;
            playlist.DisplaySongByCriteriu([&ismn](Song& song){
                return song.ISMN == ismn;
            });
        }
            break;
        case 3:
        {
            std::string artist;
            std::cin >> artist;
            playlist.DisplaySongByCriteriu([&artist](Song& song){
                return song.Artist == artist;
            });
        }
            break;
        case 4:
        {
            std::string genre;
            std::cin >> genre;
            playlist.DisplaySongByCriteriu([&genre](Song& song){
                return song.Genre == genre;
            });
        }
            break;
        case 5:
        {
            char inp[MAX_STR_LEN];
            std::cin.getline(inp,MAX_STR_LEN);
            std::string tmp = inp;
            playlist.DisplaySongByCriteriu([&tmp](Song& song){
                return song.Album == tmp;
            });
        }
            break;
    }

    //TODO: search dupa ce a selectat userul
}

void menu::AfisareListenOptiuni() {
    int optiune;
    do {
        ClearScreen();
        std::cout << "0. Back\n" <<
                  "1. Asculta dupa ISMN\n";
        std::cin >> optiune;
        ClearScreen();
        std::cin.ignore();
    } while(optiune < 0 || optiune > 1);

    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            std::string ismn;
            std::cin >> ismn;
            playlist.ListenToSongByIsmn(ismn) ? std::cout << "Melodia nu a fost gasita\n"
            : std :: cout << "Ai ascultat melodia cu succes\n";
        }
    }
}

void menu::AfisareUpdateOptiuni() {
    int optiune;
    do {
        ClearScreen();
        std::cout << "0. Back\n" <<
                  "1. Actualizeaza dupa ISMN\n" <<
                  "2. Actualizeaza dupa index\n";
        std::cin >> optiune;
        ClearScreen();
        std::cin.ignore();
    } while(optiune < 0 || optiune > 2);

    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            std::cout << "Introdu ISMN-ul melodiei pe care vrei sa o actualizezi\n";
            std::string ismn;
            std::cin >> ismn;
            std::cin.ignore();
            actions.add_state(playlist);
            if(playlist.UpdateSongByIsmn(ismn))
                std::cout << "Melodia nu a fost gasita\n";
            else
                actions.remove_last_state(), std::cout << "Melodia a fost actualizata\n";
        }
        case 2:
        {
            std::cout << "Introdu indexul melodiei pe care vrei sa o actualizezi\n";
            int imp;
            std::cin >> imp;
            std::cin.ignore();
            actions.add_state(playlist);
            if(playlist.UpdateSongByIndex(imp))
                std::cout << "Melodia nu a fost gasita\n";
            else
                actions.remove_last_state(), std::cout << "Melodia a fost actualizata\n";
        }
    }
}


void menu::StartLoop() {
    while (true) {
        auto cmd = GetUserCommand();
        switch (cmd) {
            case list:
                ClearScreen();
                std::cout << playlist;
                break;
            case clear:
                ClearScreen();
                break;
            case help:
                DisplayHelpMessage();
                break;
            case add:
                actions.add_state(playlist);
                playlist.append();
                break;
            case update:
                AfisareUpdateOptiuni();
                break;
            case save:
                playlist.SaveSongs();
                break;
            case load:
                playlist.ReadSongs();
                break;
            case quit:
                return;
            case del:
                AfisareDeleteOptiuni();
                break;
            case search:
                AfisareSearchOptiuni();
                break;
            case listen:
                AfisareListenOptiuni();
            case undo:
                actions.undo(playlist);
                break;
            case redo:
                actions.redo(playlist);
                break;
            default:
                break;
        }
    }
}
