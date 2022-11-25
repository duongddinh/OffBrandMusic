To compile file, do
```
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python3 get-pip.py
pip install lyrics-extractor
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

1. Array Struct needed or any sort of linked list
2. memory mamagement (the current code right now has high chance of crashing because of bad code and memory allocation)
3. Clean up code 
4. Make the GUI a bit more intuitive 
4. Potentially play music

# Road map

| Status      | Description | Contributor(s)|
| ----------- | ----------- |---------------|
| [DONE]       | Build basis of curl to grab Json from Genius (Nathan)       | Nathan |
| [DONE]   |  Build basis of Gtk GUI        | Duong Dinh |
| [NOT DONE] | Build advanced gtk GUI | No contributor|
|[DONE] |Build JSON parser to get 1 song name |Duong Dinh|
|[DONE] | Display one song to GUI |Duong Dinh|
|[IN PROGRESS] |Build JSON parser to get multiple songs' name |Duong Dinh|
|[NOT DONE] | Display multiple songs to GUI |No Contributor|
|[DONE] | Build JSON parser to get link to the song's lyric | Duong Dinh|
|[DONE] | Open default browser with link to the song's lyric | Duong Dinh|
| [NOT DONE] |Build JSON parser to get link to all the lyric |No contributor|
|[DONE] |Python to get full song lyric |Alanah, Duong Dinh |
| [DONE] | connect Python with C | Duong Dinh |
| [NOT DONE] | Data Structore | No contributor | 
|[NOT DONE]| DEBUG |All members|
| [NOT DONE] |Music player | no contributor|
| [IN PROGRESS] | project meets requirements| null |


