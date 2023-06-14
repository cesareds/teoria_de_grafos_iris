import networkx as nx

# Parse the .dot file and create a graph
file = "./files/output.dot"
G = nx.Graph(nx.drawing.nx_pydot.read_dot(file))

# Initialize a set to track visited nodes
visited = set()

# Define the DFS function
def dfs(graph, node):
    visited.add(node)
    print(node)

    for neighbor in graph.neighbors(node):
        if neighbor not in visited:
            dfs(graph, neighbor)

# Perform DFS starting from each unvisited node
for node in G.nodes():
    if node not in visited:
        dfs(G, node)
