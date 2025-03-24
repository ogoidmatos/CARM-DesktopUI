#include "dbmanager.h"
#include "mainwindow.h"

#include <QApplication>
#include <QSettings>

static const QString database_path = "carm_db.db";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QSettings settings("Diogo Matos", "CARM-UI");
    const bool firstExecution = settings.value("firstExecution", true).toBool();

    if (firstExecution) {
        settings.setValue("firstExecution", false);
    }

    DBManager my_db(database_path, firstExecution);
    return a.exec();
}
