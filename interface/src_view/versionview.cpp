#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include <QMessageBox>
#include "../head_view/versionview.h"
#include "../head_view/parametersview.h"

void VueVersion::buttonClicked(){
    QString versionstr=choix->currentText();
    // a changer quand on aura fonction str-> version
    if(versionstr=="legacy") version=Version::legacy;
    if(versionstr=="tactic") version=Version::tactic;

    VueParametres* param = new VueParametres(nullptr);
    this->hide();
    param->show();
}
