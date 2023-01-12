#ifndef MAINBUTTONS_H
#define MAINBUTTONS_H
#include <QWidget>
#include <QPushButton>
#include <QVector>

#include "AboutWindow.h"
#include "ChooseSampleWindow.h"

class MainButtons : public QWidget
{
	Q_OBJECT
	public:
		MainButtons(QWidget *parent=0);
		~MainButtons();

	private:
        void init();
        
    protected:
        QPushButton *m_about_btn;
        QPushButton *m_chooseSample_btn;
        QPushButton *m_clear_btn;
        QPushButton *m_quit_btn;
        QPushButton *m_reset_btn;
        
        AboutWindow *aboutwindow;
        ChooseSampleWindow *choosesamplewindow;
        QVector<QWidget*> m_buttons;
    
    public slots:
        void aboutSlot();
        void chooseSampleSlot();
        void resetSlot();
        void clearSlot();
        void quitSlot();

        
    signals:
        void quit();

    
        
	//private slots:
        
};


#endif
