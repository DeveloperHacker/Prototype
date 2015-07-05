#include "Application/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QSize sizeForm = QSize(1120, 630);
//    sizeForm = QSize(1280, 720);
//    sizeForm = QSize(940, 540);
//    sizeForm = QSize(640, 360);

    centralWidget = new QWidget();
    setCentralWidget(centralWidget);
    setMaximumSize(sizeForm.width(), sizeForm.height());
    setMinimumSize(sizeForm.width(), sizeForm.height());

    baseLayout = new QGridLayout(centralWidget);
    centralWidget->setLayout(baseLayout);

    sceleton = new QWidget();

    baseLayout->setMargin(0);
    baseLayout->setSpacing(0);
    baseLayout->addWidget(sceleton, 0, 0, coef_y, coef_x);

    // MainWindow
    screen = nullptr;
    arrow_up = nullptr;
    arrow_left = nullptr;
    arrow_right = nullptr;
    arrow_down = nullptr;
    menuButton = nullptr;

    // Pause
    pauseBackground = nullptr;
    pauseForm = nullptr;
    closeButton = nullptr;
    returnButton = nullptr;

    //Menu
    menuBackground = nullptr;
    quitButton = nullptr;
    startButton = nullptr;

    onMenuForm();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (activeForms.back() == Forms::ErrorForm)
    {
        if (event->key() == Qt::Key_Enter)
        {
            onMenuForm();
            offErrorForm();
        }
        if (event->key() == Qt::Key_Enter - 1)
        {
            onMenuForm();
            offErrorForm();
        }
        if (event->key() == Qt::Key_Escape)
        {
            onMenuForm();
            offErrorForm();
        }
    }
    else if (activeForms.back() == Forms::ResultForm)
    {
        if (event->key() == Qt::Key_Enter)
        {
            offMainForm();
            onMainForm();
            offResultForm();
        }
        if (event->key() == Qt::Key_Enter - 1)
        {
            offMainForm();
            onMainForm();
            offResultForm();
        }
    }
    else if (activeForms.back() == Forms::PauseForm)
    {
        if (event->key() == Qt::Key_Escape)
            offPauseForm();
        if (event->key() == Qt::Key_Enter)
            offPauseForm();
        if (event->key() == Qt::Key_Enter - 1)
            offPauseForm();
    }
    else if (activeForms.back() == Forms::MainForm)
    {
        if (event->key() == Qt::Key_Escape)
            onPauseForm();
        if (event->key() == Qt::Key_W || event->key() == 1062)
            screen->move_to_north();
        if (event->key() == Qt::Key_A || event->key() == 1060)
            screen->move_to_west();
        if (event->key() == Qt::Key_S || event->key() == 1067)
            screen->move_to_south();
        if (event->key() == Qt::Key_D || event->key() == 1042)
            screen->move_to_east();
        if (event->key() == Qt::Key_Up)
            screen->move_to_north();
        if (event->key() == Qt::Key_Left)
            screen->move_to_west();
        if (event->key() == Qt::Key_Down)
            screen->move_to_south();
        if (event->key() == Qt::Key_Right)
            screen->move_to_east();
    }

}

void MainWindow::onMainForm()
{
    activeForms.push_back(Forms::MainForm);
    qDebug() << "onMainForm";
    try
    {
        screen = new Screen(QSize(width(), height()), Character::Human);
    }
    catch(Exception &exception)
    {
        onErrorForm(exception);
        return;
    }

    QPixmap pushArrowUpButton("ResourceFiles/Textures/UpArrowPush.png");
    QPixmap relaxArrowUpButton("ResourceFiles/Textures/UpArrowRelax.png");
    arrow_up = new Button();
    arrow_up->setTexture(relaxArrowUpButton, pushArrowUpButton);
    arrow_up->setMaximumSize(width() / coef_x * size, height() / coef_y * size);
    arrow_up->setMinimumSize(width() / coef_x * size, height() / coef_y * size);

    QPixmap pushArrowLeftButton("ResourceFiles/Textures/LeftArrowPush.png");
    QPixmap relaxArrowLeftButton("ResourceFiles/Textures/LeftArrowRelax.png");
    arrow_left = new Button();
    arrow_left->setTexture(relaxArrowLeftButton, pushArrowLeftButton);
    arrow_left->setMaximumSize(width() / coef_x * size, height() / coef_y * size);
    arrow_left->setMinimumSize(width() / coef_x * size, height() / coef_y * size);

    QPixmap pushArrowRightButton("ResourceFiles/Textures/RightArrowPush.png");
    QPixmap relaxArrowRightButton("ResourceFiles/Textures/RightArrowRelax.png");
    arrow_right = new Button();
    arrow_right->setTexture(relaxArrowRightButton, pushArrowRightButton);
    arrow_right->setMaximumSize(width() / coef_x * size, height() / coef_y * size);
    arrow_right->setMinimumSize(width() / coef_x * size, height() / coef_y * size);

    QPixmap pushArrowDownButton("ResourceFiles/Textures/DownArrowPush.png");
    QPixmap relaxArrowDownButton("ResourceFiles/Textures/DownArrowRelax.png");
    arrow_down = new Button();
    arrow_down->setTexture(relaxArrowDownButton, pushArrowDownButton);
    arrow_down->setMaximumSize(width() / coef_x * size, height() / coef_y * size);
    arrow_down->setMinimumSize(width() / coef_x * size, height() / coef_y * size);


    QPixmap pushMenuButton("ResourceFiles/Textures/MiniMenuButtonPush.png");
    QPixmap relaxMenuButton("ResourceFiles/Textures/MiniMenuButtonRelax.png");
    menuButton = new Button();
    menuButton->setTexture(relaxMenuButton, pushMenuButton);
    menuButton->setMaximumSize(1000, 1000);
    menuButton->setMinimumSize(0, 0);

    baseLayout->addWidget(screen, 0, 0, coef_y, coef_x);
    baseLayout->addWidget(menuButton, 0, coef_x - 2 * size, size, size * 2);
    baseLayout->addWidget(arrow_up, coef_y - size * 3 - 1, coef_x - size * 2 - 1, size, size);
    baseLayout->addWidget(arrow_left, coef_y - size * 2 - 1, coef_x - size * 3 - 1, size, size);
    baseLayout->addWidget(arrow_right, coef_y - size * 2 - 1, coef_x - size * 1 - 1, size, size);
    baseLayout->addWidget(arrow_down, coef_y - size * 1 - 1, coef_x - size * 2 - 1, size, size);

    connect(menuButton, SIGNAL(clicked(bool)), this, SLOT(onPauseForm()));
    connect(arrow_up, SIGNAL(clicked(bool)), screen, SLOT(move_to_north()));
    connect(arrow_down, SIGNAL(clicked(bool)), screen, SLOT(move_to_south()));
    connect(arrow_right, SIGNAL(clicked(bool)), screen, SLOT(move_to_east()));
    connect(arrow_left, SIGNAL(clicked(bool)), screen, SLOT(move_to_west()));
    connect(screen, SIGNAL(Error(Exception)), this, SLOT(onErrorForm(Exception)));
    connect(screen, SIGNAL(End(Character)), this, SLOT(onResultForm(Character)));
}

void MainWindow::offMainForm()
{
    activeForms.removeOne(Forms::MainForm);
    qDebug() << "offMainForm";
    baseLayout->removeWidget(screen);
    baseLayout->removeWidget(arrow_up);
    baseLayout->removeWidget(arrow_left);
    baseLayout->removeWidget(arrow_right);
    baseLayout->removeWidget(arrow_down);
    baseLayout->removeWidget(menuButton);

    if (screen != nullptr) delete screen;
    if (arrow_up != nullptr) delete arrow_up;
    if (arrow_left != nullptr) delete arrow_left;
    if (arrow_right != nullptr) delete arrow_right;
    if (arrow_down != nullptr) delete arrow_down;
    if (menuButton != nullptr) delete menuButton;
}

void MainWindow::onPauseForm()
{
    activeForms.push_back(Forms::PauseForm);
    qDebug() << "onPauseForm";
    pauseBackground = new QWidget();
    pauseBackground->setPalette(QPalette(QColor(0, 0, 0, 190)));
    pauseBackground->setAutoFillBackground(true);

    pauseForm = new QWidget();
    pauseForm->setPalette(QPalette(QColor(20, 20, 20, 250)));
    pauseForm->setAutoFillBackground(true);

    QPixmap pushCloseButton("ResourceFiles/Textures/MenuButtonPush.png");
    QPixmap relaxCloseButton("ResourceFiles/Textures/MenuButtonRelax.png");
    closeButton = new Button();
    closeButton->setTexture(relaxCloseButton, pushCloseButton);
    closeButton->setMaximumSize(1000, 1000);
    closeButton->setMinimumSize(0, 0);

    QPixmap pushReturnButton("ResourceFiles/Textures/ContinueButtonPush.png");
    QPixmap relaxReturnButton("ResourceFiles/Textures/ContinueButtonRelax.png");
    returnButton = new Button();
    returnButton->setTexture(relaxReturnButton, pushReturnButton);
    returnButton->setMaximumSize(1000, 1000);
    returnButton->setMinimumSize(0, 0);

    baseLayout->addWidget(pauseBackground, 0, 0, coef_y, coef_x);
    baseLayout->addWidget(pauseForm, coef_y / 2 - size * 3 / 2, coef_x / 2 - size * 5 / 2, size * 7 / 2, size * 5);
    baseLayout->addWidget(returnButton, coef_y / 2 - size, coef_x / 2 - size * 2, size, size * 4);
    baseLayout->addWidget(closeButton, coef_y / 2 + size / 2, coef_x / 2 - size * 2, size, size * 4);

    connect(returnButton, SIGNAL(clicked(bool)), this, SLOT(offPauseForm()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(onMenuForm()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(offMainForm()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(offPauseForm()));
}

void MainWindow::offPauseForm()
{
    activeForms.removeOne(Forms::PauseForm);
    qDebug() << "offPauseForm";
    baseLayout->removeWidget(pauseBackground);
    baseLayout->removeWidget(pauseForm);
    baseLayout->removeWidget(closeButton);
    baseLayout->removeWidget(returnButton);

    if (pauseBackground != nullptr) delete pauseBackground;
    if (pauseForm != nullptr) delete pauseForm;
    if (closeButton != nullptr) delete closeButton;
    if (returnButton != nullptr) delete returnButton;
}

void MainWindow::onMenuForm()
{
    activeForms.push_back(Forms::MenuForm);
    qDebug() << "onMenuForm";

    QPixmap pushQuitButton("ResourceFiles/Textures/QuitButtonPush.png");
    QPixmap relaxQuitButton("ResourceFiles/Textures/QuitButtonRelax.png");
    quitButton = new Button();
    quitButton->setTexture(relaxQuitButton, pushQuitButton);
    quitButton->setMaximumSize(1000, 1000);
    quitButton->setMinimumSize(0, 0);

    QPixmap pushStartButton("ResourceFiles/Textures/NewGameButtonPush.png");
    QPixmap relaxStartButton("ResourceFiles/Textures/NewGameButtonRelax.png");
    startButton = new Button();
    startButton->setTexture(relaxStartButton, pushStartButton);
    startButton->setMaximumSize(1000, 1000);
    startButton->setMinimumSize(0, 0);

    QPixmap pixmapBackground("ResourceFiles/Textures/MenuBackground.png");
    QPalette palletBackground;
    QBrush brushBackground(pixmapBackground.scaled(width(), height()));
    menuBackground = new QWidget();
    palletBackground.setBrush(menuBackground->backgroundRole(), brushBackground);
    menuBackground->setPalette(palletBackground);
    menuBackground->setAutoFillBackground(true);

    baseLayout->addWidget(menuBackground, 0, 0, coef_y, coef_x);
    baseLayout->addWidget(startButton, coef_y / 2, size, size, size * 4);
    baseLayout->addWidget(quitButton, coef_y / 2 + size * 3 / 2, size, size, size * 4);

    connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(offMenuForm()));
    connect(startButton, SIGNAL(clicked(bool)), this, SLOT(onMainForm()));
    connect(startButton, SIGNAL(clicked(bool)), this, SLOT(offMenuForm()));
}

void MainWindow::offMenuForm()
{
    activeForms.removeOne(Forms::MenuForm);
    qDebug() << "offMenuForm";
    baseLayout->removeWidget(menuBackground);
    baseLayout->removeWidget(quitButton);
    baseLayout->removeWidget(startButton);

    if (menuBackground != nullptr) delete menuBackground;
    if (quitButton != nullptr) delete quitButton;
    if (startButton != nullptr) delete startButton;
}

void MainWindow::onErrorForm(Exception exception)
{
    activeForms.push_back(Forms::ErrorForm);
    qDebug() << "onErrorForm";

    if (activeForms.contains(Forms::MainForm)) offMainForm();
    if (activeForms.contains(Forms::MenuForm)) offMenuForm();
    if (activeForms.contains(Forms::PauseForm)) offPauseForm();
    if (activeForms.contains(Forms::ResultForm)) offResultForm();

    pauseBackground = new QWidget();
    pauseBackground->setPalette(QPalette(QColor(0, 0, 0, 230)));
    pauseBackground->setAutoFillBackground(true);

    pauseForm = new QWidget();
    pauseForm->setPalette(QPalette(QColor(100, 100, 100)));
    pauseForm->setAutoFillBackground(true);

    QPixmap pushCloseButton("ResourceFiles/Textures/MenuButtonPush.png");
    QPixmap relaxCloseButton("ResourceFiles/Textures/MenuButtonRelax.png");
    closeButton = new Button();
    closeButton->setTexture(relaxCloseButton, pushCloseButton);
    closeButton->setMaximumSize(1000, 1000);
    closeButton->setMinimumSize(0, 0);

    QString message;
    for (auto ch : exception.message) message.push_back(ch);
    errorMessage = new QLabel(message);
    errorMessage->setPalette(QPalette(QColor(0, 0, 0)));
    QFont font = errorMessage->font();
    font.setPointSize(20);
    font.setBold(true);
    errorMessage->setFont(font);

    baseLayout->addWidget(pauseBackground, 0, 0, coef_y, coef_x);
    baseLayout->addWidget(pauseForm, coef_y / 2 - size * 3 / 2, coef_x / 2 - size * 5 / 2, size * 7 / 2, size * 5);
    baseLayout->addWidget(errorMessage, coef_y / 2 - size / 2, coef_x / 2 - size * 2);
    baseLayout->addWidget(closeButton, coef_y / 2 + size / 2, coef_x / 2 - size * 2, size, size * 4);

    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(onMenuForm()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(offErrorForm()));
}

void MainWindow::offErrorForm()
{
    activeForms.removeOne(Forms::ErrorForm);
    qDebug() << "offErrorForm";
    baseLayout->removeWidget(pauseBackground);
    baseLayout->removeWidget(pauseForm);
    baseLayout->removeWidget(closeButton);
    baseLayout->removeWidget(errorMessage);

    if (errorMessage != nullptr) delete errorMessage;
    if (pauseBackground != nullptr) delete pauseBackground;
    if (pauseForm != nullptr) delete pauseForm;
    if (closeButton != nullptr) delete closeButton;
}

void MainWindow::onResultForm(Character winner)
{
    activeForms.push_back(Forms::ResultForm);
    qDebug() << "onResultForm";
    pauseBackground = new QWidget();
    pauseBackground->setPalette(QPalette(QColor(0, 0, 0, 230)));
    pauseBackground->setAutoFillBackground(true);

    pauseForm = new QWidget();
    pauseForm->setPalette(QPalette((winner == Character::Minotavr) ? Qt::GlobalColor::red : Qt::GlobalColor::green));
    pauseForm->setAutoFillBackground(true);

    QPixmap pushCloseButton("ResourceFiles/Textures/MenuButtonPush.png");
    QPixmap relaxCloseButton("ResourceFiles/Textures/MenuButtonRelax.png");
    closeButton = new Button();
    closeButton->setTexture(relaxCloseButton, pushCloseButton);
    closeButton->setMaximumSize(1000, 1000);
    closeButton->setMinimumSize(0, 0);

    QPixmap pushReturnButton("ResourceFiles/Textures/ContinueButtonPush.png");
    QPixmap relaxReturnButton("ResourceFiles/Textures/ContinueButtonRelax.png");
    returnButton = new Button();
    returnButton->setTexture(relaxReturnButton, pushReturnButton);
    returnButton->setMaximumSize(1000, 1000);
    returnButton->setMinimumSize(0, 0);

    baseLayout->addWidget(pauseBackground, 0, 0, coef_y, coef_x);
    baseLayout->addWidget(pauseForm, coef_y / 2 - size * 3 / 2, coef_x / 2 - size * 5 / 2, size * 7 / 2, size * 5);
    baseLayout->addWidget(returnButton, coef_y / 2 - size, coef_x / 2 - size * 2, size, size * 4);
    baseLayout->addWidget(closeButton, coef_y / 2 + size / 2, coef_x / 2 - size * 2, size, size * 4);

    connect(returnButton, SIGNAL(clicked(bool)), this, SLOT(offMainForm()));
    connect(returnButton, SIGNAL(clicked(bool)), this, SLOT(onMainForm()));
    connect(returnButton, SIGNAL(clicked(bool)), this, SLOT(offResultForm()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(onMenuForm()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(offMainForm()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(offResultForm()));
}

void MainWindow::offResultForm()
{
    activeForms.removeOne(Forms::ResultForm);
    qDebug() << "offResultForm";
    baseLayout->removeWidget(pauseBackground);
    baseLayout->removeWidget(pauseForm);
    baseLayout->removeWidget(closeButton);
    baseLayout->removeWidget(returnButton);

    if (pauseBackground != nullptr) delete pauseBackground;
    if (pauseForm != nullptr) delete pauseForm;
    if (closeButton != nullptr) delete closeButton;
    if (returnButton != nullptr) delete returnButton;
}
