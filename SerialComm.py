import serial # if you have not already done so
port = 'COM8'


ard = serial.Serial(port,9600,timeout=5)
while(True):
	ard.write(b'5')
