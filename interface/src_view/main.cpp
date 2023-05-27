#include <QApplication>
#include "../head_view/parametersview.h"
#include "../head_view/boardview.h"

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    /*
    VueVersion param;
    param.show();
    */

    VuePartie partie;
    partie.show();
    return app.exec();
}

