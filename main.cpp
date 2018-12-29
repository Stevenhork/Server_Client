
#include<iostream>
#include<cstdio>
#include<Winsock2.h>
#include<ctime>
#include<string>
#include <sstream>

using namespace std;
#pragma comment(lib,"ws2_32.lib")
int main() {
    // ����socket��̬���ӿ�(dll)
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
    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);
    bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
    listen(sockSrv, 100);
    SOCKADDR_IN  addrClient;
    int len = sizeof(SOCKADDR);
    while(true) {   // ���ϵȴ��ͻ�������ĵ���
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
        sprintf(sendBuf, ("��ã����Ƿ�������\n"+str).c_str());
        send(sockConn, sendBuf, strlen(sendBuf)+1, 0);  // ������ʾ��ӭ��Ϣ
        char recvBuf[100];
        recv(sockConn, recvBuf, 100, 0);
        cout<<(recvBuf);        // ���յ�һ����Ϣ
        char *clientName="�ͻ���";
        cout<<"����������ɣ�"<<endl;
        while(true) {
            char recevbuff[100];
            recv(sockConn,recevbuff,100,0);
            cout<<clientName<<":"<<recevbuff<<endl;

            char sendbuff[100];
            cout<<"д�ְ壺";
            gets(sendbuff);
            send(sockConn,sendbuff,strlen(sendbuff)+1,0);
            cout<<"��������"<<sendbuff<<endl;
        }
        closesocket(sockConn);
    }
    return 0;

}
