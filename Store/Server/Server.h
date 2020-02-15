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
	QTcpServer *tcpserver;//������
	QTcpSocket *clientConnection;//�׽���
	QList<QTcpSocket*> tcpClient;//�׽�������
	//quint16 blocksize;//��Ŵ�С����
	QString readMessage;//�ӿͻ��˶�ȡ������
	QSqlDatabase db;//���ݿ�
	QSqlQuery sq;
private slots:
	void SignIn();
	void rev();
	void disconnectedSlot();

};
