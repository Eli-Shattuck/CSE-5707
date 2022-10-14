\ENCODING=ISO-8859-1
\Problem name: 

Maximize
 obj1: - 0.05 Spent + Back_0 + Back_1 + Back_2 + Back_3 + Back_4 + Back_5
       + Back_6 + Back_7
Subject To
 budget:   Spent <= 10
 spent:    - Spent + Invest_1_0 + Invest_1_1 + Invest_1_2 + Invest_1_3
           + Invest_1_4 + Invest_1_5 + Invest_1_6 + Invest_1_7 + 2 Invest_2_0
           + 2 Invest_2_1 + 2 Invest_2_2 + 2 Invest_2_3 + 2 Invest_2_4
           + 2 Invest_2_5 + 2 Invest_2_6 + 2 Invest_2_7 + 3 Invest_3_0
           + 3 Invest_3_1 + 3 Invest_3_2 + 3 Invest_3_3 + 3 Invest_3_4
           + 3 Invest_3_5 + 3 Invest_3_6 + 3 Invest_3_7 + 4 Invest_4_0
           + 4 Invest_4_1 + 4 Invest_4_2 + 4 Invest_4_3 + 4 Invest_4_4
           + 4 Invest_4_5 + 4 Invest_4_6 + 4 Invest_4_7  = 0
 back_0:   - Back_0 + 4.1 Invest_1_0 + 5.8 Invest_2_0 + 6.5 Invest_3_0
           + 6.8 Invest_4_0  = 0
 back_1:   - Back_1 + 1.8 Invest_1_1 + 3 Invest_2_1 + 3.9 Invest_3_1
           + 4.5 Invest_4_1  = 0
 back_2:   - Back_2 + 1.5 Invest_1_2 + 2.5 Invest_2_2 + 3.3 Invest_3_2
           + 3.8 Invest_4_2  = 0
 back_3:   - Back_3 + 2.2 Invest_1_3 + 3.8 Invest_2_3 + 4.8 Invest_3_3
           + 5.5 Invest_4_3  = 0
 back_4:   - Back_4 + 1.3 Invest_1_4 + 2.4 Invest_2_4 + 3.2 Invest_3_4
           + 3.9 Invest_4_4  = 0
 back_5:   - Back_5 + 4.2 Invest_1_5 + 5.9 Invest_2_5 + 6.6 Invest_3_5
           + 6.8 Invest_4_5  = 0
 back_6:   - Back_6 + 2.2 Invest_1_6 + 3.5 Invest_2_6 + 4.2 Invest_3_6
           + 4.6 Invest_4_6  = 0
 back_7:   - Back_7 + Invest_1_7 + 1.7 Invest_2_7 + 2.3 Invest_3_7
           + 2.8 Invest_4_7  = 0
 invest_0: Invest_0_0 + Invest_1_0 + Invest_2_0 + Invest_3_0 + Invest_4_0  = 1
 invest_1: Invest_0_1 + Invest_1_1 + Invest_2_1 + Invest_3_1 + Invest_4_1  = 1
 invest_2: Invest_0_2 + Invest_1_2 + Invest_2_2 + Invest_3_2 + Invest_4_2  = 1
 invest_3: Invest_0_3 + Invest_1_3 + Invest_2_3 + Invest_3_3 + Invest_4_3  = 1
 invest_4: Invest_0_4 + Invest_1_4 + Invest_2_4 + Invest_3_4 + Invest_4_4  = 1
 invest_5: Invest_0_5 + Invest_1_5 + Invest_2_5 + Invest_3_5 + Invest_4_5  = 1
 invest_6: Invest_0_6 + Invest_1_6 + Invest_2_6 + Invest_3_6 + Invest_4_6  = 1
 invest_7: Invest_0_7 + Invest_1_7 + Invest_2_7 + Invest_3_7 + Invest_4_7  = 1
Bounds
      Spent >= 0
      Back_0 >= 0
      Back_1 >= 0
      Back_2 >= 0
      Back_3 >= 0
      Back_4 >= 0
      Back_5 >= 0
      Back_6 >= 0
      Back_7 >= 0
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
 Spent  Back_0  Back_1  Back_2  Back_3  Back_4  Back_5  Back_6  Back_7 
 Invest_0_0  Invest_0_1  Invest_0_2  Invest_0_3  Invest_0_4  Invest_0_5 
 Invest_0_6  Invest_0_7  Invest_1_0  Invest_1_1  Invest_1_2  Invest_1_3 
 Invest_1_4  Invest_1_5  Invest_1_6  Invest_1_7  Invest_2_0  Invest_2_1 
 Invest_2_2  Invest_2_3  Invest_2_4  Invest_2_5  Invest_2_6  Invest_2_7 
 Invest_3_0  Invest_3_1  Invest_3_2  Invest_3_3  Invest_3_4  Invest_3_5 
 Invest_3_6  Invest_3_7  Invest_4_0  Invest_4_1  Invest_4_2  Invest_4_3 
 Invest_4_4  Invest_4_5  Invest_4_6  Invest_4_7 
End
