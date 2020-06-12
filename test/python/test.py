import datetime
import pytest
import pytz

# This is a hack as of now to get cross platform CI tests running
# TODO find a more elegant way
import sys
from pathlib import Path

is_windows = hasattr(sys, 'getwindowsversion')
if is_windows:
    sys.path.append(str(Path(__file__).absolute().parent.parent.parent / "build" / "test" / "_deps" / "daylight-build" / "Release"))
else:
    sys.path.append(str(Path(__file__).absolute().parent.parent.parent / "build" / "test" / "_deps" / "daylight-build"))
# end of hack

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

    assert (sun.irradiance([
        epoch(2020, 5, 21, 3, 0, 0, tz),
        epoch(2020, 5, 21, 7, 0, 0, tz),
        epoch(2020, 5, 21, 9, 30, 0, tz),
        epoch(2020, 5, 21, 12, 0, 0, tz),
        epoch(2020, 5, 21, 16, 0, 0, tz),
        epoch(2020, 5, 21, 18, 0, 0, tz),
        epoch(2020, 5, 21, 21, 0, 0, tz),
        epoch(2020, 5, 21, 23, 59, 59, tz),
    ]) == pytest.approx([
        -0.56570521,
        0.28650605,
        0.78259762,
        0.99753419,
        0.59285478,
        0.15220325,
        -0.49458177,
        -0.79117714,
    ]))


if __name__ == "__main__":
    run_tests()
    print("All tests passed")
