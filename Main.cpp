#include <iostream>
#include "fstream"
#include "Song.h"
#include "Playlist.h"
#include "JSON.hpp"
#include "Menu.h"

#define NUME_DB "db.json"

int main() {
    menu::GetInstance().playlist.nume = NUME_DB;
    menu::GetInstance().playlist.ReadSongs();
    menu::GetInstance().DisplayHelpMessage();
    menu::GetInstance().StartLoop();

    return 0;
}
