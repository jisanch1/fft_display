import numpy as np
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import sys

class Screen:

	def __init__(self, x, y, fx, fy):
		print "Initializing..."
		self.view = pg.GraphicsView()
		self.layout = pg.GraphicsLayout(border=(100,100,100))
		self.view.setCentralItem(self.layout)
		self.view.show()
		self.view.setWindowTitle('FFT display')
		self.view.resize(800,600)
		self.p1 = self.layout.addPlot(title="Time", col=1)
		self.p1.setRange(yRange=[-y, y])
		self.p1.setRange(xRange=[0, x])
		self.layout.nextRow()
		self.p2 = self.layout.addPlot(title="FFT", col=1)
		self.p2.setRange(yRange=[0, fy])
		self.p2.setRange(xRange=[0, fx])
		self.curve1 = self.p1.plot()
		self.curve2 = self.p2.plot(stepMode=True, fillLevel=0)
		print "Creating buffers..."
		self.pos = 0
		self.len = x
		self.time = np.arange(x)
		self.data = np.zeros(x, float)
		self.freq = np.arange(fx + 1)
		self.dataf = np.zeros(fx, float)
		print "initialization complete."


	def plot(self):
		self.curve1.setData(self.time, self.data, pen=None, symbol='o', symbolPen=None, symbolSize=3, symbolBrush=('b'))
		

	def plot_fft(self): 
		self.curve2.setData(self.freq, self.dataf)

	def next_point(self, point):
		self.data[self.pos] = point
		self.pos += 1
		self.pos %= self.len

		

## Testbench
app = QtGui.QApplication([])

length = 355
screen = Screen(length, 2, 100, 2)
time = 0

def run():
	global screen
	global time
	volt = np.sin(np.pi*time/100)
	screen.next_point(volt)
	screen.plot()
	time += 1


timer = pg.QtCore.QTimer()
timer.timeout.connect(run)
timer.start(10) #milliseconds
app.instance().exec_()
