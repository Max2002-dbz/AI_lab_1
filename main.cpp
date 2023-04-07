#include <QApplication>
#include <QPushButton>
#include <Windows.h>
#include <chess.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FreeConsole();

    Chess chess;
    chess.setFixedHeight(990);
    chess.setWindowIcon(QIcon(":images/icon.png"));
    chess.show();

    return QApplication::exec();
}
