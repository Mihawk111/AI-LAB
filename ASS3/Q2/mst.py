import numpy as np
import random

graph_init = []
size = 10

for _ in range(size*(size-1)//2):
    graph_init.append(np.random.random())

graph_edge = {}
graph_adjl = [[] for _ in range(size)]
count = 0
for i in range(size):
    for j in range(i):
        
        graph_edge[(i, j)] = graph_init[count]
        graph_edge[(j, i)] = graph_init[count]

        graph_adjl[i].append((j, graph_init[count]))
        graph_adjl[j].append((i, graph_init[count]))
        count+=1

def printTreeEdges(prufer):
     
    vertices = len(prufer) + 2
    vertex_set = [0] * vertices
     
    for i in range(vertices - 2):
        vertex_set[prufer[i]] += 1
 
    j = 0
    res = []
    for i in range(vertices - 2):
        for j in range(vertices):
            if (vertex_set[j] == 0):
                vertex_set[j] = -1
                res.append([j, prufer[i]])
                vertex_set[prufer[i]] -= 1
                break
     
    j = 0
    for i in range(vertices):
        if (vertex_set[i] == 0 and j == 0):
            res.append([i, -1])
            j+=1
        elif (vertex_set[i] == 0 and j == 1):
            res[-1][1] = i
    return res



def fit_func(temp_graph_edge):
    cost = 0
    for a, b in temp_graph_edge:
        cost += graph_edge[(a, b)]
    return cost

def init (no_of_elem):
    X = []
    for _ in range(no_of_elem):
        X.append(np.random.randint(0, size-1, size-2))
    
    return X

def crossover(ar1, ar2, probability):
    parent1 = ar1.tolist()
    parent2 = ar2.tolist()
    if probability > random.random():
        crossover_pt = random.randint(1, len(parent1)-1)
        p1h = parent1[:crossover_pt]
        p2h = parent2[:crossover_pt]
        p1t = parent1[crossover_pt:]
        p2t = parent2[crossover_pt:]
        return random.choice([np.array(p1h+p2t), np.array(p2h+p1t)])
    else:
        return random.choice([np.array(parent1), np.array(parent2)])
    
def mutation(filial, probability):
    filial = filial.tolist()
    for mutation_pt in range(len(filial)):
        if probability > random.random():
            filial[mutation_pt] = random.randint(0, len(filial)+1)
    return np.array(filial)

pops = 100
p = init(pops)
max_f = 0
for i in range(1000):
    p_phenotype = list(map(lambda x : {
        "genotype": x, 
        "phenotype": printTreeEdges(x),
        "fitness": 1/(1+fit_func(printTreeEdges(x)))
    }, p))

    fitness_map = list(map(lambda x : x["fitness"], p_phenotype))
    max_f = max(max_f, max(fitness_map))
    print(i, "->Best Fitness till now: ", max_f)
    fitness_sum = sum(fitness_map)
    probability_map = list(map(lambda x : x/fitness_sum, fitness_map))

    cnt = 0
    p_fil = []
    for _ in range(pops):
        p_temp = [ i for i in range(0, pops)]
        it = np.random.choice(p_temp, 2, False, probability_map)
        
        filial = crossover(p[it[0]], p[it[1]], 0.5)
        ## mutation
        mutated_filial = mutation(filial, 0.2)
        p_fil.append(mutated_filial)
    p = p_fil

class Graph:

	def __init__(self, vertices):
		self.V = vertices
		self.graph = []

	def addEdge(self, u, v, w):
		self.graph.append([u, v, w])

	def find(self, parent, i):
		if parent[i] != i:
			parent[i] = self.find(parent, parent[i])
		return parent[i]

	def union(self, parent, rank, x, y):

		if rank[x] < rank[y]:
			parent[x] = y
		elif rank[x] > rank[y]:
			parent[y] = x

		else:
			parent[y] = x
			rank[x] += 1

	def KruskalMST(self):

		result = [] 
		i = 0
		e = 0

		self.graph = sorted(self.graph,
							key=lambda item: item[2])

		parent = []
		rank = []

		for node in range(self.V):
			parent.append(node)
			rank.append(0)

		while e < self.V - 1:

			u, v, w = self.graph[i]
			i = i + 1
			x = self.find(parent, u)
			y = self.find(parent, v)

			if x != y:
				e = e + 1
				result.append([u, v, w])
				self.union(parent, rank, x, y)

		minimumCost = 0
		print("Edges in the constructed MST")
		for u, v, weight in result:
			minimumCost += weight
			print("%d -- %d == %f" % (u, v, weight))
		print("Minimum Spanning Tree", minimumCost)
		print("Fitness: ", 1/(1+minimumCost))


graph = Graph(size)
for elem in graph_edge:
	graph.addEdge(elem[0], elem[1], graph_edge[elem])
graph.KruskalMST()