//
// Created by mgundes on 14.02.2016.
//

#include "RttPayload.h"
#include "../utils/TimeUtils.h"

RttPayload::RttPayload(long sequenceNumber)
    : _sequenceNumber(sequenceNumber)
{
    _timeInMS = TimeUtils::getSystemTimeInMilliseconds();
}

RttPayload::RttPayload()
    : _sequenceNumber(0), _timeInMS(0)
{

}