#include "Lab_12.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "myListQtClass.h"
#include "Test.h"

int main(int argc, char *argv[])
{
    testAll();
    QApplication a(argc, argv);
    
    Repository repository{ "recording.txt" };
    Saved_Repository savedRepository{ "recording.txt" };
    Service service{ repository, savedRepository, "A" };
    Lab_12 gui{ savedRepository, service };
    gui.show();

    return a.exec();
}
