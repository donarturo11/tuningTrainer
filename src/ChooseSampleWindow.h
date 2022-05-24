#ifndef CHOOSESAMPLEWINDOW_H
#define CHOOSESAMPLEWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>


//#include "MainWindow.h"
//class QPushButton;
class MainWindow;

class ChooseSampleWindow : public QDialog
{
	Q_OBJECT
	public:
		explicit ChooseSampleWindow(QWidget *parent=0);
        void init();
        QString getWavepath();
        QPushButton *m_quit_btn;
        QLabel *m_label;
        
    
	private:
        void setString();
        QLineEdit *m_waveurl;
        QPushButton *m_browse_btn;
        QPushButton *m_apply_btn;
        QPushButton *m_cancel_btn;
        QString wavepath;
        
    protected:
        QString label_str="";
        QWidget *parentClass;
    
    public slots:
        void quitSlot();
        void browseSlot();
        void applySlot();
        
    signals:
        
        
	//private slots:
        
};


#endif // CHOOSESAMPLEWINDOW_H
