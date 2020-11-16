import os
import subprocess
import sys

if (len(sys.argv) < 2):
    print("Provide a text file containing the location of your data files")
    sys.exit(1)

file = open(sys.argv[1], 'r')
lines = file.readlines()
if (len(lines) != 4):
    print("Incorrect number of paths")
    exit(1)
file.close()
cmds = []
for line in lines:
    cmds.append(line.rstrip('\n'))
print("Executing now...")
args = ("./build/facemask", cmds[0], cmds[1], cmds[2], cmds[3])
process = subprocess.Popen(args)
process.wait()



