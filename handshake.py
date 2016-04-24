__author__ = 'vutsuak'

import serial
import time
import httplib
import urllib

ard = serial.Serial('COM7', 9600)
time.sleep(2)


# Symultaneous read and write from serialBoard
def getData(command, field):
    ard.flush()
    command = str(command)
    ard.write(command)
    time.sleep(1)
    msg = ard.read(ard.inWaiting())  # read all characters in buffer
    print msg
    if msg is not None:
        params = urllib.urlencode({field: msg, 'key': '9TT66I1OF28UWUDL'})
        conn = httplib.HTTPConnection("api.thingspeak.com:80")
    try:
        conn.request("POST", "/update", params)
        response = conn.getresponse()
        print msg
        print response.status, response.reason
        data = response.read()
        conn.close()
    except:
        print "connection failed"


while True:
    getData("Temperature", "field1")
    getData("Humidity", "field2")
    getData("LDR", "field3")
