#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    M_Player = std::make_unique<QMediaPlayer>(this);
    A_Output = std::make_unique<QAudioOutput>(this);

    M_Player->setAudioOutput(A_Output.get());

    connect(M_Player.get(),&QMediaPlayer::durationChanged,this,&MainWindow::onDurationChanged);
    connect(M_Player.get(),&QMediaPlayer::positionChanged,this,&MainWindow::onPositionChanged);
    connect(ui->audio_duration, &QSlider::valueChanged, this, &MainWindow::on_audio_duration_valueChanged);


    ui->play_pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->audio_forward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->audio_backward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->mute_unmute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool IS_PAUSE=false;

void MainWindow::on_play_pause_clicked()
{

    if(IS_PAUSE == false){
        ui->play_pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        M_Player->pause();
        IS_PAUSE=true;
    }
    else{
        ui->play_pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        M_Player->play();
        IS_PAUSE=false;
    }
}

bool IS_MUTED=false;

void MainWindow::on_mute_unmute_clicked()
{
    if(IS_MUTED == false){
        ui->mute_unmute->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        A_Output->setMuted(true);
        IS_MUTED=true;
    }
    else{
        ui->mute_unmute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        A_Output->setMuted(false);
        IS_MUTED=false;
    }
}


void MainWindow::on_audio_backward_clicked()
{

}


void MainWindow::on_audio_forward_clicked()
{

}

void MainWindow::on_actionOpen_File_triggered()
{
    QString File=QFileDialog::getOpenFileName(this,tr("Select audio file"),"",tr("MP3 Files (*.mp3);;All Files(*)"));

    M_Player->setSource(QUrl(File));

    QFileInfo fileinfo(File);
    ui->file_name->setText(fileinfo.fileName());
}

void MainWindow::onDurationChanged(qint64 duration){
    ui->audio_duration->setRange(0,static_cast<int>(duration));
    qDebug() << "Duration: " << duration;

    ui->totalTime->setText(formatTime(duration));
}

void MainWindow::onPositionChanged(qint64 position){
    ui->audio_duration->blockSignals(true);
    ui->audio_duration->setValue(static_cast<int>(position));
    qDebug() << "Position: " << position;
    ui->audio_duration->blockSignals(false);

    ui->currentTime->setText(formatTime(position));
}

void MainWindow::on_audio_duration_valueChanged(int value)
{
    M_Player->setPosition(static_cast<qint64>(value));
}

void MainWindow::on_audio_volume_valueChanged(int value)
{
    A_Output->setVolume(value/100.0);
}

QString MainWindow::formatTime(qint64 timeInMs)
{
    int seconds = (timeInMs / 1000) % 60;
    int minutes = (timeInMs / (1000 * 60)) % 60;

    return QTime(0, minutes, seconds).toString("mm:ss");
}




