#pragma once
/*
#include <QAbstractTableModel>
#include <QByteArray>

class HexModel : public QAbstractTableModel {
    Q_OBJECT
public:


private:
    QByteArray fileData;
};
*/
#include <QObject>
#include <QByteArray>

class HexModel : public QObject {
    Q_OBJECT

public:
    explicit HexModel(QObject *parent = nullptr);
    bool loadFile(const QString &filePath);
    QByteArray getData() const;

private:
    QByteArray fileData;
};
