#ifndef MOVIELOADER_HPP
#define MOVIELOADER_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include "KeyValueAVLTree.hpp"
#include "Movie.hpp"

// Function to change a string to an int
int stringToInt(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (...) {
        return 0;
    }
}

// Function to change a string to a bool
bool stringToBool(const std::string& str) {
    return str == "1";
}

// Load movies into an KeyValueAVLTree
KeyValueAVLTree<int, Movie> loadMoviesToAvlTree(const std::string& filename) {
    KeyValueAVLTree<int, Movie> movieTree;
    std::ifstream file(filename);
    std::string line, cell;

    if (file.is_open()) {
        std::getline(file, line); // Skip header

        while (std::getline(file, line)) {
            std::stringstream lineStream(line);
            int id, year, type;
            std::string title, age, rottenTomatoes;
            bool netflix, hulu, primeVideo, disneyPlus;

            // Read values from CSV
            std::getline(lineStream, cell, ','); // Skip unnecessary field
            std::getline(lineStream, cell, ',');
            id = stringToInt(cell);
            std::getline(lineStream, title, ',');
            std::getline(lineStream, cell, ',');
            year = stringToInt(cell);
            std::getline(lineStream, age, ',');
            std::getline(lineStream, rottenTomatoes, ',');

            std::getline(lineStream, cell, ',');
            netflix = stringToBool(cell);
            std::getline(lineStream, cell, ',');
            hulu = stringToBool(cell);
            std::getline(lineStream, cell, ',');
            primeVideo = stringToBool(cell);
            std::getline(lineStream, cell, ',');
            disneyPlus = stringToBool(cell);

            std::getline(lineStream, cell, ',');
            type = stringToInt(cell);

            // Sort valid data and load it
            if (year > 1900 && !rottenTomatoes.empty()) {
                Movie movie(id, title, year, age, rottenTomatoes, netflix, hulu, primeVideo, disneyPlus, type);

                // Insert into the AVL Tree using Id as the key
                movieTree.insert(id, movie);
            }
        }
        file.close();
    } else {
        std::cout << "Couldn't load file." << std::endl;
    }

    return movieTree;
}

#endif
