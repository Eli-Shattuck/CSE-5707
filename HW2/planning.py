import cplex

cpx = cplex.Cplex(".\\planning.lp")

cpx.solve()

sol = cpx.solution.get_values(0, cpx.variables.get_num()-1)

k=0
for j in range(6):
    print("P_{} = {}".format(j+3, sol[k  ]))       
    k += 1

for j in range(5):
    print("S_{} = {}".format(j+3, sol[k  ]))       
    k += 1

for j in range(5):
    print("R_{} = {}".format(j+4, sol[k  ]))       
    k += 1