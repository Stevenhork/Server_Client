
#include<iostream>
#include<cstdio>
#include<Winsock2.h>
#include<ctime>
#include<string>
#include <sstream>

using namespace std;
#pragma comment(lib,"ws2_32.lib")
int main() {
    // 加载socket动态链接库(dll)
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
    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);
    bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
    listen(sockSrv, 100);
    SOCKADDR_IN  addrClient;
    int len = sizeof(SOCKADDR);
    while(true) {   // 不断等待客户端请求的到来
        SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);

        char sendBuf[100];
        char timeBuf[100];
        time_t t;
        time(&t);
        tm local = *localtime(&t);
        int year=local.tm_year+1900;
        int mon=local.tm_mon+1;
        int day=local.tm_mday;
        int hour=local.tm_hour;
        int minu=local.tm_min;
        int sec=local.tm_sec;
        stringstream ss;
        ss<<year<<":"<<mon<<":"<<day<<"    "<<hour<<":"<<minu<<":"<<sec<<endl;
        string str=ss.str();
        sprintf(sendBuf, ("你好，我是服务器！\n"+str).c_str());
        send(sockConn, sendBuf, strlen(sendBuf)+1, 0);  // 发送显示欢迎信息
        char recvBuf[100];
        recv(sockConn, recvBuf, 100, 0);
        cout<<(recvBuf);        // 接收第一次信息
        char *clientName="客户端";
        cout<<"我们来聊天吧！"<<endl;
        while(true) {
            char recevbuff[100];
            recv(sockConn,recevbuff,100,0);
            cout<<clientName<<":"<<recevbuff<<endl;

            char sendbuff[100];
            cout<<"写字板：";
            gets(sendbuff);
            send(sockConn,sendbuff,strlen(sendbuff)+1,0);
            cout<<"服务器："<<sendbuff<<endl;
        }
        closesocket(sockConn);
    }
    return 0;

}
