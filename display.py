import numpy as np
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import sys

'''
class Screen:

	def __init__(self, x, y, fx, fy):
		print "Initializing... \t",
		self.app = QtGui.QApplication([])
		self.view = pg.GraphicsView()
		self.l = pg.GraphicsLayout(border=(100,100,100))
		self.view.setCentralItem(l)
		self.view.show()
		self.view.setWindowTitle('FFT display')
		self.view.resize(800,600)
		self.p1 = l.addPlot(title="Time", col=1)
		self.p1.setRange(yRange=[-y, y])
		self.p1.setRange(xRange=[0, x])
		self.l.nextRow()
		self.p2 = l.addPlot(title="FFT", col=1)
		self.p2.setRange(yRange=[0, fy])
		self.p2.setRange(xRange=[0, fx])
		print "initialization complete."
'''
y = 2
x = 355
fx = 101
fy = 2

print "Initializing... \t",
app = QtGui.QApplication([])
view = pg.GraphicsView()
l = pg.GraphicsLayout(border=(100,100,100))
view.setCentralItem(l)
view.show()
view.setWindowTitle('FFT display')
view.resize(800,600)
p1 = l.addPlot(title="Time", col=1)
p1.setRange(yRange=[-y, y])
p1.setRange(xRange=[0, x])
l.nextRow()
p2 = l.addPlot(title="FFT", col=1)
p2.setRange(yRange=[0, fy])
p2.setRange(xRange=[0, fx])
print "initialization complete."

curve1 = p1.plot()


time = 0
data = np.zeros((x,2),float)
timeRed = np.arange(101)
dataRed = np.zeros(100)

curve2 = p2.plot(stepMode=True, fillLevel=0)

def plot():
	global time
	global data
	global dataRed
	volt = np.sin(np.pi*time/100)
	tup = (time % x, volt)
	data[time % x] = np.array(tup)
	#curve1.setData(data, pen=None, symbol='o', symbolPen=None, symbolSize=3, symbolBrush=('b'))
	curve1.setData(data, pen=None, symbol='o', symbolPen=None, symbolSize=3, symbolBrush=('b'))
	time += 1
	dataRed[(10 * time + 5) % 100] = volt
	curve2.setData(timeRed, dataRed) 

def update():
	plot()

timer = pg.QtCore.QTimer()
timer.timeout.connect(update)
timer.start(10) #milliseconds

app.instance().exec_()

## Start Qt event loop unless running in interactive mode.
