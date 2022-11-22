To compile file, do
```
gcc name.c -o name `pkg-config --cflags --libs gtk+-3.0` -lcurl
```
Working on python implementation, compile file line should be
```
gcc GUI.c -o test `pkg-config --cflags --libs gtk+-3.0` `pkg-config --cflags --libs -- python3` -lcurl
```
