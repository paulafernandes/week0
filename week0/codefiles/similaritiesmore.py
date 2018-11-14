from enum import Enum

###### RESOURCES #######
# www.geeksforgeeks.org/dynamic-programming/#concepts

# en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#Python
# Implementing Levenshtein Distance in Python VIDEO:
# stackabuse.com/levenshtein-distance-and-text-similarity-in-python/
# www.programiz.com/python-programming/tuple

class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())

def distances(a, b):
    """Calculate edit distance from a to b"""

    # length of both strings
    lena = len(a) + 1
    lenb = len(b) + 1

    # stackoverflow.com/questions/2397141/how-to-initialize-a-two-dimensional-array-in-python
    # Create a table to store results of subproblems
    distTable = [[0 for x in range(lenb)] for x in range(lena)]
    distTable[0][0] = (0, None)
    for x in range(lena):
        for y in range(lenb):
            # builds case str1 is empty, how many insertions of str2 in str1
            if x == 0:
                distTable[x][y] = (y, None)
            # builds case str2 is empty, how many deletions on str1
            elif y == 0:
                distTable[x][y] = (x, None)
            # check if last chars are equal, take the value of the diagonal (x-1,y-1)
            elif a[x - 1] == b[y - 1]:
                distTable[x][y] = distTable[x-1][y-1]
            # checks the min value of different chars and adds 1
            else:
                ins = distTable[x][y-1][0]  # inserted
                dlt = distTable[x-1][y][0]  # deleted
                subs = distTable[x-1][y-1][0]   #substituted

                # calculate the minimum of the 3 operations
                calcMin = min(ins, dlt, subs)

                # acording to the calculated minimum, choose the right operation
                if calcMin == ins:
                    distTable[x][y] = (calcMin + 1, Operation.INSERTED)
                elif calcMin == dlt:
                    distTable[x][y] = (calcMin + 1, Operation.DELETED)
                else:
                    distTable[x][y] = (calcMin + 1, Operation.SUBSTITUTED)

    return distTable