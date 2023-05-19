#include <QApplication>
#include <QPushButton>
#include "../head_view/boardview.h"

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    VuePartie partie;
    partie.show();
    return app.exec();


    /*
    QApplication app(argc, argv);
    //creation objet QPushButton
    QPushButton button("Quitter"); // pas de parent declare dans l'app donc pas besoin de 2eme argument

    VueCarte *carte=new VueCarte;


    //signaux et slots
    QObject::connect(
    &button, SIGNAL(clicked()),
    &app, SLOT(quit()));


    button.show(); //sert a afficher bouton

    return app.exec();
    */
}

