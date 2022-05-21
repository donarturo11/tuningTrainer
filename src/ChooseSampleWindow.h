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
//class QPushButton;

class ChooseSampleWindow : public QDialog
{
	Q_OBJECT
	public:
		explicit ChooseSampleWindow(QWidget *parent=0);
        
        QPushButton *m_quit_btn;
        QLabel *m_label;
        
    
	private:
        void setString();
        
    protected:
        QString label_str="";
    
    public slots:
        
    signals:
        
        
	//private slots:
        
};


#endif // CHOOSESAMPLEWINDOW_H
