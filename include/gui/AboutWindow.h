#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

//#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include "MainWindow.h"
//class QPushButton;
namespace GUI {
class AboutWindow : public QDialog
{
    Q_OBJECT
    public:
  	AboutWindow(QWidget *parent=0);
		
        QPushButton *m_quit_btn;
        QLabel *m_label;
        
    
    private:
        void setAboutString();
        
    protected:
        QString label_str="";
    
    public slots:
        
    signals:
        
        
	//private slots:
        
};
} // namespace GUI

#endif // ABOUTWINDOW_H
