#ifndef MUSIC_LIBRARY_SONG_H
#define MUSIC_LIBRARY_SONG_H

#include <vector>
#include <string>
#include "JSON.hpp"

#define MAX_LEN 100

class Song {
public:
    std::string ISMN; // International Standard Music Number
    std::string Title;
    //std::vector<std::string> Artist;
    //std::vector<std::string> Genre;
    std::string Artist;
    std::string Genre;
    std::string Album;
    int Streams;
    int Rating;
    int Duration;
    int Year;

    /**
     * @brief Class constructor
     * @param ismn - International Standard Music Number
     * @param title - song title
     * @param artist - song artist
     * @param genre - song genre
     * @param album - song album
     * @param streams - number of streams
     * @param rating - song rating
     * @param duration - song duration
     * @param year - song year
     */
    Song();
    //Song(std::string& ISMN, std::string& title, std::vector<std::string>& artists, std::vector<std::string>& genres, std::string& album, int streams, int rating, int duration, int year);
    Song(std::string& ISMN, std::string& title, std::string& artists, std::string& genres, std::string& album, int streams, int rating, int duration, int year);
    Song(nlohmann::json& json);
    ~Song();

    /**
     * @brief Function to stream the song
     */
    void listen();

    /**
     * @brief Function to get the song to a format with all details
     */
    std::string toString() const;

    /**
     * @brief Function to get the song to a json format
     */
    nlohmann::json getJson() const;

    /**
     * @brief Sets ISMN
     * @param ISMN - the new ISMN
     */
    void setISMN(std::string ISMN);
    /**
     * @brief Sets Title
     * @param title - the new title
     */
    void setTitle(std::string title);
    /**
     * @brief Sets Artist
     * @param artists - the new artists
     */
    void setArtist(std::string album);
    /**
     * @brief Sets Genre
     * @param genre - the new genre
     */
    void setGenre(std::string album);
    /**
     * @brief Sets Album
     * @param album - the new albun
     */
    void setAlbum(std::string album);
    /**
     * @brief Sets streams
     * @param streams - the new streams
     */
    void setStreams(int streams);
    /**
     * @brief Sets rating
     * @param rating - the new rating
     */
    void setRating(int rating);
    /**
     * @brief Sets duration
     * @param duration - the new duration
     */
    void setDuration(int duration);
    /**
     * @brief Sets year
     * @param year - the new year
     */
    void setYear(int year);
    /**
     * @brief Gets ISMN
     * @return ISMN
     */
    std::string getISMN() const;
    /**
     * @brief Gets Title
     * @return Title
     */
    std::string getTitle() const;
    /**
     * @brief Gets Artist
     * @return Artist
     */
    //std::vector<std::string> getArtist() const;
    std::string getArtist() const;
    /**
     * @brief Gets Genre
     * @return Genre
     */
    //std::vector<std::string> getGenre() const;
    std::string getGenre() const;
    /**
     * @brief Gets Album
     * @return Album
     */
    std::string getAlbum() const;
    /**
     * @brief Gets streams
     * @return streams
     */
    int getStreams() const;
    /**
     * @brief Gets rating
     * @return rating
     */
    int getRating() const;
    /**
     * @brief Gets duration
     * @return duration
     */
    int getDuration() const;
    /**
     * @brief Gets year
     * @return year
     */
    int getYear() const;

    friend std::ostream& operator<<(std::ostream& out, const Song& offer);
private:
};

#endif
