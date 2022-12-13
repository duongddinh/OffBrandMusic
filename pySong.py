import asyncio
import sys
import requests
import vlc
import time




def YoutubeLookup():
    global youtubeID
    name = str(sys.argv[1])
    print(name)
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
    try:
        youtubeURL = "https://www.youtube.com/watch?v=" + youtubeID
    except Exception as e:
        exit(1)


def YoutubeConvert():
    global Mp3URL, guid
    array = []
    youtubeURL = "https://www.youtube.com/watch?v=" + youtubeID
    url = "https://t-one-youtube-converter.p.rapidapi.com/api/v1/createProcess"
    querystring = {"url": youtubeURL, "format": "mp3", "responseFormat": "json", "stop": "30", "lang": "en"}
    headers = {
        #If API usage has been exceeded, change the key below to a0eb1f637bmsh09fa09d5335ca55p1fe5bajsn898b6666b127
        "X-RapidAPI-Key": "f0e0bb49b8msh380d03d27aa5fc7p19f33ajsna47ae205484d",
        "X-RapidAPI-Host": "t-one-youtube-converter.p.rapidapi.com"
    }
    response = requests.request("GET", url, headers=headers, params=querystring)
    json = str(response.text)
    split = json.split('"')
    #print(response.text)
    good = False
    count = 0
    bad = False
    tooMany = "You have exceeded the DAILY quota for Create Process on your current plan, BASIC. Upgrade your plan at https:\\/\\/rapidapi.com\\/tuttotone\\/api\\/t-one-youtube-converter"
    for i in split:
        if count == 2:
            theURL = i;
            break
        if count == 1:
            count+=1
        if i == "file":
            good = True
            count+=1
        if i == tooMany:
            print("Sorry, the API usage has been exceeded for today!")
            bad = True
            break
    if bad == False:
        if good:
            ugh = theURL.split('\\')
            s = ""
            for i in ugh:
                array.append(i)
                Mp3URL = s.join(array)
            print("The song has been gathered!")
            #print(response.text)
        else:
            guid = split[3]
            YoutubeStatus(guid)

def YoutubeStatus(guid):
    global Mp3URL
    array = []
    youtubeURL = "https://www.youtube.com/watch?v=" + youtubeID
    url = "https://t-one-youtube-converter.p.rapidapi.com/api/v1/statusProcess"

    querystring = {"guid": guid, "responseFormat": "json", "lang": "it"}

    headers = {
        #If API usage has been exceeded, change the key below to a0eb1f637bmsh09fa09d5335ca55p1fe5bajsn898b6666b127
        "X-RapidAPI-Key": "f0e0bb49b8msh380d03d27aa5fc7p19f33ajsna47ae205484d",
        "X-RapidAPI-Host": "t-one-youtube-converter.p.rapidapi.com"
    }

    response = requests.request("GET", url, headers=headers, params=querystring)
    json = str(response.text)
    split = json.split('"')
    count = 0
    good = False
    for i in split:
        if count == 2:
            theURL = i;
            break
        if count == 1:
            count+=1
        if i == "file":
            good = True
            count+=1
    if good:
        ugh = theURL.split('\\')
        s = ""import asyncio
import sys
import requests
import vlc
import time
import os




def YoutubeLookup():
    global youtubeID
    name = str(sys.argv[1])
    print(name)
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
    try:
        youtubeURL = "https://www.youtube.com/watch?v=" + youtubeID
    except Exception as e:
        exit(1)


def YoutubeConvert():
    global Mp3URL, guid
    array = []
    youtubeURL = "https://www.youtube.com/watch?v=" + youtubeID
    url = "https://t-one-youtube-converter.p.rapidapi.com/api/v1/createProcess"
    querystring = {"url": youtubeURL, "format": "mp3", "responseFormat": "json", "stop": "30", "lang": "en"}
    headers = {
        #If API usage has been exceeded, change the key below to a0eb1f637bmsh09fa09d5335ca55p1fe5bajsn898b6666b127
        "X-RapidAPI-Key": "f0e0bb49b8msh380d03d27aa5fc7p19f33ajsna47ae205484d",
        "X-RapidAPI-Host": "t-one-youtube-converter.p.rapidapi.com"
    }
    response = requests.request("GET", url, headers=headers, params=querystring)
    json = str(response.text)
    split = json.split('"')
    #print(response.text)
    good = False
    count = 0
    bad = False
    tooMany = "You have exceeded the DAILY quota for Create Process on your current plan, BASIC. Upgrade your plan at https:\\/\\/rapidapi.com\\/tuttotone\\/api\\/t-one-youtube-converter"
    for i in split:
        if count == 2:
            theURL = i;
            break
        if count == 1:
            count+=1
        if i == "file":
            good = True
            count+=1
        if i == tooMany:
            print("Sorry, the API usage has been exceeded for today!")
            bad = True
            break
    if bad == False:
        if good:
            ugh = theURL.split('\\')
            s = ""
            for i in ugh:
                array.append(i)
                Mp3URL = s.join(array)
            print("The song has been gathered!")
            #print(response.text)
        else:
            guid = split[3]
            YoutubeStatus(guid)

def YoutubeStatus(guid):
    global Mp3URL
    array = []
    youtubeURL = "https://www.youtube.com/watch?v=" + youtubeID
    url = "https://t-one-youtube-converter.p.rapidapi.com/api/v1/statusProcess"

    querystring = {"guid": guid, "responseFormat": "json", "lang": "it"}

    headers = {
        #If API usage has been exceeded, change the key below to a0eb1f637bmsh09fa09d5335ca55p1fe5bajsn898b6666b127
        "X-RapidAPI-Key": "f0e0bb49b8msh380d03d27aa5fc7p19f33ajsna47ae205484d",
        "X-RapidAPI-Host": "t-one-youtube-converter.p.rapidapi.com"
    }

    response = requests.request("GET", url, headers=headers, params=querystring)
    json = str(response.text)
    split = json.split('"')
    count = 0
    good = False
    for i in split:
        if count == 2:
            theURL = i;
            break
        if count == 1:
            count+=1
        if i == "file":
            good = True
            count+=1
    if good:
        ugh = theURL.split('\\')
        s = ""
        for i in ugh:
            array.append(i)
            Mp3URL = s.join(array)
        print("The song has been gathered!")
    else:
        #print("Have to repeat 1 more time!")
        time.sleep(2)
        YoutubeStatus(guid)


def play():
    try:
        p = vlc.MediaPlayer(Mp3URL)
        p.play()
        time.sleep(30)
    except:
        print("Have a good day!")

def main():
    YoutubeLookup()
    YoutubeConvert()
    play()

main()

        for i in ugh:
            array.append(i)
            Mp3URL = s.join(array)
        print("The song has been gathered!")
    else:
        #print("Have to repeat 1 more time!")
        time.sleep(2)
        YoutubeStatus(guid)


def play():
    try:
        p = vlc.MediaPlayer(Mp3URL)
        p.play()
        time.sleep(30)
    except:
        print("Have a good day!")

def main():
    YoutubeLookup()
    YoutubeConvert()
    play()

main()
