#include <QFile>
#include <QByteArray>

class FileHandler {
public:
    static QByteArray readFile(const QString& filePath) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) return QByteArray();
        return file.readAll();
    }
};