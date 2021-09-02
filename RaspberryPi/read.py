import serial

serialport = serial.Serial("/dev/serial0", baudrate=9600, timeout=3.0)

while True:
    # serialport.write(b"rnSay something:")
    rcv = serialport.read(100)
    print(rcv.decode('utf-8'))
