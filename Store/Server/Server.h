#pragma once

#include <QtWidgets/QDialog>
#include "ui_Server.h"
#include <QTcpServer>
#include<qtextcodec.h>
#include<qsqldatabase.h>
#include <QSqlQuery>
#include<QSqlDriver>
#include<QSqlRecord>
#include<QSqlField>
#include<string>
using namespace std;
class Server : public QDialog
{
	Q_OBJECT

public:
	Server(QWidget *parent = Q_NULLPTR);

private:
	Ui::ServerClass ui;
	QTcpServer *tcpserver;//服务器
	QTcpSocket *clientConnection;//套接字
	QList<QTcpSocket*> tcpClient;//套接字容器
	//quint16 blocksize;//存放大小数据
	QString readMessage;//从客户端读取的数据
	QSqlDatabase db;//数据库
	QSqlQuery sq;
private slots:
	void SignIn();
	void rev();
	void disconnectedSlot();

};
