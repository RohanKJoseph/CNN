import socket

# 1. Create socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 2. Bind to IP and Port
server.bind(('127.0.0.1', 5000))

# 3. Listen for connections (backlog queue size = 1)
server.listen(1)
print("TCP Server waiting for client...")

# 4. Accept connection (blocks until client connects)
conn, addr = server.accept()
print(f"Connected to: {addr}")

# 5. Receive and Send data
msg = conn.recv(1024).decode()
print(f"Client says: {msg}")

conn.sendall("Hello from TCP Server!".encode())

# 6. Close sockets
conn.close()
server.close()


import socket

# 1. Create socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 2. Connect to the server
client.connect(('127.0.0.1', 5000))

# 3. Send and Receive data
client.sendall("Hello from TCP Client!".encode())

reply = client.recv(1024).decode()
print(f"Server replied: {reply}")

# 4. Close socket
client.close()
