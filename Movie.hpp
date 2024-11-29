#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <string>
#include <iostream>

class Movie {
private:
    int id;
    std::string title;
    int year;
    std::string age;
    std::string rottenTomatoes;
    bool netflix;
    bool hulu;
    bool primeVideo;
    bool disneyPlus;
    int type;

public:
    Movie() 
        : id(0), title(""), year(0), age(""), 
          rottenTomatoes(""), netflix(false), 
          hulu(false), primeVideo(false), 
          disneyPlus(false), type(0) {}

    Movie(int id, const std::string& title, int year, const std::string& age,
          const std::string& rottenTomatoes, bool netflix, bool hulu,
          bool primeVideo, bool disneyPlus, int type)
        : id(id), title(title), year(year), age(age),
          rottenTomatoes(rottenTomatoes), netflix(netflix), hulu(hulu),
          primeVideo(primeVideo), disneyPlus(disneyPlus), type(type) {}

    // Getters
    int getId() const { return id; }
    std::string getTitle() const { return title; }
    int getYear() const { return year; }
    std::string getAge() const { return age; }
    std::string getRottenTomatoes() const { return rottenTomatoes; }
    bool isNetflix() const { return netflix; }
    bool isHulu() const { return hulu; }
    bool isPrimeVideo() const { return primeVideo; }
    bool isDisneyPlus() const { return disneyPlus; }
    int getType() const { return type; }

    bool isAvailableOnService(int service) const {
        switch(service) {
            case 1: return netflix;
            case 2: return primeVideo;
            case 3: return disneyPlus;
            case 4: return hulu;
            default: return false;
        }
    }
};

std::ostream& operator<<(std::ostream& os, const Movie& m) {
    os << "Title: " << m.getTitle() << "\n"
       << "Year: " << m.getYear() << "\n";
    if (!m.getAge().empty()) {
        os << "Age: " << m.getAge() << "\n";
    }
    os << "Rotten Tomatoes: " << m.getRottenTomatoes() << "\n"
       << "Available on Netflix: " << (m.isNetflix() ? "Yes" : "No") << "\n"
       << "Available on Hulu: " << (m.isHulu() ? "Yes" : "No") << "\n"
       << "Available on Prime Video: " << (m.isPrimeVideo() ? "Yes" : "No") << "\n"
       << "Available on Disney+: " << (m.isDisneyPlus() ? "Yes" : "No") << "\n"
       << "Type: " << m.getType() << "\n";
    return os;
}


#endif
