#ifndef MUSIC_LIBRARY_PLAYLIST_H
#define MUSIC_LIBRARY_PLAYLIST_H

#include "Song.h"
#include <list>

//mergem pe un sistem similar cu cel din go, in care vom folosi un bool pentru a returna 1 cand avem o eroare
class Playlist {
public:
    /**
     * @brief Class constructor
     * @param nume - playlist name
     */
    Playlist();
    explicit Playlist(std::string& nume);
    explicit Playlist(const char* nume);

    ~Playlist();

    /**
     * @brief Add a song to the playlist
     * @param song - song that will be added
     */
    void append(Song& s);
    void append();

    Song* FindSongByIsmn(std::string& ismn);
    Song* FindSongByIndex(size_t index);
    Song* FindSongByCriteriu(const std::function <bool (Song&)>& criteriu);

    /**
     * @brief Listen to a song
     * @param index - song index
     * @return false if the song was played, true otherwise
     */
    bool ListenToSongByIsmn(std::string& ismn);
    bool ListenToSongByIndex(size_t index);
    
    bool DeleteSongByIsmn(std::string& ismn);
    bool DeleteSongByIndex(size_t index);
    bool DeleteSongByCriteriu(const std::function <bool (Song&)>& criteriu);

    void DisplaySongByCriteriu(const std::function <bool (Song&)>& criteriu);

    bool UpdateSongByIsmn(std::string& ismn);
    bool UpdateSongByIndex(size_t index);

    bool UpdateSongByIsmnDirect(std::string& ismn, Song);
    bool UpdateSongByIndexDirect(size_t index, Song);

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& out, const Playlist& p);

    friend bool operator== (Playlist &lp,Playlist &rp); 

    /**
     * @brief Reads the songs from a file
     * @param nume - the name of the file
     */
    void ReadSongs(std::istream&);
    void ReadSongs(const char*);
    void ReadSongs();
    void ReadSongs(const std::string&);

    /**
     * @brief Writes the songs to a file
     * @param nume - the name of the file
     */
    void SaveSongs(std::ostream&);
    void SaveSongs(const std::string&);
    void SaveSongs(const char*);
    void SaveSongs();

    size_t GetSize();
    std::list<Song> GetSongs();

    std::string nume; //folosit pt nume fisier
private:
    std::list<Song> songs;
    size_t size = 0;
};

#endif
