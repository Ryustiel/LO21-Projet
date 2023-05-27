#ifndef VERSIONVIEW_H
#define VERSIONVIEW_H
#include <QWidget>
#include "../../head/Version.h"

#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

class VueVersion : public QWidget {
    Q_OBJECT
public:
    explicit VueVersion(QWidget *parent = nullptr): QWidget(parent){
        setWindowTitle("Choix de la version");

        choixV = new QLabel("Choisir une version :");

        choix = new QComboBox(parent);
        for (auto& v : Versions) {
            choix->addItem(QString::fromStdString(toString(v)));
        }

        go = new QPushButton(parent);
        go->setText("Continuer");
        connect(go, SIGNAL(clicked()), this, SLOT(buttonClicked()));

        Choix = new QHBoxLayout;
        Choix->addWidget(choixV);
        Choix->addWidget(choix);

        couche = new QVBoxLayout;
        couche->addLayout(Choix);
        couche->addWidget(go);

        setLayout(couche);
    };
    const std::string getVersion() const {return toString(version);} // à changer quand on aura le toString de la version
private:
    Version version;
    QComboBox* choix;
    QLabel* choixV;
    QHBoxLayout* Choix;
    QVBoxLayout* couche;
    QPushButton* go;
private slots:
    // slots qui gère les clics sur le bouton
    void buttonClicked();
};


#endif // VERSIONVIEW_H
