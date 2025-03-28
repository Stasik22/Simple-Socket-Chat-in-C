#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080
#define SEVRER_IP "127.0.0.1"
#define BUFFER_SIZE 1024


void *handle_client(void *client_socket);

int main() {
    int socket_fd;  //Сокет клієнта
    struct sockaddr_in server_addr; //Інфа про сервер
    char buffer [BUFFER_SIZE];   //Буфер
    pthread_t recv_thread;  //Потік для отримання повідомлення


    //Створення серверного сокета
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);  //Створює TCP сокет; AF_INET-IPv4 ;SOCK_STREAM -вказуємо що це TCP(надійний протокол)
    if (socket_fd == -1) {
        perror("Socket creation failed");
        return 1;
    }
    
    //Налаштування підключення
    server_addr.sin_family = AF_INET;  //Використовємо IPv4
    server_addr.sin_port = htons(PORT); //Порт який перетворюється в байти
    server_addr.sin_addr.s_addr = inet_addr(SEVRER_IP);  //Підключення до локального сервера

    //Підключення до серверу
    if (connect(socket_fd,(struct sockaddr*)& server_addr, sizeof(server_addr))== -1)  //Підключає клієнт до сервера
    {
        perror("Connection failed");
        close(socket_fd);
        return 1;
    }
    
    //Запуск потоку для отримання повідомлень
    if (pthread_create(&recv_thread, NULL, receive_message,(void *)&socket_fd) != 0)
    {
        perror("Thread creation failed");
        close(socket_fd);
        return 1;
    }

    //Введення і надсилання повідомлень
    while (1)
    {
        printf("You :");
        fgets(buffer, BUFFER_SIZE, stdin);  //Користувач отримує повідомлення
        send(socket_fd, buffer, strlen(buffer), 0);  //Користувач надсилає повідомлення
    }
        
}

//Отримання повідомлень
void * receive_message(void* socket_fd) {
    int sock = * (int *) socket_fd;
    char buffer[BUFFER_SIZE];
    int bytes_received;

    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0)
        {
            printf("Server disconnect \n");
            close(sock);
            exit (1);
        }

        printf("\n Server : %s", buffer);
        printf("You :");
        fflush(stdout);
    }
    

}