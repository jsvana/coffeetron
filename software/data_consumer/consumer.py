# TODO: config
# TODO: format
# TODO: argparse
import json
import sys
import time
from datetime import datetime
from typing import Any, Dict

import serial
from influxdb_client import WritePrecision, InfluxDBClient, Point
from influxdb_client.client.write_api import SYNCHRONOUS

class CoffeeChart:
    def __init__(self) -> None:
        self.client = InfluxDBClient(url="http://localhost:8086", token="asdf", org="olympus")

        self.write_api = self.client.write_api(write_options=SYNCHRONOUS)

    def write_measurement(
        self,
        measurement: str,
        field: str,
        value: Any,
    ) -> Dict[str, Any]:
        point = Point(measurement).tag("location", "garage").field(field, value).time(
            datetime.utcnow(),  WritePrecision.MS,
        )
        self.write_api.write(bucket="espresso", org="olympus", record=point)


    def send_row_to_influx(self, row: Dict[str, Any]) -> None:
        # TODO: logger
        print(row)
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


chart = CoffeeChart()

with serial.Serial('/dev/ttyACM0') as ser:
    while True:
        line = ser.readline().decode().strip()

        try:
            row = json.loads(line)
        except json.decoder.JSONDecodeError:
            continue

        chart.send_row_to_influx(row)
