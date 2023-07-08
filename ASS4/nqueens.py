import numpy as np
import random

size = 8

def fit_func(plot):
    cost = 0
    for i in range(1, len(plot)):
        for j in range(i):
            if plot[i] == plot[j]: cost+=1

    for i in range(1, len(plot)):
        for j in range(i):
            if plot[j] - plot[i] == j - i : cost+=1

    for i in range(1, len(plot)):
        for j in range(i):
            if plot[i] + i == plot[j] + j : cost+=1

    return 1/(1+cost)


def init (no_of_elem):
    X = []
    for _ in range(no_of_elem):
        X.append(np.random.permutation(size))
    return X

def permutation (pl1, pl2):
   
    plot1 = []
    plot2 = []
    for elem in pl1: plot1.append(elem)
    for elem in pl2: plot2.append(elem)

    perm = [i for i in range(size)]
    t = np.random.choice(perm, 2, False)

    if (t[0] - t[1] == 1 or t[0]-t[1] == 1):
        p = random.randint(0, 1)
        if p == 1: return plot2
        else: return plot1

    p = random.randint(0, 1)
    if p == 1: 
        plot1, plot2 = plot2, plot1


    end = (t[1] if t[1] > t[0] else t[1]+size)

    st = []
    for i in range(t[0], end):
        st.append(plot1[i%size])

    res = []
    for i in range (end, end+size):
        if plot2[i%size] not in st:
            res.append(plot2[i%size])

    for i in range(len(res)):
        plot1[(end+i)%size] = res[i]

    return plot1

pops = 20
p = init(pops)
max_f = 0
flag = False
for i in range(1000):
    p_phenotype = list(map(lambda x : {
        "genotype": x, 
        "fitness": fit_func(x)
    }, p))

    fitness_map = list(map(lambda x : x["fitness"], p_phenotype))
    max_f = max(max_f, max(fitness_map))
    print(i, "->Best Fitness till now: ", max_f)  
    if max_f == 1:
        for elem in p_phenotype:
            if elem["fitness"] == 1:
                print("Output:", elem["genotype"])
                flag = True  
    if flag: break
    fitness_sum = sum(fitness_map)
    probability_map = list(map(lambda x : x/fitness_sum, fitness_map))

    cnt = 0
    p_fil = []
    for _ in range(pops):
        p_temp = [ i for i in range(0, pops)]
        it = np.random.choice(p_temp, 2, False, probability_map)
        
        filial = permutation(p[it[0]], p[it[1]])
        p_fil.append(filial)
    p = p_fil