Minimize
 \
 obj: 15 P_3 + 15 P_4 + 15 P_5 + 15 P_6 + 15 P_7 + 15 P_8 +
      .75 S_3 + .75 S_4 + .75 S_5 + .75 S_6 + .75 S_7 +
      25 R_4 + 25 R_5 + 25 R_6 + 25 R_7 + 25 R_8

Subject To
 \ cannot produce more than 8000u/month
 \
 pc3: P_3 <= 8000
 pc4: P_4 <= 8000
 pc5: P_5 <= 8000
 pc6: P_6 <= 8000
 pc7: P_7 <= 8000
 pc8: P_8 <= 8000
 \ stored = produced + not ruined
 \
 sc3: S_3 - P_3 = -3050           \  S_3 = P_3 +    1950 - 5000
 sc4: S_4 - P_4 - .89 S_3 = -6000 \  S_4 = P_4 + .89 S_3 - 6000
 sc5: S_5 - P_5 - .89 S_4 = -6500 \  S_5 = P_5 + .89 S_4 - 6500
 sc6: S_6 - P_6 - .89 S_5 = -7000 \  S_6 = P_6 + .89 S_5 - 7000
 sc7: S_7 - P_7 - .89 S_6 = -8000 \  S_7 = P_7 + .89 S_6 - 8000
 \ produced + stored > demand
 \
 dc3: P_3           >= 3050 \ P_3 - 1950 >= 5000
 dc4: P_4 + .89 S_3 >= 6000
 dc5: P_5 + .89 S_4 >= 6500
 dc6: P_6 + .89 S_5 >= 7000
 dc7: P_7 + .89 S_6 >= 8000
 dc8: P_8 + .89 S_7 >= 9500
 \ ruined = not stored
 \
 rc4: R_4 - .11 S_3 = 0
 rc5: R_5 - .11 S_4 = 0
 rc6: R_6 - .11 S_5 = 0
 rc7: R_7 - .11 S_6 = 0
 rc8: R_8 - .11 S_7 = 0
End