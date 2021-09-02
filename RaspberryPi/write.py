import serial
from time import sleep


serialport = serial.Serial("/dev/serial0", baudrate=9600, timeout=3.0)

while True:
    serialport.write(b"odbyt from python rpi\n\r")
    sleep(1)
