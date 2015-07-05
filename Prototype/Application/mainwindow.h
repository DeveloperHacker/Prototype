#ifndef TEST_H
#define TEST_H

#include <QMainWindow>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>

#include "Application/button.h"
#include "Application/screen.h"

enum class Forms {MainForm, MenuForm, PauseForm, ErrorForm, ResultForm};
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    static const auto coef_x = 128;
    static const auto coef_y = 72;
    static const auto size = 10;

private:
    QWidget *centralWidget;
    QGridLayout *baseLayout;
    QWidget *sceleton;
    QList<Forms> activeForms;

private: // MainWindow
    Screen *screen;
    Button *arrow_up;
    Button *arrow_left;
    Button *arrow_right;
    Button *arrow_down;
    Button *menuButton;

private: // Pause
    QWidget *pauseBackground;
    QWidget *pauseForm;
    Button *closeButton;
    Button *returnButton;

private: //Menu
    QWidget *menuBackground;
    Button *quitButton;
    Button *startButton;

private: //Error
    QLabel *errorMessage;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

protected:
    void keyPressEvent(QKeyEvent *);

public slots:
    void onMainForm();
    void offMainForm();
    void onPauseForm();
    void offPauseForm();
    void onMenuForm();
    void offMenuForm();
    void onErrorForm(Exception);
    void offErrorForm();
    void onResultForm(Character);
    void offResultForm();
};

#endif // TEST_H
