import fileinput
val = 0
weight = 0

for line in fileinput.input():
    if ("Took item" in line):
        ints = [int(s) for s in line.replace("[", " ").replace("]", " ").split() if s.isdigit()]
        val += ints[1]
        weight += ints[2]
    elif (val == 0):
        print(line)
    pass

print("Val = ["+str(val)+"]\nWeight = ["+str(weight)+"]")