#include <QApplication>
#include "../head_view/parametersview.h"
#include "../head_view/boardview.h"
#include "../head_view/essai.h"
#include <QFile>
#include <QResource>

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    /*
    QFile styleFile(":/stylesheets/global.qss");
    styleFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleFile.readAll());
    */

    /*
    QFile styleFile(":/stylesheets/global.qss");
    styleFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream styleStream(&styleFile);
    QString styleSheet = styleStream.readAll();
    app.setStyleSheet(styleSheet);
    */

    QResource::registerResource("/resources.qrc");

    // Appliquer le style depuis la ressource .qss
    QFile styleFile(":/new/prefix1/stylesheets/global.qss");
    styleFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleFile.readAll());
    qApp->setStyleSheet(styleSheet);

    VueVersion version;
    Essai fenetre;

    //VuePartie partie;
    //partie.show();
    fenetre.show();
    //version.show();
    return app.exec();
}

