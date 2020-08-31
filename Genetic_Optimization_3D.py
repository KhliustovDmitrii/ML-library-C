#!/usr/bin/env python
# coding: utf-8

# In[ ]:


import random
import numpy as np
import math
class Point:
    def __init__(self, n, arr):
        self.dim = n
        self.param = np.array(arr)
        
    def hybride(self, p):
        arr = []
        for i in range(self.dim):
            s = self.param[i]
            e = p.param[i]
            m = (s+e)/2
            a = [s, e, m, random.random()]
            arr.append(random.choice(a))
        child = Point(self.dim, arr)
        return child
    def crossingover(self, p):
        self.param[0]+=p.param[0]
        p.param[0] = self.param[0] - p.param[0]
        self.param[0]-=p.param[0]
        self.param[1]+=p.param[1]
        p.param[1] = self.param[1] - p.param[1]
        self.param[1]-=p.param[1]
        
    def mutate(self):
        self.param[0]+=random.random()
        self.param[1]+=random.random()
        self.param[2]+=random.random()
        
    def fitness(self, f):
        return f(self.param[0], self.param[1], self.param[2])
    
def optimize(f, steps, cross_rate, mut_rate):
    lis = []
    for i in range(2**steps):
        lis.append(Point(3, [random.random(),random.random(),random.random()]))
    for i in range(steps):
        gen = []
        for j in range(2**(steps-1-i)):
            b = lis[j].hybride(lis[2**(steps-i) - 1-j])
            r = random.random()
            if r < cross_rate:
                lis[j].crossingover(b)
            a = lis[j] if lis[j].fitness(f)>b.fitness(f) else b
            r = random.random()
            if r < mut_rate:
                a.mutate()
            gen.append(a)
        lis = gen
    res = lis[0]    
    return res

