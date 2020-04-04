

filename = '../../instances_tme2/scholar/ID.txt'

class Authors:
    def __init__(self):
        self.names = []
        with open(filename, 'r') as f:
            for (k, line) in enumerate(f):
                s = line[:-1].split(' ')
                i = int(s[0])
                name = self.reduce(
                    s[1:],
                    lambda x, y : x + ' ' + y)
                assert(i == k)
                self.names.append(name)

    @classmethod
    def reduce(cls, s, f):
        if len(s) == 1:
            return s[0]
        else:
            return cls.reduce([f(s[0], s[1])] + s[2:], f)
