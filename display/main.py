import sys
import numpy as np
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
from serial import Serial
from display import Screen

length = 343
time = 0

def run():
	global screen
	global stream
	global time
	if (stream.in_waiting > 10):
		val = stream.readline()
		screen.next_point(float(val))
	if (time % 1 == 0):
		screen.plot()



print "Initializing..."
app = QtGui.QApplication([])
timer = pg.QtCore.QTimer()

port = sys.argv[1]
if (sys.argv[2] != None):
	baud = sys.argv[2]		
else:
	baud = 9600		

screen = Screen(length, 2, 100, 2)
stream = Serial(port, baud)

timer.timeout.connect(run)
timer.start(10) #milliseconds
print "Initialization complete."
app.instance().exec_()

stream.close()

