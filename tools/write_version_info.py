import socket
import subprocess
import sys
import time


def get_version_info(base_path=""):
    try:
        git_revision = subprocess.check_output(["git", "rev-parse", "HEAD"]).decode("utf-8") .split("\n")[0]
        git_branch = subprocess.check_output(["git", "rev-parse","--abbrev-ref", "HEAD"]).decode("utf-8").split("\n")[0]
    except (subprocess.CalledProcessError, OSError):
        git_revision = ""
        git_branch = "non-git"

    def read_version():
        with open(base_path + "VERSION") as f:
            return f.readline().strip()

    build_datetime = time.strftime("%a, %d %b %Y %H:%M:%S +0000", time.gmtime())
    version_number = read_version()

    hostname = socket.gethostname()

    return git_revision, git_branch, build_datetime, version_number, hostname


if __name__ =="__main__":
    output_file = sys.argv[1]
    with open(output_file, "w") as fout:
        fout.write("""#pragma once
namespace libdaylight{{
namespace version{{
auto constexpr git_revision = u8"{0}";
auto constexpr git_branch = u8"{1}";
auto constexpr build_datetime = u8"{2}";
auto constexpr version_number = u8"{3}";
auto constexpr build_hostname = u8"{4}";
}}
}}

""".format(*get_version_info()))
