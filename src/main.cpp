/*#include <QApplication>
#include <QMainWindow>
#include "../ui/include/mainWindow.hpp"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("HexWizardry");
    window.resize(800, 600);
    window.show();

    return app.exec();
}*/

/*
#include <QApplication>
#include "../ui/include/HexViewer.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    HexViewer viewer;
    viewer.resize(800, 600);
    viewer.loadFile("test.bin"); // Load a test binary file
    viewer.show();

    return app.exec();
}*/

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QTextEdit>
#include <QMessageBox>
#include <QByteArray>
#include <QFile>
#include <QTableWidget>
#include <QHeaderView>
/*
class FileHandler {
public:
    static QByteArray readFile(const QString &filePath) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly))
            return QByteArray();
        return file.readAll();
    }
};

class HexEditor : public QMainWindow {
    Q_OBJECT

public:
    HexEditor(QWidget *parent = nullptr) : QMainWindow(parent) {
        QMenuBar *menuBar = new QMenuBar(this);
        setMenuBar(menuBar);

        QMenu *fileMenu = menuBar->addMenu("File");
        QAction *openAction = new QAction("Open File", this);
        fileMenu->addAction(openAction);
        connect(openAction, &QAction::triggered, this, &HexEditor::openFile);

        hexTable = new QTableWidget(this);
        setupHexTable();
        setCentralWidget(hexTable);
    }

private slots:
    void openFile() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*)");
        if (fileName.isEmpty()) return;

        fileData = FileHandler::readFile(fileName);
        if (fileData.isEmpty()) {
            QMessageBox::warning(this, "Error", "Could not open file!");
            return;
        }

        loadHexView();
    }

    void loadHexView() {
        int rows = (fileData.size() + 15) / 16; // Each row is 16 bytes
        hexTable->setRowCount(rows);

        for (int row = 0; row < rows; ++row) {
            // Set offset column
            QTableWidgetItem *offsetItem = new QTableWidgetItem(QString("%1").arg(row * 16, 8, 16, QChar('0')).toUpper());
            offsetItem->setTextAlignment(Qt::AlignCenter);
            hexTable->setItem(row, 0, offsetItem);

            QString asciiText;

            for (int col = 0; col < 16; ++col) {
                int index = row * 16 + col;
                if (index < fileData.size()) {
                    unsigned char byte = static_cast<unsigned char>(fileData[index]);

                    // Set hex value
                    QTableWidgetItem *hexItem = new QTableWidgetItem(QString("%1").arg(byte, 2, 16, QChar('0')).toUpper());
                    hexItem->setTextAlignment(Qt::AlignCenter);
                    hexTable->setItem(row, col + 1, hexItem);

                    // Append ASCII representation (printable characters, otherwise '.')
                    asciiText += (byte >= 32 && byte <= 126) ? QChar(byte) : ' ';
                } else {
                    asciiText += " "; // Placeholder for empty bytes
                }
            }

            // Set ASCII column
            QTableWidgetItem *asciiItem = new QTableWidgetItem(asciiText);
            asciiItem->setFont(QFont("Courier", 10));
            hexTable->setItem(row, 17, asciiItem);
        }
    }

private:
    void setupHexTable() {
        hexTable->setColumnCount(18); // Offset, 16 hex bytes, ASCII
        QStringList headers;
        headers << "Offset";

        for (int i = 0; i < 16; ++i) {
            headers << QString("%1").arg(i, 2, 16, QChar('0')).toUpper();
        }

        headers << "ASCII";
        hexTable->setHorizontalHeaderLabels(headers);

        // Adjust column widths
        hexTable->setColumnWidth(0, 80);  // Offset
        for (int i = 1; i <= 16; ++i) {
            hexTable->setColumnWidth(i, 35); // Each hex byte
        }
        hexTable->setColumnWidth(17, 120); // ASCII column

        // Prevent user resizing columns
        hexTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    }

    QTableWidget *hexTable;
    QByteArray fileData;
};
*/

#include <QApplication>
#include "../ui/include/MainWindow.hpp"
#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("HexWizardry");
    window.resize(900, 600);
    window.show();

    return app.exec();
}

