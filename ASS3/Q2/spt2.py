import random

population_size = 100
mutation_rate = 0.1
generations = 100
chromosome_length=5
scaler=pow(2,chromosome_length)-1

edge=[]

for i in range(30):
    temp=[]
    for j in range(30):
        if(i>j):
            temp.append(edge[j][i])
        elif i==j:
            temp.append(0)
        else:
            temp.append(round(random.random(),2))
    edge.append(temp)

i=1
j=1

for row in edge:
    print(i,end='')
    for elem in row:
        print(" "+str(elem),end='')
    print("")
    i+=1


def fitness_function(prufer):
    # x=[]

    # for i in range(30):
    #     s=0
    #     for j in range(i*chromosome_length,(i+1)*chromosome_length):
    #         s=2*s+individual[j]
    #     num=29*s/scaler
    #     if (num%1)>=0.5:
    #         x.append(int(num+1))
    #     else: x.append(int(num))
    f=0
    vertices = len(prufer)+2
     
    # Initialize the array of vertices
    vertex_set = [0] * vertices
     
    # Number of occurrences of vertex in code
    for i in range(vertices - 2):
        vertex_set[prufer[i] - 1] += 1
     
    print("The edge set E(G) is :")
     
    # Find the smallest label not present in
    # prufer.
    j = 0
    for i in range(vertices - 2):
        for j in range(vertices):
             
            # If j+1 is not present in prufer set
            if (vertex_set[j] == 0):
                 
                # Remove from Prufer set and print
                # pair.
                vertex_set[j] = -1
                print("(" , (j + 1),", ",prufer[i],") ",sep = "",end = "")
                vertex_set[prufer[i] - 1] -= 1
                break
     
    j = 0
     
    # For the last element
    for i in range(vertices):
        if (vertex_set[i] == 0 and j == 0):
            print("(", (i + 1),", ", sep="", end="")
            j += 1
        else if (vertex_set[i] == 0 and j == 1):
            print((i + 1),")")
    # x.append(('0b'+''.join(str(gene) for gene in individual[0:4])))
    # x.append('0b'+''.join(str(gene) for gene in individual[4:8]))
    # x.append('0b'+''.join(str(gene) for gene in individual[8:12]))
    # x.append('0b'+''.join(str(gene) for gene in individual[12:16]))


def initialize_population(size):
    population = []
    for i in range(size):
        perm = [i for i in range(30)]
        random.shuffle(perm)
        population.append(perm)
    return population


# def selection(population):

#     parent1 = random.choice(population)
#     parent2 = random.choice(population)
#     return parent1, parent2

# define the crossover function
def crossover(parent1, parent2):
    # create a new solution by combining the two parents
    if(random.random()<0.5):
        return [mutate(parent1),mutate(parent2)]
    crossover_point = random.randint(0, len(parent1)-1)
    end_point=(crossover_point+15)%30
    child1=[-1]*30
    child2=[-1]*30

    ptr1=crossover_point
    
    while ptr1!=end_point:
        child1[ptr1]=parent1[ptr1]
        ptr1=(ptr1+1)%30
    
    ptr1=end_point
    ptr2=ptr1

    while ptr2!=crossover_point:
        if(parent2[ptr1] not in child1):
            child1[ptr2]=parent2[ptr1]
            ptr1=(ptr1+1)%30
            ptr2=(ptr2+1)%30
        else:
            ptr1=(ptr1+1)%30
    
    ptr1=crossover_point
    
    while ptr1!=end_point:
        child2[ptr1]=parent2[ptr1]
        ptr1=(ptr1+1)%30
    
    ptr1=end_point
    ptr2=ptr1

    while ptr2!=crossover_point:
        if(parent1[ptr1] not in child2):
            child2[ptr2]=parent1[ptr1]
            ptr1=(ptr1+1)%30
            ptr2=(ptr2+1)%30
        else:
            ptr1=(ptr1+1)%30

    
    # if(end_point<crossover_point):
    #     child1=parent1[:end_point]
    #     child1.extend([-1]*15)
    #     child1.extend(parent1[crossover_point:])
    #     ptr1=(end_point)%30
    #     ptr2=ptr1

    #     while True:
    #         if(parent2[ptr1] not in child1):
    #             child1[ptr2]=parent2[ptr1]
    #             ptr1=(ptr1+1)%30
    #             ptr2=(ptr2+1)%30
    #         else:
    #             ptr1=(ptr1+1)%30
            
    #         if(ptr2==crossover_point):
    #             break
    # else:
    #     child1=[-1]*crossover_point
    #     child1.extend(parent1[crossover_point:end_point])
    #     child1.extend([-1]*(30-end_point))

    #     ptr1=(end_point+1)%30
    #     ptr2=ptr1

    #     while True:
    #         if(parent2[ptr1] not in child1):
    #             child1[ptr2]=parent2[ptr1]
    #             ptr1=(ptr1+1)%30
    #             ptr2=(ptr2+1)%30
    #         else:
    #             ptr1=(ptr1+1)%30
            
    #         if(ptr2==crossover_point):
    #             break
    # print(child1)

    # if(end_point<crossover_point):
    #     child2=parent2[:end_point]
    #     child2.extend([-1]*15)
    #     child2.extend(parent2[crossover_point:])
    #     ptr1=(end_point+1)%30
    #     ptr2=ptr1

    #     while True:
    #         if(parent1[ptr1] not in child2):
    #             child2[ptr2]=parent1[ptr1]
    #             ptr1=(ptr1+1)%30
    #             ptr2=(ptr2+1)%30
    #         else:
    #             ptr1=(ptr1+1)%30
            
    #         if(ptr2==crossover_point):
    #             break
    # else:
    #     child2=[-1]*crossover_point
    #     child2.extend(parent2[crossover_point:end_point])
    #     child2.extend([-1]*(30-end_point))

    #     ptr1=(end_point+1)%30
    #     ptr2=ptr1

    #     while True:
    #         if(parent1[ptr1] not in child2):
    #             child2[ptr2]=parent1[ptr1]
    #             ptr1=(ptr1+1)%30
    #             ptr2=(ptr2+1)%30
    #         else:
    #             ptr1=(ptr1+1)%30
            
    #         if(ptr2==crossover_point):
    #             break
    # print(child2)
    # print(child1)
    # print(child2)
    return [mutate(child1),mutate(child2)]

# define the mutation function
def mutate(individual):
    # flip a random bit in the solution
    if(random.random()>0.1):
        return individual
    
    index=random.sample(range(0,len(individual)-1),2)
    temp=individual[index[0]]
    individual[index[0]]=individual[index[1]]
    individual[index[1]]=temp
    
    return individual

def getIndex(pin, cumul_prob):
    for i in range(len(cumul_prob)):
        if(pin<cumul_prob[i]):
            return i

def tournament(players,index):
    maxval=0
    winner=[]
    for i in index:
        if(fitness_function(players[i])>maxval):
            maxval=fitness_function(players[i])
            winner=players[i]

    return winner

# create the initial population
population = initialize_population(population_size)

# run the genetic algorithm for the specified number of generations
for i in range(generations):
    # evaluate the fitness of each solution in the population
    population=sorted(population, key = fitness_function, reverse=True)
    # fitness_scores = [fitness_function(solution) for solution in population]
    # aggr=sum(fitness_scores)
    # prob=list(map(fitness_scores,lambda x:x/aggr))
    # cumul_prob=[prob[0]]
    # for i in range(1,len(population)):
    #     cumul_prob.append(cumul_prob[-1]+prob[i])
    
    new_population=[]
    elite=int(population_size*10/100)
    parents=population[:]
    random.shuffle(parents)
    # create a new generation using crossover
    children = []
    for j in range(population_size//2):
        parent1=population[j]
        parent2=population[j+population_size//2]
        child = crossover(parent1, parent2)
        children.extend(child)
    
    new_population.extend(children)
    new_population.extend(population[elite:])
    random.shuffle(new_population)

    sorted(new_population,key=fitness_function, reverse= True)
    fitness_scores = [fitness_function(solution) for solution in new_population]
    aggr=sum(fitness_scores)
    prob=list(map(lambda x:x/aggr,fitness_scores))
    cumul_prob=[prob[0]]
    for j in range(1,len(new_population)):
        cumul_prob.append(cumul_prob[-1]+prob[j])
    
    pin_dist=1/(population_size-elite)
    pin=random.random()

    selected=[]

    # for _ in range(population_size-elite):
    #     selected.append(new_population[getIndex(pin,cumul_prob)])
    #     pin=(pin+pin_dist)%1

    for j in range(population_size-elite):
        candidates=random.sample(range(len(new_population)),4)
        selected.append(tournament(new_population,candidates))
    
    selected.extend(population[:elite])

    # replace the old population with the new one
    population = selected
    fitness_scores = [fitness_function(solution) for solution in population]
    aggr=sum(fitness_scores)
    print("Generation "+str(i)+": Average Fitness = "+str(aggr/len(population)))


# select the best solution from the final population
best_solution = max(population, key=fitness_function)

# print the best solution and its fitness value
print("Best solution:", best_solution)
print("Fitness value:", fitness_function(best_solution))

INF = 9999999
# number of vertices in graph
N = 30
#creating graph by adjacency matrix method

G=edge

selected_node = [0]*30

no_edge = 0

selected_node[0] = True

# printing for edge and weight
print("Edge : Weight\n")
total=0
while (no_edge < N - 1):
    
    minimum = INF
    a = 0
    b = 0
    for m in range(N):
        if selected_node[m]:
            for n in range(N):
                if ((not selected_node[n]) and G[m][n]):  
                    # not in selected and there is an edge
                    if minimum > G[m][n]:
                        minimum = G[m][n]
                        a = m
                        b = n
    print(str(a) + "-" + str(b) + ":" + str(G[a][b]))
    total+=G[a][b]
    selected_node[b] = True
    no_edge += 1

print("Prim's Result:",1/total)