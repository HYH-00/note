#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;
int main() {
    // 
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    bind(serv_sock, (sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(serv_sock, 20);

    sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (sockaddr*)&clnt_addr, &clnt_addr_size);

    char str[] = "hello world";
    write(clnt_sock, str, sizeof(str));

    char buffer[1024] = {0};
    int n = read(clnt_sock, buffer, sizeof(buffer));

}