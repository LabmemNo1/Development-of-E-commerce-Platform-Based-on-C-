#pragma once

#include <QWidget>
#include "ui_PerInf.h"

class PerInf : public QWidget
{
	Q_OBJECT

public:
	PerInf(QWidget *parent = Q_NULLPTR);
	~PerInf();

private:
	Ui::PerInf ui;
};
