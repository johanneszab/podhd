#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialogabout.h"
#include "ui_dialogabout.h"

//#include <cmath>
//#include <cstdlib>

#include <QMainWindow>
#include <QDir>
#include <QList>
#include <QCheckBox>
#include <QFileDialog>
#include <QDebug>
#include <QStringList>
#include <QFile>

#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool getFiles(QDir dir, QList<QStringList> fileFilter);
    void copyModify();
    void copyConvert(QList<QCheckBox*> chkbx);
    bool copyFiles(QDir source, QStringList files, const bool override);
    void rename(QList<QCheckBox*> chkbx, QString pressedFrom);
    bool renameFiles(QDir source, QStringList files, QStringList extension);
    void convert(QString pressedFrom);
    void modify(QString pressedFrom);

    void processSettings(QString pressedFrom);
    void processChangeAmps();
    void switchPreAmps();

    void convertPresetFiles(QStringList presetFiles, QString pressedFrom);
    void convertBundleFiles(QStringList presetFiles, QString pressedFrom);
    void convertSetlistFiles(QStringList presetFiles, QString pressedFrom);

    void translatePresetFiles(QDir source, QStringList files, QStringList extension, const bool override);

    void modifyPresetFiles(QStringList files);
    void modifyBundleFiles(QStringList files);
    void modifySetlistFiles(QStringList files);

    void changeAmps(QString pressedFrom);
    void changePresetFilesAmps(QHash<char,char> &amps, QStringList files);
    void changeBundleFilesAmps(QHash<char,char> &amps, QStringList files);
    void changeSetlistFilesAmps(QHash<char,char> &amps, QStringList files);

    //void convertPresetFilesInputs(const QHash<char, char> &inputs = QHash<char, char>(), QStringList files);
    //void convertBundleFilesInputs(const QHash<char, char> &inputs = QHash<char, char>(), QStringList files);
    //void convertSetlistFilesInputs(const QHash<char, char> &inputs = QHash<char, char>(), QStringList files);

    void convertPresetFilesInputs(QHash<char, char> &inputs, QStringList files);
    void convertBundleFilesInputs(QHash<char, char> &inputs, QStringList files);
    void convertSetlistFilesInputs(QHash<char, char> &inputs, QStringList files);

    void changeTextDesktop();
    void changeText300();
    void changeText500();
    void changeTextPro();

    bool poti(QFile &sourceFile, QFile &targetFile, int sourcePosition, int targetPosition);
    bool potiDecibel(QFile &sourceFile, QFile &targetFile, int sourcePosition, int targetPosition);
    bool potiReversed(QFile &sourceFile, QFile &targetFile, int sourcePosition, int targetPosition);
    bool potiByte(QFile &sourceFile, QFile &targetFile, int sourcePosition, int targetPosition);


private:
    Ui::MainWindow *ui;

public slots:
    void getPath();
    void runDesktop();
    void onTextEdit(QString path);
    void openDialogAbout();
    void run300();
    void run500();
    void runPro();
    void changePage300();
    void changePage400();
};

#endif // MAINWINDOW_H
