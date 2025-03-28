#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<arpa/inet.h>


#define PORT 8080   //Порт
#define MAX_CLIENTS 10   //Максимальна кількість користувачів
#define BUFFER_SIZE 1024   //Буфер

void *handle_client(void *client_socket);

//Main func

int main() {
    int server_socket, client_socket;   // Сокет сервера та сокет клієнта
    struct sockaddr_in server_addr, client_addr;   //Структура для зберігання IP і Порту серверу та інфа про людину яка підключається
    socklen_t client_len = sizeof(client_addr);   //Розмір стркутури
    pthread_t thread_id;  //зміна для потоків,які обробляють користувачів

    //Створення серверного сокета
    server_socket = socket(AF_INET, SOCK_STREAM, 0);  //Створює TCP сокет; AF_INET-IPv4 ;SOCK_STREAM -вказуємо що це TCP(надійний протокол)
    if (server_socket == -1)   
    {
        perror("Socket creation failed");
        return 1;
    }

    //Налаштування IP адресу і порту серевра
    server_addr.sin_family = AF_INET;   //Використовуємо IPv4 хоча можна було 6
    server_addr.sin_addr.s_addr = INADDR_ANY;  //сервер приймає підключення на всіх доступних IP
    server_addr.sin_port = htons(PORT);  //Використовує порт 8080 конвертує значення в мережевий порядок байтів
    
    //Привязка сокета до порта
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {  //blind-привязує серверний сокет до IP і Порту
        perror("Bind failed");   //Якщо bind() повертає -1 виводимо помилку
        close(server_socket);
        return 1;
    }

    //Запуск прослуховування підключень
    if(listen(server_socket, MAX_CLIENTS ==-1)) {  //Проводить сервер у режим очікування до 10 підключень
        perror("Listen failed");
        close(server_socket);
        return 1;
    }

    //Очікування підключень у циклі
    while(1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);  //Приймає підключення клієнта
        if(client_socket == -1) {  //Якщо помилка то сервер продовжує чекати
            perror("Accept failed");
            continue;
        }

        printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));  //Перетворює IP клієнта в рядок і друкує його
        if(pthread_create(& thread_id, NULL, handle_client,(void *)&client_socket)!= 0){  //створює новий потік для клієнта і запукає функцію handle_client()
            perror("Thread creation failed");
            close(client_socket);
        }
    }

    close (server_socket);
    return 0;
}


//Обробка клієнта у потоці
void * handle_client(void * client_socket) {
    int sock =*(int *)client_socket;  //Отримує індитифікатор клієнта сокета щоб приймати дані користувача,надсилати відповідь та закривати зєднання
    char buffer[BUFFER_SIZE];   //Буфер для зберігання повідомлень
    int bytes_received;


    //Отримання і відправка повідомлень
    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);  //Отримання повідомлень
        if (bytes_received <= 0)
        {
            printf("Client disconected \n");
            break;
        }
        printf("CLients: %s \n", buffer);
        send(sock, buffer, bytes_received, 0); //Відправляє те саме повідомлення назад
    }
    
}