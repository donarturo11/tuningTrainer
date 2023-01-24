#include "gui/WaveLoader.h"
namespace GUI {
WaveLoader::WaveLoader(QWidget *parent, unsigned int samplerate, unsigned int nChannels)
    : QWidget{parent}
{
    qDebug() << "AudioLoader c-tor";
    _finished = false;
    _samplerate = samplerate;
    _nChannels = nChannels;    
    init();
}

WaveLoader::~WaveLoader()
{
    qDebug() << "AudioLoader d-tor";
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
    connect(_decoder, SIGNAL(finished()), this, SLOT(finishedSlot()));
    connect(_decoder, SIGNAL(isDecodingChanged(bool)), this, SLOT(decodingChanged(bool)));
}

void WaveLoader::load(QString filename)
{
    if (!_decoder) return;
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
#endif
    format.setSampleRate(_samplerate);
    return format;    
}

void WaveLoader::readBuffer()
{
    qDebug() << "Read buffer";
    const QAudioBuffer &buffer = _decoder->read();
    const int nFrames = buffer.frameCount();
    const float* data = buffer.constData<float>();
    for (int i=0; i<nFrames; i++)
        _samples.push_back(data[i]);
}

void WaveLoader::finishedSlot()
{
    qDebug() << "Finished slot";
    clear();
}

void WaveLoader::clear()
{
    qDebug() << "clear";
}

void WaveLoader::decodingChanged(bool b)
{
    if (!b) {
        _decoder->stop();
        _finished = true;
        emit finished();
        emit sendWave(_samples);
        qDebug() << "finished";
    }
    //_decoder->stop();
}

} // namespace GUI