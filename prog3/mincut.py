#!/usr/bin/env python

from numpy import random,log
import numpy as np

fn = "kargerMinCut.txt"

fp = open(fn, 'r')

ncut = 20000000
for run in range(400): #200*200*log(200)):
    
    print run

    a = 200*[0]
    vert = 200*[0]
    i = 0

    for l in fp:
        adj = list(np.array(l.split(), dtype=int))
        vert[i] = list([adj.pop(0)])
        a[i] = adj
        i = i+1


    while (len(vert) > 2):

        #s = 0

        n = len(vert)
    
        if (n != len(a)):
            print n, len(a)
            print vert

        #print n, len(a)

        #size of vert
        #for x in vert:
        #    s = s+len(x)

        #if (s < 200):
        #    print s
        #    break

        i = random.random_integers(0, n-1)
        j = random.random_integers(0, len(a[i])-1)

        u = vert[i]
        v = a[i][j]

        # merge

        # find other vertex and add to effective vertex list
        for ind in range(len(vert)):
            if v in vert[ind]:
                vert[i] = vert[i]+vert[ind] # list concatenation
                # add new adjacent vertices to list
                a[i] = a[i]+a[ind] # list concatenation
                # remove self-loops (because they are stupid)
                for vv in vert[i]:
                    while (vv in a[i]):
                        a[i].remove(vv)

                crap = a.pop(ind)
                crap = vert.pop(ind)
                break

        #print vert
        #print a[0],a[1]
        #print len(a[0]), len(a[1])

    if ncut > len(a[0]):
        ncut = len(a[0])
        mincut = vert

    fp.seek(0)

print "end"
print 

print "run:", run

print mincut
print ncut

