#include <QApplication>
#include "../head_view/parametersview.h"

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    VueVersion param;
    param.show();
    return app.exec();
}

