#https://www.geeksforgeeks.org/create-a-gui-to-extract-lyrics-from-song-using-python/
#from lyrics_extractor import SongLyrics
#extract_lyrics = SongLyrics("AIzaSyAioc_cAMamMxqE_E6VgXj_z4RITnfD4ZM", "b571a4104c6254ba5")
#extract_lyrics.get_lyrics("Shape of You")
import sys
from tkinter import *
from lyrics_extractor import SongLyrics

# user defined function

def get_lyrics():

    extract_lyrics = SongLyrics("AIzaSyAioc_cAMamMxqE_E6VgXj_z4RITnfD4ZM", "b571a4104c6254ba5")

    temp = extract_lyrics.get_lyrics(str(sys.argv[1]))
    res = temp['lyrics']
    result.set(res)


# object of tkinter
# and background set to light grey
master = Tk()
master.configure(bg='light grey')

# Variable Classes in tkinter
result = StringVar()

# Creating label for each information
# name using widget Label


Label(master, text="Result :",
      bg="light grey").grid(row=3, sticky=W)


# Creating label for class variable
# name using widget Entry
Label(master, text="", textvariable=result,
      bg="light grey").grid(row=3, column=1, sticky=W)

# creating a button using the widget

get_lyrics()



mainloop()
