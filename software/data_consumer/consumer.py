# TODO: config
# TODO: format
# TODO: argparse
import json
import sys
import time
from dataclasses import asdict, dataclass
from datetime import datetime
from typing import Any, Dict, List

import serial
from influxdb_client import WritePrecision, InfluxDBClient, Point
from influxdb_client.client.write_api import SYNCHRONOUS
from matplotlib import pyplot
from matplotlib.cm import get_cmap

@dataclass
class YMark:
    event: str
    time: int

    @classmethod
    def from_dict(cls, item: Dict[str, Any]) -> "YMark":
        return YMark(item["event"], item["time"])

class CoffeeChart:
    temp_times: List[int]
    temps: List[float]
    weight_times: List[int]
    weights: List[float]

    target_boiler_temp: int

    y_marks: List[YMark]

    start_time: int

    def __init__(self) -> None:
        self.temp_times = []
        self.temps = []
        self.weight_times = []
        self.weights = []

        self.target_boiler_temp = 0

        self.y_marks = []

        self.client = InfluxDBClient(url="http://localhost:8086", token="asdf", org="olympus")

        self.write_api = self.client.write_api(write_options=SYNCHRONOUS)

        start_time = int(time.time())

    def add_row(self, row: Dict[str, Any]) -> None:
        row_time = int(time.time())

        if row["type"] == "event":
            self.y_marks.append(YMark(
                row["event"],
                row_time,
            ))
            return

        if row["type"] == "temp":
            self.temp_times.append(row_time)
            self.temps.append(row["boiler_temp"])

            self.target_boiler_temp = row["target_boiler_temp"]

            return

        if row["type"] == "brew":
            self.weight_times.append(row_time)
            self.weights.append(max(0, row["weight"]))

            return

        raise ValueError('Unsupported row type "{}"'.format(row["type"]))

    @property
    def datapoint_count(self) -> int:
        return max(len(self.temp_times), len(self.weight_times))

    def write_datapoints(self, path: str) -> None:
        with open(path, "w") as f:
            json.dump({
                "temp_times": sorted(self.temp_times),
                "weight_times": sorted(self.weight_times),
                "temps": self.temps,
                "weights": self.weights,
                "target_boiler_temp": self.target_boiler_temp,
                "y_marks": [asdict(m) for m in self.y_marks],
            }, f)

    def generate_chart(self, path: str) -> None:
        pyplot.close()
        pyplot.clf()
        pyplot.cla()

        fig, ax1 = pyplot.subplots()

        ax1.set_xlabel('Seconds from start')
        ax1.set_ylabel('Boiler temp')
        ax1.tick_params(axis='y', labelcolor='green')

        ax1.axhline(y=self.target_boiler_temp, label="Target temp", color="green")

        for mark in self.y_marks:
            ax1.axvline(x=mark.time, linestyle="dashed")
            ax1.text(mark.time, self.target_boiler_temp, mark.event, rotation=270, verticalalignment='top')

        ax1.plot(self.temp_times, self.temps, color="green")

        if self.weights:
            ax2 = ax1.twinx()

            ax2.set_ylabel("Brew weight")
            ax2.tick_params(axis='y', labelcolor='blue')
            ax2.plot(self.weight_times, self.weights, color="blue")

        fig.tight_layout()

        pyplot.savefig(path)

    def write_measurement(
        self,
        measurement: str,
        field: str,
        value: Any,
    ) -> Dict[str, Any]:
        point = Point(measurement).tag("location", "garage").field(field, value).time(
            datetime.utcnow(),  WritePrecision.MS,
        )
        # print(point.to_line_protocol())
        # point = Point("my_measurement").tag("location", "Prague").field("temperature", 25.3).time(datetime.now(), WritePrecision.MS)
        self.write_api.write(bucket="espresso", org="olympus", record=point)

    def send_row_to_influx(self, row: Dict[str, Any]) -> None:
        row_time = int(time.time())

        if row["type"] == "event":
            self.write_measurement(
                "event",
                "event",
                row["event"],
            )
        elif row["type"] == "temp":
            self.write_measurement(
                "boiler_temp",
                "temperature",
                row["boiler_temp"],
            )

            self.write_measurement(
                "grouphead_temp",
                "temperature",
                row["grouphead_temp"],
            )

            self.write_measurement(
                "target_boiler_temp",
                "temperature",
                row["target_boiler_temp"],
            )
        elif row["type"] == "brew":
            self.write_measurement(
                "brew",
                "weight",
                row["weight"],
            )
        else:
            raise ValueError('Unsupported row type "{}"'.format(row["type"]))


DATA_FILE = "/home/jsvana/tmp/brew_data.json"
GRAPH_IMAGE = "graph2.png"

chart = CoffeeChart()

now = int(time.time())
data_file = "brew.{}.json".format(now)
graph_image = "brew.{}.png".format(now)

with serial.Serial('/dev/ttyACM0') as ser:
    while True:
        line = ser.readline().decode().strip()

        try:
            row = json.loads(line)
        except json.decoder.JSONDecodeError:
            continue

        chart.send_row_to_influx(row)

        # chart.add_row(row)

        # chart.write_datapoints(data_file)
        # chart.generate_chart(graph_image)
