import sys
import numpy as np
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
from serial import Serial
from display import Screen

length = 500

def run():
	global screen
	global stream
	while (stream.in_waiting > 10):
		val = stream.readline()
		#screen.next_point(float(val))
		line = val.split(',')
		freq = 0
		for mag in line:
			screen.update_fft(freq, mag)
			freq += 15
	#screen.plot()
	screen.plot_fft()


print "Initializing..."
app = QtGui.QApplication([])
timer = pg.QtCore.QTimer()

port = sys.argv[1]
if (len(sys.argv) >= 3):
	baud = sys.argv[2]		
else:
	baud = 9600		

screen = Screen(length, 5, 120, 5)
stream = Serial(port, baud)

timer.timeout.connect(run)
timer.start(1) #milliseconds
print "Initialization complete."
app.instance().exec_()

stream.close()

