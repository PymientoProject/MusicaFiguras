from __future__ import print_function
import serial
import threading

def arduinoRead():
    while True:
        try:

            line = ser.readline()
            x = line.decode('ascii', errors='replace')  # Decode and pass to ascii

            print(x, end='')

        except KeyboardInterrupt:
            print("Exiting")
            break

try:
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1.0, rtscts=True, dsrdtr=True)      #Start the communication with the arduino
    #arduinoRead()
    inputArduinoThread = threading.Thread(target=arduinoRead, name="inputAduino")  # Start a thread for listening the arduino
    inputArduinoThread.daemon = True
    inputArduinoThread.start()

except (ImportError, serial.SerialException) as error:
    print("Error opening port " + str(error))
