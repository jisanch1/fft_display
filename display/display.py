import numpy as np
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import sys

class Screen:

	def __init__(self, x, y, fx, fy):
		
		self.view = pg.GraphicsView()
		self.layout = pg.GraphicsLayout(border=(100,100,100))
		self.view.setCentralItem(self.layout)
		self.view.show()
		self.view.setWindowTitle('FFT display')
		self.view.resize(800,600)
		#self.p1 = self.layout.addPlot(title="Time", col=1)
		#self.p1.setRange(yRange=[0, y])
		#self.p1.setRange(xRange=[0, x])
		#self.layout.nextRow()
		self.p2 = self.layout.addPlot(title="FFT", col=1)
		self.p2.setRange(yRange=[0, fy])
		self.p2.setRange(xRange=[0, fx])
		#self.curve1 = self.p1.plot()
		self.curve2 = self.p2.plot(stepMode=True, fillLevel=0)
		#self.pos = 0
		#self.time = np.arange(x)
		#self.data = np.zeros(x, float)
		self.freq = np.arange(fx + 1)
		self.fdata = np.zeros(fx, float)


	def plot(self):
		self.curve1.setData(self.time, self.data)
		#self.curve1.setData(self.time, self.data, pen=None, symbol='o', symbolPen=None, symbolSize=3, symbolBrush=('b'))

	def plot_fft(self): 
		self.curve2.setData(self.freq, self.fdata)

	def next_point(self, point):
		self.data[self.pos] = point
		self.pos += 1
		self.pos %= self.time.size

	def update_fft(self, freq, val):
		self.fdata[freq] = val

	def reset_fft(self):
		self.fdata = np.zeros(self.fdata.size, float)

		

## Testbench
'''
print "Initializing..."
app = QtGui.QApplication([])
length = 347
screen = Screen(length, 2, 100, 2)
time = 0

def run():
	global screen
	global time
	volt = np.sin(np.pi*time/34)
	screen.next_point(volt)
	if (time % 1 == 0):
		screen.plot()
	if (time % 1 == 0):
		screen.update_fft((time % 10)*10, volt)
	if (time % 10 == 0):
		screen.plot_fft()
	time += 1

timer = pg.QtCore.QTimer()
timer.timeout.connect(run)
timer.start(10) #milliseconds
print "initialization complete."

app.instance().exec_()
'''