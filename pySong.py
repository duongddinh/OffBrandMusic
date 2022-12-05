import asyncio
import sys
import time

import requests
import vlc




def YoutubeLookup():
    global youtubeID
    name = "I'm Still Standing By Elton John"
    url = "https://youtube-v2.p.rapidapi.com/search/"

    querystring = {"query": name, "lang": "en", "country": "us"}

    headers = {
        "X-RapidAPI-Key": "f0e0bb49b8msh380d03d27aa5fc7p19f33ajsna47ae205484d",
        "X-RapidAPI-Host": "youtube-v2.p.rapidapi.com"
    }

    response = requests.request("GET", url, headers=headers, params=querystring)

    json = str(response.text)
    splitting = json.split('"')
    number = 0
    for s in splitting:
        if number == 2:
            youtubeID = s
            break
        if number == 1:
            number+=1
        if s == "video_id":
            number +=1
    youtubeURL = "https://www.youtube.com/watch?v=" + youtubeID
    print(youtubeURL)

def YoutubeConvert():
    global Mp3URL
    array = []
    youtubeURL = "https://www.youtube.com/watch?v=" + youtubeID
    url = "https://t-one-youtube-converter.p.rapidapi.com/api/v1/createProcess"
    querystring = {"url": youtubeURL, "format": "mp3", "responseFormat": "json", "stop": "30", "lang": "en"}
    headers = {
        "X-RapidAPI-Key": "f0e0bb49b8msh380d03d27aa5fc7p19f33ajsna47ae205484d",
        "X-RapidAPI-Host": "t-one-youtube-converter.p.rapidapi.com"
    }
    response = requests.request("GET", url, headers=headers, params=querystring)
    json = str(response.text)
    split = json.split('"')
    try:
        theURL = split[11]
        ugh = theURL.split('\\')
        s = ""
        for i in ugh:
            array.append(i)
            Mp3URL = s.join(array)
        print(response.text)
    except:
        guid = split[3];
        YoutubeStatus(guid)
def YoutubeStatus(guid):
    global Mp3URL
    array = []
    youtubeURL = "https://www.youtube.com/watch?v=" + youtubeID
    url = "https://t-one-youtube-converter.p.rapidapi.com/api/v1/statusProcess"

    querystring = {"guid": guid, "responseFormat": "json", "lang": "it"}

    headers = {
        "X-RapidAPI-Key": "f0e0bb49b8msh380d03d27aa5fc7p19f33ajsna47ae205484d",
        "X-RapidAPI-Host": "t-one-youtube-converter.p.rapidapi.com"
    }

    response = requests.request("GET", url, headers=headers, params=querystring)
    json = str(response.text)
    split = json.split('"')
    theURL = split[11]
    ugh = theURL.split('\\')
    s = ""
    for i in ugh:
        array.append(i)
        Mp3URL = s.join(array)
    print(response.text)



def play():
    p = vlc.MediaPlayer(Mp3URL)
    p.play()

def main():
    YoutubeLookup()
    YoutubeConvert()
    play()
main()
