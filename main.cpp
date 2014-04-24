#include "widget.h"
#include <QtWidgets/QApplication>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QTranslator translator;
	if(QLocale().system().name() == "ru_RU")
		translator.load(":/qrc/translate.qm");
	QCoreApplication::installTranslator(&translator);

    Widget w;
    w.show();

    return a.exec();
}
