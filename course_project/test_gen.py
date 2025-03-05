import random
import math
import heapq

def generate_test_case(n, m, q):
    vertices = [
        (random.randint(-10**9, 10**9), random.randint(-10**9, 10**9))
        for _ in range(n)
    ]

    edges = set()
    # Create a connected chain (0-1-2-...-n-1)
    for i in range(n-1):
        u, v = i, i+1
        if u > v:
            u, v = v, u
        edges.add((u, v))

    # Add random edges
    while len(edges) < m:
        u = random.randint(0, n-1)
        v = random.randint(0, n-1)
        if u == v:
            continue
        if u > v:
            u, v = v, u
        if (u, v) not in edges:
            edges.add((u, v))

    edges = list(edges)[:m]  # Trim if over

    # Build adjacency list with weights
    adj = [[] for _ in range(n)]
    for u, v in edges:
        dx = vertices[u][0] - vertices[v][0]
        dy = vertices[u][1] - vertices[v][1]
        weight = math.hypot(dx, dy)
        adj[u].append((v, weight))
        adj[v].append((u, weight))

    # Generate queries
    queries = [(random.randint(1, n), random.randint(1, n)) for _ in range(q)]

    return vertices, edges, queries, adj

def write_input_file(vertices, edges, queries):
    with open("input.txt", "w") as f:
        f.write(f"{len(vertices)} {len(edges)}\n")
        for x, y in vertices:
            f.write(f"{x} {y}\n")
        for u, v in edges:
            f.write(f"{u+1} {v+1}\n")
        f.write(f"{len(queries)}\n")
        for a, b in queries:
            f.write(f"{a} {b}\n")

def calculate_answers(adj, queries):
    answers = []
    for a, b in queries:
        start = a-1
        end = b-1
        n = len(adj)
        dist = [math.inf] * n
        dist[start] = 0
        heap = [(0, start)]

        while heap:
            d, u = heapq.heappop(heap)
            if u == end:
                break
            if d > dist[u]:
                continue
            for v, w in adj[u]:
                if dist[v] > dist[u] + w:
                    dist[v] = dist[u] + w
                    heapq.heappush(heap, (dist[v], v))

        if dist[end] == math.inf:
            answers.append(-1)
        else:
            answers.append(round(dist[end], 6))
    return answers

def main():
    n = 100_000
    m = 2 * n
    q = 1

    vertices, edges, queries, adj = generate_test_case(n, m, q)
    write_input_file(vertices, edges, queries)

    # answers = calculate_answers(adj, queries)
    # print("Correct answers:")
    # for ans in answers:
    #     print(ans if ans == -1 else f"{ans:.6f}")

if __name__ == "__main__":
    main()
