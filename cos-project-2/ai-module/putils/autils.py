import sys
sys.path.append("..")
from algorithms.lstm import Lstm

def init_algorithms(model_manager):
    model_manager.add_algorithm(Lstm("lstm"))
