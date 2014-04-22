/// \file widget.h
/// \brief Widget class
/// \author Radianto
/// \date 22.04.2014

#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QDateTime>

class QLabel;

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget* parent = 0);
	~Widget();

private slots:
	void reset();

private:
	bool eventFilter(QObject* obj, QEvent* event);

private:
	unsigned count_;
	// gui
	QDateTime lastClick_;
	QWidget* labelContainer_;
	QLabel* label_;
};

