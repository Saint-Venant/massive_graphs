import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import time


class PageRank:
    def __init__(self, outputDir):
        self.outputDir = outputDir
        self.file1 = 'exercise2_1_2.txt'
        self.fileAlpha10 = 'exercise2_save10.txt'
        self.fileAlpha15 = 'exercise2_save15.txt'
        self.fileAlpha20 = 'exercise2_save20.txt'
        self.fileAlpha50 = 'exercise2_save50.txt'
        self.fileAlpha90 = 'exercise2_save90.txt'

    @staticmethod
    def readLine_v1(s):
        return float(s[1])

    @staticmethod
    def readLine_v2(s):
        return int(s[2])

    @staticmethod
    def readLine_v3(s):
        return int(s[3][:-1])

    @classmethod
    def readLine(cls, pos):
        if pos == 1:
            return cls.readLine_v1
        if pos == 2:
            return cls.readLine_v2
        if pos == 3:
            return cls.readLine_v3

    def readFile1(self, posA, posB):
        filepath = self.outputDir + self.file1
        A = []
        B = []
        readA = self.readLine(posA)
        readB = self.readLine(posB)
        with open(filepath, 'r') as f:
            f.readline()
            for (k, line) in enumerate(f):
                s = line.split(' ')
                A.append(readA(s))
                B.append(readB(s))

        return np.array(A), np.array(B)        

    def readAlpha(self, alpha):
        if alpha == 0.1:
            filepath = self.outputDir + self.fileAlpha10
        elif alpha == 0.15:
            filepath = self.outputDir + self.fileAlpha15
        elif alpha == 0.2:
            filepath = self.outputDir + self.fileAlpha20
        elif alpha == 0.5:
            filepath = self.outputDir + self.fileAlpha50
        elif alpha == 0.9:
            filepath = self.outputDir + self.fileAlpha90

        pagerank = []
        readFunction = self.readLine(1)
        with open(filepath, 'r') as f:
            f.readline()
            for (k, line) in enumerate(f):
                s = line.split(' ')
                pagerank.append(readFunction(s))
        return np.array(pagerank)

    @staticmethod
    def extractSample(Nsample, x, y, size):
        index = np.arange(size)
        np.random.shuffle(index)
        sample = index[:Nsample]
        return x[sample], y[sample]

    @staticmethod
    def getValidArrays(pagerank, degree):
        valid = np.where(degree > 0)[0]
        pagerank = pagerank[valid]
        degree = degree[valid]
        n = valid.shape[0]
        return pagerank, degree, n

    @staticmethod
    def computeGrid(x, y, nbPages):
        grid = dict()
        for i in range(nbPages):
            key = (x[i], y[i])
            if (key[0] <= 0) or (key[1] <= 0):
                pass
            elif key in grid:
                grid[key] += 1
            else:
                grid[key] = 1
        return grid

    @staticmethod
    def proj(val, epsilon, reduction):
        k = int(val/epsilon)
        return epsilon*(k - k%reduction)

    @classmethod
    def plotWithCmap_v1(cls, pagerank, degree, nbPages, maxPoints):
        print('nb pages = ', nbPages)
        grid = cls.computeGrid(pagerank, degree, nbPages)
        reduction = 0
        epsilon = np.max(pagerank) / np.max(degree)
        while len(grid.keys()) > maxPoints:
            reduction += 1
            print(' > reduction : ', reduction)
            val1 = [cls.proj(val, epsilon, reduction) for val in pagerank]
            val2 = [(val - val%reduction) for val in degree]
            grid = cls.computeGrid(val1, val2, nbPages)
            print('   > length = ', len(grid.keys()))

        x = [z[0] for z in grid.keys()]
        y = [z[1] for z in grid.keys()]
        density = [val for val in grid.values()]
        plt.scatter(x, y, s=12, c=density, cmap='jet')

        cmap = plt.cm.get_cmap("jet")
        norm = mpl.colors.SymLogNorm(
            2,
            vmin=np.min(density),
            vmax=np.max(density),
            base=10)
        sm = mpl.cm.ScalarMappable(norm=norm, cmap=cmap)
        sm.set_array([])
        plt.colorbar(sm)

    @classmethod
    def plotWithCmap_v2(cls, pagerankA, pagerankB, nbPages, maxPoints):
        print('nb pages = ', nbPages)
        grid = cls.computeGrid(pagerankA, pagerankB, nbPages)
        reduction = 5
        nbSubdiv = 10**6
        epsilonA = np.max(pagerankA) / nbSubdiv
        epsilonB = np.max(pagerankB) / nbSubdiv
        while len(grid.keys()) > maxPoints:
            reduction += 2
            print(' > reduction : ', reduction)
            val1 = [cls.proj(val, epsilonA, reduction) for val in pagerankA]
            val2 = [cls.proj(val, epsilonB, reduction) for val in pagerankB]
            grid = cls.computeGrid(val1, val2, nbPages)
            print('   > length = ', len(grid.keys()))

        x = [z[0] for z in grid.keys()]
        y = [z[1] for z in grid.keys()]
        density = [val for val in grid.values()]
        plt.scatter(x, y, s=5, c=density, cmap='jet')

        cmap = plt.cm.get_cmap("jet")
        norm = mpl.colors.SymLogNorm(
            2,
            vmin=np.min(density),
            vmax=np.max(density),
            base=10)
        sm = mpl.cm.ScalarMappable(norm=norm, cmap=cmap)
        sm.set_array([])
        plt.colorbar(sm)

    def plotPRvsDegree(self, paramDegree, paramPlot, Nsample=1000, \
                       maxPoints=1000):
        assert(paramDegree in ['IN', 'OUT'])
        assert(paramPlot in ['sample', 'cmap'])
        
        t1 = time.time()
        if paramDegree == 'IN':
            xPageRank, yDegree = self.readFile1(1, 2)
            figureName = 'Ex2_figure1'
            labelY = 'Degree IN'
            title1 = 'Degree IN vs. PageRank for alpha = 0.15'
        elif paramDegree == 'OUT':
            xPageRank, yDegree = self.readFile1(1, 3)
            figureName = 'Ex2_figure2'
            labelY = 'Degree OUT'
            title1 = 'Degree OUT vs. PageRank for alpha = 0.15'
        t2 = time.time()

        xPageRank, yDegree, nbPages = self.getValidArrays(xPageRank, yDegree)
        
        plt.figure(figureName)
        if paramPlot == 'sample':
            title2 = '\n(sample of {} points)'.format(Nsample)
            x, y = self.extractSample(Nsample, xPageRank, yDegree, nbPages)
            plt.scatter(x, y, s=1)
        elif paramPlot == 'cmap':
            title2 = ''
            self.plotWithCmap_v1(xPageRank, yDegree, nbPages, maxPoints)
        
        plt.xscale('log')
        plt.yscale('log')
        plt.xlabel('PageRank (alpha = 0.15)')
        plt.ylabel(labelY)
        plt.title(title1 + title2)
        t3 = time.time()

        print('Reading time : ', t2 - t1)
        print('Plotting time : ', t3 - t2)

    @classmethod
    def plot_comparePageRank(cls, xPageRank, xAlpha, yPageRank, \
                             yAlpha, figureName, paramPlot, \
                             Nsample=1000, maxPoints=1000):
        assert(paramPlot in ['sample', 'cmap'])
        nbPages = xPageRank.shape[0]

        plt.figure(figureName)
        if paramPlot == 'sample':
            title2 = '\n(sample of {} points)'.format(Nsample)
            x, y = cls.extractSample(Nsample, xPageRank, yPageRank, nbPages)
            plt.scatter(x, y, s=1)
        elif paramPlot == 'cmap':
            title2 = ''
            cls.plotWithCmap_v2(xPageRank, yPageRank, nbPages, maxPoints)
        
        plt.xscale('log')
        plt.yscale('log')
        plt.xlabel('PageRank (alpha = {})'.format(xAlpha))
        plt.ylabel('PageRank (alpha = {})'.format(yAlpha))
        title1 = 'PageRank (alpha = {}) vs. PageRank (alpha = {})'.format(
            yAlpha,
            xAlpha)
        plt.title(title1 + title2)

    def plot3(self, paramPlot, Nsample=1000, maxPoints=1000):
        assert(paramPlot in ['sample', 'cmap'])
        
        t1 = time.time()
        pagerank15 = self.readAlpha(0.15)
        pagerank10 = self.readAlpha(0.1)

        t2 = time.time()
        self.plot_comparePageRank(
            pagerank15, 0.15,
            pagerank10, 0.1,
            'Ex2_figure3',
            paramPlot,
            Nsample=Nsample, maxPoints=maxPoints)
        t3 = time.time()

        print('Reading time : ', t2 - t1)
        print('Plotting time : ', t3 - t2)

    def plot4(self, paramPlot, Nsample=1000, maxPoints=1000):
        assert(paramPlot in ['sample', 'cmap'])
        
        t1 = time.time()
        pagerank15 = self.readAlpha(0.15)
        pagerank20 = self.readAlpha(0.2)

        t2 = time.time()
        self.plot_comparePageRank(
            pagerank15, 0.15,
            pagerank20, 0.2,
            'Ex2_figure4',
            paramPlot,
            Nsample=Nsample, maxPoints=maxPoints)
        t3 = time.time()

        print('Reading time : ', t2 - t1)
        print('Plotting time : ', t3 - t2)

    def plot5(self, paramPlot, Nsample=1000, maxPoints=1000):
        assert(paramPlot in ['sample', 'cmap'])
        
        t1 = time.time()
        pagerank15 = self.readAlpha(0.15)
        pagerank50 = self.readAlpha(0.5)

        t2 = time.time()
        self.plot_comparePageRank(
            pagerank15, 0.15,
            pagerank50, 0.5,
            'Ex2_figure4',
            paramPlot,
            Nsample=Nsample, maxPoints=maxPoints)
        t3 = time.time()

        print('Reading time : ', t2 - t1)
        print('Plotting time : ', t3 - t2)

    def plot6(self, paramPlot, Nsample=1000, maxPoints=1000):
        assert(paramPlot in ['sample', 'cmap'])
        
        t1 = time.time()
        pagerank15 = self.readAlpha(0.15)
        pagerank90 = self.readAlpha(0.9)

        t2 = time.time()
        self.plot_comparePageRank(
            pagerank15, 0.15,
            pagerank90, 0.9,
            'Ex2_figure4',
            paramPlot,
            Nsample=Nsample, maxPoints=maxPoints)
        t3 = time.time()

        print('Reading time : ', t2 - t1)
        print('Plotting time : ', t3 - t2)
        

if __name__ == '__main__':
    outputDir = '../outputEx2/'
    pr = PageRank(outputDir)

    N = 3*10**4

    # PageRank vs. degree IN
    # --- sample of points
    #pr.plotPRvsDegree('IN', 'sample', Nsample=N)
    # --- all points (cmap)
    #pr.plotPRvsDegree('IN', 'cmap', maxPoints=N)

    # PageRank vs. degree OUT
    # --- sample of points
    #pr.plotPRvsDegree('OUT', 'sample', Nsample=N)
    # --- all points (cmap)
    #pr.plotPRvsDegree('OUT', 'cmap', maxPoints=N)

    # PageRank (alpha=0.1) vs. PageRank (alpha=0.15)
    #pr.plot3('sample', Nsample=N)
    #pr.plot3('cmap', maxPoints=N)

    # PageRank (alpha=0.2) vs. PageRank (alpha=0.15)
    #pr.plot4('sample', Nsample=N)
    #pr.plot4('cmap', maxPoints=N)

    # PageRank (alpha=0.5) vs. PageRank (alpha=0.15)
    #pr.plot5('sample', Nsample=N)
    #pr.plot5('cmap', maxPoints=N)
    
    # PageRank (alpha=0.9) vs. PageRank (alpha=0.15)
    #pr.plot6('sample', Nsample=N)
    pr.plot6('cmap', maxPoints=N)
    
    plt.show()
