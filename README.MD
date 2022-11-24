To compile file, do
```
pip install lyrics-extractor
```
```
gcc name.c -o name `pkg-config --cflags --libs gtk+-3.0` -lcurl
```

get python prerequiritories for macOS only if you are using linux, google how to get pip and python-tk

```
brew install python-tk
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
```

~Working on python implementation, compile file line should be (DONT DO THIS)~
```
gcc GUI.c -o test `pkg-config --cflags --libs gtk+-3.0` `pkg-config --cflags --libs -- python3` -lcurl
```
## TODO

1. Clean up code
2. memory mamagement (the current code right now has high chance of crashing because of bad code and memory allocation)
3. Array Struct needed or any sort of linked list
4. Potentially play music
