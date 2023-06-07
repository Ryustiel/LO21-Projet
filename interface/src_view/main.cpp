#include <QApplication>
#include "../head_view/versionview.h"
#include "../head_view/boardview.h"


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    VuePartie::setInstance();
    //VuePartie::getInstance()->launchUserInterface();
    VuePartie::getInstance()->quickLaunch(0,0,Version::legacy);
    //QApplication app(argc, argv);
    return 0;
}


