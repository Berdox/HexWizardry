#pragma once

/*#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

class MainWindow : public QMainWindow {
    
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    private slots:
    QTextEdit * openFile() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt);;All Files (*)");

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                textEdit->setText(in.readAll());
                file.close();
            } else {
                QMessageBox::warning(this, "Error", "Could not open file!");
            }
        }
    }

private:
    QTextEdit *textEdit;
};*/

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include "HexView.hpp"
#include "HexModel.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *hexLayout;
    QTextEdit *textEdit;
    HexView *hexView;
    HexModel *hexModel;
};
