#include "../include/HexView.hpp"
//#include <QVBoxLayout>
//#include <QHeaderView>
#include <QFont>
#include <QHeaderView>

HexView::HexView(QWidget *parent) : QWidget(parent) {
    hexTable = new QTableWidget(this);
    setupTable();
}

void HexView::setupTable() {
    hexTable->setColumnCount(18); // Offset, 16 hex bytes, ASCII
    QStringList headers;
    headers << "Offset";

    for (int i = 0; i < 16; ++i) {
        headers << QString("%1").arg(i, 2, 16, QChar('0')).toUpper();
    }

    headers << "ASCII";
    hexTable->setHorizontalHeaderLabels(headers);
    hexTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    hexTable->setColumnWidth(0, 80);
    for (int i = 1; i <= 16; ++i) {
        hexTable->setColumnWidth(i, 35);
    }
    hexTable->setColumnWidth(17, 120);
}

void HexView::displayHex(const QByteArray &data) {
    int rows = (data.size() + 15) / 16;
    hexTable->setRowCount(rows);

    for (int row = 0; row < rows; ++row) {
        QTableWidgetItem *offsetItem = new QTableWidgetItem(QString("%1").arg(row * 16, 8, 16, QChar('0')).toUpper());
        offsetItem->setTextAlignment(Qt::AlignCenter);
        hexTable->setItem(row, 0, offsetItem);

        QString asciiText;
        for (int col = 0; col < 16; ++col) {
            int index = row * 16 + col;
            if (index < data.size()) {
                unsigned char byte = static_cast<unsigned char>(data[index]);
                
                QTableWidgetItem *hexItem = new QTableWidgetItem(QString("%1").arg(byte, 2, 16, QChar('0')).toUpper());
                hexItem->setTextAlignment(Qt::AlignCenter);
                hexTable->setItem(row, col + 1, hexItem);

                asciiText += (byte >= 32 && byte <= 126) ? QChar(byte) : '.';
            } else {
                asciiText += " ";
            }
        }

        QTableWidgetItem *asciiItem = new QTableWidgetItem(asciiText);
        asciiItem->setFont(QFont("Courier", 10));
        hexTable->setItem(row, 17, asciiItem);
    }
}
