#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include <QMessageBox>
#include "../../head/Version.h"
#include "../head_view/versionview.h"

void VueVersion::buttonClicked(){
    const std::string versionstr=choix->currentText().toStdString();
    version=toVersion(versionstr);
    this->hide();
    parameterView.show();
}
