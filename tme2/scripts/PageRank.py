import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import time

from mod2 import Output
from mod2 import PlotTools


class PageRank:
    def __init__(self):
        pass

    @staticmethod
    def getValidArrays(pagerank, degree):
        valid = np.where(degree > 0)[0]
        pagerank = pagerank[valid]
        degree = degree[valid]
        n = valid.shape[0]
        return pagerank, degree, n

    def plotPRvsDegree(self, paramDegree, paramPlot, maxPoints=1000):
        t1 = time.time()
        reader = Output.PageRankReader()
        xPageRank, yDegree = reader.readWithDegree(paramDegree)
        if paramDegree == 'IN':
            figureName = 'Ex2_figure1'
            labelY = 'Degree IN'
            title1 = 'Degree IN vs. PageRank for alpha = 0.15'
        elif paramDegree == 'OUT':
            figureName = 'Ex2_figure2'
            labelY = 'Degree OUT'
            title1 = 'Degree OUT vs. PageRank for alpha = 0.15'
        t2 = time.time()

        xPageRank, yDegree, nbPages = self.getValidArrays(xPageRank, yDegree)
        
        plt.figure(figureName)
        if paramPlot == 'sample':
            title2 = '\n(sample of {} points)'.format(maxPoints)
        elif paramPlot == 'cmap':
            title2 = ''
        PlotTools.draw_v1(xPageRank, yDegree, nbPages, paramPlot,
                          maxPoints, 500)
        
        plt.xscale('log')
        plt.yscale('log')
        plt.xlabel('PageRank (alpha = 0.15)')
        plt.ylabel(labelY)
        plt.title(title1 + title2)
        t3 = time.time()

        print('Reading time : ', t2 - t1)
        print('Plotting time : ', t3 - t2)

    def plot_comparePageRank(self, yAlpha, figureName, paramPlot,
                             maxPoints=1000):
        assert(paramPlot in ['sample', 'cmap'])

        t1 = time.time()
        reader = Output.PageRankReader()
        xPageRank, yPageRank = reader.readWithAlpha(yAlpha)
        xAlpha = 0.15
        nbPages = xPageRank.shape[0]

        t2 = time.time()
        plt.figure(figureName)
        if paramPlot == 'sample':
            title2 = '\n(sample of {} points)'.format(maxPoints)
            #x, y = self.extractSample(Nsample, xPageRank, yPageRank, nbPages)
            #plt.scatter(x, y, s=1)
        elif paramPlot == 'cmap':
            title2 = ''
            #self.plotWithCmap_v2(xPageRank, yPageRank, nbPages, maxPoints)
        PlotTools.draw_v2(xPageRank, yPageRank, nbPages, paramPlot,
                          maxPoints, 500)
        
        plt.xscale('log')
        plt.yscale('log')
        plt.xlabel('PageRank (alpha = {})'.format(xAlpha))
        plt.ylabel('PageRank (alpha = {})'.format(yAlpha))
        title1 = 'PageRank (alpha = {}) vs. PageRank (alpha = {})'.format(
            yAlpha,
            xAlpha)
        plt.title(title1 + title2)
        t3 = time.time()

        print('Reading time : ', t2 - t1)
        print('Plotting time : ', t3 - t2)

    def plot3(self, paramPlot, maxPoints=1000):
        self.plot_comparePageRank(
            0.1,
            'Ex2_figure3', paramPlot,
            maxPoints=maxPoints)

    def plot4(self, paramPlot, maxPoints=1000):
        self.plot_comparePageRank(
            0.2,
            'Ex2_figure4', paramPlot,
            maxPoints=maxPoints)

    def plot5(self, paramPlot, maxPoints=1000):
        self.plot_comparePageRank(
            0.5,
            'Ex2_figure5', paramPlot,
            maxPoints=maxPoints)

    def plot6(self, paramPlot, maxPoints=1000):
        self.plot_comparePageRank(
            0.9,
            'Ex2_figure6', paramPlot,
            maxPoints=maxPoints)
        

if __name__ == '__main__':
    pr = PageRank()

    N = 3*10**4

    # PageRank vs. degree IN
    # --- sample of points
    #pr.plotPRvsDegree('IN', 'sample', maxPoints=N)
    # --- all points (cmap)
    pr.plotPRvsDegree('IN', 'cmap', maxPoints=N)

    # PageRank vs. degree OUT
    # --- sample of points
    #pr.plotPRvsDegree('OUT', 'sample', maxPoints=N)
    # --- all points (cmap)
    #pr.plotPRvsDegree('OUT', 'cmap', maxPoints=N)

    # PageRank (alpha=0.1) vs. PageRank (alpha=0.15)
    #pr.plot3('sample', maxPoints=N)
    #pr.plot3('cmap', maxPoints=N)

    # PageRank (alpha=0.2) vs. PageRank (alpha=0.15)
    #pr.plot4('sample', maxPoints=N)
    #pr.plot4('cmap', maxPoints=N)

    # PageRank (alpha=0.5) vs. PageRank (alpha=0.15)
    #pr.plot5('sample', maxPoints=N)
    #pr.plot5('cmap', maxPoints=N)
    
    # PageRank (alpha=0.9) vs. PageRank (alpha=0.15)
    #pr.plot6('sample', maxPoints=N)
    #pr.plot6('cmap', maxPoints=N)
    
    plt.show()
