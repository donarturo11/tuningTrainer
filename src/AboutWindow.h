#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QtGui>
#ifndef __APPLE__
#include <QApplication>
#endif
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
//class QPushButton;

class AboutWindow : public QDialog
{
	Q_OBJECT
	public:
		explicit AboutWindow(QWidget *parent=0);
        
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


#endif // ABOUTWINDOW_H
