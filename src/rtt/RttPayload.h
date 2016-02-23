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

    long getLocalTimeInMS() const {
        return _localTimeInMS;
    }

    long getRemoteTimeInMS() const {
        return _remoteTimeInMS;
    }

    void setLocalTimeInMS(long timeInMS) {
        RttPayload::_localTimeInMS = timeInMS;
    }

    void setRemoteTimeInMS(long timeInMS) {
        RttPayload::_remoteTimeInMS = timeInMS;
    }

private:
    long _localTimeInMS;
    long _remoteTimeInMS;
    long _sequenceNumber;
};


#endif //NETWORK_DIAGNOSTICS_RTTPAYLOAD_H
