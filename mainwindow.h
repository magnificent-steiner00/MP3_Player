#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMediaPlayer>
#include<QWidget>
#include<QStyle>
#include<QFileDialog>
#include<QAudioOutput>
#include<QDebug>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_play_pause_clicked();

    void on_mute_unmute_clicked();

    void on_actionOpen_File_triggered();

    void on_audio_duration_valueChanged(int value);

    void on_audio_volume_valueChanged(int value);

    void on_audio_backward_clicked();

    void on_audio_forward_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<QMediaPlayer>M_Player;
    std::unique_ptr<QAudioOutput>A_Output;
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    QString formatTime(qint64 timeInMs);

};
#endif // MAINWINDOW_H
