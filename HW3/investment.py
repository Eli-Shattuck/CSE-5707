import cplex
from cplex.exceptions import CplexError

# R[L][F]
R = [[0  , 0  ,	0  ,	0  ,	0  ,	0  ,	0  ,	0],
     [4.1, 1.8,	1.5,	2.2,	1.3,	4.2,	2.2,	1.0],
     [5.8, 3.0,	2.5,	3.8,	2.4,	5.9,	3.5,    1.7],
     [6.5, 3.9,	3.3,	4.8,	3.2,	6.6,	4.2,	2.3],
     [6.8, 4.5,	3.8,	5.5,	3.9,	6.8,	4.6,	2.8]
]

LEVELS = 5
INVESTMENTS = 8
N = LEVELS * INVESTMENTS

# data common to all populateby functions
# -0.05 Spent + ∑ Back_Level 
my_obj = [-0.05] + [1]*LEVELS + [0]*N
my_ub = [cplex.infinity] + ([cplex.infinity] * LEVELS) + ([1] * N)
my_lb = [0] + [0] * LEVELS + [0] * N
my_ctype = "I" + "I" * LEVELS + "I" * N
my_colnames = ["Spent"] + ["Back_{}".format(l) for l in range(LEVELS)] + ["I_{}_{}".format(l, f) for l in range(LEVELS) for f in range(INVESTMENTS)]

# S <= 10   ∀F ∑_L I_L_F * R_L_F - B = 0    ∀F ∑_L I_L_F = 1    ∑_
my_rhs = [10] + [0] * LEVELS + [1] * N
my_rownames = ["budget"] + ["return_{}_{}".format(s) for s in range(SONS)] + ["son_{}_C".format(s) for s in range(SONS)]
my_sense = "L" + "E" * LEVELS + "E" * N

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