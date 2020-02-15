#include "Store.h"
#include "QPushButton.h"
#include "FPage.h"
#include<vector>
#include <QMessageBox>

using namespace std;   
Store::Store(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	
	tcpsocketSign = new QTcpSocket(this);
	setFocus();
	//调试
	/*fp = new FPage();
	fp->server_2 = this;
	fp->show();*/



	initStore();


	

	//信号与槽连接
	//登录
	connect(ui.P_Signin, &QPushButton::clicked,this, &Store::signin);
	//注册
	connect(ui.P_Signup, &QPushButton::clicked, this, &Store::signup);
	//有数据发过来之后 根据信息决定干什么
	connect(tcpsocketSign, &QTcpSocket::readyRead, this, &Store::rev);
	//自动读取错误信息
	connect(tcpsocketSign, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ReadError(QAbstractSocket::SocketError)));
	//关闭和最小化
	connect(ui.P_Min, &QPushButton::clicked, this, &Store::showMinimized);
	connect(ui.P_Close, &QPushButton::clicked, this, &Store::close);




	//调试FPage
	/*this->hide();
	fp = new FPage();
	fp->server_2 = this;


	fp->show();*/
	
}
//初始化函数
void Store::initStore()
{

	//注册的几个控件要隐藏
	ui.LE_PassWord_2->hide();
	ui.L_Pass_2->hide();
	ui.P_Signin->setGeometry(120, 270, 235, 35);
	ui.P_Signup->setText(QString::fromLocal8Bit("注册账号"));


	//阴影边框
	auto shadowEffect = new QGraphicsDropShadowEffect(this);
	shadowEffect->setOffset(0, 0);
	shadowEffect->setColor(Qt::black);
	shadowEffect->setBlurRadius(10);
	this->setGraphicsEffect(shadowEffect);


	//背景widget动态变换
	colorFactor = 0.2;
	isAddFactor = false;
	ColorTimer.setInterval(30);
	connect(&ColorTimer, &QTimer::timeout, this, [=]
	{
		// 这里自己可以自行调整渐变色rgb值已经动态变换的规则;

		if (colorFactor > 0.8)
		{
			isAddFactor = false;
		}
		else if (colorFactor < 0.3)
		{
			isAddFactor = true;
		}
		ui.TopBackWidget->setStyleSheet(QString("QWidget#TopBackWidget{\
					background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,stop:0 #86fde8, stop:%1 #4776E6, stop:1 #8E54E9);\
                    border-top-left-radius:3px;border-top-right-radius:3px;}").arg(colorFactor));

		if (isAddFactor)
		{
			colorFactor += 0.01;
		}
		else
		{
			colorFactor -= 0.006;
		}

	}
	);
	ColorTimer.start();
	//取消标题栏
	//this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowMinimizeButtonHint);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground);


	//暗注释
	ui.LE_UserName->setPlaceholderText(QString::fromLocal8Bit("你的账号"));
	ui.LE_PassWord->setPlaceholderText(QString::fromLocal8Bit("密码"));
	ui.LE_PassWord_2->setPlaceholderText(QString::fromLocal8Bit("再输入一次密码"));




	//图片加载
	ui.P_Min->setIcon(QIcon("StoreUI/minimizeButton.png"));
	ui.P_Min->setIconSize(QSize(13, 13));

	ui.P_Close->setIcon(QIcon("StoreUI/closeButton.png"));
	ui.P_Close->setIconSize(QSize(13, 13));

	ui.UI_Login->setPixmap(QPixmap("StoreUI/Login.png"));

	ui.L_User->setPixmap(QPixmap("StoreUI/username.png"));
	ui.L_Pass->setPixmap(QPixmap("StoreUI/password.png"));
	ui.L_Pass_2->setPixmap(QPixmap("StoreUI/password.png"));



	ui.UI_Login->setScaledContents(true);
	ui.L_User->setScaledContents(true);
	ui.L_Pass->setScaledContents(true);
	ui.L_Pass_2->setScaledContents(true);



	//按钮文字
	ui.P_Signin->setText(QString::fromLocal8Bit("登录"));
}





//槽函数
//键盘事件
void Store::keyPressEvent(QKeyEvent * event)
{
	if (Qt::Key_Return == event->key())
		signin();
			
		
		

			
}



//鼠标事件
void Store::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isPressed = true;
		//取得点击时的桌面坐标
		m_startMovePos = event->globalPos();
	}

	return QWidget::mousePressEvent(event);
}

void Store::mouseMoveEvent(QMouseEvent *event)
{
	if (m_isPressed)
	{
		//不断的循环，move事件相当于不断的点击
		QPoint movePoint = event->globalPos() - m_startMovePos;
		//获取鼠标移动到的坐标
		QPoint widgetPos = this->pos() + movePoint;
		m_startMovePos = event->globalPos();
		this->move(widgetPos.x(), widgetPos.y());
	}
	return QWidget::mouseMoveEvent(event);
}

void Store::mouseReleaseEvent(QMouseEvent *event)
{
	m_isPressed = false;
	return QWidget::mouseReleaseEvent(event);
}






//登录和注册的按钮
void Store::signin()
{
	
	
	if (ui.P_Signin->text() == QString::fromLocal8Bit("登录"))
	{
		tcpsocketSign->abort();//取消已有的连接
		tcpsocketSign->connectToHost("localhost", 6667);//连接服务器
		if (tcpsocketSign->waitForConnected(5000))//我只给服务器五秒时间
		{
			sendSignMessage();
		}
	}
	else
	{
		if (ui.LE_PassWord->text() == ui.LE_PassWord_2->text())
		{
			QString send = 'u' + ui.LE_UserName->text() + "password" + ui.LE_PassWord->text();
			tcpsocketSign->write(send.toLocal8Bit());
		}
	}
	
	
	
}


//注册
void Store::signup()
{
	//如果文本是注册账号，那就是登录页面
	if (ui.P_Signup->text() == QString::fromLocal8Bit("注册账号"))
	{
		tcpsocketSign->abort();//取消已有的连接
		tcpsocketSign->connectToHost("localhost", 6667);//连接服务器
		if (tcpsocketSign->waitForConnected(5000))//我只给服务器五秒时间
		{
			//不用新窗口了 在本窗口换样式就行
			/*sup = new SignUp();
			sup->show();
			sup->server = this;*/
			ui.L_Pass_2->show();
			ui.LE_PassWord_2->show();

			ui.P_Signup->setText(QString::fromLocal8Bit("返回"));
			ui.P_Signin->setGeometry(120, 300, 235, 35);



			ui.P_Signin->setText(QString::fromLocal8Bit("确认注册"));

		}
	}
	//否则就是注册页面 返回登录
	else
	{
		//控件还原
		ui.LE_PassWord_2->hide();
		ui.L_Pass_2->hide();
		ui.P_Signin->setGeometry(120, 270, 235, 35);
		ui.P_Signup->setText(QString::fromLocal8Bit("注册账号"));
		//文本清空
		ui.LE_UserName->clear();
		ui.LE_PassWord->clear();
		ui.LE_PassWord_2->clear();

	}
}

//登录发送套接字
void Store::sendSignMessage()
{
	

	//发送账户密码
	
	QString send = 's' + ui.LE_UserName->text() +"password"+ ui.LE_PassWord->text();
	
	
	tcpsocketSign->write(send.toLocal8Bit());//发送unicode编码
	



}

//读取服务器返回的信息
void Store::rev()
{
	
	revm = tcpsocketSign->readAll();
	
	
	//switch不支持string
	switch (revm.at(0))
	{
	//账号密码正确
	case '0':
		username = ui.LE_UserName->text();
		this->hide();
		fp = new FPage();
		fp->server_2 = this;
		
		
		fp->show();
		
		
		
		break;

	//账号密码错误
	case '1':
		tcpsocketSign->disconnectFromHost();
		QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("账号或密码错误"),
			QMessageBox::Yes, QMessageBox::Yes);
		break;
	//注册成功
	case '2':
		QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("注册成功！"),
			QMessageBox::Yes, QMessageBox::Yes);
		break;
	//注册失败
	case '3':
		QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("注册失败！"),
			QMessageBox::Yes, QMessageBox::Yes);
		break;
	case '4':case '5':case '6':case '7':case '8':case 'p':
		fp->rev_2();
		break;

	}

}
//错误信息
void Store::ReadError(QAbstractSocket::SocketError)
{
	tcpsocketSign->disconnectFromHost();
	QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("failed to connect server because %1").arg(tcpsocketSign->errorString()),
		QMessageBox::Yes, QMessageBox::Yes);
}

Store::~Store()
{
	//delete fp;
	//delete sup;
}
//外部接口
QTcpSocket* Store::getTcp() { return tcpsocketSign; }

QByteArray Store::getMessage()const { return revm; }


