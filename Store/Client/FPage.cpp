#include "FPage.h"

FPage::FPage(QWidget *parent)
	: QWidget(parent)
{
	//��ʼ��
	ui.setupUi(this);
	
	initFPage();
	
	//�����źźͲ�
	//���� ������Ϣ�Ͷ���

	connect(ui.P_Inf, &QPushButton::clicked, this, &FPage::Send_PerInf);
	connect(ui.P_Order, &QPushButton::clicked, this, &FPage::InitOrders);



	//������ť
	connect(ui.P_Search, &QPushButton::clicked, this, &FPage::search_clicked);


	//ͼƬ��ť
	connect(FPagePB_1.at(0), &QPushButton::clicked, this, &FPage::P_C1_clicked);
	connect(FPagePB_1.at(1), &QPushButton::clicked, this, &FPage::P_C1_clicked);
	connect(FPagePB_1.at(2), &QPushButton::clicked, this, &FPage::P_C1_clicked);
	connect(FPagePB_1.at(3), &QPushButton::clicked, this, &FPage::P_C1_clicked);
	connect(FPagePB_1.at(4), &QPushButton::clicked, this, &FPage::P_C1_clicked);
	//����᳡��ť
	connect(FPagePB_2.at(0), &QPushButton::clicked, this, &FPage::P_C11_clicked);
	connect(FPagePB_2.at(1), &QPushButton::clicked, this, &FPage::P_C11_clicked);
	connect(FPagePB_2.at(2), &QPushButton::clicked, this, &FPage::P_C11_clicked);
	connect(FPagePB_2.at(3), &QPushButton::clicked, this, &FPage::P_C11_clicked);
	connect(FPagePB_2.at(4), &QPushButton::clicked, this, &FPage::P_C11_clicked);
	//��������
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoad(QNetworkReply*)));
	
	connect(manager_digital, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoad_digital(QNetworkReply*)));







	//��ʱ�� ��ֹ����ʱ��Ұָ��
	connect(fptimer, &QTimer::timeout, this, &FPage::revurl);
	//�رպ���С��
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
	//��Ӱ
	auto shadowEffect = new QGraphicsDropShadowEffect(this);
	shadowEffect->setOffset(0, 0);
	shadowEffect->setColor(Qt::black);
	shadowEffect->setBlurRadius(10);
	this->setGraphicsEffect(shadowEffect);
	

	//��Ʒ������
	ui.Goods_Display->hide();
	InitPerInfWidget();



	
	//ͼƬ����
	
	//��ҳͼƬ
	ui.UI_Image->setPixmap(QPixmap("FPageUI/home.png"));
	ui.UI_Image->setScaledContents(true);
	//logo
	ui.UI_FPage->setPixmap(QPixmap("FPageUI/UI_FPage.png"));
	ui.UI_FPage->setScaledContents(true);
	//��ť
	ui.P_Min->setIcon(QIcon("StoreUI/minimizeButton.png"));
	ui.P_Min->setIconSize(QSize(13, 13));
	ui.P_Close->setIcon(QIcon("StoreUI/closeButton.png"));
	ui.P_Close->setIconSize(QSize(13, 13));
	ui.P_Search->setIcon(QIcon("FPageUI/search.png"));
	ui.P_Search->setIconSize(QSize(30, 30));
	
	
	//��ҳ�İ���list��ʼ��
	FPagePB_1 << ui.P_C1 << ui.P_C2 << ui.P_C3 << ui.P_C4 << ui.P_C5;
	FPagePB_2 << ui.P_C11 << ui.P_C22 << ui.P_C33 << ui.P_C44 << ui.P_C55;





	//ȡ��������
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground);

	



}
//����¼��ۺ���
//�����˼·�Ǵ�url���һ��"/"�������png�����֣�Ȼ����ص�pixmap���̶����ص�label��

void FPage::P_C1_clicked()
{

	//manager->get(QNetworkRequest(QUrl(url1)));
	
	int start = url1.lastIndexOf("/") + 1;
	QString name_sender = sender()->objectName();
	//���ݷ����߲�ͬ
	//����
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

//����᳡�ۺ���
void FPage::P_C11_clicked()
{
	//�Ѹ�����Ϣ�Ķ������ص�
	head->hide();
	headBack->hide();
	id->hide();
	PerInfWidget->hide();
	label_favourite->hide();
	FavouriteWidget->hide();

	
	ui.UI_Image->hide();
	ui.Goods_Display->show();
	
	QString name_sender = sender()->objectName();
	//���ݷ����߲�ͬ
	//����
	if(name_sender.compare(QStringLiteral("P_C11"))==0)
	{
		server_2->getTcp()->write("d");
	}
	//ʳƷ
	if (name_sender.compare(QStringLiteral("P_C22")) == 0)
	{
		server_2->getTcp()->write("f");
	}
	//�Ҿ�
	if (name_sender.compare(QStringLiteral("P_C33")) == 0)
	{
		server_2->getTcp()->write("h");
	}
	//����
	if (name_sender.compare(QStringLiteral("P_C44")) == 0)
	{
		server_2->getTcp()->write("k");
	}
	//����
	if (name_sender.compare(QStringLiteral("P_C55")) == 0)
	{
		server_2->getTcp()->write("c");
	}
	

}

//����
void FPage::search_clicked()
{//�Ѹ�����Ϣ�Ķ������ص�
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

//���͸�����Ϣ����
void FPage::Send_PerInf()
{
	qDebug() << server_2->username << endl;
	server_2->getTcp()->write("p"+server_2->username.toLocal8Bit());
}




//��ʱ��
void FPage::revurl()
{
	QString url = server_2->getMessage();
	fptimer->stop();
	
	
	url=url.mid(1);//ȥ����һ��ͨ�ű�־
	//���url�ı�־
	int f1 = url.indexOf("http", 4);//��һ��url��β���ȣ��Դ�����
	int f2 = url.indexOf("http", f1+4);

	int f3 = url.indexOf("http", f2+4);
	int f4 = url.indexOf("http", f3+4);
	
	
	//���ͼƬ��url
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
	//����ͼƬ
	manager->get(QNetworkRequest(QUrl(url1)));
	manager->get(QNetworkRequest(QUrl(url2)));
	manager->get(QNetworkRequest(QUrl(url3)));
	manager->get(QNetworkRequest(QUrl(url4)));
	manager->get(QNetworkRequest(QUrl(url5)));


		
}
//����������ɲۺ���
void FPage::slotReplyPixmapLoad(QNetworkReply* reply)
{
	if (reply->error() == QNetworkReply::NoError)
	{
		
		qDebug() << "reply111111 :" << reply << endl;
		//��ȡ������
		bytes = reply->readAll();
		
		//��url���ҵ��ؼ��֣���ȷ������ͼƬ������
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
		//��ȡ������
		bytes = reply->readAll();

		//��url���ҵ��ؼ��֣���ȷ������ͼƬ������
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



//����¼�
void FPage::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isPressed = true;
		//ȡ�õ��ʱ����������
		m_startMovePos = event->globalPos();
	}

	return QWidget::mousePressEvent(event);
}

void FPage::mouseMoveEvent(QMouseEvent *event)
{
	if (m_isPressed)
	{
		//���ϵ�ѭ����move�¼��൱�ڲ��ϵĵ��
		QPoint movePoint = event->globalPos() - m_startMovePos;
		//��ȡ����ƶ���������
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



//���ܷ�������Ϣ
void FPage::rev_2()
{
	QByteArray FPmessage = server_2->getMessage();
	//��ֹ��������
	QTextCodec *tc = QTextCodec::codecForName("GBK");
	QString message = tc->toUnicode(FPmessage);
	//��Ʒ������Ϣ
	int size_d;

	//������Ϣ
	QString head, id, money, address, goods, favourite, orders;
	switch ((server_2->getMessage()).at(0))
	{
	//���յ�������������᳡��Ϣ
	case '4':case '5':case'6':case '7':case '8': case'9':
		//���������
		name_rev.clear();
		url_rev.clear();
		user_rev.clear();
		description_rev.clear();
		price_rev.clear();
		//�ж��ټ���Ʒ
		size_d = QString(message.at(1)).toInt();
		qDebug()<<"size is"<<size_d<<endl;
		//ȥ����ʶ��
		message = message.mid(2);

		for (int i = 0; i < size_d; i++)
		{
			//�ҵ�������Ϣ��λ��
			int name_address = message.indexOf("name:") + 5;
			int url_address= message.indexOf("url:") + 4;
			int user_address = message.indexOf("user:") + 5;
			int description_address = message.indexOf("description:") + 12;
			int price_address = message.indexOf("price:") + 6;
			int name_next = message.indexOf("name:", price_address);
			//��ȡ��Ϣ
			QString name_s = message.mid(name_address, url_address - name_address-4);
			QString url_s = message.mid(url_address, user_address - url_address - 5);
			QString user_s = message.mid(user_address, description_address - user_address - 12);
			QString description_s = message.mid(description_address, price_address - description_address-6);
			QString price_s= message.mid(price_address, name_next - price_address);
			//����������
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


			//��ȡ���ù�����һ��
			message=message.mid(name_next);

		}
	InitGoods();
	break;
	//���յ�������Ϣ
	case 'p':
		//ȥ����ʶ��
		ui.UI_Image->hide();
		ui.Goods_Display->show();
		message = message.mid(1);
		
		




		InitPerInf(message);
		break;

	}
}

//��Դ����
void FPage::InitGoods()
{
	if (name_rev.size() > goods_image.size())//�����Ҫ���ص���Ʒ��list�еĶ�
	{
		qDebug() << "SIZE BIG" << name_rev.size() - goods_image.size() << endl;
		//�����µ���Ʒ��Ҳ����label��pushbutton
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
			//��ֹ�ռ䲻����������������С�߶ȣ����ֻ���
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

		//��֪�����������ﲻһ��������ֻѭ����һ��
		//for (int j = 0; j < (name_digital.size() - goods_image.size()); j++)
		//{
		//	//�ؼ�������
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
	//����һ��ѭ����ʾurl������͹���ҳ��
	qDebug() << "goods_image size is" << goods_image.size() << endl;
	for (int i = 0; i < name_rev.size(); i++)
	{	//�ҵ�ͼƬ��
		int start = url_rev.at(i).lastIndexOf("/") + 1;
		QString loadpath = url_rev.at(i).mid(start);
		//����ͼƬ
		QFileInfo file(QString("FPageUI/%1").arg(loadpath));
		//����Ѿ��������
		if (file.isFile())
		{	//������ƷͼƬ
			goods_image.at(i)->setPixmap(QString("FPageUI/%1").arg(loadpath));
			goods_image.at(i)->show();
			goods_image.at(i)->setScaledContents(true);
		}
		else//�����������������ټ���
		{
			QNetworkReply *reply = manager_digital->get(QNetworkRequest(QUrl(url_rev.at(i))));
			connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
			loop.exec();
			goods_image.at(i)->setPixmap(QString("FPageUI/%1").arg(loadpath));
			goods_image.at(i)->show();
			goods_image.at(i)->setScaledContents(true);

		}
		
		//��ʾ�۸�
		goods_price.at(i)->setText(QString::fromLocal8Bit("<html><head / ><body><p><span style = \
			' font-size:16pt; font-weight:600;color:red;'\
			>%1< / span>< / p>< / body>< / html>").arg(price_rev.at(i)));

		qDebug() << "price is" << price_rev.at(i) << endl;
		goods_price.at(i)->show();
		//����ť �����Ʒ������
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
		//���
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


		//���ӹ���͵�ң�ת����Һ͹���ҳ��
		//��Ҫ���ݵ���ļ�¼�����ݿ�д��
		connect();
		
	}

}
//������Ϣҳ��
void FPage::InitPerInf(QString message)
{
	//������Ϣ
	//ÿ����Ϣ�����ڵĵ�ַ
	int head_address, id_address, money_address, address_address, goods_address, favourite_address, orders_address;
	QString head_text, id_text, money_text, address_text, goods_text, favourite_text, orders_text;

	head_address = message.indexOf("head:") + 5;
	id_address = message.indexOf("id:") + 3;
	money_address = message.indexOf("money:") + 6;
	address_address = message.indexOf("address:") + 8;
	goods_address = message.indexOf("goods:") + 6;
	favourite_address = message.indexOf("favourite:") + 10;
	orders_address = message.indexOf("orders:") + 7;
	//������Ϣ��
	head_text = message.mid(head_address, id_address - head_address - 3);
	id_text = message.mid(id_address, money_address - id_address - 6);
	money_text = message.mid(money_address, address_address - money_address - 8);
	address_text = message.mid(address_address, goods_address - address_address - 6);
	goods_text = message.mid(goods_address, favourite_address - goods_address - 10);
	favourite_text = message.mid(favourite_address, orders_address - favourite_address - 7);
	orders_text = message.mid(orders_address);


	
	//������� 240 243 239
	//���ص�������Ʒ��Ϣ
	for (int i = 0; i < goods_image.size(); i++)
	{
		goods_image.at(i)->hide();
		goods_price.at(i)->hide();
		buy.at(i)->hide();
		user.at(i)->hide();
	}
//	//Ǯ����
//	//����ͷ���id
//	QLabel *headBack = new QLabel(ui.Goods_area);
//	QPushButton *head = new QPushButton(ui.Goods_area);
//	QLabel *id = new QLabel(ui.Goods_area);
//	headBack->setGeometry(QRect(10, 10, 200, 200));
//	head->setGeometry(QRect(40, 20, 140, 140));
//	id->setGeometry(QRect(70,170,100,20));
//
//
//	//����Ǯ��widget
//	QWidget *PerInfWidget = new QWidget(ui.Goods_area);
//	PerInfWidget->setGeometry(QRect(210, 30, 720, 150));
//	//����Ǯ��widget�еĿؼ�
//	QLabel *wallet = new QLabel(PerInfWidget);
//	QFrame *line = new QFrame(PerInfWidget);
//	QLabel *AccBlan = new QLabel(PerInfWidget);
//	QPushButton *number = new QPushButton(PerInfWidget);
//	QPushButton *address = new QPushButton(PerInfWidget);
//
//
//	//��������������ϲ��
//	QLabel* label_favourite = new QLabel(ui.Goods_area);
//	QWidget* FavouriteWidget = new QWidget(ui.Goods_area);
//
//
//
//	//��������
//	//Ǯ������
//	wallet->setGeometry(QRect(20,10,140,20));
//	line->setGeometry(QRect(0, 30, 720, 20));
//	line->setFrameShape(QFrame::HLine);
//	line->setFrameShadow(QFrame::Sunken);
//	number->setGeometry(QRect(100, 60, 170, 50));
//	AccBlan->setGeometry(QRect(100,120,50,20));
//	address->setGeometry(QRect(300,40,160,90));
//	//����ϲ������
//	label_favourite->setGeometry(QRect(100, 220, 750, 50));
//	FavouriteWidget->setGeometry(QRect(100, 270, 750, 370));
//
//	//��ʽ��
//	//widget��ʽ��
//	ui.Goods_area->setStyleSheet("background-color: rgb(240,243,239);");
//	
//	//Ǯ����ʽ��
//	headBack->setStyleSheet("background-color: rgb(226, 35, 26);");
//	head->setStyleSheet("border-radius: 50px;border - width: 0 0 0 0;");
//	id->setStyleSheet("background-color: rgb(226, 35, 26);color: rgb(255, 255, 255);");
//	wallet->setStyleSheet("font-size:18px;background-color: rgb(250, 250, 250);");
//	number->setStyleSheet("border:none;text-align:left;");
//	address->setStyleSheet("border:none;");
//	//����ϲ����ʽ��
//	label_favourite->setStyleSheet("background-color: rgb(160, 205, 235);\
//									color: rgb(255, 255, 255);\
//									font - size:18px; ");
//	FavouriteWidget->setStyleSheet("background-color: rgb(245,248,250);");
////���������ʽ
//	head->setCursor(Qt::PointingHandCursor);
//	number->setCursor(Qt::PointingHandCursor);
//	address->setCursor(Qt::PointingHandCursor);
	//����ͼƬ������
	id->setText(id_text);
	wallet->setText(QString::fromLocal8Bit("�ҵ�Ǯ��"));
	AccBlan->setText(QString::fromLocal8Bit("���"));
	number->setText(QString::fromLocal8Bit("%1").arg(money_text));
	address->setText(address_text);

	label_favourite->setText(QString::fromLocal8Bit("�������������ϲ��"));

	






	//show
	PerInfWidget->show();
	label_favourite->show();
	headBack->show();
	head->show();
	id->show();

	id->raise();




	//����ϲ��

	InitFavGoods();





	//�����źźͲ�






	//������ͷ���ͼƬ
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
	else//�����������������ټ���
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
//��������
void FPage::InitOrders()
{

}

void FPage::InitFavGoods()
{

}
void FPage::InitPerInfWidget()
{
	//Ǯ����
//����ͷ���id
	headBack = new QLabel(ui.Goods_area);
	head = new QPushButton(ui.Goods_area);
	id = new QLabel(ui.Goods_area);
	headBack->setGeometry(QRect(10, 10, 200, 200));
	head->setGeometry(QRect(40, 20, 140, 140));
	id->setGeometry(QRect(70, 170, 100, 20));


	//����Ǯ��widget
	PerInfWidget = new QWidget(ui.Goods_area);
	PerInfWidget->setGeometry(QRect(210, 30, 720, 150));
	//����Ǯ��widget�еĿؼ�
	wallet = new QLabel(PerInfWidget);
	line = new QFrame(PerInfWidget);
	AccBlan = new QLabel(PerInfWidget);
	number = new QPushButton(PerInfWidget);
	address = new QPushButton(PerInfWidget);


	//��������������ϲ��
	label_favourite = new QLabel(ui.Goods_area);
	FavouriteWidget = new QWidget(ui.Goods_area);



	//��������
	//Ǯ������
	wallet->setGeometry(QRect(20, 10, 140, 20));
	line->setGeometry(QRect(0, 30, 720, 20));
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	number->setGeometry(QRect(100, 60, 170, 50));
	AccBlan->setGeometry(QRect(100, 120, 50, 20));
	address->setGeometry(QRect(300, 40, 160, 90));
	//����ϲ������
	label_favourite->setGeometry(QRect(100, 220, 750, 50));
	FavouriteWidget->setGeometry(QRect(100, 270, 750, 370));

	//��ʽ��
	//widget��ʽ��
	ui.Goods_area->setStyleSheet("background-color: rgb(240,243,239);");

	//Ǯ����ʽ��
	PerInfWidget->setStyleSheet("background-color: rgb(250, 250, 250);");
	headBack->setStyleSheet("background-color: rgb(226, 35, 26);");
	head->setStyleSheet("border-radius: 50px;border - width: 0 0 0 0;");
	id->setStyleSheet("background-color: rgb(226, 35, 26);color: rgb(255, 255, 255);");
	wallet->setStyleSheet("font-size:18px;background-color: rgb(250, 250, 250);");
	number->setStyleSheet("border:none;text-align:left;");
	address->setStyleSheet("border:none;");
	//����ϲ����ʽ��
	label_favourite->setStyleSheet("background-color:rgb(160, 205, 235);\
									color:rgb(255, 255, 255);\
									font-size:18px;");
	FavouriteWidget->setStyleSheet("background-color:rgb(245,248,250);");



	//���������ʽ
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


