import numpy as np
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import sys


print "Initializing... \t",
app = QtGui.QApplication([])
view = pg.GraphicsView()
l = pg.GraphicsLayout(border=(100,100,100))
view.setCentralItem(l)
view.show()
view.setWindowTitle('FFT display')
view.resize(800,600)
print "initialization complete."


p1 = l.addPlot(title="Time", col=1)
l.nextRow()
p2 = l.addPlot(title="FFT", col=1)








app.instance().exec_()

## Start Qt event loop unless running in interactive mode.
