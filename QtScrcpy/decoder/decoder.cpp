#include "decoder.h"

Decoder::Decoder()
{

}

bool Decoder::init()
{
    if(avformat_network_init()) {
        return false;
    }
    return true;
}
