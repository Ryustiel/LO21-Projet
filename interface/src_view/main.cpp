#include <QApplication>
#include "../head_view/parametersview.h"
#include "../head_view/boardview.h"


int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    VueVersion version;
    VuePartie partie;
    //partie.show();
    version.show();
    return app.exec();
}

