#pragma once
/*
#include <QWidget>
#include <QTableView>
#include <QTableWidget>
#include "./HexModel.hpp"

class HexView : public QWidget {
    Q_OBJECT
public:
    explicit HexView(QWidget *parent = nullptr);
    void loadFile(const QString &filePath);

private:
    QTableWidget *hexTable;
    QTableView *tableView;
    HexModel *hexModel;
};*/

#include <QWidget>
#include <QHeaderView>
#include <QTableWidget>

class HexView : public QWidget {
    Q_OBJECT

public:
    explicit HexView(QWidget *parent = nullptr);
    void displayHex(const QByteArray &data);

private:
    void setupTable();
    QTableWidget *hexTable;
};

