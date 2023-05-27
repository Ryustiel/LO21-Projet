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
    const QString versionstr=choix->currentText();
    //version=toVersion(versionstr);

    VueParametres* param = new VueParametres(nullptr);
    this->hide();
    param->show();
}
