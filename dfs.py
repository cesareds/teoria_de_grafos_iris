import networkx as nx
import pydot 
import community
from tabulate import tabulate
import matplotlib.pyplot as plt

# Parse the .dot file and create a graph
file = "./files/output.dot"
G = nx.Graph(nx.drawing.nx_pydot.read_dot(file))
G.remove_node('\\n')
'''
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
'''


# Apply the Louvain algorithm
partition = community.best_partition(G)

# Calculate the community sums
community_sums = {}
for community_id in partition.values():
    community_sums[community_id] = community_sums.get(community_id, 0) + 1

# Create the table with colorized community sums
table_data = [["\033[1mCommunity\033[0m", "\033[1mSum\033[0m"]]
for community_id, community_sum in community_sums.items():
    color_code = f"\033[9{community_id % 6 + 1}m"  # Generate color escape sequence based on community ID
    table_data.append([f"{color_code}{community_id}\033[0m", f"{color_code}{community_sum}\033[0m"])

# Print the colorized table
table = tabulate(table_data, headers="firstrow", tablefmt="grid")
print(table)

pos = nx.spring_layout(G)

# Plot the nodes with different colors based on their communities
node_colors = [partition[node] for node in G.nodes()]
nx.draw_networkx_nodes(G, pos, node_color=node_colors, cmap=plt.cm.Set1, alpha=0.8)

# Plot the edges
nx.draw_networkx_edges(G, pos, alpha=0.5)

# Add labels to the nodes
nx.draw_networkx_labels(G, pos)

# Set the plot title
plt.title("Graph")

# Show the plot
plt.show()