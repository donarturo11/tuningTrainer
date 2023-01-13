#ifndef MAINBUTTONS_H
#define MAINBUTTONS_H
#include <QWidget>
#include <QPushButton>

#include "gui/AboutWindow.h"
#include "gui/ChooseSampleWindow.h"
#include "MainWindow.h"

class AboutWindow;

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
    
    public slots:
        void aboutSlot();
        void chooseSampleSlot();
        void resetSlot();
        void clearSlot();
        void quitSlot();

    signals:
        void quit();
        void clear();
        void reset();

    
        
	//private slots:
        
};


#endif
