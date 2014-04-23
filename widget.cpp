/// \file widget.cpp
/// \brief Widget class (implementation)
/// \author Radianto
/// \date 22.04.2014

#include "widget.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtGui/QFontDatabase>
#include <QtCore/QEvent>

Widget::Widget(QWidget* parent)
	: QWidget(parent),
	  count_(0),
	  lastClick_(QDateTime::currentDateTime()),
	  labelContainer_(new QWidget(this)),
	  label_(new QLabel("0"))
{
	labelContainer_->setLayout(new QHBoxLayout);
	reinterpret_cast<QHBoxLayout*>(labelContainer_->layout())->addStretch(1);
	reinterpret_cast<QHBoxLayout*>(labelContainer_->layout())->addWidget(label_, 5, Qt::AlignHCenter);
	reinterpret_cast<QHBoxLayout*>(labelContainer_->layout())->addStretch(1);
	labelContainer_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	label_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	labelContainer_->installEventFilter(this);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(new QLabel("<b>" + tr("Incrementator")+ "</b>"), 0, Qt::AlignHCenter);
	QLabel* authorLabel = new QLabel(tr("Created by Radianto [www.radianto.ru]"));
	layout->addWidget(authorLabel, 0 , Qt::AlignHCenter);
	layout->addWidget(labelContainer_, 2);
	QPushButton* button = new QPushButton(tr("Reset"), this);
	connect(button, SIGNAL(clicked()), SLOT(reset()));
	layout->addWidget(button, 0);

	this->setWindowTitle(tr("Incrementator"));

	QFont font = QApplication::font();

	int fontId = QFontDatabase::addApplicationFont(":/qrc/OpenSans-Light.ttf");
	if (fontId != -1)
		font = QFont(QFontDatabase::applicationFontFamilies(fontId).first());

	font.setPointSize(font.pointSize()+20);
	QApplication::setFont(font);

	font.setPointSize(font.pointSize()-20);
	authorLabel->setFont(font);

	fontId = QFontDatabase::addApplicationFont(":/qrc/JosefinSans-Thin.ttf");
	if (fontId != -1)
		font = QFont(QFontDatabase::applicationFontFamilies(fontId).first());

	font.setPointSize(font.pointSize()+180);

	label_->setFont(font);
}

Widget::~Widget()
{
}

void Widget::reset()
{
	label_->setText(QString::number(count_ = 0, 16));
}

bool Widget::eventFilter(QObject* obj, QEvent* event)
{
	if(obj == labelContainer_ && event->type() == QEvent::MouseButtonPress)
	{
		// timeout without click
		if(lastClick_.msecsTo(QDateTime::currentDateTime()) > 100)
		{
			label_->setText(QString::number(++count_, 16));
			lastClick_ = QDateTime::currentDateTime();
		}
		return true;
	}
	return QObject::eventFilter(obj, event);
}

