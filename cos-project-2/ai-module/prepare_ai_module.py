import os
import sys
import argparse
import logging
from utils.etc import camel_code

def prepare_algorithms(dname):
    edir = "{}".format(dname)

    anames = []

    algorithms = [f for f in os.listdir(edir) if f.endswith(".py") and f != "algorithm.py"]

    for a in algorithms:
        anames.append(a.split(".")[0])

    return anames

def make_initializer(anames):
    with open("utils/autils.py", "w") as of:
        of.write("import sys\n")
        of.write("sys.path.append(\"..\")\n")
        
        for f in anames:
            of.write("from algorithms.{} import {}\n".format(f, camel_code(f)))

        of.write("\n")
        of.write("def init_algorithms(model_manager):\n")

        for f in anames:
            of.write("    model_manager.add_algorithm({}(\"{}\"))\n".format(camel_code(f), f))

def command_line_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-a", "--algorithms", help="Detection algorithm directory", type=str, default="algorithms")
    parser.add_argument("-l", "--log", help="Log level (DEBUG/INFO/WARNING/ERROR/CRITICAL)", default="INFO", type=str)
    args = parser.parse_args()
    return args

def main():
    args = command_line_args()

    if not os.path.exists(args.algorithms):
        print ("Invalid algorithm directory. Please insert the correct algorithm directory")
        sys.exit(1)

    logging.basicConfig(level=args.log)
    anames = prepare_algorithms(args.algorithms)
    make_initializer(anames)

if __name__ == "__main__":
    main()
