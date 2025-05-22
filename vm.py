#!/bin/python3

import sys


with open(sys.argv[1], "r") as f:
    raw = f.read()

cmds = []

for line in map(str.strip, raw.split('\n')):
    if len(line) == 0:
        continue

    cmds.append((line.split(' ') + [None])[:2])


pc = 0
acc = 0
mem = [0 for x in range(16)]

labs = {}
for index, cmd in enumerate(cmds):
    inst, arg = cmd

    if (inst == 'label'):
        labs[arg] = index


while pc < len(cmds):
    inst, arg = cmds[pc]
    pc += 1

    if arg:
        if arg.isdigit():
            arg = int(arg)
        else:
            arg = labs[arg]

    match inst.lower():
        case 'const': acc = arg
        case 'add'  : acc += mem[arg]
        case 'sub'  : acc -= mem[arg]
        case 'load' : acc = mem[arg]
        case 'store': mem[arg] = acc
        case 'print': print(acc)
        case 'jump' : pc = arg
        case 'branch':
            if acc == 0:
                pc = arg
        case 'halt' : break


