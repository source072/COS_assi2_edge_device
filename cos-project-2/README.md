# project



## Getting started

1. Fork this repository to your profile: Then, the URL of the repo would be `https://github.com/[your ID]/cos-project-2.git`

2. Download the source code by on your laptop and Raspberry Pi
`git clone https://github.com/[your ID]/cos-project-2.git`

3. Check your connectivity between your laptop and your Raspberry Pi

1) from your laptop type the following:
`ping 172.24.1.1`

2) check your IP address of your laptop
`ipconfig /all (Windows) or ifconfig (Linux/Mac)`

2. Open three terminals: Terminal 1 of your laptop, Terminal 2 of your laptop, and Terminal 3 of your Raspberry Pi

1) Terminal 1: AI module 
`cd ~/project/ai-module`
`python3 ai.py --port [port]`
`e.g., python3 ai.py --port 5556`

2) Terminal 2: Server
`cd ~/project/server`
`python3 server.py --algorithm [algorithm] --dimension [dimension] --index [index of power values] --caddr 127.0.0.1 --cport [port number of AI module] --lport [port number for Server] --name [name of the model]`
`e.g., python3 server.py --algorithm lstm --dimension 1 --index 0 --caddr 127.0.0.1 --cport 5556 --lport 5555 --name lstm`

3) Terminal 3: Edge device (Raspberry Pi)
`cd ~/project/edge`
`make`
`./edge --addr [IP address of your laptop] --port [port number of Server]`
`e.g., ./edge --addr 172.24.1.2 --port 5555`
