#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>
#include <set>
#include <cmath>
#include <set>
#include <iomanip>

using namespace std;

const bool DEBUG = false;
const double INF = numeric_limits<double>::infinity();

struct Vertex {
    double x, y;
};

class Graph {
public:
    vector<Vertex> vertices;
    vector<vector<bool>> adjacency_matrix;

    Graph(int vertices_count) {
        vertices.resize(vertices_count);
        adjacency_matrix.resize(
            vertices_count, vector<bool>(vertices_count, false)
        );
    }

    size_t get_vertices_count() {
        return vertices.size();
    }

    pair<int, int> get_coordinates(int vertex_number) {
        Vertex vertex = vertices[vertex_number];
        return {vertex.x, vertex.y};
    }

    void addVertex(int vertex_number, double x, double y) {
        vertices[vertex_number] = {x, y};
    }

    void addEdge(int s, int f) {
        adjacency_matrix[s][f] = true;
        adjacency_matrix[f][s] = true;
    }

    void print_adjacency_matrix() {
        for (size_t i = 0; i < adjacency_matrix.size(); ++i) {
            for (size_t j = 0; j < adjacency_matrix.size(); ++j) {
                cout << adjacency_matrix[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};

struct Node {
    int vertex_number;
    double f;

    bool operator>(const Node node) const {
        return f > node.f;
    }
};

Graph input_graph() {
    int n, m;
    cin >> n >> m;

    Graph graph(n);

    int x, y;
    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y;
        graph.addVertex(i, x, y);
    }

    int s, f;
    for (int i = 0; i < m; ++i)
    {
        cin >> s >> f;
        graph.addEdge(s - 1, f - 1);
    }

    return graph;
}

double distance(pair<int, int> a, pair<int, int> b) {
    int x = b.first - a.first;
    int y = b.second - a.second;
    return sqrt(x * x + y * y);
}

double a_star(Graph graph, int start, int finish) {
    priority_queue<Node, vector<Node>, greater<Node>> open;
    vector<bool> closed(graph.get_vertices_count(), false);
    vector<double> g(graph.get_vertices_count(), INF);
    vector<double> f(graph.get_vertices_count(), INF);

    g[start] = 0;
    f[start] = distance(
        graph.get_coordinates(start),
        graph.get_coordinates(finish)
    );
    open.push({start, f[start]});

    while (!open.empty()) {
        Node node = open.top();
        int current = node.vertex_number;
        open.pop();
        closed[current] = true;

        if (current == finish) {
            return g[current];
        }

        vector<bool> neighbors = graph.adjacency_matrix[current];
        for (size_t neighbor = 0; neighbor < neighbors.size(); ++neighbor) {
            bool is_achievable = neighbors[neighbor];
            bool is_neighbor_in_closed = closed[neighbor];

            if (!is_achievable || is_neighbor_in_closed) {
                continue;
            }

            double g_temp = g[current] + distance(
                graph.get_coordinates(current),
                graph.get_coordinates(static_cast<int>(neighbor))
            );

            if (g_temp >= g[neighbor]) {
                continue;
            }

            g[neighbor] = g_temp;
            f[neighbor] = g[neighbor] + distance(
                graph.get_coordinates(static_cast<int>(neighbor)),
                graph.get_coordinates(finish)
            );
            open.push({static_cast<int>(neighbor), f[neighbor]});
        }
    }

    return -1;
}

void shortest_paths_between_vertices() {
    Graph graph = input_graph();

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int start, finish;
        cin >> start >> finish;

        --start;
        --finish;

        cout << fixed << setprecision(6);
        cout << a_star(graph, start, finish) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    shortest_paths_between_vertices();

    return 0;
}
