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

text = """
This example demonstrates the use of GraphicsLayout to arrange items in a grid.<br>
The items added to the layout must be subclasses of QGraphicsWidget (this includes <br>
PlotItem, ViewBox, LabelItem, and GrphicsLayout itself).
"""
l.addLabel(text, col=1, colspan=4)	








app.instance().exec_()

## Start Qt event loop unless running in interactive mode.
