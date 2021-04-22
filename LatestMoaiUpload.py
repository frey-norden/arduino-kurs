#First, we have a set of imports from libraries:
from time import sleep_ms, ticks_ms
from machine import I2C, Pin, DAC, PWM
import esp8266_i2c_lcd 
from hcsr04 import HCSR04
import network
import socket
import random
import urequests
import machine
import json

try:
    #Then, we create some variables and settings
    sensor = HCSR04(trigger_pin=16, echo_pin=23) #ultrasound sensor implementation
    i2c = I2C(scl=Pin(21), sda=Pin(22), freq=400000) #settings for LCD
    lcd = esp8266_i2c_lcd.I2cLcd(i2c, 0x27, 4, 20) #LCD implementation
    led=Pin(17,Pin.OUT)  #create LED object from pin2,Set Pin2 to output
    myDelay = 50 #define the length of the norse dot - this guides all timing
    myAdVar = 0 #define the variable that picks the random message
    #this sets up the array of letters from which the morse code index is found
    myMorseLetterString = "abdcefghijklmnopqrstuvwxyz.,01234567890!"
    #this sets up the array of morse code characters
    myMorseList = [".-", "-...", ".-.-", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", ".-", "..-", ".--", "-..-", "-.--", "--..",".-.-.-","--..--","-----", ".----", "..---", "...--", "....-", ".....","-....", "--...", "---..", "----.", "------","-.-.--"]
    #this sets up the array of advertising messages
    myAdsList = [["3D affects every\nline of business\nso learn some now!"],["3D Printing is the\nnew norm of working\nfor businesses!"],["Blender 3D is open\nsource, powerful\nand always free!"],["It is easy to learn\nhow to make robots\nwith Arduino!"],["It is real cool to\nlearn robotics\nand electronics."],["Join HaagaHelia\n3D Group on FB,\nover 400 members!"],["Teach yourself 3D\nmodeling, it is \nworth the effort!"],["The Internet of\nThings is great\nthe way forward!"],["We use Arduinos\nand Raspberries\nand ESP32 WROOM"],["Welcome to the\n3D and Robo Lab\nof Haaga-Helia"],["Why not learn to do\n3D and robotics, it\nis so much fun!"],["You have no idea\nhow much fun 3D is\nso come and learn!"],["Come on in and see\na 3D printer make\nsomething useful"],["Every business\nneeds to see how\n3D affects it"],["Teach yourself\nrobotics for a\ngood investment"],["Come and see how we\nmake robots and do\ninteresting stuff!"],["This Morse Moai is\nconnected to the\nInternet, really!"],["My message can be\nchanged wirelessly\nover the Internet!"],["I can make Morse\ncode out of anything\nyou want to say!"]]
    #REMOVE myAnswer =""
    #REMOVE myCodedAnswer =""
    p5=Pin(5)                    #create music object from pin5
    pwm5=PWM(p5)
    pwm5.deinit()
    myRawNetMsg = "" #this is the return string before converting to byte array
    myFinalMsg = "" #this is the return string in UTF-8 format
    myNetMsg ="" #this is the string passed on to be morse coded
    SSID="moaiwlan"
    PASSWORD="Ossi1Paavo234"
    url = "http://www.sabulo.com/moai3.txt" #this is the URL to get the message from 
    host="192.168.3.147" #the IP address given to the ESP32 at connection time
    port=100
    wlan=None
    s=None
    
    def connectWifi(ssid,passwd): #function to connect to the Web
      global wlan #declare a WLAN object
      lcd.move_to(0, 0) #move LCD cursor to top left corner
      lcd.putstr("Connecting to WLAN") #write the string to the LCD
      wlan=network.WLAN(network.STA_IF)                     #create a wlan object
      wlan.active(True)                                     #Activate the network interface
      wlan.disconnect()                                     #Disconnect the last connected WiFi
      wlan.connect(ssid,passwd)                             #connect wifi
      while(wlan.ifconfig()[0]=='0.0.0.0'): #wait for connection
        sleep_ms(1)
      sleep_ms(1000) #hold on for 1 second
      lcd.move_to(0, 0) #move cursor to top left corner
      lcd.putstr("Connected to WLAN   ") #write the string to LCD, note the blanks to erase the previous message
      url = "http://www.sabulo.com/myIoTBD.php"
      headers = {'content-type': 'application/json'}
      data = {'message': 'WLAN connected'}
      jsonObj = json.dumps(data)
      resp = urequests.post(url, data=jsonObj, headers=headers)
      sleep_ms(1000)  #hold on for 1 second
      lcd.clear() #clear the LCD screen
      return True 
      
    
    def getDist():
      distance = sensor.distance_cm()
      if (distance < 50):
        return True
      else:
        sleep_ms(1000)
        return False
    
    def mySendToCode(myLineToCode):
        for x in myLineToCode:
          if (x != "\n"):
            if (x == " "):
              myMorseAction("S","SPACE")
            elif (x == "P"):
              myMorseAction("P","PAUSE")
            elif (x== "!"):
              myMorseAction("!","-.-.--")
            else:    
              z = x.lower()
              myIndex = myMorseLetterString.find(z)
              myMorseAction(z,myMorseList[myIndex])
              sleep_ms(6* myDelay)
    
    def myMorseAction(myCharToShow,myCode):
      for myCharToPlay in myCode:
        lcd.move_to(0, 3)
        myMorseToShow = myCharToShow + " = " + myCode + "     "
        lcd.putstr(myMorseToShow)
        for x in myCharToPlay:
          if (x == "."):
            myPlaySound(myDelay)
            sleep_ms(40)
          elif (x == "-"):
            myPlaySound(3*myDelay)
            sleep_ms(40)
          elif (x== "P"):
            sleep_ms(3*myDelay)
          elif (x== "S"):
            sleep_ms(4*myDelay)
    
    def myPlaySound(length):
      p5=Pin(5)                    #create music object from pin5
      pwm5=PWM(p5)
      pwm5.duty(5000)
      pwm5.freq(300)
      led.value(1)
      sleep_ms(length)
      pwm5.deinit()
      led.value(0)
      
    def getURLMessage():
        try:
            response = urequests.get(url)
            if len(response.content) > 3:
              lcd.putstr("Getting message\nfrom server\nstay tuned!")
              sleep_ms(2000)
              lcd.clear()
              myRawNetMsg = response.content.decode('utf-8', 'ignore')
              #lcd.putstr(myRawNetMsg)
              #sleep_ms(5000)
              myFinalMsg = myRawNetMsg.split('\n')
              return(myFinalMsg)
            else:    
              lcd.putstr("No server message -\nso I will advertise\nthe 3D and Robo Lab")
              sleep_ms(2000)
              myFinalMsg=""
              lcd.clear()
            return(myFinalMsg)
    
        except Exception as e:
            print(e)
        sleep_ms(100)
    
      
    
    def main():
      connectWifi(SSID,PASSWORD)
      url = "http://www.sabulo.com/myIoTBD.php"
      headers = {'content-type': 'application/json'}
      data = {'message': 'Boot sequence','crash': 'LatestMoaiUpload.py'}
      jsonObj = json.dumps(data)
      resp = urequests.post(url, data=jsonObj, headers=headers)
      while(True):
        if (getDist() == True):
          lcd.display_on()
          lcd.backlight_on()
          myNetMsg = getURLMessage()
          if(myNetMsg == ""):
            myAdVar = random.randint(0, 18)
            vastaus = myAdsList[myAdVar]
            url = "http://www.sabulo.com/myIoTBD.php"
            headers = {'content-type': 'application/json'}
            data = {'message': 'Trigger random'}
            jsonObj = json.dumps(data)
            resp = urequests.post(url, data=jsonObj, headers=headers)
          else:
            url = "http://www.sabulo.com/myIoTBD.php"
            headers = {'content-type': 'application/json'}
            data = {'message': 'Trigger server'}
            jsonObj = json.dumps(data)
            resp = urequests.post(url, data=jsonObj, headers=headers)
            vastaus = myNetMsg
          chary=0    
          for line in vastaus:
            lcd.move_to(0, chary)
            lcd.putstr(line)
            chary = chary + 1
          for line in vastaus:    
             mySendToCode(line)
          else:
            sleep_ms(100)  
        lcd.clear()
        lcd.display_off()
        lcd.backlight_off()
        sleep_ms(500)  
    
    main()

except Exception as e:
    url = "http://www.sabulo.com/myIoTBD.php"
    headers = {'content-type': 'application/json'}
    data = {'message': 'Crashed', "crash":str(e)}
    jsonObj = json.dumps(data)
    resp = urequests.post(url, data=jsonObj, headers=headers)                
    import machine
    machine.reset()