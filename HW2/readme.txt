Problem 1 --

    run with `python cargo.py`

    Our goal is to maximize profit, which is sum of the amount of each type of cargo in each hold multiplied by the profit per tonne of that kind of cargo.

    Our variables are the amount of each cargo type in each section CN_M where CN_M is the amount of cargo type N, in section M.

    Our constraints are the mass and volume of each type is limited by a maximum threshold. And the total mass in each section times the ratio that section is of the total minus the sum of all the mass must be 0. (i.e. the mass in a section over the total mass must equal that sections mass ratio)

    This is our solution vector:
    C1_F: 0.0
    C2_F: 10.0
    C3_F: 0.0
    C4_F: 0.0
    C1_C: 0.0
    C2_C: 0.0
    C3_C: 12.947368421052632
    C4_C: 3.052631578947368
    C1_B: 0.0
    C2_B: 5.0
    C3_B: 3.0
    C4_B: 0.0

    Our total profit is $13830.833333
    
Problem 2 --

    run with `python planning.py`

    Our goal is to minimize cost, which is the sum of the production cost each month, the cost of the amount stored each month, and the cost of the amount ruined each month. 

    Our variables are: P_3 - P_8, where P_N is the amount produced in month N,
                       S_3 - S_7, where S_N is the amount stored at the end of month N,
                       R_4 - R_8, where R_N is the amount ruined between month N-1 and N.

    Our constraints are a maximum production amount each month, stored units getting ruined each month, and the demand each month.


    We have the property that forall months, m >= 3, .89*(P + .89P - D_{m-1}) + P >= D_m
    where P is the max production and D_m is the demand for month m

    Because of this, and because we can sell stock first, we never need to store stock for more than one month, which is why we can ignore the constraint that after two months 47% of the stock gets ruined. Except for month 3, where S_0 is multipled by 0, S_1 is multiplied by .53, and S_2 is multiplied by .89. Where S_0 - S_3 = {500, 2000, 1000}

    Our total cost is $266589.604295    

    Our solution vector:
    P_3 = 3050.0
    P_4 = 6000.0
    P_5 = 7504.157629626268
    P_6 = 8000.0
    P_7 = 8000.0
    P_8 = 8000.0

    This results in the other variables being:
    S_3 = 0.0
    S_4 = 0.0
    S_5 = 1004.1576296262683
    S_6 = 1893.7002903673783
    S_7 = 1685.393258426966
    R_4 = 0.0
    R_5 = 0.0
    R_6 = 110.45733925888952
    R_7 = 208.3070319404116
    R_8 = 185.39325842696627