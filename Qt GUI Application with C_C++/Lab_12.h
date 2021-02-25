#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab_12.h"
#include "Service.h"

class Lab_12 : public QMainWindow
{
    Q_OBJECT

public:
    Lab_12(Saved_Repository& savedRepo, Service& serv, QWidget *parent = Q_NULLPTR);

private:
    Ui::Lab_12Class ui;
    Service& service;
    Saved_Repository& savedRepository;

    // initialization -----------   
    void populateList();     // |
    void makeConnections();  // |
    // --------------------------


    // Settings -----------------    
    void setMode();          // |
    void setRepository();    // |
    // --------------------------


    // Mode A -------------------
    void deleteRecording();  // |
    int getSelectedIndex();  // |
    void addRecording();     // |
    void updateRecording();  // |
    void filterRecordings(); // |
    void listRecordings();   // |
    void undo();             // |
    void redo();             // |
    // --------------------------


    // Mode B --------------------
    void saveRecording();     // |
    void nextRecording();     // |
    void myListRecordings();  // |
    int getSelectedForSave(); // |
    // ---------------------------
};
