#include "Store.h"
#include <QtWidgets/QApplication>
#include<qsqldatabase.h>


int main(int argc, char *argv[])
{


	QApplication a(argc, argv);
	Store w;
	w.show();
	return a.exec();
}
