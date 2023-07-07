#ifndef FREQUENCYCONTROLLER_H
#define FREQUENCYCONTROLLER_H
#include <QWidget>
#include <QDoubleSpinBox>
#include <QDial>
#include <QVBoxLayout>
class QWidget;
class QDoubleSpinBox;
class QDial;
namespace GUI {

class FrequencyController : public QWidget
{
Q_OBJECT
public:
    inline static int index = 0;
    inline static int position_x = 0;
    FrequencyController(bool semitone = false, QWidget* parent=0);
    ~FrequencyController();
    void init();
    int getIndex() { return _index; };
    float getFrequency() { return _frequency; }
    void setFrequency(float freq);
private slots:
    void onSpinValueChanged(double value);
    void onDialValueChanged(int value);
signals:
    void frequencyChanged(int index, double freq);
protected:
    int _pos_x;
    int _index;
    QDial *m_dial;
    QDoubleSpinBox *m_spin;
    QVBoxLayout *m_layout;
    bool semitoneKey;
    const int freq_min=32.00;
    const int freq_max=2048.00;
    float _frequency;
};

} // namespace GUI
#endif // FREQUENCYCONTROLLER_H
