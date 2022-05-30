#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "fstream"
#include "Playlist.h"
#include "Song.h"
#include "JSON.hpp"
#include "Menu.h"
#include<QDebug>

#define NUME_DB "db.json"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    menu::GetInstance().playlist.nume = NUME_DB;

    menu::GetInstance().playlist.ReadSongs();

    ui->comboBox->addItem("Index");
    ui->comboBox->addItem("ISMN");

    ui->actionCombo->addItem("Update");
    ui->actionCombo->addItem("Remove");
    ui->actionCombo->addItem("Add");

    //ui->tableWidget->setSelectionBehavior( QAbstractItemView::SelectItems );
    ui->tableWidget->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget->setColumnCount(10);

    MainWindow::RefreshTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->clearContents();

    menu::GetInstance().playlist.ReadSongs();

    ui->tableWidget->setRowCount(menu::GetInstance().playlist.GetSize());

    int _index=0;

    for (auto& song : menu::GetInstance().playlist.GetSongs()) {

        QTableWidgetItem *songId = new QTableWidgetItem(QString::number(_index));
        QTableWidgetItem *ismn = new QTableWidgetItem(QString::fromStdString(song.getISMN()));
        QTableWidgetItem *title = new QTableWidgetItem(QString::fromStdString(song.getTitle()));
        QTableWidgetItem *artist = new QTableWidgetItem(QString::fromStdString(song.getArtist()));
        QTableWidgetItem *genre = new QTableWidgetItem(QString::fromStdString(song.getGenre()));
        QTableWidgetItem *album = new QTableWidgetItem(QString::fromStdString(song.getAlbum()));
        QTableWidgetItem *streams = new QTableWidgetItem(QString::number(song.getStreams()));
        QTableWidgetItem *rating = new QTableWidgetItem(QString::number(song.getRating()));
        QTableWidgetItem *duration = new QTableWidgetItem(QString::number(song.getDuration()));
        QTableWidgetItem *year = new QTableWidgetItem(QString::number(song.getYear()));

        ui->tableWidget->setItem(_index, 0, songId);
        ui->tableWidget->setItem(_index, 1, ismn);
        ui->tableWidget->setItem(_index, 2, title);
        ui->tableWidget->setItem(_index, 3, artist);
        ui->tableWidget->setItem(_index, 4, genre);
        ui->tableWidget->setItem(_index, 5, album);
        ui->tableWidget->setItem(_index, 6, streams);
        ui->tableWidget->setItem(_index, 7, rating);
        ui->tableWidget->setItem(_index, 8, duration);
        ui->tableWidget->setItem(_index, 9, year);

        _index++;
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    menu::GetInstance().playlist.SaveSongs();
    MainWindow::on_pushButton_clicked();
}

void MainWindow::RefreshTable()
{
    ui->tableWidget->clearContents();

    ui->tableWidget->setRowCount(menu::GetInstance().playlist.GetSize());

    int _index=0;

    for (auto& song : menu::GetInstance().playlist.GetSongs()) {

        if(_index > menu::GetInstance().playlist.GetSize() - 1) break;

        QTableWidgetItem *songId = new QTableWidgetItem(QString::number(_index));
        QTableWidgetItem *ismn = new QTableWidgetItem(QString::fromStdString(song.getISMN()));
        QTableWidgetItem *title = new QTableWidgetItem(QString::fromStdString(song.getTitle()));
        QTableWidgetItem *artist = new QTableWidgetItem(QString::fromStdString(song.getArtist()));
        QTableWidgetItem *genre = new QTableWidgetItem(QString::fromStdString(song.getGenre()));
        QTableWidgetItem *album = new QTableWidgetItem(QString::fromStdString(song.getAlbum()));
        QTableWidgetItem *streams = new QTableWidgetItem(QString::number(song.getStreams()));
        QTableWidgetItem *rating = new QTableWidgetItem(QString::number(song.getRating()));
        QTableWidgetItem *duration = new QTableWidgetItem(QString::number(song.getDuration()));
        QTableWidgetItem *year = new QTableWidgetItem(QString::number(song.getYear()));

        ui->tableWidget->setItem(_index, 0, songId);
        ui->tableWidget->setItem(_index, 1, ismn);
        ui->tableWidget->setItem(_index, 2, title);
        ui->tableWidget->setItem(_index, 3, artist);
        ui->tableWidget->setItem(_index, 4, genre);
        ui->tableWidget->setItem(_index, 5, album);
        ui->tableWidget->setItem(_index, 6, streams);
        ui->tableWidget->setItem(_index, 7, rating);
        ui->tableWidget->setItem(_index, 8, duration);
        ui->tableWidget->setItem(_index, 9, year);

        //qDebug() << "--" << _index << "--" << song.getTitle().c_str();

        _index++;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    MainWindow::RefreshTable();
}


void MainWindow::on_updateBtn_clicked()
{

    if(ui->actionCombo->currentText() == "Update")
    {
        if(ui->target->text().isEmpty() || ui->newIsmn->text().isEmpty() || ui->newTitle->text().isEmpty() || ui->newArtist->text().isEmpty() || ui->newGenre->text().isEmpty() || ui->newAlbum->text().isEmpty()) return;

        menu::GetInstance().actions.add_state(menu::GetInstance().playlist);
        MainWindow::enableUndoBtn(false);

        std::string newismn = ui->newIsmn->text().toStdString();
        std::string newtitle = ui->newTitle->text().toStdString();
        std::string newartist = ui->newArtist->text().toStdString();
        std::string newgenre = ui->newGenre->text().toStdString();
        std::string newalbum = ui->newAlbum->text().toStdString();

        Song s = Song(newismn,newtitle,newartist,newgenre,newalbum,ui->newStreams->value(),ui->newRating->value(),ui->newDuration->value(),ui->newYear->value());

        if(ui->comboBox->currentText() == "Index")
        {
            menu::GetInstance().playlist.UpdateSongByIndexDirect(ui->target->text().toInt(),s);
        }
        else if(ui->comboBox->currentText() == "ISMN")
        {
            std::string targg =ui->target->text().toStdString();
            menu::GetInstance().playlist.UpdateSongByIsmnDirect(targg,s);
        }
    }

    if(ui->actionCombo->currentText() == "Remove")
    {
        if(ui->target->text().isEmpty()) return;
        MainWindow::enableUndoBtn(false);

        menu::GetInstance().actions.add_state(menu::GetInstance().playlist);

        if(ui->comboBox->currentText() == "Index")
        {
            menu::GetInstance().playlist.DeleteSongByIndex(ui->target->text().toInt());
        }
        else if(ui->comboBox->currentText() == "ISMN")
        {
            std::string targg =ui->target->text().toStdString();
            menu::GetInstance().playlist.DeleteSongByIsmn(targg);
        }

    }

    if(ui->actionCombo->currentText() == "Add")
    {
        if(ui->newIsmn->text().isEmpty() || ui->newTitle->text().isEmpty() || ui->newArtist->text().isEmpty() || ui->newGenre->text().isEmpty() || ui->newAlbum->text().isEmpty()) return;

        menu::GetInstance().actions.add_state(menu::GetInstance().playlist);
        MainWindow::enableUndoBtn(false);

        std::string newismn = ui->newIsmn->text().toStdString();
        std::string newtitle = ui->newTitle->text().toStdString();
        std::string newartist = ui->newArtist->text().toStdString();
        std::string newgenre = ui->newGenre->text().toStdString();
        std::string newalbum = ui->newAlbum->text().toStdString();

        Song temp = Song(newismn,newtitle,newartist,newgenre,newalbum,ui->newStreams->value(),ui->newRating->value(),ui->newDuration->value(),ui->newYear->value());

        menu::GetInstance().playlist.append(temp);
    }


    MainWindow::RefreshTable();
}

void MainWindow::on_actionCombo_currentIndexChanged(int index)
{
    bool disabled = true;
    if(index == 0)
    {
        ui->executeLbl->setText("Song By");
        ui->comboBox->setDisabled(!disabled);
        ui->target->setDisabled(!disabled);
        ui->newIsmn->setDisabled(!disabled);
        ui->newTitle->setDisabled(!disabled);
        ui->newArtist->setDisabled(!disabled);
        ui->newGenre->setDisabled(!disabled);
        ui->newAlbum->setDisabled(!disabled);
        ui->newStreams->setDisabled(!disabled);
        ui->newRating->setDisabled(!disabled);
        ui->newDuration->setDisabled(!disabled);
        ui->newYear->setDisabled(!disabled);
    }
    if(index == 1)
    {
        ui->executeLbl->setText("Song By");
        ui->comboBox->setDisabled(!disabled);
        ui->target->setDisabled(!disabled);

        ui->newIsmn->setDisabled(disabled);
        ui->newTitle->setDisabled(disabled);
        ui->newArtist->setDisabled(disabled);
        ui->newGenre->setDisabled(disabled);
        ui->newAlbum->setDisabled(disabled);
        ui->newStreams->setDisabled(disabled);
        ui->newRating->setDisabled(disabled);
        ui->newDuration->setDisabled(disabled);
        ui->newYear->setDisabled(disabled);
    }
    if(index == 2)
    {
        ui->executeLbl->setText("Song");
        ui->comboBox->setDisabled(disabled);
        ui->target->setDisabled(disabled);
        ui->newIsmn->setDisabled(!disabled);
        ui->newTitle->setDisabled(!disabled);
        ui->newArtist->setDisabled(!disabled);
        ui->newGenre->setDisabled(!disabled);
        ui->newAlbum->setDisabled(!disabled);
        ui->newStreams->setDisabled(!disabled);
        ui->newRating->setDisabled(!disabled);
        ui->newDuration->setDisabled(!disabled);
        ui->newYear->setDisabled(!disabled);
    }
}


void MainWindow::on_listenSong_clicked()
{
    if(ui->tableWidget->selectedItems().empty()) return;
    int _target = ui->tableWidget->currentItem()->row();
    if(menu::GetInstance().playlist.ListenToSongByIndex(_target))
        return;
    else MainWindow::RefreshTable();
}

void MainWindow::enableUndoBtn(bool enabled)
{
    ui->undoBtn->setDisabled(enabled);
}

void MainWindow::enableRedoBtn(bool enabled)
{
    ui->redoBtn->setDisabled(enabled);
}

void MainWindow::on_undoBtn_clicked()
{
    MainWindow::enableRedoBtn(false);
    menu::GetInstance().actions.undo(menu::GetInstance().playlist);
    MainWindow::RefreshTable();
}


void MainWindow::on_redoBtn_clicked()
{
    menu::GetInstance().actions.redo(menu::GetInstance().playlist);
    MainWindow::RefreshTable();
}

