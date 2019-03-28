#include <stdio.h>
#include <winsock2.h>
#include <string.h>

using namespace std;

//Cliente
int main()
{
    WSADATA wsData;
    SOCKET client;
    struct sockaddr_in endpoint;

    char ipAddr[15];
    char message[100];
    char msg[100];
    char exitMessage[100] = "salir";
    int port = 6590;    ///puerto que usara el cliente

    int error = WSAStartup(MAKEWORD(2, 2), &wsData);

    memset(ipAddr, 0, sizeof(ipAddr));
    if(error != 0)
    {
        printf("Winsock error %d ocurrido\n", WSAGetLastError());
        WSACleanup();
        Sleep(4000);
        return EXIT_FAILURE;
    }
    else
        puts("SISTEMA DE CLIENTE");

    printf("\nDireccion IP a conectar: ");
    scanf("%s", ipAddr);

    client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    endpoint.sin_addr.s_addr = inet_addr(ipAddr); ///asignacion de cualquier IP
    endpoint.sin_family      = AF_INET;
    endpoint.sin_port        = htons(port);

    ///Conexion al servidor
    if(connect(client, (struct sockaddr*)&endpoint, sizeof(endpoint)) != 0) ///Error
    {
        printf("Error %d ocurrido al conectar servidor\n", WSAGetLastError());
        Sleep(4000);
        return EXIT_FAILURE;
    }

    puts("Cliente ya se conecto; \n");

    while(strncmp(message, "salir", 5) != 0 || strncmp(msg, "salir", 5) != 0)
    {

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

        if(strncmp(message, "salir", 5) == 0) break;

         ///ahora esperamos mensaje del servidor
        memset(msg, 0, sizeof(msg)); //limpiamos buffer
        if(recv(client, msg, sizeof(msg), 0) != sizeof(msg))
        {
            puts("Nada recibido");
            closesocket(client);
            WSACleanup();
            Sleep(4000);
            return EXIT_FAILURE;
        }
        else
        {
            printf("Servidor: %s", msg);
        }

    }

    //pasa por aqui, cerramos limpiamente el cliente
    Sleep(4000);
    closesocket(client);
    WSACleanup();
    system("pause");
    return 0;
}
