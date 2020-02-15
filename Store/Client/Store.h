#pragma once

#include <QtWidgets/QWidget>
#include <QtNetwork>
#include <QTcpSocket>
#include <QMovie>
#include <QKeyEvent>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include "ui_Store.h"
#include "FPage.h"
#include "SignUp.h"
class FPage;
class SignUp;
class Store : public QWidget
{
	Q_OBJECT
	
public:
	Store(QWidget *parent = Q_NULLPTR);
	~Store();
	//外部接口
	QTcpSocket* getTcp();
	QByteArray getMessage()const;
	//记录账号
	QString username;

	
private:
	Ui::StoreClass ui;
	//指针
	FPage *fp;//主页跳转
	QTcpSocket *tcpsocketSign;
	//对象
	
	

	//背景渐变时钟
	QTimer ColorTimer;
	qreal colorFactor;
	bool isAddFactor;





	//函数
	//初始化
	void initStore();
	//回车登录键盘事件
	void keyPressEvent(QKeyEvent * event);
	//鼠标的事件，因为取消了标题栏
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	//窗口拖动
	bool m_isPressed;
	QPoint m_startMovePos;



	QByteArray revm;//接受服务器信息
	


private slots://槽函数
	void signin();//登录
	void signup();//注册
	void sendSignMessage();//发送账户信息

	void rev();//接受服务器端信息
	void ReadError(QAbstractSocket::SocketError);//错误处理




};
