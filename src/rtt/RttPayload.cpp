//
// Created by mgundes on 14.02.2016.
//

#include "RttPayload.h"
#include "../utils/TimeUtils.h"

RttPayload::RttPayload(long sequenceNumber)
    : _sequenceNumber(sequenceNumber), _remoteTimeInMS(0)
{
    _localTimeInMS = TimeUtils::getSystemTimeInMilliseconds();
}

RttPayload::RttPayload()
    : _sequenceNumber(0), _localTimeInMS(0), _remoteTimeInMS(0)
{

}