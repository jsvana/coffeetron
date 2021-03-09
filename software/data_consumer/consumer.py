import json
import time

import serial
from matplotlib import pyplot

x_series = []
y_series = []

with serial.Serial('/dev/ttyACM0') as ser:
    while True:
        line = ser.readline().decode().strip()

        try:
            data = json.loads(line)
        except json.decoder.JSONDecodeError:
            continue

        x_series.append(int(time.time()))
        y_series.append(data["boiler_temp"])

        if len(x_series) % 10 == 0:
            pyplot.plot(x_series, y_series)
            pyplot.axhline(y=int(data["target_boiler_temp"]), color="r", linestyle="-")
            pyplot.xlabel("Time")
            pyplot.ylabel("Boiler Temp")
            pyplot.title("Boiler temp over time")
            pyplot.savefig("graph.png")
