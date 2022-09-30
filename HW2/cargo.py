import cplex

cpx = cplex.Cplex(".\\cargo.lp")

cpx.solve()

sol = cpx.solution.get_values(0, cpx.variables.get_num()-1)

print()
k = 0
for i in range(3):
    for j in range(4):
        print("C{}_{}: {}".format(j+1, 'FCB'[i], sol[k]))
        k += 1
print()
FCB = []
for i in range(3):
    s = 0
    for j in range(4):
        s += sol[i*4+j]
    FCB.append(s)
    print("{} = {}".format('FCB'[i], s))
print()
print("F/ΣFCB = {} = {}".format(FCB[0] / sum(FCB), 10/34))
print("C/ΣFCB = {} = {}".format(FCB[1] / sum(FCB), 16/34))
print("B/ΣFCB = {} = {}".format(FCB[2] / sum(FCB),  8/34))
print()
for i in range(4):
    s = 0
    for j in range(3):
        s += sol[j*4+i]
    print("C_{} = {}".format(i+1, s))