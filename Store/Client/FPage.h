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
	void rev_2();//���ܷ�������Ϣ
private:
	Ui::FPage ui;



	
	//����URL����
	QNetworkAccessManager *manager;//��ҳͼƬ����
	//��ƷͼƬ����
	QNetworkAccessManager *manager_digital;
	QNetworkAccessManager *manager_food;
	QNetworkAccessManager *manager_home;
	QNetworkAccessManager *manager_kitchen;
	QNetworkAccessManager *manager_clothes; 
	
	QPixmap store;//��ҳͼƬ
	//url·��
	QString url1;
	QString url2;
	QString url3;
	QString url4;
	QString url5;
	//��ʱ��
	//��㹹��storeָ��
	QTimer *fptimer;

	//����������
	QByteArray bytes;
	//����
	QList<QPushButton*> FPagePB_1;;//��ҳ��ť����
	QList<QPushButton*> FPagePB_2;//����᳡��ť����
	QList<QString> name_rev, url_rev, user_rev, description_rev,price_rev;//��Ʒҳ����Ϣ����

	
	//��Ʒҳ��ؼ�����
	QList<QLabel*> goods_image,goods_price;//�����Ʒ��ͼ�������
	QList<QPushButton*> buy;//����ť
	QList<QPushButton*> user;//�̼Ұ�ť






	//�����¼�����Ϊȡ���˱�����
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	//�����϶�
	bool m_isPressed;
	QPoint m_startMovePos;





	//���ظ�����Ϣ�Ŀؼ�
	void InitPerInfWidget();

	//��Ʒ��Դ����
	void InitGoods();
	//���캯��
	void initFPage();
	//������Ϣ
	void InitPerInf(QString);
	//����
	void InitOrders();
	//��������Ƽ�
	void InitFavGoods();



	
	//һ��ѭ���¼�
	QEventLoop loop;




	//Ǯ����
//����ͷ���id
	QLabel *headBack;
	QPushButton *head;
	QLabel *id;



	//Ǯ��widget
	QWidget *PerInfWidget;
	
	QLabel *wallet;
	QFrame *line;
	QLabel *AccBlan;
	QPushButton *number;
	QPushButton *address;


	//�����������ϲ��
	QLabel* label_favourite;
	QWidget* FavouriteWidget;














private slots:
	//url��Ϣ������ɲۺ���
	void slotReplyPixmapLoad(QNetworkReply*);
	void slotReplyPixmapLoad_digital(QNetworkReply*);


	//��ҳ����ͼƬ����
	void P_C1_clicked();
	//void P_C2_clicked();
	//void P_C3_clicked();
	//void P_C4_clicked();
	//void P_C5_clicked();
	//����᳡����
	void P_C11_clicked();

	//����
	void search_clicked();
	//������Ϣ����
	void Send_PerInf();

	
	void revurl();//��ʱ���ź�

};
