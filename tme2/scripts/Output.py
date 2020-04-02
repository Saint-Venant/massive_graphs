import numpy as np


outputDir = '../outputEx2/'
file1 = 'exercise2_1_2.txt'
fileAlpha10 = 'exercise2_save10.txt'
fileAlpha15 = 'exercise2_save15.txt'
fileAlpha20 = 'exercise2_save20.txt'
fileAlpha50 = 'exercise2_save50.txt'
fileAlpha90 = 'exercise2_save90.txt'

class FileReader:
    def __init__(self):
        pass

    @staticmethod
    def readLine_v1(s, pos):
        return float(s[pos])

    @staticmethod
    def readLine_v2(s, pos):
        return int(s[pos])

    @staticmethod
    def readLine_v3(s, pos):
        return int(s[pos][:-1])

    @staticmethod
    def readLine_v4(s, pos):
        return float(s[pos][:-1])
    

class PageRankReader(FileReader):
    def __init__(self):
        pass        

    @classmethod
    def readTemplate1(cls, readA, readB):
        filepath = outputDir + file1
        A = []
        B = []
        with open(filepath, 'r') as f:
            f.readline()
            for (k, line) in enumerate(f):
                s = line.split(' ')
                A.append(readA(s))
                B.append(readB(s))
        return np.array(A), np.array(B)

    @classmethod
    def readWithDegree(cls, paramDegree):
        assert(paramDegree in ['IN', 'OUT'])
        readPageRank = lambda s : cls.readLine_v1(s, 1)
        if paramDegree == 'IN':
            readDegree = lambda s : cls.readLine_v2(s, 2)
        elif paramDegree == 'OUT':
            readDegree = lambda s : cls.readLine_v3(s, 3)
        return cls.readTemplate1(readPageRank, readDegree)

    @classmethod
    def readAlpha(cls, alpha):
        if alpha == 0.1:
            filepath = outputDir + fileAlpha10
        elif alpha == 0.15:
            filepath = outputDir + fileAlpha15
        elif alpha == 0.2:
            filepath = outputDir + fileAlpha20
        elif alpha == 0.5:
            filepath = outputDir + fileAlpha50
        elif alpha == 0.9:
            filepath = outputDir + fileAlpha90

        pagerank = []
        readPR = lambda s : cls.readLine_v4(s, 1)
        with open(filepath, 'r') as f:
            f.readline()
            for (k, line) in enumerate(f):
                s = line.split(' ')
                pagerank.append(readPR(s))
        return np.array(pagerank)

    @classmethod
    def readWithAlpha(cls, alpha):
        assert(alpha in [0.1, 0.2, 0.5, 0.9])
        return cls.readAlpha(0.15), cls.readAlpha(alpha)
