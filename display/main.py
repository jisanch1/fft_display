import sys
import numpy as np
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
from serial import Serial
from display import Screen

length = 343

def run():
	global screen
	global stream

	volt = np.sin(np.pi*time/34)
	screen.next_point(volt)
	if (time % 1 == 0):
		screen.plot()
	if (time % 1 == 0):
		screen.update_fft((time % 10)*10, volt)
	if (time % 10 == 0):
		screen.plot_fft()
	time += 1



print "Initializing..."
app = QtGui.QApplication([])
timer = pg.QtCore.QTimer()

port = sys.argv[1]
baud = sys.argv[2]

screen = Screen(length, 2, 100, 2)
stream = Serial(port, baud)

time = 0



timer.timeout.connect(run)
timer.start(10) #milliseconds
print "Initialization complete."
app.instance().exec_()

