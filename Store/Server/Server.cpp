#include "Server.h"
#include<QtNetwork>
#include<QDataStream>
#include<qtextcodec.h>
#include<qsqldatabase.h>
#include <QSqlQuery>
Server::Server(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//连接数据库
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setPort(3306);
	
	db.setUserName("root");
	db.setPassword("mao1090879073");
	db.setDatabaseName("store");
	
	if (db.open())
		ui.succ->setText(QString::fromLocal8Bit("QtMysql驱动加载成功"));
	sq=QSqlQuery(db);
	//创建TCP对象
	tcpserver = new QTcpServer(this);
	tcpserver->listen(QHostAddress::LocalHost, 6667);//监听
	
	
	connect(tcpserver, &QTcpServer::newConnection, this, &Server::SignIn);//新的连接信号

	
	
}
void Server::SignIn()
{
	clientConnection = tcpserver->nextPendingConnection();//获取连接套接字
	tcpClient.append(clientConnection);
	connect(clientConnection, &QTcpSocket::readyRead, this, &Server::rev);//当有新数据来到
	connect(clientConnection, &QTcpSocket::disconnected, this, &Server::disconnectedSlot);
	


	

	

	
	


}
void Server::rev()
{
	for (int i = 0; i < tcpClient.length(); i++)//因为不知道是哪个套接字收到消息
	{	//接收
		QByteArray block;
		//读取套接字信息
		block = tcpClient[i]->readAll();
		if (block.isEmpty()) continue;
		//防止中文乱码
		QTextCodec *tc = QTextCodec::codecForName("GBK");
		QString rev = tc->toUnicode(block);
		
		//先实例化string
		QString username;
		QString password;
		QString send;
		QString image;
		QString searchtext;
		switch (block.at(0))
		{
		//登录信息
		case 's':
			
			sq.prepare("select username,password from user where username = :username and password = :password;");
			//从秩为1开始（包括自己），搜索password所在秩序减一即为用户名个数
			username=block.mid(1,block.indexOf("password")-1);
			password=block.mid(block.indexOf("password")+8);
			//绑定上
			sq.bindValue(":username", username);
			sq.bindValue(":password", password);
			sq.exec();
			qDebug() << sq.size() << endl;
			//允许登录，发送用户信息和客户端资源信息
			
			if (sq.next()) 
			{
				send = '0';
				sq.prepare("select path from FPageIMG where name = 'First';");
			
				sq.exec();
				

				//循环遍历每一条记录
				for (int i = 0; i < sq.size(); i++)
				{
					sq.next();
					send += sq.value(0).toString();
				}
				
				

				qDebug() << send << endl;
			}
			else 
			{
				send = "1";
			}
			
			tcpClient[i]->write(send.toLocal8Bit());
			break;
		//注册信息
		case 'u':
			sq.prepare("insert into user VALUES(:username,:password,NULL);");
			username = block.mid(1, block.indexOf("password") - 1);
			password = block.mid(block.indexOf("password") + 8);
			sq.bindValue(":username", username);
			sq.bindValue(":password", password);
			if (sq.exec())
			{
				send = "2";
			}
			else
			{
				send = "3";
			}

			tcpClient[i]->write(send.toLocal8Bit());
			break;
		
		
		
		//数码会场
		case 'd':
			sq.prepare("select name,path,user,description,price from goods where category = 'Digital';");
			sq.exec();
			send = "4";
			send += QString::number(sq.size());
			for (int i = 0; i < sq.size(); i++)
			{
				sq.next();
				send += "name:"+sq.value(0).toString() + "url:"+sq.value(1).toString() + "user:"+sq.value(2).toString()+"description:"+sq.value(3).toString()+"price:"+sq.value(4).toString();
				
			}

			tcpClient[i]->write(send.toLocal8Bit());

			break;


		//食品会场
		case 'f':
			sq.prepare("select name,path,user,description,price from goods where category = 'Food';");
			sq.exec();
			send = "5";
			send += QString::number(sq.size());
			for (int i = 0; i < sq.size(); i++)
			{
				sq.next();
				send += "name:" + sq.value(0).toString() + "url:" + sq.value(1).toString() + "user:" + sq.value(2).toString() + "description:" + sq.value(3).toString() + "price:" + sq.value(4).toString();

			}

			tcpClient[i]->write(send.toLocal8Bit());

			break;
		

		//家居
		case 'h':
			sq.prepare("select name,path,user,description,price from goods where category = 'Home';");
			sq.exec();
			send = "6";
			send += QString::number(sq.size());
			for (int i = 0; i < sq.size(); i++)
			{
				sq.next();
				send += "name:" + sq.value(0).toString() + "url:" + sq.value(1).toString() + "user:" + sq.value(2).toString() + "description:" + sq.value(3).toString() + "price:" + sq.value(4).toString();

			}

			tcpClient[i]->write(send.toLocal8Bit());

			break;
		//厨具
		case 'k':
			sq.prepare("select name,path,user,description,price from goods where category = 'Kitchen';");
			sq.exec();
			send = "7";
			send += QString::number(sq.size());
			for (int i = 0; i < sq.size(); i++)
			{
				sq.next();
				send += "name:" + sq.value(0).toString() + "url:" + sq.value(1).toString() + "user:" + sq.value(2).toString() + "description:" + sq.value(3).toString() + "price:" + sq.value(4).toString();

			}

			tcpClient[i]->write(send.toLocal8Bit());

			break;
		//衣物
		case 'c':
			sq.prepare("select name,path,user,description,price from goods where category = 'Clothes';");
			sq.exec();
			send = "8";
			send += QString::number(sq.size());
			for (int i = 0; i < sq.size(); i++)
			{
				sq.next();
				send += "name:" + sq.value(0).toString() + "url:" + sq.value(1).toString() + "user:" + sq.value(2).toString() + "description:" + sq.value(3).toString() + "price:" + sq.value(4).toString();

			}

			tcpClient[i]->write(send.toLocal8Bit());

			break;
		//搜索
		case 'z':
			searchtext = rev.mid(1);
			qDebug() << searchtext << endl;

			sq.prepare("select name,path,user,description,price from goods where name = :searchtext;");
			sq.bindValue(":searchtext", searchtext);

			sq.exec();
			send = "9";
			send += QString::number(sq.size());
			for (int i = 0; i < sq.size(); i++)
			{
				sq.next();
				send += "name:" + sq.value(0).toString() + "url:" + sq.value(1).toString() + "user:" + sq.value(2).toString() + "description:" + sq.value(3).toString() + "price:" + sq.value(4).toString();

			}
			qDebug() << send << endl;
			tcpClient[i]->write(send.toLocal8Bit());

			break;
		//个人信息
		case 'p':
			username = rev.mid(1);
			sq.prepare("select head,id,money,address,goods,favourite,orders from user where username = :username;");
			sq.bindValue(":username", username);






			sq.exec();
			send = "p";
			for (int i = 0; i < sq.size(); i++)
			{
				sq.next();
				send += "head:" + sq.value(0).toString() + "id:" + sq.value(1).toString() + "money:" + sq.value(2).toString() + "address:"
					+ sq.value(3).toString() + "goods:" + sq.value(4).toString()+"favourite:"+sq.value(5).toString()+"orders:"+ sq.value(6).toString();

			}
			qDebug() << "Person information is"<<send << endl;
			tcpClient[i]->write(send.toLocal8Bit());


			

			break;

		}
		
		



			
		
		
	}

}

void Server::disconnectedSlot()
{
	for (int i = 0; i < tcpClient.length(); i++)
	{
		if (tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
		{
			
			
			tcpClient[i]->destroyed();
			tcpClient.removeAt(i);
		}
	}
}

