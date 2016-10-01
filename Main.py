import CustomVLCClass
import serial
import time
import threading

print("empieza")

numOfNFC = 5
numOfTags = 6

pastRead = []
for nfc in range(numOfNFC):
    pastRead.append(0)

while True:
    def arduinoListener():			#It is function that is listening if the arduino is sending something
        while True:
            try:
                line = ser.readline()	#Read the line
                if not line:
                    continue

                x = line.decode('ascii', errors='replace')	#Decode and pass to ascii

                for nfc in range(numOfNFC):
                    if x == str(nfc) + '0\r\n':
                        for tag in range(numOfTags):
                            if pastRead[nfc] == tag + 1:    #the for starts with a 0, we need the loop starting with 1
                                vlcObj[tag].mute()
                        pastRead[nfc] = 0

                    for tag in range(numOfTags):
                        if x == str(nfc) + str(tag + 1) + '\r\n':     #The for starts with a 0, we need the loop starting with 1 because now we are checking from 1 to the number of nfc, this means that there is a tag in the nfc
                            pastRead[nfc] = tag + 1
                            vlcObj[tag].unmute()

            except KeyboardInterrupt:
                print("exiting")
                break


    ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1.0)
    ser.setDTR(False)
    time.sleep(1)
    ser.flushInput()
    ser.setDTR(True)

    vlcObj = []
    for audio in range(numOfTags):
        vlcObj.append(CustomVLCClass.CustomVLCClass(filename=("/audio/" + str(audio + 1)) +".mp3"))

    for nfc in range(numOfNFC):
        for tag in range(numOfTags):
            if pastRead[nfc] == tag + 1:
                vlcObj[tag].unmute()

    inputArduinoThread = threading.Thread(target=arduinoListener, name="inputAduino")
    inputArduinoThread.start()

    while vlcObj[0].mediaplayer.is_playing() and vlcObj[1].mediaplayer.is_playing:
        time.sleep(0.1)
