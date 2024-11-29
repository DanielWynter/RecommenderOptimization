#ifndef WEIGHTED_UNDIRECTED_GRAPH_HPP
#define WEIGHTED_UNDIRECTED_GRAPH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include "Movie.hpp" // Include Movie.hpp

using namespace std;

class Graph {
private:
    unordered_map<string, vector<pair<string, double>>> adjacencyList;
    vector<string> vertices_;
    unordered_map<string, size_t> mapping_;

public:
    void add_vertex(const string& v) {
        if (contains_vertex(v)) {
            std::cout << "Vertex with the same id already exists" << std::endl;
            return;
        }        
        vertices_.push_back(v);
        mapping_[v] = vertices_.size() - 1;
    }

    void add_edge(const string& movie1, const string& movie2, double weight) {
        adjacencyList[movie1].emplace_back(movie2, weight);
        adjacencyList[movie2].emplace_back(movie1, weight);
    }

    vector<pair<string, double>> getNeighbors(const string& movie) const {
        if (adjacencyList.find(movie) != adjacencyList.end()) {
            return adjacencyList.at(movie);
        }
        return {};
    }

    void displayAdjacent(const string& movie) const {
        cout << "Neighbors of \"" << movie << "\":\n";
        auto neighbors = getNeighbors(movie);
        if (!neighbors.empty()) {
            for (const auto& neighbor : neighbors) {
                cout << " - " << neighbor.first << " (weight: " << neighbor.second << ")" << endl;
            }
        } else {
            cout << "The movie \"" << movie << "\" has no adjacent movies or is not in the graph." << endl;
        }
    }

    bool contains_vertex(const string& v) const {
        return mapping_.find(v) != mapping_.end();
    }

    vector<string> bfs(const string& start) const {
        vector<string> result;
        if (!contains_vertex(start)) return result;

        unordered_map<string, bool> visited;
        queue<string> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            string current = q.front();
            q.pop();
            result.push_back(current);

            for (const auto& neighbor : getNeighbors(current)) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        return result;
    }

    vector<string> dfs(const string& start) const {
        vector<string> result;
        if (!contains_vertex(start)) return result;

        unordered_map<string, bool> visited;
        stack<string> s;

        s.push(start);

        while (!s.empty()) {
            string current = s.top();
            s.pop();

            if (!visited[current]) {
                visited[current] = true;
                result.push_back(current);

                for (const auto& neighbor : getNeighbors(current)) {
                    if (!visited[neighbor.first]) {
                        s.push(neighbor.first);
                    }
                }
            }
        }
        return result;
    }

    bool find_path_bfs(const string& start, const string& end, vector<string>& path) const {
        if (!contains_vertex(start) || !contains_vertex(end)) return false;

        unordered_map<string, bool> visited;
        unordered_map<string, string> parent;
        queue<string> q;

        visited[start] = true;
        q.push(start);
        parent[start] = "";

        while (!q.empty()) {
            string current = q.front();
            q.pop();

            if (current == end) {
                string step = end;
                while (!step.empty()) {
                    path.push_back(step);
                    step = parent[step];
                }
                reverse(path.begin(), path.end());
                return true;
            }

            for (const auto& neighbor : getNeighbors(current)) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    parent[neighbor.first] = current;
                    q.push(neighbor.first);
                }
            }
        }
        return false;
    }

    bool find_path_dfs(const string& start, const string& end, vector<string>& path) const {
        if (!contains_vertex(start) || !contains_vertex(end)) return false;

        unordered_map<string, bool> visited;
        unordered_map<string, string> parent;
        stack<string> s;

        s.push(start);
        parent[start] = "";

        while (!s.empty()) {
            string current = s.top();
            s.pop();

            if (!visited[current]) {
                visited[current] = true;

                if (current == end) {
                    string step = end;
                    while (!step.empty()) {
                        path.push_back(step);
                        step = parent[step];
                    }
                    reverse(path.begin(), path.end());
                    return true;
                }

                for (const auto& neighbor : getNeighbors(current)) {
                    if (!visited[neighbor.first]) {
                        parent[neighbor.first] = current;
                        s.push(neighbor.first);
                    }
                }
            }
        }
        return false;
    }

    double calculate_path_distance(const vector<string>& path) const {
        double distance = 0.0;
        for (size_t i = 1; i < path.size(); ++i) {
            for (const auto& neighbor : getNeighbors(path[i - 1])) {
                if (neighbor.first == path[i]) {
                    distance += neighbor.second;
                    break;
                }
            }
        }
        return distance;
    }
};

double calculateSimilarity(const Movie& movie1, const Movie& movie2) {
    double similarity = 0.0;
    int totalCharacteristics = 5;

    if (movie1.getYear() == movie2.getYear()) similarity += 1.0;
    if (movie1.isNetflix() == movie2.isNetflix()) similarity += 1.0;
    if (movie1.isHulu() == movie2.isHulu()) similarity += 1.0;
    if (movie1.isPrimeVideo() == movie2.isPrimeVideo()) similarity += 1.0;
    if (movie1.isDisneyPlus() == movie2.isDisneyPlus()) similarity += 1.0;

    return similarity / totalCharacteristics;
}

#endif
