#include "FPage.h"

FPage::FPage(QWidget *parent)
	: QWidget(parent)
{
	//初始化
	ui.setupUi(this);
	
	initFPage();
	
	//连接信号和槽
	//顶部 个人信息和订单

	connect(ui.P_Inf, &QPushButton::clicked, this, &FPage::Send_PerInf);
	connect(ui.P_Order, &QPushButton::clicked, this, &FPage::InitOrders);



	//搜索按钮
	connect(ui.P_Search, &QPushButton::clicked, this, &FPage::search_clicked);


	//图片按钮
	connect(FPagePB_1.at(0), &QPushButton::clicked, this, &FPage::P_C1_clicked);
	connect(FPagePB_1.at(1), &QPushButton::clicked, this, &FPage::P_C1_clicked);
	connect(FPagePB_1.at(2), &QPushButton::clicked, this, &FPage::P_C1_clicked);
	connect(FPagePB_1.at(3), &QPushButton::clicked, this, &FPage::P_C1_clicked);
	connect(FPagePB_1.at(4), &QPushButton::clicked, this, &FPage::P_C1_clicked);
	//进入会场按钮
	connect(FPagePB_2.at(0), &QPushButton::clicked, this, &FPage::P_C11_clicked);
	connect(FPagePB_2.at(1), &QPushButton::clicked, this, &FPage::P_C11_clicked);
	connect(FPagePB_2.at(2), &QPushButton::clicked, this, &FPage::P_C11_clicked);
	connect(FPagePB_2.at(3), &QPushButton::clicked, this, &FPage::P_C11_clicked);
	connect(FPagePB_2.at(4), &QPushButton::clicked, this, &FPage::P_C11_clicked);
	//网络请求
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoad(QNetworkReply*)));
	
	connect(manager_digital, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoad_digital(QNetworkReply*)));







	//定时器 防止构造时的野指针
	connect(fptimer, &QTimer::timeout, this, &FPage::revurl);
	//关闭和最小化
	connect(ui.P_Min, &QPushButton::clicked, this, &FPage::showMinimized);
	connect(ui.P_Close, &QPushButton::clicked, this, &FPage::close);


	fptimer->start(100);
}
void FPage::initFPage()

{
	fptimer = new QTimer(this);
	manager = new QNetworkAccessManager(this);
	manager_digital = new QNetworkAccessManager(this);
	manager_food = new QNetworkAccessManager(this);
	manager_home = new QNetworkAccessManager(this);
	manager_kitchen = new QNetworkAccessManager(this);
	manager_clothes = new QNetworkAccessManager(this);
	//阴影
	auto shadowEffect = new QGraphicsDropShadowEffect(this);
	shadowEffect->setOffset(0, 0);
	shadowEffect->setColor(Qt::black);
	shadowEffect->setBlurRadius(10);
	this->setGraphicsEffect(shadowEffect);
	

	//商品先隐藏
	ui.Goods_Display->hide();
	InitPerInfWidget();



	
	//图片加载
	
	//首页图片
	ui.UI_Image->setPixmap(QPixmap("FPageUI/home.png"));
	ui.UI_Image->setScaledContents(true);
	//logo
	ui.UI_FPage->setPixmap(QPixmap("FPageUI/UI_FPage.png"));
	ui.UI_FPage->setScaledContents(true);
	//按钮
	ui.P_Min->setIcon(QIcon("StoreUI/minimizeButton.png"));
	ui.P_Min->setIconSize(QSize(13, 13));
	ui.P_Close->setIcon(QIcon("StoreUI/closeButton.png"));
	ui.P_Close->setIconSize(QSize(13, 13));
	ui.P_Search->setIcon(QIcon("FPageUI/search.png"));
	ui.P_Search->setIconSize(QSize(30, 30));
	
	
	//首页的按键list初始化
	FPagePB_1 << ui.P_C1 << ui.P_C2 << ui.P_C3 << ui.P_C4 << ui.P_C5;
	FPagePB_2 << ui.P_C11 << ui.P_C22 << ui.P_C33 << ui.P_C44 << ui.P_C55;





	//取消标题栏
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground);

	



}
//点击事件槽函数
//这里的思路是从url最后一个"/"后检索到png的名字，然后加载到pixmap，继而加载到label中

void FPage::P_C1_clicked()
{

	//manager->get(QNetworkRequest(QUrl(url1)));
	
	int start = url1.lastIndexOf("/") + 1;
	QString name_sender = sender()->objectName();
	//根据发送者不同
	//数码
	if (name_sender.compare(QStringLiteral("P_C1")) == 0)
	{
		QString loadpath = url1.mid(start);
		store.load(QString("FPageUI/%1").arg(loadpath));
	}
	if (name_sender.compare(QStringLiteral("P_C2")) == 0)
	{
		QString loadpath = url2.mid(start);
		store.load(QString("FPageUI/%1").arg(loadpath));
		
	}
	if (name_sender.compare(QStringLiteral("P_C3")) == 0)
	{
		QString loadpath = url3.mid(start);
		store.load(QString("FPageUI/%1").arg(loadpath));
	}
	if (name_sender.compare(QStringLiteral("P_C4")) == 0)
	{
		QString loadpath = url4.mid(start);
		store.load(QString("FPageUI/%1").arg(loadpath));
	}
	if (name_sender.compare(QStringLiteral("P_C5")) == 0)
	{
		QString loadpath = url5.mid(start);
		store.load(QString("FPageUI/%1").arg(loadpath));
	}



	ui.UI_Image->setPixmap(store);
	ui.UI_Image->setScaledContents(true);

	ui.UI_Image->show();
	ui.Goods_Display->hide();
	
}

//进入会场槽函数
void FPage::P_C11_clicked()
{
	//把个人信息的东西隐藏掉
	head->hide();
	headBack->hide();
	id->hide();
	PerInfWidget->hide();
	label_favourite->hide();
	FavouriteWidget->hide();

	
	ui.UI_Image->hide();
	ui.Goods_Display->show();
	
	QString name_sender = sender()->objectName();
	//根据发送者不同
	//数码
	if(name_sender.compare(QStringLiteral("P_C11"))==0)
	{
		server_2->getTcp()->write("d");
	}
	//食品
	if (name_sender.compare(QStringLiteral("P_C22")) == 0)
	{
		server_2->getTcp()->write("f");
	}
	//家居
	if (name_sender.compare(QStringLiteral("P_C33")) == 0)
	{
		server_2->getTcp()->write("h");
	}
	//厨具
	if (name_sender.compare(QStringLiteral("P_C44")) == 0)
	{
		server_2->getTcp()->write("k");
	}
	//衣物
	if (name_sender.compare(QStringLiteral("P_C55")) == 0)
	{
		server_2->getTcp()->write("c");
	}
	

}

//搜索
void FPage::search_clicked()
{//把个人信息的东西隐藏掉
	head->hide();
	headBack->hide();
	id->hide();
	PerInfWidget->hide();
	label_favourite->hide();
	FavouriteWidget->hide();
	ui.UI_Image->hide();
	ui.Goods_Display->show();

	QByteArray searchText = 'z' + ui.LE_Search->text().toLocal8Bit();
	qDebug() << searchText << endl;
	server_2->getTcp()->write(searchText);
}

//发送个人信息请求
void FPage::Send_PerInf()
{
	qDebug() << server_2->username << endl;
	server_2->getTcp()->write("p"+server_2->username.toLocal8Bit());
}




//定时器
void FPage::revurl()
{
	QString url = server_2->getMessage();
	fptimer->stop();
	
	
	url=url.mid(1);//去掉第一个通信标志
	//五个url的标志
	int f1 = url.indexOf("http", 4);//第一个url结尾的秩，以此类推
	int f2 = url.indexOf("http", f1+4);

	int f3 = url.indexOf("http", f2+4);
	int f4 = url.indexOf("http", f3+4);
	
	
	//五个图片的url
	url1 = url.mid(0, f1);
	url2 = url.mid(f1,f2-f1);
	url3 = url.mid(f2, f3 - f2);
	url4 = url.mid(f3, f4 - f3);
	url5 = url.mid(f4);
	qDebug() << url << endl;
	qDebug() << url1 << endl;
	qDebug() << url2 << endl;
	qDebug() << url3 << endl;
	qDebug() << url4 << endl;
	qDebug() << url5 << endl;
	//下载图片
	manager->get(QNetworkRequest(QUrl(url1)));
	manager->get(QNetworkRequest(QUrl(url2)));
	manager->get(QNetworkRequest(QUrl(url3)));
	manager->get(QNetworkRequest(QUrl(url4)));
	manager->get(QNetworkRequest(QUrl(url5)));


		
}
//网络请求完成槽函数
void FPage::slotReplyPixmapLoad(QNetworkReply* reply)
{
	if (reply->error() == QNetworkReply::NoError)
	{
		
		qDebug() << "reply111111 :" << reply << endl;
		//读取数据流
		bytes = reply->readAll();
		
		//从url中找到关键字，来确定下载图片的名字
		QString downloadname = reply->url().toString();
		int start = downloadname.lastIndexOf("/")+1;
		downloadname = downloadname.mid(start);
		qDebug() << downloadname << endl;
		QFile file(QString("FPageUI/%1").arg(downloadname));
		if (file.open(QIODevice::WriteOnly))
			file.write(bytes);
		
		file.close();
		reply->deleteLater();
		
	}
	else
	{
		
		qDebug() <<  reply->error() << endl;
	}
	
}
void FPage::slotReplyPixmapLoad_digital(QNetworkReply* reply)
{
	if (reply->error() == QNetworkReply::NoError)
	{

		qDebug() << "reply111111 :" << reply << endl;
		//读取数据流
		bytes = reply->readAll();

		//从url中找到关键字，来确定下载图片的名字
		QString downloadname = reply->url().toString();
		int start = downloadname.lastIndexOf("/") + 1;
		downloadname = downloadname.mid(start);
		qDebug() << downloadname << endl;
		QFile file(QString("FPageUI/%1").arg(downloadname));
		if (file.open(QIODevice::WriteOnly))
			file.write(bytes);

		file.close();





		reply->deleteLater();


	}
}



//鼠标事件
void FPage::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isPressed = true;
		//取得点击时的桌面坐标
		m_startMovePos = event->globalPos();
	}

	return QWidget::mousePressEvent(event);
}

void FPage::mouseMoveEvent(QMouseEvent *event)
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

void FPage::mouseReleaseEvent(QMouseEvent *event)
{
	m_isPressed = false;
	return QWidget::mouseReleaseEvent(event);
}



//接受服务器信息
void FPage::rev_2()
{
	QByteArray FPmessage = server_2->getMessage();
	//防止中文乱码
	QTextCodec *tc = QTextCodec::codecForName("GBK");
	QString message = tc->toUnicode(FPmessage);
	//商品数量信息
	int size_d;

	//个人信息
	QString head, id, money, address, goods, favourite, orders;
	switch ((server_2->getMessage()).at(0))
	{
	//接收到服务器端数码会场信息
	case '4':case '5':case'6':case '7':case '8': case'9':
		//先清空容器
		name_rev.clear();
		url_rev.clear();
		user_rev.clear();
		description_rev.clear();
		price_rev.clear();
		//有多少件商品
		size_d = QString(message.at(1)).toInt();
		qDebug()<<"size is"<<size_d<<endl;
		//去掉标识符
		message = message.mid(2);

		for (int i = 0; i < size_d; i++)
		{
			//找到各种信息的位置
			int name_address = message.indexOf("name:") + 5;
			int url_address= message.indexOf("url:") + 4;
			int user_address = message.indexOf("user:") + 5;
			int description_address = message.indexOf("description:") + 12;
			int price_address = message.indexOf("price:") + 6;
			int name_next = message.indexOf("name:", price_address);
			//截取信息
			QString name_s = message.mid(name_address, url_address - name_address-4);
			QString url_s = message.mid(url_address, user_address - url_address - 5);
			QString user_s = message.mid(user_address, description_address - user_address - 12);
			QString description_s = message.mid(description_address, price_address - description_address-6);
			QString price_s= message.mid(price_address, name_next - price_address);
			//放入容器中
			name_rev.append(name_s);
			url_rev.append(url_s);
			user_rev.append(user_s);
			description_rev.append(description_s);
			price_rev.append(price_s);
			qDebug() << message << endl;
			qDebug() << name_s << endl;
			qDebug() << url_s << endl;
			qDebug() << user_s << endl;
			qDebug() << description_s << endl;
			qDebug() << price_s << endl;


			//截取掉用过的那一段
			message=message.mid(name_next);

		}
	InitGoods();
	break;
	//接收到个人信息
	case 'p':
		//去掉标识符
		ui.UI_Image->hide();
		ui.Goods_Display->show();
		message = message.mid(1);
		
		




		InitPerInf(message);
		break;

	}
}

//资源加载
void FPage::InitGoods()
{
	if (name_rev.size() > goods_image.size())//如果需要加载的商品比list中的多
	{
		qDebug() << "SIZE BIG" << name_rev.size() - goods_image.size() << endl;
		//创建新的商品，也就是label和pushbutton
		int x = 20,ima_y=20,pri_y = 220,buy_y = 250,user_y=300;
	
		while (goods_image.size() != name_rev.size())
		{
			if (x > 930)
			{
				x = 20;
				ima_y += 340;
				pri_y += 340;
				buy_y += 340;
				user_y += 340;
			}
			//防止空间不够，增大容器的最小高度，出现滑轮
			if (user_y + 20 > ui.Goods_area->minimumHeight())
			{
				ui.Goods_area->setMinimumHeight(ui.Goods_area->minimumHeight() + 340);
			}
			QLabel* l_digital_ima = new QLabel(ui.Goods_area);
			QLabel* l_digital_pri = new QLabel(ui.Goods_area);
			QPushButton* p_digital_buy = new QPushButton(ui.Goods_area);
			QPushButton* p_digital_user = new QPushButton(ui.Goods_area);
			l_digital_ima->setGeometry(QRect(x, ima_y, 200, 200));
			l_digital_pri->setGeometry(QRect(x, pri_y, 200, 30));
			p_digital_buy->setGeometry(QRect(x, buy_y, 200, 50));
			p_digital_user->setGeometry(QRect(x, user_y, 200, 20));

			x += 220;
			qDebug() << "loop" << endl;
			goods_image.append(l_digital_ima); 
			goods_price.append(l_digital_pri);
			buy.append(p_digital_buy);
			user.append(p_digital_user);
		}

		//不知道和下面哪里不一样，但是只循环了一次
		//for (int j = 0; j < (name_digital.size() - goods_image.size()); j++)
		//{
		//	//控件的坐标
		//	if (x == 930)
		//	{
		//		x = 0;
		//		ima_y += 320;
		//		des_y += 320;
		//		buy_y += 320;
		//	}
		//	QLabel* l_digital_ima = new QLabel(ui.Goods_area);
		//	QLabel* l_digital_des = new QLabel(ui.Goods_area);
		//	QPushButton* p_digital_buy = new QPushButton(ui.Goods_area);
		//	l_digital_ima->setGeometry(QRect(x, ima_y, 310, 200));
		//	l_digital_des->setGeometry(QRect(x, des_y, 310, 90));
		//	p_digital_buy->setGeometry(QRect(x, buy_y, 310, 90));

		//	x += 310;
		//	qDebug() << "loop" << endl;
		//	goods_image.append(l_digital_ima);
		//	goods_des.append(l_digital_des);
		//	buy.append(p_digital_buy);
		//} 

	

	}
	//再来一个循环显示url，详情和购买页面
	qDebug() << "goods_image size is" << goods_image.size() << endl;
	for (int i = 0; i < name_rev.size(); i++)
	{	//找到图片名
		int start = url_rev.at(i).lastIndexOf("/") + 1;
		QString loadpath = url_rev.at(i).mid(start);
		//缓存图片
		QFileInfo file(QString("FPageUI/%1").arg(loadpath));
		//如果已经缓存过了
		if (file.isFile())
		{	//加载商品图片
			goods_image.at(i)->setPixmap(QString("FPageUI/%1").arg(loadpath));
			goods_image.at(i)->show();
			goods_image.at(i)->setScaledContents(true);
		}
		else//否则先下载下来，再加载
		{
			QNetworkReply *reply = manager_digital->get(QNetworkRequest(QUrl(url_rev.at(i))));
			connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
			loop.exec();
			goods_image.at(i)->setPixmap(QString("FPageUI/%1").arg(loadpath));
			goods_image.at(i)->show();
			goods_image.at(i)->setScaledContents(true);

		}
		
		//显示价格
		goods_price.at(i)->setText(QString::fromLocal8Bit("<html><head / ><body><p><span style = \
			' font-size:16pt; font-weight:600;color:red;'\
			>%1< / span>< / p>< / body>< / html>").arg(price_rev.at(i)));

		qDebug() << "price is" << price_rev.at(i) << endl;
		goods_price.at(i)->show();
		//购买按钮 点击商品的描述
		QString description_goods = description_rev.at(i);
		if (description_goods.size() > 16)
		{
			
			description_goods.insert(16,"\n");
		}
		


		
		buy.at(i)->setText(description_goods);
		buy.at(i)->setStyleSheet("QPushButton{\
									font-size:15px;\
									text-align:left;\
									color:rgb(65, 65, 65);\
									border:none;\
											}\
								QPushButton:hover{\
									text-decoration:underline;\
									color:red;\
									}");
		
		buy.at(i)->setCursor(Qt::PointingHandCursor);
		buy.at(i)->show();
		//店家
		user.at(i)->setText(user_rev.at(i));
		user.at(i)->setStyleSheet("QPushButton{\
									font-size:12px;\
									text-align:left;\
									color:gray;\
									border:none;\
											}\
									QPushButton:hover{\
									}");
		user.at(i)->setCursor(Qt::PointingHandCursor);
		user.at(i)->show();


		//连接购买和店家，转到店家和购买页面
		//还要根据点击的记录向数据库写入
		connect();
		
	}

}
//个人信息页面
void FPage::InitPerInf(QString message)
{
	//处理信息
	//每个信息段所在的地址
	int head_address, id_address, money_address, address_address, goods_address, favourite_address, orders_address;
	QString head_text, id_text, money_text, address_text, goods_text, favourite_text, orders_text;

	head_address = message.indexOf("head:") + 5;
	id_address = message.indexOf("id:") + 3;
	money_address = message.indexOf("money:") + 6;
	address_address = message.indexOf("address:") + 8;
	goods_address = message.indexOf("goods:") + 6;
	favourite_address = message.indexOf("favourite:") + 10;
	orders_address = message.indexOf("orders:") + 7;
	//个人信息串
	head_text = message.mid(head_address, id_address - head_address - 3);
	id_text = message.mid(id_address, money_address - id_address - 6);
	money_text = message.mid(money_address, address_address - money_address - 8);
	address_text = message.mid(address_address, goods_address - address_address - 6);
	goods_text = message.mid(goods_address, favourite_address - goods_address - 10);
	favourite_text = message.mid(favourite_address, orders_address - favourite_address - 7);
	orders_text = message.mid(orders_address);


	
	//背景填充 240 243 239
	//隐藏掉所有商品信息
	for (int i = 0; i < goods_image.size(); i++)
	{
		goods_image.at(i)->hide();
		goods_price.at(i)->hide();
		buy.at(i)->hide();
		user.at(i)->hide();
	}
//	//钱包栏
//	//构造头像和id
//	QLabel *headBack = new QLabel(ui.Goods_area);
//	QPushButton *head = new QPushButton(ui.Goods_area);
//	QLabel *id = new QLabel(ui.Goods_area);
//	headBack->setGeometry(QRect(10, 10, 200, 200));
//	head->setGeometry(QRect(40, 20, 140, 140));
//	id->setGeometry(QRect(70,170,100,20));
//
//
//	//构造钱包widget
//	QWidget *PerInfWidget = new QWidget(ui.Goods_area);
//	PerInfWidget->setGeometry(QRect(210, 30, 720, 150));
//	//构造钱包widget中的控件
//	QLabel *wallet = new QLabel(PerInfWidget);
//	QFrame *line = new QFrame(PerInfWidget);
//	QLabel *AccBlan = new QLabel(PerInfWidget);
//	QPushButton *number = new QPushButton(PerInfWidget);
//	QPushButton *address = new QPushButton(PerInfWidget);
//
//
//	//构造根据浏览，猜喜欢
//	QLabel* label_favourite = new QLabel(ui.Goods_area);
//	QWidget* FavouriteWidget = new QWidget(ui.Goods_area);
//
//
//
//	//设置坐标
//	//钱包坐标
//	wallet->setGeometry(QRect(20,10,140,20));
//	line->setGeometry(QRect(0, 30, 720, 20));
//	line->setFrameShape(QFrame::HLine);
//	line->setFrameShadow(QFrame::Sunken);
//	number->setGeometry(QRect(100, 60, 170, 50));
//	AccBlan->setGeometry(QRect(100,120,50,20));
//	address->setGeometry(QRect(300,40,160,90));
//	//猜你喜欢坐标
//	label_favourite->setGeometry(QRect(100, 220, 750, 50));
//	FavouriteWidget->setGeometry(QRect(100, 270, 750, 370));
//
//	//样式表
//	//widget样式表
//	ui.Goods_area->setStyleSheet("background-color: rgb(240,243,239);");
//	
//	//钱包样式表
//	headBack->setStyleSheet("background-color: rgb(226, 35, 26);");
//	head->setStyleSheet("border-radius: 50px;border - width: 0 0 0 0;");
//	id->setStyleSheet("background-color: rgb(226, 35, 26);color: rgb(255, 255, 255);");
//	wallet->setStyleSheet("font-size:18px;background-color: rgb(250, 250, 250);");
//	number->setStyleSheet("border:none;text-align:left;");
//	address->setStyleSheet("border:none;");
//	//猜你喜欢样式表
//	label_favourite->setStyleSheet("background-color: rgb(160, 205, 235);\
//									color: rgb(255, 255, 255);\
//									font - size:18px; ");
//	FavouriteWidget->setStyleSheet("background-color: rgb(245,248,250);");
////设置鼠标样式
//	head->setCursor(Qt::PointingHandCursor);
//	number->setCursor(Qt::PointingHandCursor);
//	address->setCursor(Qt::PointingHandCursor);
	//设置图片和文字
	id->setText(id_text);
	wallet->setText(QString::fromLocal8Bit("我的钱包"));
	AccBlan->setText(QString::fromLocal8Bit("余额"));
	number->setText(QString::fromLocal8Bit("%1").arg(money_text));
	address->setText(address_text);

	label_favourite->setText(QString::fromLocal8Bit("根据浏览，猜我喜欢"));

	






	//show
	PerInfWidget->show();
	label_favourite->show();
	headBack->show();
	head->show();
	id->show();

	id->raise();




	//猜你喜欢

	InitFavGoods();





	//连接信号和槽






	//最后加载头像的图片
	int start = head_text.lastIndexOf("/") + 1;
	QString loadpath = head_text.mid(start);
	
	QFileInfo file(QString("FPageUI/%1").arg(loadpath));
	if (file.isFile())
	{	
		head->setStyleSheet(QString("min-width:140px;\
									min-height:140px;\
									max-width:140px;\
									max-height:140px;\
									border-radius:70px;\
									border:3px solid white;border-image:url(FPageUI/%1);").arg(loadpath));
		head->show();
		
	}//
	else//否则先下载下来，再加载
	{
		QNetworkReply *reply = manager_digital->get(QNetworkRequest(QUrl(head_text)));
		connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();
		head->setStyleSheet(QString("min-width:140px;\
									min-height:140px;\
									max-width:140px;\
									max-height:140px;\
									border-radius:70px;\
									border:3px solid white;border-image:url(FPageUI/%1);").arg(loadpath));
		
		head->show();
	}//border - image:url((FPageUI/%1);").arg(loadpath)





}
//订单界面
void FPage::InitOrders()
{

}

void FPage::InitFavGoods()
{

}
void FPage::InitPerInfWidget()
{
	//钱包栏
//构造头像和id
	headBack = new QLabel(ui.Goods_area);
	head = new QPushButton(ui.Goods_area);
	id = new QLabel(ui.Goods_area);
	headBack->setGeometry(QRect(10, 10, 200, 200));
	head->setGeometry(QRect(40, 20, 140, 140));
	id->setGeometry(QRect(70, 170, 100, 20));


	//构造钱包widget
	PerInfWidget = new QWidget(ui.Goods_area);
	PerInfWidget->setGeometry(QRect(210, 30, 720, 150));
	//构造钱包widget中的控件
	wallet = new QLabel(PerInfWidget);
	line = new QFrame(PerInfWidget);
	AccBlan = new QLabel(PerInfWidget);
	number = new QPushButton(PerInfWidget);
	address = new QPushButton(PerInfWidget);


	//构造根据浏览，猜喜欢
	label_favourite = new QLabel(ui.Goods_area);
	FavouriteWidget = new QWidget(ui.Goods_area);



	//设置坐标
	//钱包坐标
	wallet->setGeometry(QRect(20, 10, 140, 20));
	line->setGeometry(QRect(0, 30, 720, 20));
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	number->setGeometry(QRect(100, 60, 170, 50));
	AccBlan->setGeometry(QRect(100, 120, 50, 20));
	address->setGeometry(QRect(300, 40, 160, 90));
	//猜你喜欢坐标
	label_favourite->setGeometry(QRect(100, 220, 750, 50));
	FavouriteWidget->setGeometry(QRect(100, 270, 750, 370));

	//样式表
	//widget样式表
	ui.Goods_area->setStyleSheet("background-color: rgb(240,243,239);");

	//钱包样式表
	PerInfWidget->setStyleSheet("background-color: rgb(250, 250, 250);");
	headBack->setStyleSheet("background-color: rgb(226, 35, 26);");
	head->setStyleSheet("border-radius: 50px;border - width: 0 0 0 0;");
	id->setStyleSheet("background-color: rgb(226, 35, 26);color: rgb(255, 255, 255);");
	wallet->setStyleSheet("font-size:18px;background-color: rgb(250, 250, 250);");
	number->setStyleSheet("border:none;text-align:left;");
	address->setStyleSheet("border:none;");
	//猜你喜欢样式表
	label_favourite->setStyleSheet("background-color:rgb(160, 205, 235);\
									color:rgb(255, 255, 255);\
									font-size:18px;");
	FavouriteWidget->setStyleSheet("background-color:rgb(245,248,250);");



	//设置鼠标样式
	head->setCursor(Qt::PointingHandCursor);
	number->setCursor(Qt::PointingHandCursor);
	address->setCursor(Qt::PointingHandCursor);






	//show
	PerInfWidget->show();
	label_favourite->show();
	headBack->show();
	head->show();
	id->show();

	id->raise();
}




FPage::~FPage()
{
	//delete server_2;
}


