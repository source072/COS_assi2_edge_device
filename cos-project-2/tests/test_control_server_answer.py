import requests
import random
import json

def main():
    lst = []
    base = 5
    for _ in range(1000):
        noise = random.randint(-3, 3)
        num = base + noise
        lst.append(num)
        base += 5

    training = lst[:800]
    testing = lst[800:]

    # By using the requests module, please write the code following the instructions below:
    # 1) Initialize a model "my_model" with the "lstm" algorithm, the dimension 1, and the index 0
    print ("1) Initialize a model 'my_mode' with the 'lstm' algorithm, the dimension 1, and the index 0")
    data = {}
    data["algorithm"] = "lstm"
    data["dimension"] = 1
    data["index"] = 0
    js = json.dumps(data)
    response = requests.post("http://127.0.0.1:5556/my_model", json=js)
    print ("Response from a server: {}".format(response.json()))

    # 2) Check if the model you generated is listed in the available models (print it!)
    print ("\n2) Check if the model you generated is listed in the available models")
    response = requests.get("http://127.0.0.1:5556/")
    js = response.json()
    print ("Response from a server: {}".format(js))
    print ("Check if my_model is generated: {}".format("my_model" in js["models"]["value"]))

    # 3) Get the information about the model you generated (print it!)
    print ("\n3) Get the information about the model you generated")
    response = requests.get("http://127.0.0.1:5556/my_model")
    js = response.json()
    print ("Response from a server: {}".format(js))

    # 4) Add all the training instance to the AI module
    print ("\n4) Add all the training instance to the AI module")
    for value in training:
        data = {}
        data["value"] = [value]
        js = json.dumps(data)
        response = requests.put("http://127.0.0.1:5556/my_model/training", json=js)

    # 5) Generate the model based on the training dataset
    print ("\n5) Generate the model based on the training dataset")
    response = requests.post("http://127.0.0.1:5556/my_model/training")
    print ("Response from a server: {}".format(response.json()))

    # 6) Add all the testing instance to the AI module
    print ("\n6) Add all the testing instance to the AI module")
    for value in testing:
        data = {}
        data["value"] = [value]
        js = json.dumps(data)
        response = requests.put("http://127.0.0.1:5556/my_model/testing", json=js)

    # 7) Get the prediction result from the AI module
    print ("\n7) Get the prediction result from the AI module")
    response = requests.get("http://127.0.0.1:5556/my_model/result")
    print ("Response from a server: {}".format(response.json()))

if __name__ == "__main__":
    main()
