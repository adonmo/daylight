import datetime
import pytz
import sys
from pathlib import Path
sys.path.append(str(Path(__file__).absolute().parent.parent.parent / "build" / "pybind"))

import daylight


def epoch(year, month, day, hour=0, minute=0, second=0, tz=pytz.UTC):
    return int(tz.localize(datetime.datetime(year, month, day, hour, minute, second)).timestamp())


def run_tests():
    tz = pytz.timezone("Asia/Kolkata")
    tz_offset = tz.utcoffset(datetime.datetime.utcnow()).total_seconds() / 3600

    sun = daylight.Sunclock(17.3859, 78.4867, tz_offset)
    assert sun.irradiance(epoch(2020, 5, 21, 14, 10, 35, tz)) == 0.882753920406182
    assert sun.sunrise(epoch(2020, 5, 21, tz=tz)) == epoch(2020, 5, 21, 5, 42, 41, tz)
    assert sun.solar_noon(epoch(2020, 5, 21, tz=tz)) == epoch(2020, 5, 21, 12, 12, 34, tz)
    assert sun.sunset(epoch(2020, 5, 21, tz=tz)) == epoch(2020, 5, 21, 18, 42, 28, tz)


if __name__ == "__main__":
    run_tests()
    print("All tests passed")
