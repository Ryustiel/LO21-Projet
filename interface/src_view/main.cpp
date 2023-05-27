#include <QApplication>
#include "../head_view/parametersview.h"

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    VueVersion version;
    version.show();
    return app.exec();
}

