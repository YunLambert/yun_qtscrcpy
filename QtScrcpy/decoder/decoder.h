#ifndef DECODER_H
#define DECODER_H

extern "C"  //C++中包含C
{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
}

class Decoder
{
public:
    Decoder();

    static bool init();
};

#endif // DECODER_H
