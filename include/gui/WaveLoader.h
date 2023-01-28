#ifndef WAVELOADER_H
#define WAVELOADER_H

#include <QWidget>
#include <QFile>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <QAudioBuffer>
#include <QBuffer>
#include <QUrl>
#include <QFloat16>
#include <vector>
#include <iostream>

namespace GUI { 
class WaveLoader : public QWidget
{
    Q_OBJECT
public:
    WaveLoader(QWidget *parent = nullptr, unsigned int samplerate = 44100, unsigned int nChannels=1);
    ~WaveLoader();
    void load(QString filename);
    std::vector <float> getSamples(){ return _samples; }
private:
    void init();
    void clear();
    QAudioFormat getAudioFormat();
signals:
    void finished();
    void sendWave(std::vector <float> wave);

public slots:
    void readBuffer();
    void finishedSlot();
#ifdef QT6
    void decodingChanged(bool b);
#endif
#ifdef QT5
    void decodingChanged(QAudioDecoder::State b);
#endif
protected:
    unsigned int _samplerate;
    unsigned int _nChannels;
    bool _finished;
    QFile* _audioFile;
    QAudioDecoder* _decoder;
    QBuffer _input;
    QBuffer _output;
    QByteArray _data;
    std::vector <float> _samples;
};
} // namespace GUI
#endif // AUDIOLOADER_H
