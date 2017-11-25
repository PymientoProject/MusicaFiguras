from __future__ import print_function

import CustomVLCClass
import serial
import time
import sys

'''This script mute or unmute audio files with nfc and tags. In my case, I have 5 NFC modules and 6 tags, when i put a tag in a module, the raspberry pi starts playing the song that is associated to the tag, with this method we can create a "DJ" table.
The arduino sends to the raspberry pi, via serial, when we enter a tag and when we take out the tag:
00 means that in the nfc 0 there is no tag
01 means that in the nfc 0 there is the tag 1
02 means that in the nfc 0 there is the tag 1
...
10 means that in the nfc 1 there is no tag
11 means that in the nfc 1 there is the tag 1
...
20 means that in the nfc 2 there is no tag'''

print("empieza")

numOfNFC = 6    #The number of NFC we have
numOfTags = 8   #The number of tags we have, IMPORTANT we must have the equal amount of tags and audios

pastRead = []   #Where we will storage the pastRead from the arduino
for nfc in range(numOfNFC):
    pastRead.append(0)


def arduinoListener():			#It is function that is listening if the arduino is sending something
    line = ser.readline()	# Read the line
    if not line:
        return ""

    x = line.decode('ascii', errors='replace')	#Decode and pass to ascii
    print(x, end='')

    return x

try:
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1.0, rtscts=True, dsrdtr=True)  # Start the communication with the arduino arduinoRead()
    print('Reiniciando arduino')
    time.sleep(6)
    print('Ya')

except (ImportError, serial.SerialException) as error:
    print("Error opening port " + str(error))
    sys.exit(1)

while True:
    try:
        vlcObj = []  # The vlc obj for playing the songs
        for audio in range(numOfTags):
            vlcObj.append(CustomVLCClass.CustomVLCClass(filename=("/audio/" + str(audio + 1)) + ".mp3"))

        for nfc in range(
                numOfNFC):  # The program is continually looping, so when the songs finish we have to start playing the songs associated to the tags that are in the nfc. If we don't do this, when the program start another time, the songs are muted even if there are tags in the nfc's
            for tag in range(numOfTags):
                if pastRead[nfc] == tag + 1:
                    vlcObj[tag].unmute()

        while vlcObj[0].mediaplayer.is_playing() and vlcObj[1].mediaplayer.is_playing:  # We wait until all the songs end
            try:
                 x = arduinoListener()
                 for nfc in range(numOfNFC):     #Read all the modules
                     if x == str(nfc) + '0\r\n':     #if the module have to tag we mute the song associated to the tag that was before
                         for tag in range(numOfTags):    #Check what tag was before
                             if pastRead[nfc] == tag + 1:    #the for starts with a 0, we need the loop starting with 1
                                 vlcObj[tag].mute()
                         pastRead[nfc] = 0       #After muting the song, we put that there is no tag in the nfc

                     for tag in range(numOfTags):    #This means, that there is a tag in the nfc, we read what tag is in, and then we save in pastRead an unmute the song.
                         if x == str(nfc) + str(tag + 1) + '\r\n':     #The for starts with a 0, we need the loop starting with 1 because now we are checking from 1 to the number of nfc, this means that there is a tag in the nfc
                             pastRead[nfc] = tag + 1
                             vlcObj[tag].unmute()
            except KeyboardInterrupt:
                print("exiting")
                sys.exit()
    except KeyboardInterrupt:
        print("Exiting")
        sys.exit()