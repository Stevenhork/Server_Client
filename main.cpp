// client.cpp

#include <iostream>
#include <cstdio>
#include <Winsock2.h>

using namespace std;

int main() {
    WORD wVersionRequested;
    WSADATA wsaData;    // 这结构是用于接收Wjndows Socket的结构信息的
    int err;

    wVersionRequested = MAKEWORD( 1, 1 );   // 请求1.1版本的WinSock库

    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ) {
        return -1;          // 返回值为零的时候是表示成功申请WSAStartup
    }

    if ( LOBYTE( wsaData.wVersion ) != 1 || HIBYTE( wsaData.wVersion ) != 1 ) {
        // 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本
        // 否则的话，调用WSACleanup()清除信息，结束函数
        WSACleanup( );
        return -1;
    }
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");      // 本地回路地址是127.0.0.1;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);
    connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
    send(sockClient, "你好，我是客户端！\n", strlen("你好，我是客户端！\n")+1, 0);
    char recvBuf[100];
    recv(sockClient, recvBuf, 100, 0);
    printf("%s\n", recvBuf);
    printf("我们来聊天吧！\n");
    cout<<endl;
    do{
        char talk[100];
        cout<<"写字板：";
        gets(talk);
        send(sockClient, talk, strlen(talk)+1, 0);          // 发送信息
        cout<<"客户端："<<talk<<endl;

        char recvBuf[100];
        recv(sockClient, recvBuf, 100, 0);
        printf("%s%s\n", "服务器：", recvBuf);     // 接收信息
    }while(true);


    closesocket(sockClient);
    WSACleanup();   // 终止对套接字库的使用

    printf("\n");
    system("pause");
    return 0;



}
