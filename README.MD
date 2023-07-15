Ensure pip and python-tk are installed

To compile file, do
```
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python3 get-pip.py
pip install lyrics-extractor
pip install requests
pip install python-vlc
```
```
gcc GUI.c -o GUI `pkg-config --cflags --libs gtk+-3.0` -lcurl
```
To run the program execute it with 
```
./GUI
```
To run the program with no GUI execute it with
```
./GUI silent
```
