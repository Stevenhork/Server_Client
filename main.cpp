// client.cpp

#include <iostream>
#include <cstdio>
#include <Winsock2.h>

using namespace std;

int main() {
    WORD wVersionRequested;
    WSADATA wsaData;    // ��ṹ�����ڽ���Wjndows Socket�Ľṹ��Ϣ��
    int err;

    wVersionRequested = MAKEWORD( 1, 1 );   // ����1.1�汾��WinSock��

    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ) {
        return -1;          // ����ֵΪ���ʱ���Ǳ�ʾ�ɹ�����WSAStartup
    }

    if ( LOBYTE( wsaData.wVersion ) != 1 || HIBYTE( wsaData.wVersion ) != 1 ) {
        // ���������ֽ��ǲ���1�����ֽ��ǲ���1��ȷ���Ƿ������������1.1�汾
        // ����Ļ�������WSACleanup()�����Ϣ����������
        WSACleanup( );
        return -1;
    }
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");      // ���ػ�·��ַ��127.0.0.1;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);
    connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
    send(sockClient, "��ã����ǿͻ��ˣ�\n", strlen("��ã����ǿͻ��ˣ�\n")+1, 0);
    char recvBuf[100];
    recv(sockClient, recvBuf, 100, 0);
    printf("%s\n", recvBuf);
    printf("����������ɣ�\n");
    cout<<endl;
    do{
        char talk[100];
        cout<<"д�ְ壺";
        gets(talk);
        send(sockClient, talk, strlen(talk)+1, 0);          // ������Ϣ
        cout<<"�ͻ��ˣ�"<<talk<<endl;

        char recvBuf[100];
        recv(sockClient, recvBuf, 100, 0);
        printf("%s%s\n", "��������", recvBuf);     // ������Ϣ
    }while(true);


    closesocket(sockClient);
    WSACleanup();   // ��ֹ���׽��ֿ��ʹ��

    printf("\n");
    system("pause");
    return 0;



}
