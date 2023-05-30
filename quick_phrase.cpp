#include "quick_phrase.h"

QuickPhrase::QuickPhrase(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.lineEdit->installEventFilter(this);
    ui.listWidget->installEventFilter(this);
    clipboard = QApplication::clipboard();

    connect(ui.ADD, SIGNAL(clicked()), this, SLOT(ADDClicked()));
    connect(ui.listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(listWidgetRowChanged(int)));

    loadData();
}

QuickPhrase::~QuickPhrase()
{
    saveData();
}

void QuickPhrase::listwidgetInsertItem(QString str) {
    QListWidgetItem* temp = new QListWidgetItem(ui.listWidget);
    temp->setText(str);
    temp->setFont(QFont("Microsoft YaHei", 16));
    temp->setTextAlignment(Qt::AlignHCenter);
}

void QuickPhrase::saveData()
{
    QString path = QDir::currentPath();
    QString name("local_data.txt");
    QFile f(path + "/" + name);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "file open error\n";
        return;
    }

    QTextStream txtOutput(&f);

    int num = ui.listWidget->count();
    for (size_t i = 0; i < num; i++)
    {
        auto item = ui.listWidget->item(i);
        txtOutput << item->text() << Qt::endl;
    }
    f.close();
    return;
}

void QuickPhrase::loadData()
{
    QString path = QDir::currentPath();
    QString name("local_data.txt");
    QFile f(path + "/" + name);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "file open error\n";
        return;
    }
    QTextStream txtOutput(&f);
    while (!txtOutput.atEnd()) {
        QString temp(txtOutput.readLine());
        //qDebug() << temp;
        listwidgetInsertItem(temp);
    }
}

bool QuickPhrase::eventFilter(QObject* object, QEvent* event)
{
    if (object == ui.lineEdit) {
        if (event->type() == QEvent::FocusOut) {
            ui.stackedWidget->setCurrentIndex(0);
            ui.lineEdit->clear();
        }
        else if (event->type() == QEvent::KeyPress) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Return)
            {
                listwidgetInsertItem(ui.lineEdit->text());
                ui.lineEdit->clear();
                ui.stackedWidget->setCurrentIndex(0);
                // 不希望该事件继续传递
                return true;
            }
        }
    }
    else if (object == ui.listWidget) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Delete) {
                auto item = ui.listWidget->takeItem(ui.listWidget->currentRow());
                delete item;
                return true;
            }
        }
    }

    return false;
}

void QuickPhrase::keyPressEvent(QKeyEvent* keyEvent)
{
    if (keyEvent->key() == Qt::Key_Up ||
        keyEvent->key() == Qt::Key_Down ||
        keyEvent->key() == Qt::Key_Left ||
        keyEvent->key() == Qt::Key_Right) 
    {
        ui.listWidget->setFocus();
    }
}

void QuickPhrase::listWidgetRowChanged(int row)
{
    if (row < 0) return;
    auto item = ui.listWidget->item(row);
    clipboard->setText(item->text());
}

void QuickPhrase::ADDClicked() {
    ui.stackedWidget->setCurrentIndex(1);
}