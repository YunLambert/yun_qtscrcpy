#include "tcpserver.h"
#include "devicesocket.h"

TcpServer::TcpServer(QObject *parent)
    :QTcpServer(parent)
{

}

void TcpServer::incomingConnection(qintptr handle)
{
    DeviceSocket* socket=new DeviceSocket();
    socket->setSocketDescriptor(handle);
    addPendingConnection(socket);
}
