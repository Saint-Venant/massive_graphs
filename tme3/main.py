import pandas
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

import sys

# thank you stackoverflow :)
def get_cmap(n, name='hsv'):
    '''Returns a function that maps each index in 0, 1, ..., n-1 to a distinct 
    RGB color; the keyword argument name must be a standard mpl colormap name.'''
    return plt.cm.get_cmap(name, n)

df = pandas.read_csv(sys.argv[1], header=None, sep=' ')
G = nx.Graph()
G.add_edges_from([(df.iloc[i, 0], df.iloc[i, 1]) for i in range(len(df))])

if len(sys.argv) == 2:
    nx.draw(G, with_labels=True, font_weight='bold')
    plt.show()
elif len(sys.argv) == 3:
    df_colors = pandas.read_csv(sys.argv[2], header=None, sep=' ')
    classes = np.unique(df_colors.iloc[:,1])
    cmap = get_cmap(len(classes))
    cmap = [np.array(cmap(i)).reshape(1, -1) for i in range(len(classes))]
    if len(classes) == 4:
        cmap = ['r', 'g', 'b', 'm']
    pos = nx.spring_layout(G)
    for i, c in enumerate(classes):
        nx.draw(G, pos, 
                nodelist=list((df_colors[df_colors.iloc[:, 1] == c]).iloc[:, 0]), 
                node_color=cmap[i])
    plt.show()
