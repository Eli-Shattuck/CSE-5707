Maximize
 obj: 310 C1_F + 380 C2_F + 350 C3_F + 285 C4_F
    + 310 C1_C + 380 C2_C + 350 C3_C + 285 C4_C
    + 310 C1_B + 380 C2_B + 350 C3_B + 285 C4_B

Subject To
 \ Ammount of each cargo constraints 
 c1: C1_F + C1_C + C1_B <= 18
 c2: C2_F + C2_C + C2_B <= 15
 c3: C3_F + C3_C + C3_B <= 23
 c4: C4_F + C4_C + C4_B <= 12
 \ Volume Constraints
  front_volume:  480 C1_F + 650 C2_F + 580 C3_F + 390 C4_F <= 6800
  center_volume: 480 C1_C + 650 C2_C + 580 C3_C + 390 C4_C <= 8700
  back_volume:   480 C1_B + 650 C2_B + 580 C3_B + 390 C4_B <= 5300
 \ Weight Constraints
  front_weight:  C1_F + C2_F + C3_F + C4_F <= 10
  center_weight: C1_C + C2_C + C3_C + C4_C <= 16
  back_weight:   C1_B + C2_B + C3_B + C4_B <= 8
 \ Ratio Constraints
  front_ratio:  3.4 C1_F + 3.4 C2_F + 3.4 C3_F + 3.4 C4_F - C1_F - C2_F - C3_F - C4_F - 
                                                            C1_C - C2_C - C3_C - C4_C -
                                                            C1_B - C2_B - C3_B - C4_B <= 0
  center_ratio: 2.125 C1_C + 2.125 C2_C + 2.125 C3_C + 2.125 C4_C - C1_F - C2_F - C3_F - C4_F - 
                                                                    C1_C - C2_C - C3_C - C4_C -
                                                                    C1_B - C2_B - C3_B - C4_B <= 0
  back_ratio:   4.25 C1_B + 4.25 C2_B + 4.25 C3_B + 4.25 C4_B - C1_F - C2_F - C3_F - C4_F - 
                                                                C1_C - C2_C - C3_C - C4_C -
                                                                C1_B - C2_B - C3_B - C4_B <= 0

Bounds
 C1_F >= 0
 C1_C >= 0
 C1_B >= 0
 C2_F >= 0
 C2_C >= 0
 C2_B >= 0
 C3_F >= 0
 C3_C >= 0
 C3_B >= 0
 C4_F >= 0
 C4_C >= 0
 C4_B >= 0

End