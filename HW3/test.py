import cplex
from cplex.exceptions import CplexError

# data common to all populateby functions
my_obj = [1.0, 2.0, 3.0, 1.0]
my_ub = [40.0, cplex.infinity, cplex.infinity, 3.0]
my_lb = [0.0, 0.0, 0.0, 2.0]
my_ctype = "CCCI"
my_colnames = ["x1", "x2", "x3", "x4"]
my_rhs = [20.0, 30.0, 0.0]
my_rownames = ["r1", "r2", "r3"]
my_sense = "LLE"


def populate(prob):
    prob.objective.set_sense(prob.objective.sense.maximize)

    prob.variables.add(obj=my_obj, lb=my_lb, ub=my_ub, types=my_ctype,
                       names=my_colnames)

    rows = [[["x1", "x2", "x3", "x4"], [-1.0, 1.0, 1.0, 10.0]],
            [["x1", "x2", "x3"]      , [1.0, -3.0, 1.0]],
            [["x2", "x4"]            , [1.0, -3.5]]]

    prob.linear_constraints.add(lin_expr=rows, senses=my_sense,
                                rhs=my_rhs, names=my_rownames)

def main():
    try:
        model = cplex.Cplex()
        populate(model)
        model.solve()
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

    for j in range(numrows):
        print("Row %d:  Slack = %10f" % (j, slack[j]))
    for j in range(numcols):
        print("Column %d:  Value = %10f" % (j, x[j]))


if __name__ == '__main__':
    main()