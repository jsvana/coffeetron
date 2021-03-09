# TODO: Pipfile
# TODO: config
# TODO: format
# TODO: argparse
import json
import sys
import time

import serial
from matplotlib import pyplot

DATA_FILE = "/home/jsvana/tmp/brew_data.json"
GRAPH_IMAGE = "graph2.png"

if len(sys.argv) > 1 and sys.argv[1] == "--existing":
    with open(DATA_FILE, "r") as f:
        data = json.load(f)

    pyplot.plot(data["x_series"], data["y_series"])
    pyplot.axhline(y=data["target_boiler_temp"], color="r", linestyle="-")
    pyplot.xlabel("Seconds from start")
    pyplot.ylabel("Boiler temp")
    pyplot.title("Boiler temp over time")
    pyplot.savefig(GRAPH_IMAGE)

    sys.exit(0)


x_series = []
y_series = []

start_time = int(time.time())

with serial.Serial('/dev/ttyACM0') as ser:
    while True:
        line = ser.readline().decode().strip()

        try:
            data = json.loads(line)
        except json.decoder.JSONDecodeError:
            continue

        x_series.append(int(time.time()) - start_time)
        y_series.append(data["boiler_temp"])

        if len(x_series) % 10 == 0:
            with open(DATA_FILE, "w") as f:
                json.dump({
                    "x_series": x_series,
                    "y_series": y_series,
                    "target_boiler_temp": data["target_boiler_temp"],
                }, f)

            pyplot.plot(x_series, y_series)
            pyplot.axhline(y=data["target_boiler_temp"], color="r", linestyle="-")
            pyplot.xlabel("Seconds from start")
            pyplot.ylabel("Boiler temp")
            pyplot.title("Boiler temp over time")
            pyplot.savefig(GRAPH_IMAGE)
