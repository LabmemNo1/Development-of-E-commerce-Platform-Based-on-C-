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
	//�ⲿ�ӿ�
	QTcpSocket* getTcp();
	QByteArray getMessage()const;
	//��¼�˺�
	QString username;

	
private:
	Ui::StoreClass ui;
	//ָ��
	FPage *fp;//��ҳ��ת
	QTcpSocket *tcpsocketSign;
	//����
	
	

	//��������ʱ��
	QTimer ColorTimer;
	qreal colorFactor;
	bool isAddFactor;





	//����
	//��ʼ��
	void initStore();
	//�س���¼�����¼�
	void keyPressEvent(QKeyEvent * event);
	//�����¼�����Ϊȡ���˱�����
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	//�����϶�
	bool m_isPressed;
	QPoint m_startMovePos;



	QByteArray revm;//���ܷ�������Ϣ
	


private slots://�ۺ���
	void signin();//��¼
	void signup();//ע��
	void sendSignMessage();//�����˻���Ϣ

	void rev();//���ܷ���������Ϣ
	void ReadError(QAbstractSocket::SocketError);//������




};
