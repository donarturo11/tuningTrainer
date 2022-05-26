#ifndef CHOOSESAMPLEWINDOW_H
#define CHOOSESAMPLEWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>


//#include "MainWindow.h"
//class QPushButton;
class MainWindow;

class ChooseSampleWindow : public QDialog
{
	Q_OBJECT
	public:
		ChooseSampleWindow(QWidget *parent, QString wavepath);
        void init();
        void setWavepath(QString path);
        QString getWavepath();
        QPushButton *m_quit_btn;
        QLabel *m_label;
        
    
	private:
        void setString();
        QLineEdit *m_waveurl;
        QPushButton *m_browse_btn;
        QPushButton *m_apply_btn;
        QPushButton *m_cancel_btn;
        QLabel *m_baseFreq_label;
        QSpinBox *m_baseFreq_spin;
        
        QString wavepath;
        int baseFreq;
        
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
