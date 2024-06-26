#include "gui/WaveLoader.h"
namespace GUI {
WaveLoader::WaveLoader(QWidget *parent, unsigned int samplerate, unsigned int nChannels)
    : QWidget{parent}
{
    #ifdef DEBUG
    qDebug() << "AudioLoader c-tor";
    #endif
    _finished = false;
    _samplerate = samplerate;
    _nChannels = nChannels;    
    init();
}

WaveLoader::~WaveLoader()
{
#ifdef DEBUG
    qDebug() << "AudioLoader d-tor";
#endif
    if (_audioFile->isOpen())
        _audioFile->close();
    if (_decoder)
        delete _decoder;
    if (_audioFile)
        delete _audioFile;
}

void WaveLoader::init()
{
    qDebug() << "Init";
    auto format = getAudioFormat();
    
    _decoder = new QAudioDecoder(this);
    _decoder->setAudioFormat (format);
    
    connect(_decoder, SIGNAL(bufferReady()), this, SLOT(readBuffer()));
#ifdef QT6
    connect(_decoder, SIGNAL(isDecodingChanged(bool)), this, SLOT(decodingChanged(bool)));
#endif
#ifdef QT5
    connect(_decoder, SIGNAL(stateChanged(QAudioDecoder::State)), this, SLOT(decodingChanged(QAudioDecoder::State)));
#endif
}

void WaveLoader::load(QString filename)
{
    _audioFile = new QFile(filename, this);
    _audioFile->open(QIODevice::ReadOnly);
    _decoder->setSourceDevice(_audioFile);
    _decoder->start();
}

QAudioFormat WaveLoader::getAudioFormat()
{
    QAudioFormat format;
    format.setChannelCount(_nChannels);
#ifdef QT6
    format.setSampleFormat(QAudioFormat::Float);
#endif
#ifdef QT5
    format.setSampleType(QAudioFormat::Float);
    format.setSampleSize(32);
    format.setCodec("audio/x-wav");
#endif
    format.setSampleRate(_samplerate);
    return format;    
}

void WaveLoader::readBuffer()
{
    const QAudioBuffer &buffer = _decoder->read();
    const int nFrames = buffer.frameCount();
    const float* data = buffer.constData<float>();
    for (int i=0; i<nFrames; i++)
        _samples.push_back(data[i]);
}

void WaveLoader::finishedSlot()
{
#ifdef DEBUG
    qDebug() << "Finished slot";
#endif
    clear();
}

void WaveLoader::clear()
{
#ifdef DEBUG
    qDebug() << "clear";
#endif
    _decoder->stop();
    _audioFile->close();
}

#ifdef QT6
void WaveLoader::decodingChanged(bool b)
#endif
#ifdef QT5
void WaveLoader::decodingChanged(QAudioDecoder::State b)
#endif
{
    if (!b) {
        _finished = true;
        emit sendWave(_samples);
        emit finished();
#ifdef DEBUG
        qDebug() << "finished";
        qDebug() << "_samples size" << _samples.size();
#endif
    }
    //_decoder->stop();
}

} // namespace GUI
