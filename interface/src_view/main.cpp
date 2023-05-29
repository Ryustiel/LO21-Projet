#include <QApplication>
#include "../head_view/parametersview.h"
#include "../head_view/boardview.h"
#include "../head_view/essai.h"


int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    VueVersion version;
    Essai fenetre;

    //VuePartie partie;
    //partie.show();
    fenetre.show();
    //version.show();
    return app.exec();
}

