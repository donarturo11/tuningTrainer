#ifndef MAINBUTTONS_H
#define MAINBUTTONS_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>

#include "MainWindow.h"

namespace GUI {
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
        QVBoxLayout *m_buttons_layout;
        QCheckBox* toggleDebug;
            
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
} // namespace GUI

#endif
