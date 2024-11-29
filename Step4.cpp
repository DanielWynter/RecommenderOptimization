#include "Movie.hpp"
#include "WeightedUndirectedGraph.hpp"
#include "KeyValueAVLTree.hpp"
#include "MovieLoader.hpp"
#include <chrono>
#include <iostream>
#include <iomanip>

void performBFS(const Graph& graph, const std::string& startMovie) {
    std::vector<std::string> bfsResult = graph.bfs(startMovie);
    std::cout << "\n****************************\n";
    std::cout << "BFS Traversal from \"" << startMovie << "\":\n";
    std::cout << "****************************\n";
    for (size_t i = 0; i < bfsResult.size(); ++i) {
        std::cout << std::setw(2) << i+1 << ". " << bfsResult[i] << "\n";
    }
    std::cout << "****************************\n";
}

void performDFS(const Graph& graph, const std::string& startMovie) {
    std::vector<std::string> dfsResult = graph.dfs(startMovie);
    std::cout << "\n++++++++++++++++++++++++++++\n";
    std::cout << "DFS Traversal from \"" << startMovie << "\":\n";
    std::cout << "++++++++++++++++++++++++++++\n";
    for (size_t i = 0; i < dfsResult.size(); ++i) {
        std::cout << std::setw(2) << i+1 << ". " << dfsResult[i] << "\n";
    }
    std::cout << "++++++++++++++++++++++++++++\n";
}

void verifyPaths(const Graph& graph, const std::vector<std::pair<std::string, std::string>>& moviePairs) {
    for (const auto& pair : moviePairs) {
        const std::string& movie1 = pair.first;
        const std::string& movie2 = pair.second;
        std::vector<std::string> path;

        std::cout << "\n=============================\n";
        std::cout << "Verifying path between \"" << movie1 << "\" and \"" << movie2 << "\":\n";
        std::cout << "=============================\n";

        if (graph.find_path_bfs(movie1, movie2, path)) {
            std::cout << "Path found with BFS:\n";
            for (const auto& movie : path) {
                std::cout << movie << " -> ";
            }
            std::cout << "end\n";
            double distance = graph.calculate_path_distance(path);
            std::cout << "Distance: " << distance << "\n";
        } else {
            std::cout << "No path found with BFS.\n";
        }

        path.clear();
        if (graph.find_path_dfs(movie1, movie2, path)) {
            std::cout << "Path found with DFS:\n";
            for (const auto& movie : path) {
                std::cout << movie << " -> ";
            }
            std::cout << "end\n";
            double distance = graph.calculate_path_distance(path);
            std::cout << "Distance: " << distance << "\n";
        } else {
            std::cout << "No path found with DFS.\n";
        }

        std::cout << "=============================\n";
    }
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

    // Perform BFS and DFS from a product and display results
    std::vector<std::string> startMovies = {
        "Roma", "Okja", "The Irishman", "Virunga", "Swades"
    };

    for (const auto& startMovie : startMovies) {
        performBFS(movieGraph, startMovie);
        performDFS(movieGraph, startMovie);
    }

    // Verify paths between pairs of movies and display the distances
    std::vector<std::pair<std::string, std::string>> moviePairs = {
        {"Roma", "Okja"},
        {"The Irishman", "Virunga"},
        {"Dangal", "Mudbound"},
        {"Miss Americana", "Fyre"},
        {"Lagaan: Once Upon a Time in India", "The Social Dilemma"}
    };

    verifyPaths(movieGraph, moviePairs);

    return 0;
}
