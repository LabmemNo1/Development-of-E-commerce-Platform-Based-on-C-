#pragma once
#include <QtNetwork>
#include <QTcpSocket>
#include <QWidget>
#include "ui_SignUp.h"
#include "Store.h"
class Store;
class SignUp : public QWidget
{
	Q_OBJECT

public:
	SignUp(QWidget *parent = Q_NULLPTR);
	~SignUp();
	Store *server;
private:
	Ui::SignUp ui;
	
	
private slots:
	void P_Signup();
	
};
