#include "Movie.hpp"
#include "MovieLoader.hpp"
#include "KeyValueAVLTree.hpp"
#include <chrono>
#include <iostream>

int main() {
    const std::string filename = "MoviesOnStreamingPlatforms.csv";
    KeyValueAVLTree<int, std::vector<Movie>> avlYear;
    KeyValueAVLTree<bool, std::vector<Movie>> avlNetflix;
    KeyValueAVLTree<bool, std::vector<Movie>> avlHulu;
    KeyValueAVLTree<bool, std::vector<Movie>> avlPrimeVideo;
    KeyValueAVLTree<bool, std::vector<Movie>> avlDisney;

    // Load movies into the tree and calculate building tree time
    auto start = std::chrono::high_resolution_clock::now();
    KeyValueAVLTree<int, Movie> movieTree = loadMoviesToAvlTree(filename);

    // Insert movies into AVL tree based on year
    for (const auto& moviePair : movieTree.inorder_traversal()) {
        const Movie& movie = moviePair.second;
        auto node = avlYear.find(movie.getYear());
        if (node) {
            node->value.push_back(movie);
        } else {
            avlYear.insert(movie.getYear(), std::vector<Movie>{movie});
        }
    }
    
    // Insert movies into AVL tree based on streaming platforms
    for (const auto& moviePair : movieTree.inorder_traversal()) {
        const Movie& movie = moviePair.second;

        // Netflix
        auto netflixNode = avlNetflix.find(movie.isNetflix());
        if (netflixNode) {
            netflixNode->value.push_back(movie);
        } else {
            avlNetflix.insert(movie.isNetflix(), std::vector<Movie>{movie});
        }

        // Hulu
        auto huluNode = avlHulu.find(movie.isHulu());
        if (huluNode) {
            huluNode->value.push_back(movie);
        } else {
            avlHulu.insert(movie.isHulu(), std::vector<Movie>{movie});
        }

        // Prime Video
        auto primeNode = avlPrimeVideo.find(movie.isPrimeVideo());
        if (primeNode) {
            primeNode->value.push_back(movie);
        } else {
            avlPrimeVideo.insert(movie.isPrimeVideo(), std::vector<Movie>{movie});
        }

        // Disney+
        auto disneyNode = avlDisney.find(movie.isDisneyPlus());
        if (disneyNode) {
            disneyNode->value.push_back(movie);
        } else {
            avlDisney.insert(movie.isDisneyPlus(), std::vector<Movie>{movie});
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken to build the AVL trees: " << duration.count() << " seconds" << std::endl;

    // Ask the user for the year
    int searchYear;
    std::cout << "Enter the year you want to search for: ";
    std::cin >> searchYear;

    // Ask the user for the platform
    int searchPlatform;
    std::cout << "Do you wish for it to be in a specific platform?: " << std::endl;
    std::cout << "1: Netflix" << std::endl;
    std::cout << "2: Hulu" << std::endl;
    std::cout << "3: Prime Video" << std::endl;
    std::cout << "4: Disney+" << std::endl;
    std::cout << "5: No preference" << std::endl;
    std::cin >> searchPlatform;

    // Function to print movie details
    auto printMovies = [](const std::vector<Movie>& movies) {
        for (const auto& movie : movies) {
            std::cout << "--------------------------------------------" << std::endl;
            std::cout << movie << "\n";
            std::cout << "--------------------------------------------" << std::endl;
        }
    };

    // Search for movies in the specified year and platform
    for(int i = 0; i < 20; i++) {
        start = std::chrono::high_resolution_clock::now();
        KeyValueAVLNode<int, std::vector<Movie>>* yearNode = avlYear.find(searchYear);
        if (yearNode && !yearNode->value.empty()) {
            std::vector<Movie> filteredMovies;
            for (const auto& movie : yearNode->value) {
                bool matchesPlatform = false;
                switch (searchPlatform) {
                    case 1: matchesPlatform = movie.isNetflix(); break;
                    case 2: matchesPlatform = movie.isHulu(); break;
                    case 3: matchesPlatform = movie.isPrimeVideo(); break;
                    case 4: matchesPlatform = movie.isDisneyPlus(); break;
                    case 5: matchesPlatform = true; break; // No preference
                }
                if (matchesPlatform) {
                    filteredMovies.push_back(movie);
                }
            }

            if (!filteredMovies.empty()) {
                std::cout << "Movies from the year " << searchYear;
                if (searchPlatform != 5) {
                    std::cout << " and on the selected platform";
                }
                std::cout << ":\n";
                printMovies(filteredMovies);
            } else {
                std::cout << "No movies found for the year " << searchYear << " on the selected platform.\n";
            }
        } else {
            std::cout << "No movies found for the year " << searchYear << ".\n";
        }

        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationFindYear = end - start;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "Time taken to find the movies from the year " << searchYear << ": " << durationFindYear.count() << " seconds" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;

        searchYear++;
    }

    return 0;
}
