
#include "../include/MainWindow.hpp"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    hexModel = new HexModel(this);
    hexView = new HexView(this);

        // Create central widget and ensure it expands
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = menuBar->addMenu("File");
    QAction *openAction = new QAction("Open File", this);
    fileMenu->addAction(openAction);
    
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);


    // Set the central widget layout (QVBoxLayout)
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);  // Remove margins for full width
    mainLayout->setSpacing(0);  // No extra space between widgets

    // Create horizontal layout for HexView (this layout takes full width)
    hexLayout = new QHBoxLayout();
    hexLayout->setContentsMargins(0, 0, 0, 0);  // Remove margins to ensure full width
    hexLayout->setSpacing(0);  // No gaps inside the layout

    // Create HexView (Custom Widget)
    hexView = new HexView(this);
    hexView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);  // Ensures full width & height
    hexLayout->addWidget(hexView);  // Add HexView to horizontal layout

    // Create text box (fixed height)
    textEdit = new QTextEdit(this);
    textEdit->setPlaceholderText("fuck...");
    textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);  // Expands horizontally, fixed height
    textEdit->setMaximumHeight(100);  // Set a fixed height for QTextEdit, you can adjust this value

    // Add layouts and set stretch factors
    mainLayout->addLayout(hexLayout);  // Add hexLayout to mainLayout
    mainLayout->addWidget(textEdit);   // Add QTextEdit below hexLayout

    // Ensure HexView takes up 80% of the height, and QTextEdit takes 20%
    mainLayout->setStretch(0, 8);  // 80% height for HexView
    mainLayout->setStretch(1, 2);  // 20% height for QTextEdit

        /*QWidget *centralWidget = new QWidget(this);
    centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setCentralWidget(centralWidget);

    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = menuBar->addMenu("File");
    QAction *openAction = new QAction("Open File", this);
    fileMenu->addAction(openAction);
    
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    // Create main vertical layout
    mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);  // Remove margins for full width
    mainLayout->setSpacing(0);  // No extra space between widgets

    // Create horizontal layout for HexView
    hexLayout = new QHBoxLayout();
    hexLayout->setContentsMargins(0, 0, 0, 0);  // Remove margins to ensure full width
    hexLayout->setSpacing(0);  // No gaps inside the layout

    // Create HexView (Custom Widget)
    hexView = new HexView(this);
    hexView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // Ensures full width & height
    hexLayout->addWidget(hexView);  // Add HexView to horizontal layout

    // Create text box
    textEdit = new QTextEdit(this);
    textEdit->setPlaceholderText("Enter notes here...");
    textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);  // Expands horizontally, fixed height

    // Add layouts and set stretch factors
    mainLayout->addLayout(hexLayout, 4);  // 80% height
    mainLayout->addWidget(textEdit, 1);   // 20% height

    // Set layout on central widget
    centralWidget->setLayout(mainLayout);*/

        // Create central widget
    /*QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = menuBar->addMenu("File");
    QAction *openAction = new QAction("Open File", this);
    fileMenu->addAction(openAction);
    
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    // Create layouts
    mainLayout = new QVBoxLayout();
    hexLayout = new QHBoxLayout();

    // Create HexView (Your custom hex viewer widget)
    hexView = new HexView(this);  // Assuming HexView is a QWidget
    hexView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // Make it stretch
    hexLayout->addWidget(hexView);  // Add HexView to horizontal layout

    // Create text box
    textEdit = new QTextEdit(this);
    textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    textEdit->setPlaceholderText("Enter notes here...");

   // Add layouts and set stretch factors
    mainLayout->addLayout(hexLayout, 4);  // 80% of height
    mainLayout->addWidget(textEdit, 1);   // 20% of height

    // Set layout on the central widget
    centralWidget->setLayout(mainLayout);*/

        /////////

    /*setCentralWidget(hexView);

    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = menuBar->addMenu("File");
    QAction *openAction = new QAction("Open File", this);
    fileMenu->addAction(openAction);
    
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);*/
}

MainWindow::~MainWindow() {}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*)");
    if (fileName.isEmpty()) return;

    if (!hexModel->loadFile(fileName)) {
        QMessageBox::warning(this, "Error", "Could not open file!");
        return;
    }

    hexView->displayHex(hexModel->getData());
}
