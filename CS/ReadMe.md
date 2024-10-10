Getting Familiar with Socket Programming in C

Server Side Workflow using following functions.(sys/socket.h) Program compilation occurs in Linux env

# Socket() Function : Which is used to craete a socket object with TCP Stream for communication.
# Bind() Function : Which is used to bind the host to particular IP and Port. Before declaring the bind fucntion have to declare a structure.
# Listen() Fucntion : Which is used to listen the incoming connection using IP/Port.
# Accept() Function : Which is used to accept the connection taht meet the requirements.
# Send() and Recv() : Which used to send and receive the data streams between client and the server.

Client Side Workflow using following function. (winsock2.h) Progarm compilation occurs in Windows Env.
(If you need to compile the client side code in linux env `sys/socket.h` header is capable.)

Difference (sys/socket.h / winsock2.h) => The workflow is same in both libaries but the syntax is different in both libararies.

# Socket() Function : Create a socket for communication.
# Connect() Function : Used to connect with the target.
# Send() and Recv() : Request And Response between Client and server.

