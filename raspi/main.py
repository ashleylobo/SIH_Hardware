import serial


with serial.Serial('/dev/ttyACM0', 9600, timeout=10) as ser:
    # x = ser.read()          # read one byte
    line = ser.readline()   # read a '\n' terminated line
    # s = ser.read(10)        # read up to ten bytes (timeout)
    print line

    ser.write(b'fuckyou')

    while(not line):


        line = ser.readline()   # read a '\n' terminated line

    print "Response: ", line