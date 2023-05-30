#pragma once

#include <QtWidgets/QMainWindow>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QClipboard>
#include <QDir>

#include "ui_quick_phrase.h"

class QuickPhrase : public QMainWindow
{
    Q_OBJECT

public:
    QuickPhrase(QWidget *parent = nullptr);
    ~QuickPhrase();
    void listwidgetInsertItem(QString str);
    void saveData();
    void loadData();

public slots:
    void ADDClicked();
    bool eventFilter(QObject*, QEvent*);
    void keyPressEvent(QKeyEvent*);
    void listWidgetRowChanged(int);

private:
    Ui::quick_phraseClass ui;
    QClipboard* clipboard;
};
