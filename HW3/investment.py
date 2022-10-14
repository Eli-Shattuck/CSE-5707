import cplex
from cplex.exceptions import CplexError

# R[L][F]
R = [[0  , 0  ,	0  ,	0  ,	0  ,	0  ,	0  ,	0],
     [4.1, 1.8,	1.5,	2.2,	1.3,	4.2,	2.2,	1.0],
     [5.8, 3.0,	2.5,	3.8,	2.4,	5.9,	3.5,    1.7],
     [6.5, 3.9,	3.3,	4.8,	3.2,	6.6,	4.2,	2.3],
     [6.8, 4.5,	3.8,	5.5,	3.9,	6.8,	4.6,	2.8]
]

LEVELS = 5      # L
INVESTMENTS = 8 # F
N = LEVELS * INVESTMENTS

#vars = Spent, Back_F ∀F, Invest_L_F ∀L ∀F

# -0.05 Spent + ∑ B_F
my_obj      = [-0.05]          + [1]              * INVESTMENTS                    + [0] * N
my_ub       = [cplex.infinity] + [cplex.infinity] * INVESTMENTS                    + [1] * N
my_lb       = [0]              + [0]              * INVESTMENTS                    + [0] * N
my_ctype    = "I"              + "I"              * INVESTMENTS                    + "I" * N
my_colnames = ["Spent"]        + ["Back_{}".format(f) for f in range(INVESTMENTS)] + ["Invest_{}_{}".format(l, f) for l in range(LEVELS) for f in range(INVESTMENTS)]

# S <= 10   ∀F ∑_L I_L_F * R_L_F - B = 0    ∀F ∑_L I_L_F = 1    ∑_
# budget: S ≤ 10
# spent : ∑∑(F ⋅ I_L_F) - S = 0
# back  : ∀F ∑(R_L_F ⋅ I_L_F) - B_F = 0
# invest: ∀F ∑(I_L_F) = 1
my_rownames = ["budget"] + ["spent"] + ["back_{}".format(f) for f in range(INVESTMENTS)] + ["invest_{}".format(f) for f in range(INVESTMENTS)]
my_rhs      = [10]       + [0]       + [0] * INVESTMENTS                                 + [1] * INVESTMENTS
my_sense    = "L"        + "E"       + "E" * INVESTMENTS                                 + "E" * INVESTMENTS

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

    # budget
    rows.append([ ["Spent"], [1] ])

    # spent
    vars = ["Spent"]
    mult = [-1]
    for l in range(LEVELS):
        for f in range(INVESTMENTS):
            vars.append("Invest_{}_{}".format(l, f))
            mult.append(l)
    rows.append([ vars, mult ])

    # back
    for f in range(INVESTMENTS):
        vars = ["Back_{}".format(f)]
        mult = [-1]
        for l in range(LEVELS):
            vars.append("Invest_{}_{}".format(l, f))
            mult.append(R[l][f])
        rows.append([ vars, mult ])

    # invest
    for f in range(INVESTMENTS):
        vars = []
        mult = []
        for l in range(LEVELS):
            vars.append("Invest_{}_{}".format(l, f))
            mult.append(1)
        rows.append([ vars, mult ])

    prob.linear_constraints.add(lin_expr=rows, senses=my_sense,
                                rhs=my_rhs, names=my_rownames)

def main():
    try:
        model = cplex.Cplex()
        populate(model)
        model.solve()

        model.write("invest.lp")
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
    
    print("Spent: {}".format(x[0]))


    ε = 1e-6
    for f in range(INVESTMENTS):
        dv_f = ""
        for l in range(LEVELS):
            i = l * INVESTMENTS + f + 1 + INVESTMENTS

            if abs(x[i] - 1) < ε: 
                dv_f += "Level: {:2d} ".format(l)
            # dv_s += "{} ".format(i)
        print("Investment {}:".format(f+1))
        print(dv_f)
        print()


if __name__ == '__main__':
    main()