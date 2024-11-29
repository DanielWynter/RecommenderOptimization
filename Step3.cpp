#include "Movie.hpp"
#include "WeightedUndirectedGraph.hpp"
#include "KeyValueAVLTree.hpp"
#include "MovieLoader.hpp"
#include <chrono>
#include <iostream>

void displayNeighbors(const Graph& graph, const std::string& title) {
    std::cout << "\n=============================\n";
    std::cout << "Neighbors of \"" << title << "\":\n";
    std::cout << "=============================\n";
    graph.displayAdjacent(title);
}

int main() {
    const std::string filename = "MoviesOnStreamingPlatforms.csv";
    KeyValueAVLTree<int, Movie> movieTree = loadMoviesToAvlTree(filename);
    Graph movieGraph;

    // Add nodes to the graph
    for (const auto& moviePair : movieTree.inorder_traversal()) {
        const Movie& movie = moviePair.second;
        movieGraph.add_vertex(movie.getTitle());
    }

    // Add edges based on similarity
    double similarityThreshold = 0.5;
    auto movies = movieTree.inorder_traversal();
    for (size_t i = 0; i < movies.size(); ++i) {
        for (size_t j = i + 1; j < movies.size(); ++j) {
            const Movie& m1 = movies[i].second;
            const Movie& m2 = movies[j].second;
            double similarity = calculateSimilarity(m1, m2);
            if (similarity >= similarityThreshold) {
                double weight = 1.0 - similarity;
                movieGraph.add_edge(m1.getTitle(), m2.getTitle(), weight);
            }
        }
    }

    std::vector<std::string> movieTitles = {
        "The Irishman", "Dangal", "Roma", "Okja", "Virunga",
        "Mudbound", "Swades", "Fyre", "Miss Americana", "Black Friday",
        "Lagaan: Once Upon a Time in India", "The Social Dilemma",
        "The Ballad of Buster Scruggs", "The Trial of the Chicago 7",
        "Article 15", "To All the Boys I've Loved Before",
        "Jim & Andy: The Great Beyond", "Dolemite Is My Name",
        "Big Sharks Rule", "Man Among Cheetahs"
    };

    for (const auto& title : movieTitles) {
        displayNeighbors(movieGraph, title);
    }

    return 0;
}
