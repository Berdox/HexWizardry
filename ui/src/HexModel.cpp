#include "../include/HexModel.hpp"
#include <QFile>

HexModel::HexModel(QObject *parent) : QObject(parent) {}

bool HexModel::loadFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    fileData = file.readAll();
    return true;
}

QByteArray HexModel::getData() const {
    return fileData;
}
