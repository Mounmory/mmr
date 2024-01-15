#include <QtWidgets/QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QWidget w;
	w.setWindowTitle("qtTest");
	w.setFixedSize(300, 200);
	w.show();
	return a.exec();
}

