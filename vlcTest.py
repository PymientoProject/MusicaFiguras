import CustomVLCClass
import time

song = CustomVLCClass.CustomVLCClass(filename=("/audio/1.mp3"))
song.unmute()
time.sleep(0.1)

while song.mediaplayer.is_playing():  # We wait until all the songs end
    time.sleep(0.1)
