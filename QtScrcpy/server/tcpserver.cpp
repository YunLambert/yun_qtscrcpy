#include "tcpserver.h"
#include "devicesocket.h"
TcpServer::TcpServer(QObject *parent)
    : QTcpServer(parent)
{

}

//QTcpserver通过nextPendingConnection获得的就为DeviceSocket* 而不是 QTcpServer*类型的了
void TcpServer::incomingConnection(qintptr handle)
{
    DeviceSocket* socket = new DeviceSocket();
    socket->setSocketDescriptor(handle);
    addPendingConnection(socket);
}
