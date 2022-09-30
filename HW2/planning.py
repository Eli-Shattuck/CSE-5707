import cplex

cpx = cplex.Cplex(".\\planning.lp")

cpx.solve()

sol = cpx.solution.get_values(0, cpx.variables.get_num()-1)

k=0
for i in range(2):
    for j in range(6):
        print("{}_{} = {}".format('UP'[i], j+3, sol[k  ]))       
        k += 1