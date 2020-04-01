import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import time


class CoreValue:
    def __init__(self, outputDir):
        self.outputDir = outputDir
        self.filepath = outputDir + 'exercise4_save.txt'

    @staticmethod
    def readFile(filepath):
        xDegree = []
        yCoreValue = []
        with open(filepath, 'r') as f:
            f.readline()
            for (k, line) in enumerate(f):
                s = line.split(' ')
                xDegree.append(int(s[2][:-1]))
                yCoreValue.append(int(s[1]))
        return np.array(xDegree), np.array(yCoreValue)

    @staticmethod
    def extractSample(Nsample, x, y, size):
        index = np.arange(size)
        np.random.shuffle(index)
        sample = index[:Nsample]
        return x[sample], y[sample]

    def plot_scatter(self, Nsample=1000):
        t1 = time.time()
        xDegree, yCoreValue = self.readFile(self.filepath)
        t2 = time.time()

        valid = np.where(xDegree > 0)[0]
        xDegree = xDegree[valid]
        yCoreValue = yCoreValue[valid]
        nbNodes = valid.shape[0]
        print('nbNodes = ', nbNodes)

        if nbNodes < Nsample:
            Nsample = nbNodes
        x, y = self.extractSample(Nsample, xDegree, yCoreValue, nbNodes)

        plt.figure('Ex4_figure1')
        plt.scatter(x, y, s=2)
        plt.plot([1, np.max(x)], [1, np.max(x)], c='k')
        plt.xscale('log')
        plt.yscale('log')
        plt.xlabel('Degree')
        plt.ylabel('Core value')
        title1 = 'Core value vs. Degree\n'
        title2 = '(sample of {} points)'.format(Nsample)
        plt.title(title1 + title2)
        t3 = time.time()

        print('Reading time : ', t2 - t1)
        print('Plotting time : ', t3 - t2)

    @staticmethod
    def computeGrid(x, y, nbNodes):
        grid = dict()
        for i in range(nbNodes):
            key = (x[i], y[i])
            if key in grid:
                grid[key] += 1
            else:
                grid[key] = 1
        return grid

    def plot_cmap(self, maxPoints):
        t1 = time.time()
        xDegree, yCoreValue = self.readFile(self.filepath)
        t2 = time.time()

        valid = np.where(xDegree > 0)[0]
        xDegree = xDegree[valid]
        yCoreValue = yCoreValue[valid]
        nbNodes = valid.shape[0]
        print('nbNodes = ', nbNodes)

        grid = self.computeGrid(xDegree, yCoreValue, nbNodes)
        reduction = 1
        while len(grid.keys()) > maxPoints:
            reduction += 1
            val1 = [(val - val%reduction) for val in xDegree]
            val2 = [(val - val%reduction) for val in yCoreValue]
            grid = self.computeGrid(val1, val2, nbNodes)
        print('reduction : ', reduction)
        x = [z[0] for z in grid.keys()]
        y = [z[1] for z in grid.keys()]
        density = [val for val in grid.values()]

        cmap = plt.cm.get_cmap("jet")
        norm = mpl.colors.SymLogNorm(
            2,
            vmin=np.min(density),
            vmax=np.max(density),
            base=10)
        sm = mpl.cm.ScalarMappable(norm=norm, cmap=cmap)
        sm.set_array([])

        plt.figure('Ex4_figure1')
        plt.plot([1, np.max(x)], [1, np.max(x)], c='k')
        plt.scatter(x, y, s=20, c=density, cmap='jet')
        plt.xscale('log')
        plt.yscale('log')
        plt.xlabel('Degree')
        plt.ylabel('Core value')
        plt.title('Core value vs. Degree')
        plt.colorbar(sm)
        t3 = time.time()

        print('Reading time : ', t2 - t1)
        print('Plotting time : ', t3 - t2)
    


if __name__ == '__main__':
    outputDir = '../outputEx4/'
    cv = CoreValue(outputDir)

    N = 10**4
    #cv.plot_scatter(Nsample=N)
    cv.plot_cmap(10**4)
    
    plt.show()
