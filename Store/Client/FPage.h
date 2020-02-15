#pragma once

#include <QWidget>
#include <QtNetwork>
#include <QTcpSocket>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include<QTimer>
#include <QGraphicsDropShadowEffect>
#include <QTextCodec>
#include <QEventLoop>
#include<string>
#include "ui_FPage.h"
#include "Store.h"
using namespace std;
class Store;
class FPage : public QWidget
{
	Q_OBJECT

public:
	FPage(QWidget *parent = Q_NULLPTR);
	~FPage();
	Store *server_2;
	void rev_2();//接受服务器信息
private:
	Ui::FPage ui;



	
	//网络URL下载
	QNetworkAccessManager *manager;//首页图片下载
	//商品图片下载
	QNetworkAccessManager *manager_digital;
	QNetworkAccessManager *manager_food;
	QNetworkAccessManager *manager_home;
	QNetworkAccessManager *manager_kitchen;
	QNetworkAccessManager *manager_clothes; 
	
	QPixmap store;//首页图片
	//url路径
	QString url1;
	QString url2;
	QString url3;
	QString url4;
	QString url5;
	//定时器
	//晚点构造store指针
	QTimer *fptimer;

	//缓存数据流
	QByteArray bytes;
	//容器
	QList<QPushButton*> FPagePB_1;;//首页按钮容器
	QList<QPushButton*> FPagePB_2;//进入会场按钮容器
	QList<QString> name_rev, url_rev, user_rev, description_rev,price_rev;//商品页面信息容器

	
	//商品页面控件容器
	QList<QLabel*> goods_image,goods_price;//存放商品的图像和描述
	QList<QPushButton*> buy;//购买按钮
	QList<QPushButton*> user;//商家按钮






	//鼠标的事件，因为取消了标题栏
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	//窗口拖动
	bool m_isPressed;
	QPoint m_startMovePos;





	//加载个人信息的控件
	void InitPerInfWidget();

	//商品资源加载
	void InitGoods();
	//构造函数
	void initFPage();
	//个人信息
	void InitPerInf(QString);
	//订单
	void InitOrders();
	//根据浏览推荐
	void InitFavGoods();



	
	//一个循环事件
	QEventLoop loop;




	//钱包栏
//构造头像和id
	QLabel *headBack;
	QPushButton *head;
	QLabel *id;



	//钱包widget
	QWidget *PerInfWidget;
	
	QLabel *wallet;
	QFrame *line;
	QLabel *AccBlan;
	QPushButton *number;
	QPushButton *address;


	//根据浏览，猜喜欢
	QLabel* label_favourite;
	QWidget* FavouriteWidget;














private slots:
	//url信息下载完成槽函数
	void slotReplyPixmapLoad(QNetworkReply*);
	void slotReplyPixmapLoad_digital(QNetworkReply*);


	//首页分类图片按键
	void P_C1_clicked();
	//void P_C2_clicked();
	//void P_C3_clicked();
	//void P_C4_clicked();
	//void P_C5_clicked();
	//进入会场按键
	void P_C11_clicked();

	//搜索
	void search_clicked();
	//个人信息请求
	void Send_PerInf();

	
	void revurl();//定时器信号

};
