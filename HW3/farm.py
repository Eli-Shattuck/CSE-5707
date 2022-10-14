import cplex
from cplex.exceptions import CplexError

COWS = 81
SONS = 9
N = COWS * SONS + 2

my_obj = [1, 0] + [0] * (N-2)
my_ub = [cplex.infinity, cplex.infinity] + ([1] * (N-2))
my_lb = [0] * N
my_ctype = "I" * N
my_colnames = ["C", "M"] + ["T_{}_{}".format(s, c) for s in range(SONS) for c in range(COWS)]
my_rhs = ([1] * COWS) + ([0] * SONS) + ([0] * SONS)
my_rownames = ["cow_{}".format(c) for c in range(COWS)] + ["son_{}_M".format(s) for s in range(SONS)] + ["son_{}_C".format(s) for s in range(SONS)]
my_sense = "E" * (COWS + SONS + SONS)

print(len(my_obj))
print(len(my_ub))
print(len(my_lb))
print(len(my_ctype))
print(len(my_colnames))
print(len(my_rhs))
print(len(my_rownames))
print(len(my_sense))

print(my_colnames)

def populate(prob):
    prob.objective.set_sense(prob.objective.sense.maximize)

    prob.variables.add(obj=my_obj, lb=my_lb, ub=my_ub, types=my_ctype,
                       names=my_colnames)

    rows = []

    for c in range(COWS):
        vars = []
        for s in range(SONS):
            vars.append("T_{}_{}".format(s, c))
        rows.append([ vars, [1.]*SONS ])

    for s in range(SONS):
        vars = []
        mult = []
        for c in range(COWS):
            vars.append("T_{}_{}".format(s, c))
            mult.append(c+1.)
        vars.append("M")
        mult.append(-1.0)
        rows.append([ vars, mult ])

    for s in range(SONS):
        vars = []
        mult = []
        for c in range(COWS):
            vars.append("T_{}_{}".format(s, c))
            mult.append(1.)
        vars.append("C")
        mult.append(-1.0)
        rows.append([ vars, mult ])

    prob.linear_constraints.add(lin_expr=rows, senses=my_sense,
                                rhs=my_rhs, names=my_rownames)

def main():
    try:
        model = cplex.Cplex()
        populate(model)
        model.solve()

        model.write("farm.lp")
    except CplexError as e:
        print(e)
        return

    print()
    # solution.get_status() returns an integer code
    print("Solution status = ", model.solution.get_status(), ":", end=' ')
    # the following line prints the corresponding string
    print(model.solution.status[model.solution.get_status()])
    print("Solution value  = ", model.solution.get_objective_value())

    numcols = model.variables.get_num()
    numrows = model.linear_constraints.get_num()

    slack = model.solution.get_linear_slacks()
    x = model.solution.get_values()
    y = model.variables.get_names()
    print("M: {}".format(x[1]))
    print("C: {}".format(x[0]))

    all = {c:0 for c in range(81)}
    ε = 1e-6
    for s in range(SONS):
        dv_s = ""
        total = 0
        for c in range(COWS):
            i = s * COWS + c + 2
            
            if abs(x[i] - 1) < ε: 
                dv_s += "{:2d} ".format(c+1)
                total += (c+1)
                all[c] = 1
            # dv_s += "{} ".format(i)
        print("Son {}:".format(s+1))
        print(dv_s + "= {}".format(total))
        print()

    vals = ""
    for k,v in all.items():
        if (v == 0):
            vals += "{}: {} ".format(k, v)
    
    print(vals)
    # for j in range(numrows):
    #     print("Row %d:  Slack = %10f" % (j, slack[j]))
    # for j in range(numcols):
    #     print("Column %d:  Value = %10f" % (j, x[j]))


if __name__ == '__main__':
    main()