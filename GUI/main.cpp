#include "GUI.h"
#include <QtWidgets/QApplication>
#include "LibraryGUI.h"
#include "C:\Users\robi_\source\repos\Tema 6-7 OOP\Tema 6-7 OOP\Tests.h"

int main(int argc, char *argv[])
{
        TestAll();
        if (argc == 0)
            return 0;
        QApplication a(argc, argv);
        Repo repo;
        Validator valid;
        Service serv{ repo,valid };
        LibraryGUI w{ serv };
        w.show();
        return a.exec();
}
