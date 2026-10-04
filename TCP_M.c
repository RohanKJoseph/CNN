#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    int N, matrix[10][10];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Enter order of matrix (N): ");
    scanf("%d", &N);

    srand(time(0));

    printf("\nGenerated Matrix:\n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 51 ;  
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Send N
    send(sock, &N, sizeof(N), 0);

    // Send matrix
    send(sock, matrix, sizeof(matrix), 0);

    char result[50];
    recv(sock, result, sizeof(result), 0);

    printf("\nMatrix Type: %s\n", result);

    close(sock);
    return 0;
}


//Server Program (C)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int N, matrix[10][10];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Server waiting...\n");

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // Receive N
    recv(new_socket, &N, sizeof(N), 0);

    // Receive matrix
    recv(new_socket, matrix, sizeof(matrix), 0);

    int upper = 1, lower = 1, diagonal = 1;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(i > j && matrix[i][j] != 0)
                upper = 0;

            if(i < j && matrix[i][j] != 0)
                lower = 0;

            if(i != j && matrix[i][j] != 0)
                diagonal = 0;
        }
    }

    char result[50];

    if(diagonal)
        strcpy(result, "Diagonal Matrix");
    else if(upper)
        strcpy(result, "Upper Triangular Matrix");
    else if(lower)
        strcpy(result, "Lower Triangular Matrix");
    else
        strcpy(result, "Not a special matrix");

    send(new_socket, result, strlen(result)+1, 0);

    close(new_socket);
    close(server_fd);

    return 0;
}

//gcc server.c -o server
//gcc client.c -o client
