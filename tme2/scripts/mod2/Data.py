import numpy as np


class Data:
    def __init__(self, values, nbValues, nbSubdiv):
        self.values = values
        self.nbValues = nbValues
        self.minValue = np.min(values)
        self.maxValue = np.max(values)

        self.valuesLog = np.log(values)/np.log(10)
        self.minValueLog = np.log(self.minValue)/np.log(10)
        self.maxValueLog = np.log(self.maxValue)/np.log(10)
        self.delta = self.maxValueLog - self.minValueLog
        self.nbSubdiv = nbSubdiv
        self.epsilon = self.delta/nbSubdiv

    def projLog_val(self, i, reduction):
        val = self.valuesLog[i] - self.minValueLog
        k = int(val/self.epsilon)
        return self.minValueLog + self.epsilon*(k - k%reduction)
        
class DataFloat(Data):
    def __init__(self, values, nbValues, nbSubdiv):
        super().__init__(values, nbValues, nbSubdiv)

    def proj(self, reduction):
        return [10**self.projLog_val(i, reduction) \
                for i in range(self.nbValues)]


class DataInt(Data):
    def __init__(self, values, nbValues, nbSubdiv):
        super().__init__(values, nbValues, nbSubdiv)

    def proj(self, reduction):
        return [round(10**self.projLog_val(i, reduction)) \
                for i in range(self.nbValues)]
