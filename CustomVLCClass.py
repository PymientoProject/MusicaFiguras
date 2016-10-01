import vlc
import os

class CustomVLCClass:

    def __init__(self, filename):
        self.instance = vlc.Instance()
        self.mediaplayer = self.instance.media_player_new()

        self.media = self.instance.media_new(
            os.path.normpath(os.getcwd() + filename))
        self.mediaplayer.set_media(self.media)
        self.mediaplayer.audio_set_volume(0)
        self.mediaplayer.play()


    def stop(self):
        self.mediaplayer.stop()

    def play(self):
        self.mediaplayer.play()

    def pause(self):
        self.mediaplayer.pause()

    def mute(self):
        self.mediaplayer.audio_set_volume(0)

    def unmute(self):
        self.mediaplayer.audio_set_volume(100)
