#include <stdio.h>
#include <winsock2.h>
#include <string.h>

using namespace std;

//Servidor
int main()
{
    WSADATA wsData;
    SOCKET  server;
    SOCKET  client;
    sockaddr_in endpoint;

    char msg[100];
    char message[100];
    char exitMessage[100] = "salir";

    ///Iniciar winsock version 2.2
    int error = WSAStartup(MAKEWORD(2, 2), &wsData);

    if(error != 0) // checar errores
    {
        printf("Winsock error %d ocurrido\n", WSAGetLastError());
        WSACleanup();
        Sleep(4000);
        return EXIT_FAILURE;
    }
    else
        puts("SISTEMA DE SERVIDOR");

    ///AF_INET = usar IP V4
    ///SOCK_STREAM mejora TCP,, puede usarse SOCK_DGRAM para mejorar UPD
    ///IPPROTO_TCP , IPPROTO_UDP
    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    endpoint.sin_addr.s_addr = htonl(INADDR_ANY); ///Esperando asignacion de IP
    endpoint.sin_family = AF_INET;
    endpoint.sin_port = htons(6590); ///Usando puerto 6590

    if(bind(server, (struct sockaddr*)&endpoint, sizeof(endpoint)) != 0)
    {
        printf("Winsock error %d occurrio en bind!", WSAGetLastError());
        Sleep(4000);
        return EXIT_FAILURE;
    }

    listen(server, 1); ///Activar listening

    puts("Esperamos cliente");
    client = accept(server, NULL, NULL); ///Esperamos conexion de cliente

    while(strncmp(msg, "salir", 5) != 0 || strncmp(message, "salir", 5) != 0)
    {
        ///ahora esperamos mensaje del cliente
        memset(msg, 0, sizeof(msg)); //limpiamos buffer
        if(recv(client, msg, sizeof(msg), 0) != sizeof(msg))
        {
            puts("Nada recibido");
            closesocket(client);
            closesocket(server);
            WSACleanup();
            Sleep(4000);
            return EXIT_FAILURE;
        }
        else
        {
            printf("Cliente: %s", msg);
        }

        if(strncmp(msg, "salir", 5) == 0) break;

        ///ahora nosotros contestamos
        printf("Yo: ");
        fgets(message, 100, stdin);

        if(send(client, message, sizeof(message), 0) != sizeof(message))
        {
            puts("Conexion perdida");
            closesocket(client);
            WSACleanup();
            Sleep(4000);
            return EXIT_FAILURE;
        }
    }

    ///Cerramos conexiones
    closesocket(server);
    closesocket(client);
    WSACleanup();
    system("pause");
    return 0;
}
