Problem 1 --

    run with `python invest2.py`

    This was our second attempt hence the 2.

    Our goal is to maximize return on investment minus 5% of what isn't invested.

    Our variables are the total amount spent on investments, and a levels x investments boolean matrix of decision variables.

    Our constraints are that you can only invest in each investment once and you cannot invest more than 100 million.

    This is our solution:

        Spent        : 10.0
        Investment 1 : Level 2
        Investment 2 : Level 1
        Investment 3 : Level 1
        Investment 4 : Level 2
        Investment 5 : Level 1
        Investment 6 : Level 2
        Investment 7 : Level 1
        Investment 8 : Level 0
        Total Revenue: 22.3
    
Problem 2 --

    run with `python farm.py`

    Our goal is to maximize the number of cows given to each son.

    Our variables are the number of cows per son, the ammount of milk per son, and a cows x sons boolean matrix of decision variables.

    Our constraints are each cow can only be given to one son, and each son must recive the same ammount of milk and the same number of cows.

    This is our solution:
        M: 369.0
        C: 9.0
        Son 1:
         1 11 12 27 34 61 70 73 80 = 369
        Son 2:
        18 24 32 36 40 48 53 54 64 = 369
        Son 3:
         2  3 10 15 42 71 72 76 78 = 369
        Son 4:
        19 20 21 28 39 45 51 65 81 = 369
        Son 5:
        22 29 30 31 38 44 50 57 68 = 369
        Son 6:
         9 25 26 33 37 46 56 60 77 = 369
        Son 7:
         6  7 17 35 55 58 62 63 66 = 369
        Son 8:
         4  5  8 13 52 59 74 75 79 = 369
        Son 9:
        14 16 23 41 43 47 49 67 69 = 369