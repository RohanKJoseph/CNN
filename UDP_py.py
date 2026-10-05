import socket

# 1. Create UDP socket
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 2. Bind to IP and Port
server.bind(('127.0.0.1', 6000))
print("UDP Server waiting for datagrams...")

# 3. Receive message and sender's address
msg, client_addr = server.recvfrom(1024)
print(f"Received from {client_addr}: {msg.decode()}")

# 4. Send reply directly to client's address
server.sendto("Hello from UDP Server!".encode(), client_addr)

# 5. Close socket
server.close()



import socket

# 1. Create UDP socket
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('127.0.0.1', 6000)

# 2. Send message directly to server address
client.sendto("Hello from UDP Client!".encode(), server_addr)

# 3. Receive reply from server
reply, _ = client.recvfrom(1024)
print(f"Server replied: {reply.decode()}")

# 4. Close socket
client.close()
