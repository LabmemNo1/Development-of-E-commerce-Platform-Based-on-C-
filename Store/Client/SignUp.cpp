#include "SignUp.h"

SignUp::SignUp(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	connect(ui.P_Signup, &QPushButton::clicked, this, &SignUp::P_Signup);
	

}


void SignUp::P_Signup()
{	//如果两次密码一致
	if (ui.LI_Password->text() == ui.LI_Password_2->text())
	{
		QString send = 'u' + ui.LI_Username->text() + "password" + ui.LI_Password->text();
		server->getTcp()->write(send.toLocal8Bit());
	}
}

SignUp::~SignUp()
{
	//delete server;
}
