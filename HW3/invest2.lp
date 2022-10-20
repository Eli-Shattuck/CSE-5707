\ENCODING=ISO-8859-1
\Problem name: 

Maximize
 obj1: - 0.5 Spent + 4.1 Invest_1_0 + 1.8 Invest_1_1 + 1.5 Invest_1_2
       + 2.2 Invest_1_3 + 1.3 Invest_1_4 + 4.2 Invest_1_5 + 2.2 Invest_1_6
       + Invest_1_7 + 5.8 Invest_2_0 + 3 Invest_2_1 + 2.5 Invest_2_2
       + 3.8 Invest_2_3 + 2.4 Invest_2_4 + 5.9 Invest_2_5 + 3.5 Invest_2_6
       + 1.7 Invest_2_7 + 6.5 Invest_3_0 + 3.9 Invest_3_1 + 3.3 Invest_3_2
       + 4.8 Invest_3_3 + 3.2 Invest_3_4 + 6.6 Invest_3_5 + 4.2 Invest_3_6
       + 2.3 Invest_3_7 + 6.8 Invest_4_0 + 4.5 Invest_4_1 + 3.8 Invest_4_2
       + 5.5 Invest_4_3 + 3.9 Invest_4_4 + 6.8 Invest_4_5 + 4.6 Invest_4_6
       + 2.8 Invest_4_7
Subject To
 spent:    - Spent + Invest_1_0 + Invest_1_1 + Invest_1_2 + Invest_1_3
           + Invest_1_4 + Invest_1_5 + Invest_1_6 + Invest_1_7 + 2 Invest_2_0
           + 2 Invest_2_1 + 2 Invest_2_2 + 2 Invest_2_3 + 2 Invest_2_4
           + 2 Invest_2_5 + 2 Invest_2_6 + 2 Invest_2_7 + 3 Invest_3_0
           + 3 Invest_3_1 + 3 Invest_3_2 + 3 Invest_3_3 + 3 Invest_3_4
           + 3 Invest_3_5 + 3 Invest_3_6 + 3 Invest_3_7 + 4 Invest_4_0
           + 4 Invest_4_1 + 4 Invest_4_2 + 4 Invest_4_3 + 4 Invest_4_4
           + 4 Invest_4_5 + 4 Invest_4_6 + 4 Invest_4_7  = 0
 invest_0: Invest_0_0 + Invest_1_0 + Invest_2_0 + Invest_3_0 + Invest_4_0  = 1
 invest_1: Invest_0_1 + Invest_1_1 + Invest_2_1 + Invest_3_1 + Invest_4_1  = 1
 invest_2: Invest_0_2 + Invest_1_2 + Invest_2_2 + Invest_3_2 + Invest_4_2  = 1
 invest_3: Invest_0_3 + Invest_1_3 + Invest_2_3 + Invest_3_3 + Invest_4_3  = 1
 invest_4: Invest_0_4 + Invest_1_4 + Invest_2_4 + Invest_3_4 + Invest_4_4  = 1
 invest_5: Invest_0_5 + Invest_1_5 + Invest_2_5 + Invest_3_5 + Invest_4_5  = 1
 invest_6: Invest_0_6 + Invest_1_6 + Invest_2_6 + Invest_3_6 + Invest_4_6  = 1
 invest_7: Invest_0_7 + Invest_1_7 + Invest_2_7 + Invest_3_7 + Invest_4_7  = 1
Bounds
 0 <= Spent <= 10
 0 <= Invest_0_0 <= 1
 0 <= Invest_0_1 <= 1
 0 <= Invest_0_2 <= 1
 0 <= Invest_0_3 <= 1
 0 <= Invest_0_4 <= 1
 0 <= Invest_0_5 <= 1
 0 <= Invest_0_6 <= 1
 0 <= Invest_0_7 <= 1
 0 <= Invest_1_0 <= 1
 0 <= Invest_1_1 <= 1
 0 <= Invest_1_2 <= 1
 0 <= Invest_1_3 <= 1
 0 <= Invest_1_4 <= 1
 0 <= Invest_1_5 <= 1
 0 <= Invest_1_6 <= 1
 0 <= Invest_1_7 <= 1
 0 <= Invest_2_0 <= 1
 0 <= Invest_2_1 <= 1
 0 <= Invest_2_2 <= 1
 0 <= Invest_2_3 <= 1
 0 <= Invest_2_4 <= 1
 0 <= Invest_2_5 <= 1
 0 <= Invest_2_6 <= 1
 0 <= Invest_2_7 <= 1
 0 <= Invest_3_0 <= 1
 0 <= Invest_3_1 <= 1
 0 <= Invest_3_2 <= 1
 0 <= Invest_3_3 <= 1
 0 <= Invest_3_4 <= 1
 0 <= Invest_3_5 <= 1
 0 <= Invest_3_6 <= 1
 0 <= Invest_3_7 <= 1
 0 <= Invest_4_0 <= 1
 0 <= Invest_4_1 <= 1
 0 <= Invest_4_2 <= 1
 0 <= Invest_4_3 <= 1
 0 <= Invest_4_4 <= 1
 0 <= Invest_4_5 <= 1
 0 <= Invest_4_6 <= 1
 0 <= Invest_4_7 <= 1
Generals
 Spent  Invest_0_0  Invest_0_1  Invest_0_2  Invest_0_3  Invest_0_4  Invest_0_5 
 Invest_0_6  Invest_0_7  Invest_1_0  Invest_1_1  Invest_1_2  Invest_1_3 
 Invest_1_4  Invest_1_5  Invest_1_6  Invest_1_7  Invest_2_0  Invest_2_1 
 Invest_2_2  Invest_2_3  Invest_2_4  Invest_2_5  Invest_2_6  Invest_2_7 
 Invest_3_0  Invest_3_1  Invest_3_2  Invest_3_3  Invest_3_4  Invest_3_5 
 Invest_3_6  Invest_3_7  Invest_4_0  Invest_4_1  Invest_4_2  Invest_4_3 
 Invest_4_4  Invest_4_5  Invest_4_6  Invest_4_7 
End
