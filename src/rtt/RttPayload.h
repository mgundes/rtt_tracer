//
// Created by mgundes on 14.02.2016.
//

#ifndef NETWORK_DIAGNOSTICS_RTTPAYLOAD_H
#define NETWORK_DIAGNOSTICS_RTTPAYLOAD_H

#include <chrono>

class RttPayload {
public:
    RttPayload(long sequenceNumber);
    RttPayload();

    long getSequenceNumber() const {
        return _sequenceNumber;
    }

    void setSequenceNumber(long sequenceNumber) {
        RttPayload::_sequenceNumber = sequenceNumber;
    }

    long getTimeInMS() const {
        return _timeInMS;
    }

    void setTimeInMS(long timeInMS) {
        RttPayload::_timeInMS = timeInMS;
    }

private:
    long _timeInMS;
    long _sequenceNumber;
};


#endif //NETWORK_DIAGNOSTICS_RTTPAYLOAD_H
