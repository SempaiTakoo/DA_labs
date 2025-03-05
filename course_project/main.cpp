#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>
#include <set>
#include <cmath>
#include <set>
#include <iomanip>
#include <chrono>

using namespace std;

const bool DEBUG = false;
const double INF = numeric_limits<double>::infinity();

double get_distance(pair<int, int> a, pair<int, int> b) {
    long x = b.first - a.first;
    long y = b.second - a.second;
    return sqrt(x * x + y * y);
}

class Graph {
public:
    vector<pair<double, double>> vertices;
    vector<vector<pair<int, double>>> adjacency_list;

    Graph(int vertices_count) {
        vertices.resize(vertices_count);
        adjacency_list.resize(vertices_count);
    }

    void addVertex(int vertex_number, double x, double y) {
        vertices[vertex_number] = {x, y};
    }

    void addEdge(int s, int f) {
        double distance = get_distance(vertices[s], vertices[f]);
        adjacency_list[s].push_back({f, distance});
        adjacency_list[f].push_back({s, distance});
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

double a_star(Graph& graph, int start, int finish) {
    size_t dim = graph.vertices.size();

    priority_queue<Node, vector<Node>, greater<Node>> open;
    vector<bool> closed(dim, false);
    vector<double> g(dim, INF);
    vector<double> f(dim, INF);

    g[start] = 0;
    f[start] = get_distance(graph.vertices[start], graph.vertices[finish]);
    open.push({start, f[start]});

    while (!open.empty()) {
        Node node = open.top();
        int current = node.vertex_number;
        open.pop();
        closed[current] = true;

        if (current == finish) {
            return g[current];
        }

        for (pair<int, double> edge : graph.adjacency_list[current]) {
            int neighbor = edge.first;
            double distance = edge.second;

            if (closed[neighbor]) {
                continue;
            }

            double g_temp = g[current] + distance;
            if (g_temp >= g[neighbor]) {
                continue;
            }

            g[neighbor] = g_temp;
            f[neighbor] = g[neighbor] + get_distance(
                graph.vertices[neighbor],
                graph.vertices[finish]
            );
            open.push({neighbor, f[neighbor]});
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

        auto time1 = chrono::high_resolution_clock::now();

        a_star(graph, start, finish);

        auto time2 = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = time2 - time1;
        cout << elapsed.count() << " seconds\n";

        // double answer = a_star(graph, start, finish);
        // if (answer == -1) {
        //     cout << -1 << '\n';
        // } else {
        //     cout << fixed << setprecision(6) << answer << '\n';
        // }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    shortest_paths_between_vertices();

    return 0;
}
