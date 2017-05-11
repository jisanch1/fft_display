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

nsamples = 555 #Number of lines for the data

p1 = l.addPlot(title="Time", col=1)
p1.setRange(yRange=[-1, 1])
p1.setRange(xRange=[0, nsamples])
l.nextRow()
p2 = l.addPlot(title="FFT", col=1)
p2.setRange(yRange=[0, 10])
p2.setRange(xRange=[0, 120])

curve1 = p1.plot()
curve2 = p2.plot()

time = 0
data = np.zeros((nsamples,2),float)

def plot():
	global time
	global data
	volt = np.sin(np.pi*time/100)
	tup = (time % nsamples, volt)
	data[time % nsamples] = np.array(tup)

	curve1.setData(data, pen=None, symbol='o', symbolPen=None, symbolSize=2, symbolBrush=('b'))
	time += 1
    #curve2.setData(dataRed, pen=None, symbol='o', symbolPen=None, symbolSize=4, symbolBrush=('r')) 

def update():
	plot()

timer = pg.QtCore.QTimer()
timer.timeout.connect(update)
timer.start(10) #milliseconds

app.instance().exec_()

## Start Qt event loop unless running in interactive mode.
