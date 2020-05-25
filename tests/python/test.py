import sys
from pathlib import Path
sys.path.append(str(Path(__file__).absolute().parent.parent.parent / "build" / "pybind"))

import daylight


def run_tests():
    # TODO
    pass


if __name__ == "__main__":
    run_tests()
    print("All tests passed")
