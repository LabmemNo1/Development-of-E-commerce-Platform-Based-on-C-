#include "Server.h"
#include <QtWidgets/QApplication>
#include<qsqldatabase.h>
#include<qtextcodec.h>

int main(int argc, char *argv[])
{
	
	
	


	QApplication a(argc, argv);
	Server w;
	w.show();
	return a.exec();
}
