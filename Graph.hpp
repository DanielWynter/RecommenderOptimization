﻿#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

//Structure that defines an edge in a graph.
struct edge {

    std::string v1;          /**< The first vertex of the edge. */
    std::string v2;          /**< The second vertex of the edge. */
    double weight;

};

//Class that defines an undirected graph.
class Graph {
public:

    //Default constructor. 
    Graph() = default;
    //Clears the graph.
    void clear()
    {
        vertices_.clear();
        edges_.clear();
        mapping_.clear();
    }
    //Returns the vector with the vertices of the graph.
    const std::vector<std::string>& vertices() const 
    { 
        return vertices_; 
    }

    //Returns the vector with the edges of the graph.
    const std::vector<edge>& edges() const
    {
        return edges_;
    }

    //Checks if the graph is empty.
    bool empty() const
    {
        return vertices_.empty();
    }

    //Adds a new vertex to the graph.
    void add_vertex(const std::string& v)
    {
        // Check if the vertex already exists
        if (contains_vertex(v)) {
            std::cout << "Vertex with the same id already exists" << std::endl;
            return;
        }        
        
        // Add the vertex to the collection of vertices.
        vertices_.push_back({ v });

        // Add the vertex to the mapping.
        mapping_[v] = vertices_.size() - 1;
    }

    //Removes the specified vertex from the graph.
    void remove_vertex(const std::string& v)
    {
        // Check if the vertex exists
        if (mapping_.find(v) == mapping_.end()) {
            std::cout << "Vertex with the id does not exist" << std::endl;
            return;
        }

        // Remove the vertex from the mapping.
        mapping_.erase(v);

        // Remove the vertex from the collection of vertices.                
        auto new_vertices_end = std::remove(vertices_.begin(), vertices_.end(), v);
        vertices_.erase(new_vertices_end, vertices_.end());

        // Remove the edges that contain the vertex.
        auto new_edges_end = std::remove_if(edges_.begin(), edges_.end(),
            [&v](const edge& edge) {
                return edge.v1 == v || edge.v2 == v;
            });

        edges_.erase(new_edges_end, edges_.end());

    }

    //Checks if the graph contains the specified vertex.
    bool contains_vertex(const std::string& v) const
    {
        return mapping_.find(v) != mapping_.end();
    }

    //Adds a new edge to the graph.
    void add_edge(const std::string& v1, const std::string& v2)
    {
        // Check if the vertices exist
        if (!contains_vertex(v1) || !contains_vertex(v2)) {
            std::cout << "One or more vertices do not exist" << std::endl;
            return;
        }

        // Check if the edge is a loop
        if (v1 == v2) {
            std::cout << "The edge is a loop" << std::endl;
            return;
        }

        // Check if the edge already exists
        if (contains_edge(v1, v2)) {
            std::cout << "The edge already exist" << std::endl;
            return;
        }

        // Add the edge to the collection of edges.
        edges_.push_back({ v1, v2 });
    }

    //Adds a new edge to the graph.
    void add_edge(const std::string& v1, const std::string& v2, double weight)
    {
        // Check if the vertices exist
        if (!contains_vertex(v1) || !contains_vertex(v2)) {
            std::cout << "One or more vertices do not exist" << std::endl;
            return;
        }

        // Check if the edge is a loop
        if (v1 == v2) {
            std::cout << "The edge is a loop" << std::endl;
            return;
        }

        // Check if the edge already exists
        if (contains_edge(v1, v2)) {
            std::cout << "The edge already exist" << std::endl;
            return;
        }

        // Add the edge to the collection of edges.
        edges_.push_back({ v1, v2, weight});
    }

    //Removes the specified edge from the graph.
    void remove_edge(const std::string& v1, const std::string& v2)
    {
        // Check if the edge exists
        if (!contains_edge(v1, v2)) {
            std::cout << "The edge does not exist" << std::endl;
            return;
        }

        // Remove the edge from the collection of edges.
        auto new_edges_end = std::remove_if(edges_.begin(), edges_.end(),
            [&v1, &v2](const edge& edge) {
                return (edge.v1 == v1 && edge.v2 == v2) || (edge.v1 == v2 && edge.v2 == v1);
            });

        edges_.erase(new_edges_end, edges_.end());
    }

    //Checks if the graph contains the specified edge.
    bool contains_edge(const std::string& v1, const std::string& v2) const
    {
        for (const auto& ei : edges_) {
            if ((ei.v1 == v1 && ei.v2 == v2) || (ei.v1 == v2 && ei.v2 == v1))
                return true;
        }

        return false;
    }

    //Returns the neighbors of the specified vertex.
    std::vector<std::string> neighbors(const std::string& v) const
    {   
        std::vector<std::string> result;

        for (const auto& e : edges_) {
            if (e.v1 == v)
                result.push_back(vertices_[mapping_.at(e.v2)]);
            else if (e.v2 == v)
                result.push_back(vertices_[mapping_.at(e.v1)]);
        }

        return result;
    }

    //Returns the degree of the specified vertex.
    unsigned long long degree(const std::string& v) const
    {
        return neighbors(v).size();
    }

    //Traverses the vertices of the graph starting from the specified vertex using a breadth-first search (BFS) algorithm.
    std::vector<std::string> bfs(const std::string& start) const
    {
        // Check if the graph is empty
        if (vertices_.empty()) {
            std::cout << "Graph is empty" << std::endl;
            return std::vector<std::string>();
        }

        // Check if the vertex exists
        if (!contains_vertex(start)) {
            std::cout << "Vertex with the id does not exists" << std::endl;
            return std::vector<std::string>();
        }

        // Print the BFS traversal message
        std::cout << "BFS traversal from " << start << ": ";

        // Initialize the explored array and the frontier queue
        std::vector<bool> explored(vertices_.size(), false);
        std::queue<std::string> frontier;
        std::vector<std::string> visited;

        // Add the first vertex to the frontier
        frontier.push(start);
        explored[mapping_.at(start)] = true;

        // Perform the BFS traversal
        while (!frontier.empty()) {

            auto current = frontier.front();
            frontier.pop();
            size_t currentIndex = mapping_.at(current);
            visited.push_back(vertices_[currentIndex]);

            for (const auto& neighbor : neighbors(current)) {

                auto it = mapping_.find(neighbor);
                if (it != mapping_.end()) {

                    size_t neighborIndex = it->second;

                    if (!explored[neighborIndex]) {
                        frontier.push(neighbor);
                        explored[neighborIndex] = true;
                    }

                }
            }
        }

        return visited;
    }

    //Traverses the vertices of the graph starting from the specified vertex using a breadth-first search (DFS) algorithm.
    std::vector<std::string> dfs(const std::string& start) const
    {
        // Check if the graph is empty
        if (vertices_.empty()) {
            std::cout << "Graph is empty" << std::endl;
            return std::vector<std::string>();
        }

        // Check if the vertex exists
        if (!contains_vertex(start)) {
            std::cout << "Vertex with the id does not exists" << std::endl;
            return std::vector<std::string>();
        }

        // Print the DFS traversal message
        std::cout << "DFS traversal from " << start << ": ";

        // Initialize the explored array and the frontier stack
        std::vector<bool> explored(vertices_.size(), false);
        std::stack<std::string> frontier;
        std::vector<std::string> visited;

        // Add the first vertex to the frontier
        frontier.push(start);
        explored[mapping_.at(start)] = true;

        // Perform the DFS traversal
        while (!frontier.empty()) {

            std::string current = frontier.top();
            frontier.pop();
            size_t currentIndex = mapping_.at(current);
            visited.push_back(vertices_[currentIndex]);

            for (const auto& neighborId : neighbors(current)) {

                auto it = mapping_.find(neighborId);

                if (it != mapping_.end()) {

                    size_t neighborIndex = it->second;

                    if (!explored[neighborIndex]) {
                        frontier.push(neighborId);
                        explored[neighborIndex] = true;
                    }

                }
            }
        }

        return visited;
    }

    //Prints the vertices of the graph starting from the specified vertex using a breadth-first search (BFS) traversal.
    void print_bfs(const std::string& start) const
    {   
        // Check if the graph is empty
        if (vertices_.empty()) {
            std::cout << "Graph is empty" << std::endl;
            return;
        }

        // Check if the vertex exists
        if (!contains_vertex(start)) {
            std::cout << "Vertex with the id does not exists" << std::endl;
            return;
        }        

        // Print the BFS traversal message
        std::cout << "BFS traversal from " << start << ": ";

        // Initialize the explored array and the frontier queue
        std::vector<bool> explored(vertices_.size(), false);
        std::queue<std::string> frontier;

        // Add the first vertex to the frontier
        frontier.push(start);
        explored[mapping_.at(start)] = true;

        // Perform the BFS traversal
        while (!frontier.empty()) {

            auto current = frontier.front();
            frontier.pop();
            size_t currentIndex = mapping_.at(current);
            std::cout << vertices_[currentIndex] << " ";

            for (const auto& neighbor : neighbors(current)) {

                auto it = mapping_.find(neighbor);
                if (it != mapping_.end()) {
                    
                    size_t neighborIndex = it->second;

                    if (!explored[neighborIndex]) {
                        frontier.push(neighbor);
                        explored[neighborIndex] = true;
                    }

                }
            }
        }

        std::cout << std::endl;
    }

    //Prints the vertices of the graph starting from the specified vertex using a breadth-first search (DFS) traversal.
    void print_dfs(const std::string& start) const
    {
        // Check if the graph is empty
        if (vertices_.empty()) {
            std::cout << "Graph is empty" << std::endl;
            return;
        }

        // Check if the vertex exists
        if (!contains_vertex(start)) {
            std::cout << "Vertex with the id does not exists" << std::endl;
            return;
        }    

        // Print the DFS traversal message
        std::cout << "DFS traversal from " << start << ": ";

        // Initialize the explored array and the frontier stack
        std::vector<bool> explored(vertices_.size(), false);
        std::stack<std::string> frontier;

        // Add the first vertex to the frontier
        frontier.push(start);
        explored[mapping_.at(start)] = true;

        // Perform the DFS traversal
        while (!frontier.empty()) {

            std::string current = frontier.top();
            frontier.pop();
            size_t currentIndex = mapping_.at(current);
            std::cout << vertices_[currentIndex] << " ";

            for (const auto& neighborId : neighbors(current)) {

                auto it = mapping_.find(neighborId);
                
                if (it != mapping_.end()) {

                    size_t neighborIndex = it->second;

                    if (!explored[neighborIndex]) {
                        frontier.push(neighborId);
                        explored[neighborIndex] = true;
                    }

                }
            }
        }

        std::cout << std::endl;
    }

    //Finds a path between two vertices using a breadth-first search (BFS) traversal.
    std::vector<std::string> find_path_bfs(const std::string& start, const std::string& end) const
    {        
        std::vector<std::string> path;

        // Check if the graph is empty
        if (vertices_.empty()) {
            std::cout << "Graph is empty" << std::endl;
            return path;
        }

        // Check if the vertices exist
        if (!contains_vertex(start) || !contains_vertex(end)) {
            std::cout << "One or more vertices do not exist" << std::endl;
            return path;
        }

        // Initialize the explored array, the parents array, and the frontier queue        
        std::vector<bool> explored(vertices_.size(), false);
        std::unordered_map<std::string, std::string> parents;
        std::queue<std::string> frontier;

        // Add the start vertex to the frontier
        frontier.push(start);
        explored[mapping_.at(start)] = true;
        parents[start] = "";

        // Perform the BFS traversal
        while (!frontier.empty()) {

            std::string current = frontier.front();
            frontier.pop();

            if (current == end) {
                //  The end vertex has been reached, reconstruct the path
                std::string pathVertex = current;
                
                while (pathVertex != "") {
                    path.push_back(pathVertex);
                    pathVertex = parents[pathVertex];
                }

                std::reverse(path.begin(), path.end());
                break;
            }

            // Explore the neighbors of the current vertex
            for (const auto& neighbor : neighbors(current)) {

                auto it = mapping_.find(neighbor);

                if (it != mapping_.end()) {

                    size_t neighborIndex = it->second; 
                    
                    if (!explored[neighborIndex]) {
                        frontier.push(neighbor);
                        explored[neighborIndex] = true;
                        parents[neighbor] = current;
                    }

                }
            }
        }

        return path;
    }

    //Finds a path between two vertices using a depth-first search (DFS) traversal.
    std::vector<std::string> find_path_dfs(const std::string& start, const std::string& end) const
    {
        std::vector<std::string> path;

        // Check if the graph is empty
        if (vertices_.empty()) {
            std::cout << "Graph is empty" << std::endl;
            return path;
        }

        // Check if the vertices exist
        if (!contains_vertex(start) || !contains_vertex(end)) {
            std::cout << "One or more vertices do not exist" << std::endl;
            return path;
        }

        // Initialize the explored array, the parents array, and the frontier stack
        std::vector<bool> explored(vertices_.size(), false);
        std::unordered_map<std::string, std::string> parents;
        std::stack<std::string> frontier;

        // Add the start vertex to the frontier
        frontier.push(start);
        explored[mapping_.at(start)] = true;
        parents[start] = "";

        // Perform the DFS traversal
        while (!frontier.empty()) {

            std::string current = frontier.top();
            frontier.pop();

            if (current == end) {
                //  The end vertex has been reached, reconstruct the path
                std::string pathVertex = current;

                while (pathVertex != "") {
                    path.push_back(pathVertex);
                    pathVertex = parents[pathVertex];
                }

                std::reverse(path.begin(), path.end());
                break;
            }

            // Explore the neighbors of the current vertex
            for (const auto& neighbor : neighbors(current)) {

                auto it = mapping_.find(neighbor);
                
                if (it != mapping_.end()) {

                    size_t neighborIndex = it->second;

                    if (!explored[neighborIndex]) {
                        frontier.push(neighbor);
                        explored[neighborIndex] = true;
                        parents[neighbor] = current;
                    }

                }
            }
        }

        return path;
    }

private:

    std::vector<std::string> vertices_;                             /**< The vertices of the graph. */
    std::vector<edge> edges_;                                       /**< The edges of the graph. */
    std::unordered_map<std::string, unsigned long long> mapping_;   /**< Mapping from vertex Ids to indices in `vertices_`. */
};
