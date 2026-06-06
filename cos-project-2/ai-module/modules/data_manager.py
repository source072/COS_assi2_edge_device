import argparse
import logging

class DataManager:
    def __init__(self):
        logging.info("Initializing the data manager")
        self.data = []

    def add_data(self, value):
        self.data.append(value)

    def get_num_of_training_data(self):
        return len(self.data)

    def get_data(self):
        return self.data

    def pop_data(self):
        return self.data.pop(0)

def command_line_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-l", "--log", metavar="<log level (DEBUG/INFO/WARNING/ERROR/CRITICAL)>", help="Log level (DEBUG/INFO/WARNING/ERROR/CRITICAL)", default="INFO", type=str)
    args = parser.parse_args()
    return args

def main():
    args = command_line_args()
    logging.basicConfig(level=args.log)

    dm = DataManager()

if __name__ == "__main__":
    main()
