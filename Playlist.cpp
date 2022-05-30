#include "Playlist.h"
#include <functional>
#include <iostream>
#include "fstream"

Playlist::Playlist(std::string& Nume) : nume(Nume) {}
Playlist::Playlist(const char* Nume) : nume(Nume) {}

std::string Playlist::toString() const {
    std::ostringstream str;

    str << "<-- Playlist: " << nume << " -->" << std::endl;
    int index=0;
    for (auto& s : songs) {
        str << "Index: " << index++ << std::endl;
        str << s;
        str << "\n";
    }

    return str.str();
}

std::ostream& operator<<(std::ostream& out, const Playlist& playlist)
{
	out << playlist.toString();
	return out;
}

bool operator== (Playlist &lp,Playlist &rp)
{
    if (lp.songs.size() != rp.songs.size()) return false;
    for (auto& s : lp.songs) {
        auto ismn = s.getISMN();
        if (rp.FindSongByIsmn(ismn) == nullptr) return false;
    }
    return true;
}

void Playlist::append(Song &song) {
    songs.emplace_back(song);
    this->size++;
}

void Playlist::append() {
    songs.emplace_back(Song());
    this->size++;
}

Song* Playlist::FindSongByIsmn(std::string &ismn) {
    for (auto& song : songs)
        if (song.ISMN == ismn) return &song;
    return nullptr;
}

Song *Playlist::FindSongByIndex(size_t index) {
    int _index=0;
    for (auto& song : songs) {
        if (_index==index) return &song;
        _index++;
    }
    return nullptr;
}

Song *Playlist::FindSongByCriteriu(const std::function <bool (Song&)>& criteriu) {
    for (auto& song : songs)
        if (criteriu(song)) return &song;
    return nullptr;
}

bool Playlist::ListenToSongByIsmn(std::string& ismn){
    for (auto& song : songs)
        if (song.ISMN == ismn)
        {
            song.listen();
            return false;
        }
    return true;
}

bool Playlist::ListenToSongByIndex(size_t index){

    int _index=0;
    for (auto& song : songs) {
        if (_index==index)
        {
            song.listen();
            return false;
        }
        _index++;
    }
    return true;
}

bool Playlist::DeleteSongByIsmn(std::string &ismn) {
    for (auto i = songs.begin(); i!=songs.end(); i++) {
        if (i->ISMN == ismn) {
            songs.erase(i);
            this->size--;
            return false;
        }
    }
    return true;
}

bool Playlist::DeleteSongByIndex(size_t index) {
    if (index>this->size) return true;
    auto i=songs.begin();
    for (; index!=0; index--,i++) {}
    this->size--;
    songs.erase(i);
    return false;
}

bool Playlist::DeleteSongByCriteriu(const std::function <bool (Song&)>& criteriu) {
    auto i=songs.begin();
    for (auto& song : songs) {
        if (criteriu(song)) {
            songs.erase(i);
            this->size--;
            return false;
        }
        i++;
    }
    return true;
}

void Playlist::DisplaySongByCriteriu(const std::function <bool (Song&)>& criteriu) {
    int index=0;
    for (auto& song : songs) {
        //modifica ca la ambele sa fie << overloading
        if (criteriu(song))
        {
            std::cout<<"Index: "<<index<<"\n";
            std::cout<<song;
        }
        index++;
    }
}

bool Playlist::UpdateSongByIsmn(std::string &ismn) {
    for (auto& song : songs)
    {
        if (song.ISMN == ismn)
        {
            char inp[MAX_LEN];
            
            std::cout << "Introdu ISMN-ul melodiei:\n";
            std::cin.getline(inp,MAX_LEN);
            song.setISMN(inp);
            
            
            std::cout << "Introdu titlul melodiei:\n";
            std::cin.getline(inp,MAX_LEN);
            song.setTitle(inp);
            
            
            std::cout << "Introdu albumul din care face parte melodia:\n";
            std::cin.getline(inp,MAX_LEN);
            song.setAlbum(inp);
            
            std::cout << "Introdu artistul melodiei:\n";
            std::cin.getline(inp,MAX_LEN);
            song.setArtist(inp);


            std::cout << "Introdu genul melodiei:\n";
            std::cin.getline(inp,MAX_LEN);
            song.setGenre(inp);


            //   int artistsNr,genresNr;

            //             song.Artist.clear();

            //             std::cout << "Introdu numarul de artisti\n";
            //             std::cin >> artistsNr;
            //             std::cin.get();
            //             song.Artist.reserve(artistsNr); // alocam numarul de autori
            //             artistsNr++;

            //             for (int i = 1; i < artistsNr; i++) {
            //                 std::cout << "Introdu artistul cu numarul " << i << "\n";
            //                 std::cin.getline(inp,MAX_LEN);
            //                 song.Artist.emplace_back(inp);
            //             }

            //             song.Genre.clear();

            //             std::cout << "Introdu numarul de genuri\n";
            //             std::cin >> genresNr;
            //             std::cin.get();
            //             song.Genre.reserve(genresNr); // alocam numarul de genuri
            //             genresNr++;

            //             for (int i = 1; i < genresNr; i++) {
            //                 std::cout << "Introdu genul cu numarul " << i << "\n";
            //                 std::cin.getline(inp,MAX_LEN);
            //                 song.Genre.emplace_back(inp);

            //             }

            int i1,i2,i3,i4;

            std::cout << "Introdu numarul de streamuri\n";
            std::cin >> i1;
            song.setStreams(i1);
            std::cin.get();

            std::cout << "Introdu rating-ul melodiei (1-5)\n";
            std::cin >> i2;
            song.setRating(i2);
            std::cin.get();

            std::cout << "Introdu durata melodiei (in secunde)\n";
            std::cin >> i3;
            song.setDuration(i3);
            std::cin.get();

            std::cout << "Introdu anul lansarii melodiei\n";
            std::cin >> i4;
            song.setYear(i4);
            std::cin.get();

            return false;
        }        
    }

    return true;
}

bool Playlist::UpdateSongByIsmnDirect(std::string &ismn, Song s) {
    for (auto& song : songs)
    {
        if (song.ISMN == ismn)
        {
            song = s;
            return false;
        }
    }

    return true;
}

bool Playlist::UpdateSongByIndex(size_t index) {
    int _index=0;
    for (auto& song : songs)
    {
        if (_index == index)
        {
            char inp[MAX_LEN];
            
            std::cout << "Introdu ISMN-ul melodiei:\n";
            std::cin.getline(inp,MAX_LEN);
            song.setISMN(inp);
            
            
            std::cout << "Introdu titlul melodiei:\n";
            std::cin.getline(inp,MAX_LEN);
            song.setTitle(inp);
            
            
            std::cout << "Introdu albumul din care face parte melodia:\n";
            std::cin.getline(inp,MAX_LEN);
            song.setAlbum(inp);

            std::cout << "Introdu albumul din care face parte melodia:\n";
            std::cin.getline(inp,MAX_LEN);
            song.setAlbum(inp);

            std::cout << "Introdu albumul din care face parte melodia:\n";
            std::cin.getline(inp,MAX_LEN);
            song.setAlbum(inp);
            
            std::cout << "Introdu artistul melodiei:\n";
            std::cin.getline(inp,MAX_LEN);
            song.setArtist(inp);

            std::cout << "Introdu genul melodiei:\n";
            std::cin.getline(inp,MAX_LEN);
            song.setGenre(inp);

            //   int artistsNr,genresNr;

            //             song.Artist.clear();

            //             std::cout << "Introdu numarul de artisti\n";
            //             std::cin >> artistsNr;
            //             std::cin.get();
            //             song.Artist.reserve(artistsNr); // alocam numarul de autori
            //             artistsNr++;

            //             for (int i = 1; i < artistsNr; i++) {
            //                 std::cout << "Introdu artistul cu numarul " << i << "\n";
            //                 std::cin.getline(inp,MAX_LEN);
            //                 song.Artist.emplace_back(inp);
            //             }

            //             song.Genre.clear();

            //             std::cout << "Introdu numarul de genuri\n";
            //             std::cin >> genresNr;
            //             std::cin.get();
            //             song.Genre.reserve(genresNr); // alocam numarul de genuri
            //             genresNr++;

            //             for (int i = 1; i < genresNr; i++) {
            //                 std::cout << "Introdu genul cu numarul " << i << "\n";
            //                 std::cin.getline(inp,MAX_LEN);
            //                 song.Genre.emplace_back(inp);

            //             }

            int i1,i2,i3,i4;

            std::cout << "Introdu numarul de streamuri\n";
            std::cin >> i1;
            song.setStreams(i1);
            std::cin.get();

            std::cout << "Introdu rating-ul melodiei (1-5)\n";
            std::cin >> i2;
            song.setRating(i2);
            std::cin.get();

            std::cout << "Introdu durata melodiei (in secunde)\n";
            std::cin >> i3;
            song.setDuration(i3);
            std::cin.get();

            std::cout << "Introdu anul lansarii melodiei\n";
            std::cin >> i4;
            song.setYear(i4);
            std::cin.get();

            return false;
        }
        _index++;
    }

    return true;
}

bool Playlist::UpdateSongByIndexDirect(size_t index, Song s) {
    int _index=0;
    for (auto& song : songs)
    {
        if (_index == index)
        {
            song = s;

            return false;
        }
        _index++;
    }

    return true;
}

size_t Playlist::GetSize(){
    return this->size;
}

std::list<Song> Playlist::GetSongs(){
    return this->songs;
}

void Playlist::ReadSongs(std::istream& stream) {
    nlohmann::json json;
    stream >> json;

    nlohmann::json outJson;
    for (auto& it : json["Songs"]) {
        outJson = nlohmann::json::parse(it.dump());
        songs.emplace_back(outJson);
    }

    this->size = json["size"];
}

void Playlist::ReadSongs(const std::string& file) {
    std::fstream stream;
    stream.open(file, std::fstream::in);
    if (stream.fail()) return;
    ReadSongs(stream);
}

void Playlist::ReadSongs(const char* file) {
    std::fstream stream;
    stream.open(file, std::fstream::in);
    if (stream.fail()) return;
    ReadSongs(stream);
}

void Playlist::ReadSongs() {
    ReadSongs(this->nume);
}

void Playlist::SaveSongs(std::ostream& stream) {
    nlohmann::json json;
    int _index = 0;
    for (Song& song : songs) {
        if(_index > this->size - 1) break;
        json["Songs"].push_back(song.getJson());
        _index++;
    }
    json["size"] = this->size;

    stream<<json;
}

void Playlist::SaveSongs(const char* file) {
    std::fstream stream;
    stream.open(file, std::fstream::out);
    SaveSongs(stream);
}

void Playlist::SaveSongs(const std::string& file) {
    std::fstream stream;
    stream.open(file, std::fstream::out);
    SaveSongs(stream);
}

void Playlist::SaveSongs() {
    SaveSongs(this->nume);
}

Playlist::~Playlist()
{
    this->songs.clear();
}

Playlist::Playlist() = default;
