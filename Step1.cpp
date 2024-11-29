#include "Movie.hpp"
#include "MovieLoader.hpp"
#include "KeyValueAVLTree.hpp"
#include <chrono>

int main() {
    const std::string filename = "MoviesOnStreamingPlatforms.csv";

    //Calculate the duration of loading movies into the tree
    auto start = std::chrono::high_resolution_clock::now();
    KeyValueAVLTree<int, Movie> movieTree = loadMoviesToAvlTree(filename);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    //Print time and movies in-order traversal by ID
    std::cout << "Movies loaded in AVL Tree (In-Order Traversal):" << std::endl;
    movieTree.print_inorder();

    //Search for a specific movie by ID
    int searchId = 9500;
    for (int i = 0; i < 20; i++){
        start = std::chrono::high_resolution_clock::now();
        KeyValueAVLNode<int, Movie>* foundNode = movieTree.find(searchId);
        if (foundNode) {
            end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationFind = end - start;
            std::cout << "--------------------------------------------" << std::endl;
            std::cout << "Movie with ID " << searchId << " found:" << std::endl;
            std::cout << foundNode->value << std::endl;
            std::cout << "Time taken to find the movie: " << durationFind.count() << " seconds" << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
        } 
        else {
            end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationFind = end - start;
            std::cout << "Movie with ID " << searchId << " not found." << std::endl;
            std::cout << "Time taken to look the movie up: " << durationFind.count() << " seconds" << std::endl;
        }
        searchId++;
    }

    std::cout << "Time taken to build the AVL tree: " << duration.count() << " seconds" << std::endl;
    return 0;
}
