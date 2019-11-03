from collections import Counter
import os


def score(NV, EDGES, COORD):
    ''' NV    : int Number of vertices in the input
        EDGES : list of edges as tuple (a,b) of the input
        COORD : list of coordinates as tuple (x,y) of the output
    '''
    if len(COORD) != NV: return f"bad size {len(COORD)} {NV}"
    C = Counter(COORD)
    SCORE_VERTICES = sum(3 * ((i - 1) ** 2) for i in C.values())
    SCORE_EDGES = 0
    for a, b in EDGES:
        d = abs(COORD[a][0] - COORD[b][0]) + abs(COORD[a][1] - COORD[b][1])
        if d == 0: return f"edge {a},{b} size 0"
        # print(a,b,2*((d-1)**2))
        SCORE_EDGES += 2 * ((d - 1) ** 2)
    min_x, min_y, max_x, max_y = COORD[0][0], COORD[0][1], COORD[0][0], COORD[0][1]
    for i in range(1, NV):
        min_x = min(min_x, COORD[i][0])
        max_x = max(max_x, COORD[i][0])
        min_y = min(min_y, COORD[i][1])
        max_y = max(max_y, COORD[i][1])
    if min_x < 0 or min_y < 0: return f"negative coordinates"
    SCORE_DIM = max(max_x - min_x, max_y - min_y) ** 2
    return sum((SCORE_VERTICES, SCORE_EDGES, SCORE_DIM))  # , SCORE_VERTICES, SCORE_EDGES,


if __name__ == '__main__':

    for name in os.listdir("./files"):
        if ".txt" in name:
            f = open("./files/" + name)
            NV = 0
            EDGES = []
            for line in f:
                if NV is 0:
                    NV = int(line.split()[0])
                else:
                    EDGES.append(tuple([int(x) for x in line.split()]))
                    COORD = []
            name = "./files/" + name.replace(".txt", ".ans")
            f = open(name)
            for line in f:
                COORD.append(tuple([int(x) for x in line.split()]))
                # print(len(COORD), len(EDGES), NV)
            print(name, " SCORE : ")
            print(score(NV, EDGES, COORD))
