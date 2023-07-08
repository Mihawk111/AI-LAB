import random


population_size = 100
mutation_rate = 0.1
generations = 100
chromosome_length = 8
scaler = pow(2, chromosome_length)-1
SP = 2

C = [[4, 1, 8, 6, 3, 2, 5, 8, 6, 7], [4, 1, 8, 6, 7, 9, 3, 1, 2, 3.6],
     [4, 1, 8, 6, 3, 2, 5, 8, 6, 7], [4, 1, 8, 6, 7, 9, 3, 1, 2, 3.6]]

beta = [0.1, 0.2, 0.2, 0.4, 0.4, 0.6, 0.3, 0.7, 0.5, 0.5]


def fitness_function(individual):
    x = []

    for i in range(4):
        s = 0
        for j in range(i*chromosome_length, (i+1)*chromosome_length):
            s = 2*s+individual[j]
        x.append(10*s/scaler)

    f = 0

    for i in range(10):
        denom = 0
        for j in range(4):
            p = (x[j]-C[j][i])
            denom += p*p
        f += 1/(denom+beta[i])

    f = 1/(1+f)

    return f

    # x.append(('0b'+''.join(str(gene) for gene in individual[0:4])))
    # x.append('0b'+''.join(str(gene) for gene in individual[4:8]))
    # x.append('0b'+''.join(str(gene) for gene in individual[8:12]))
    # x.append('0b'+''.join(str(gene) for gene in individual[12:16]))


def initialize_population(size):
    population = []
    for i in range(size):
        solution = [random.randint(0, 1) for _ in range(chromosome_length*4)]
        population.append(solution)
    return population


# def selection(population):

#     parent1 = random.choice(population)
#     parent2 = random.choice(population)
#     return parent1, parent2

# define the crossover function
def crossover(parent1, parent2):
    # create a new solution by combining the two parents
    if (random.random() > 0.5):
        return [mutate(parent1), mutate(parent2)]

    crossover_point = random.randint(1, len(parent1)-1)

    child1 = parent1[:crossover_point]
    child1.extend(parent2[crossover_point:])
    child2 = parent2[:crossover_point]
    child2.extend(parent1[crossover_point:])
    return [mutate(child1), mutate(child2)]

# define the mutation function


def mutate(individual):
    # flip a random bit in the solution
    if (random.random() > 0.1):
        return individual

    index = random.randint(0, len(individual)-1)
    if individual[index] == 0:
        individual[index] = 1
    else:
        individual[index] = 0

    return individual


def getIndex(pin, cumul_prob):
    for i in range(len(cumul_prob)):
        if (pin < cumul_prob[i]):
            return i


def tournament(players, index):
    maxval = 0
    winner = []
    for i in index:
        if (fitness_function(players[i]) > maxval):
            maxval = fitness_function(players[i])
            winner = players[i]

    return winner


# create the initial population
population = initialize_population(population_size)

# run the genetic algorithm for the specified number of generations
for i in range(generations):
    # evaluate the fitness of each solution in the population
    population = sorted(population, key=fitness_function, reverse=True)
    # fitness_scores = [fitness_function(solution) for solution in population]
    # aggr=sum(fitness_scores)
    # prob=list(map(fitness_scores,lambda x:x/aggr))
    # cumul_prob=[prob[0]]
    # for i in range(1,len(population)):
    #     cumul_prob.append(cumul_prob[-1]+prob[i])

    new_population = []
    elite = int(population_size*10/100)
    parents = population[:]
    random.shuffle(parents)
    # create a new generation using crossover
    children = []
    for j in range(population_size//2):
        parent1 = population[j]
        parent2 = population[j+population_size//2]
        child = crossover(parent1, parent2)
        children.extend(child)

    new_population.extend(children)
    new_population.extend(population[elite:])
    random.shuffle(new_population)

    sorted(new_population, key=fitness_function, reverse=True)
    fitness_scores = [fitness_function(solution)
                      for solution in new_population]
    aggr = sum(fitness_scores)
    prob = list(map(lambda x: x/aggr, fitness_scores))
    cumul_prob = [prob[0]]
    for j in range(1, len(new_population)):
        cumul_prob.append(cumul_prob[-1]+prob[j])

    pin_dist = 1/(population_size-elite)
    pin = random.random()

    selected = []

    # for _ in range(population_size-elite):
    #     selected.append(new_population[getIndex(pin,cumul_prob)])
    #     pin=(pin+pin_dist)%1

    for j in range(population_size-elite):
        candidates = random.sample(range(len(new_population)), 4)
        selected.append(tournament(new_population, candidates))

    selected.extend(population[:elite])

    # replace the old population with the new one
    population = selected
    fitness_scores = [fitness_function(solution) for solution in population]
    aggr = sum(fitness_scores)
    print("Generation "+str(i)+": Average Fitness = "+str(aggr/len(population)))


# select the best solution from the final population
best_solution = max(population, key=fitness_function)
x = []

for i in range(4):
    s = 0
    for j in range(i*chromosome_length, (i+1)*chromosome_length):
        s = 2*s+best_solution[j]
    x.append(10*s/scaler)

# print the best solution and its fitness value
print("Best solution:", x)
print("Fitness value:", fitness_function(best_solution))
