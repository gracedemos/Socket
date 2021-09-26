import socket
import threading

PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)

def handle_client(conn, addr):
	while True:
		msg = conn.recv(2048).decode()
		print(msg)

def start():
	server.listen()
	print("[SERVER] is listening on " + SERVER + ":" + str(PORT))
	while True:
		conn, addr = server.accept()
		thread = threading.Thread(target = handle_client, args = (conn, addr))
		thread.start()
		print("[SERVER] " + addr[0] + " connected")
		conn.send(b"Yay!!")

start()