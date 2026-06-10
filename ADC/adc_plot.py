import serial
import matplotlib.pyplot as plt
from collections import deque

ser = serial.Serial('COM5',230400)

buf = deque(maxlen=1000)

plt.ion()

while True:
    try:
        line = ser.readline()

        value = int(
            line.decode().strip()
        )

        buf.append(value)

        plt.clf()
        plt.plot(buf)

        plt.pause(0.001)

    except:
        pass
