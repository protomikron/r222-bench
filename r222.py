#!/usr/bin/python3

op0 = [1,3,0,2,21,20,6,7,4,5,10,11,12,13,14,15,9,8,18,19,16,17,22,23]
op1 = [0,1,8,10,5,7,4,6,15,9,14,11,12,13,20,22,16,17,18,19,3,21,2,23]
op2 = [0,19,2,17,4,1,6,3,9,11,8,10,12,7,14,5,16,13,18,15,20,21,22,23]

def update(cfg, op):
    targets = op0 if op == 0 else (op1 if op == 1 else op2)
    new_cfg = list(cfg)

    for i in range(24):
        new_cfg[i] = cfg[targets[i]]

    return ''.join(new_cfg)

SOLVED = 'RRRRYYYYBBBBOOOOWWWWGGGG'
tree = {SOLVED: ''}
tmp_tree = {SOLVED: ''}
while len(tmp_tree) > 0:
    new_tree = {}

    for cfg, ops in tmp_tree.items():
        for op in range(3):
            new_cfg = update(cfg, op)
            if new_cfg not in tree:
                tree[new_cfg] = ops + str(op)
                new_tree[new_cfg] = ops + str(op)

    tmp_tree = new_tree

for cfg, ops in tree.items():
    print(cfg + ': \'' + ops + '\'')
