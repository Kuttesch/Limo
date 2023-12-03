import time

import serial


ser = serial.Serial(port='/dev/tty.usbmodem1101',
                    baudrate=9600,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    bytesize=serial.EIGHTBITS)


def write_rotation(y: int, z: int):
    x = str(y)+","+str(z)
    print(x)
    ser.write(bytes(x, "ascii"))
    print(ser.readline())
