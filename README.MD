To compile file, do
```
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python3 get-pip.py
pip install lyrics-extractor
pip install requests
```
```
gcc name.c -o name `pkg-config --cflags --libs gtk+-3.0` -lcurl
```

get python prerequiritories for macOS only if you are using linux, google how to get pip and python-tk

```
brew install python-tk

```

~Working on python implementation, compile file line should be (DONT DO THIS)~
```
gcc GUI.c -o test `pkg-config --cflags --libs gtk+-3.0` `pkg-config --cflags --libs -- python3` -lcurl
```
## TODO

1. Clean up code 
2. Make the GUI a bit more intuitive 
3. Potentially play music
4. No GUI mode where UI is just a terminal with terminal UI environment

# Road map

| Status      | Description | Contributor(s)|
| ----------- | ----------- |---------------|
| [DONE]       | Build basis of curl to grab Json from Genius      | Nathan Murphy |
| [DONE]   |  Build basis of Gtk GUI        | Duong Dinh |
| [NOT DONE] | Build advanced gtk GUI | No contributor|
|[DONE] |Build JSON parser to get 1 song name |Duong Dinh|
|[DONE] | Display one song to GUI |Duong Dinh|
|[DONE] |Build JSON parser to get multiple songs' name |Nathan Murphy|
|[DONE] | Display multiple songs to GUI |Nathan Murphy, Duong Dinh|
|[DONE] | Build JSON parser to get link to the song's lyric | Duong Dinh|
|[DONE] | Open default browser with link to the song's lyric | Duong Dinh|
| [DONE] |Build JSON parser to get link to all the lyric | Nathan Murphy |
|[DONE] |Python to get full song lyric |Alanah, Duong Dinh |
| [DONE] | connect Python with C | Duong Dinh |
| [DONE] | Data Structure | Nathan Murphy | 
|[DONE]| DEBUG -- realloc at WriteMemoryCallback| Nathan Murphy |
| [DONE] |Python Code For Playing Song | Aafant Shrestha / Nathan Murphy |
| [DONE] |Music player | Nathan Murphy |
| [NOT DONE] |Clean up code and warnings | no contributor |
| [IN PROGRESS] |No GUI mode where UI is just a terminal with option | Aafant Shrestha |
| [IN PROGRESS] | project meets requirements| YES |


