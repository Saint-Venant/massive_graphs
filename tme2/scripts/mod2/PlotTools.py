import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

from mod2 import Data


class DrawWithSample:
    def __init__(self):
        pass

    @staticmethod
    def extractSample(xValues, yValues, nbValues, Nsample):
        index = np.arange(nbValues)
        np.random.shuffle(index)
        sample = index[:Nsample]
        return xValues[sample], yValues[sample]

    def plot(self, xValues, yValues, nbValues, Nsample):
        Nsample = min(Nsample, nbValues)
        x, y = self.extractSample(xValues, yValues, nbValues, Nsample)
        plt.scatter(x, y, s=1)

class DrawWithCmap:
    def __init__(self):
        pass

    @staticmethod
    def computeGrid(xValues, yValues, nbValues):
        grid = dict()
        for i in range(nbValues):
            key = (xValues[i], yValues[i])
            if key in grid:
                grid[key] += 1
            else:
                grid[key] = 1
        return grid

    @classmethod
    def adjustGrid(cls, xData, yData, nbValues, maxPoints):
        grid = cls.computeGrid(xData.values, yData.values, nbValues)
        reduction = 1
        while len(grid.keys()) > maxPoints:
            print(' > reduction : ', reduction)
            val1 = xData.proj(reduction)
            val2 = yData.proj(reduction)
            grid = cls.computeGrid(val1, val2, nbValues)
            print('   > length = ', len(grid.keys()))
            reduction *= 2
        return grid

    @staticmethod
    def proj(val, epsilon, reduction):
        k = int(val/epsilon)
        return epsilon*(k - k%reduction)

    @staticmethod
    def getSize(val, maxDensity, minDensity):
        return (np.log(1+val)/5)**2.5

    @classmethod
    def getSizes(cls, density):
        maxDensity = np.max(density)
        minDensity = np.min(density)
        return [cls.getSize(val, maxDensity, minDensity) for val in density]

    @classmethod
    def plotFromGrid(cls, grid):
        x = [z[0] for z in grid.keys()]
        y = [z[1] for z in grid.keys()]
        density = [val for val in grid.values()]
        sizes = cls.getSizes(density)
        plt.scatter(x, y, s=sizes, c=density, cmap='jet')

        cmap = plt.cm.get_cmap("jet")
        norm = mpl.colors.SymLogNorm(
            2,
            vmin=np.min(density),
            vmax=np.max(density),
            base=10)
        sm = mpl.cm.ScalarMappable(norm=norm, cmap=cmap)
        sm.set_array([])
        plt.colorbar(sm)

    def plot(self, xData, yData, nbValues, maxPoints):
        print('nbValues = ', nbValues)
        grid = self.adjustGrid(
            xData, yData, nbValues,
            maxPoints)
        self.plotFromGrid(grid)
        
def draw_v1(xPageRank, yDegree, nbValues, paramPlot, N, nbSubdiv):
    assert(paramPlot in ['sample', 'cmap'])
    if paramPlot == 'sample':
        drawer = DrawWithSample()
        drawer.plot(xPageRank, yDegree, nbValues, N)
    elif paramPlot == 'cmap':
        drawer = DrawWithCmap()
        
        xData = Data.DataFloat(xPageRank, nbValues, nbSubdiv)
        yData = Data.DataInt(yDegree, nbValues, nbSubdiv)
        
        drawer.plot(xData, yData, nbValues, N)
        
def draw_v2(xPageRank, yPageRank, nbValues, paramPlot, N, nbSubdiv):
    assert(paramPlot in ['sample', 'cmap'])
    if paramPlot == 'sample':
        drawer = DrawWithSample()
        drawer.plot(xPageRank, yPageRank, nbValues, N)
    elif paramPlot == 'cmap':
        drawer = DrawWithCmap()

        xData = Data.DataFloat(xPageRank, nbValues, nbSubdiv)
        yData = Data.DataFloat(yPageRank, nbValues, nbSubdiv)
        
        drawer.plot(xData, yData, nbValues, N)
