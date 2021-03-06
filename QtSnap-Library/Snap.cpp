#include "Snap.h"

//ALWAYS
const QString Snap::ID_KEY = "id";
const QString Snap::STATE_KEY = "st";
const QString Snap::MEDIA_TYPE_KEY = "m";
const QString Snap::TIMESTAMP_KEY = "ts";
const QString Snap::SENT_TIMESTAMP_KEY = "sts";
//RECEIVED SNAPS - ALWAYS
const QString Snap::SENDER_KEY = "sn";
//RECEIVED SNAPS - UNSEEN
const QString Snap::TIMER_KEY = "timer";
//SENT/RECEIVED - VIDEO SNAPS (ALWAYS)
const QString Snap::ZIPPED_KEY = "zipped";
//SENT - ALWAYS
const QString Snap::RECIPIENT_KEY = "rp";

Snap::Snap(QJsonObject snapObj)
{
    //Parse keys that are always there
    this->id = snapObj[ID_KEY].toString();
    this->state = snapObj[STATE_KEY].toInt();
    this->mediaType = snapObj[MEDIA_TYPE_KEY].toInt();
    this->timestamp = snapObj[TIMESTAMP_KEY].toString().toLongLong();
    this->sentTimestamp = snapObj[SENT_TIMESTAMP_KEY].toString().toLongLong();

    //Determine if we sent or received this snap
    this->incoming = this->id.endsWith("r", Qt::CaseInsensitive);

    //If it is a snap received
    if(this->incoming){
        this->senderName = snapObj[SENDER_KEY].toString();
        this->timer = snapObj.contains(TIMER_KEY) ? snapObj[TIMER_KEY].toString().toFloat() : 0;
    }else{
        this->recipientName = snapObj[RECIPIENT_KEY].toString();
    }
    this->zipped = snapObj.contains(ZIPPED_KEY) ? snapObj[ZIPPED_KEY].toBool() : false;
}

bool Snap::isIncoming() const {
    return this->incoming;
}

const QString Snap::getID() const {
    return this->id;
}

const QString Snap::getSenderName() const {
    return this->senderName;
}

const QString Snap::getRecipientName() const {
    return this->recipientName;
}

qint64 Snap::getLastInteractionTime() const {
    return this->timestamp;
}

qint64 Snap::getSentTime() const {
    return this->sentTimestamp;
}

bool Snap::isViewed() const {
    return this->state == VIEWED || this->state == SCREENSHOT;
}

bool Snap::isScreenshotted() const {
    return this->state == SCREENSHOT;
}

float Snap::getDuration() const {
    return this->timer;
}

bool Snap::isZipped() const{
    return this->zipped;
}

bool Snap::isVideo() const {
    return this->mediaType == VIDEO || this->mediaType == VIDEO_NOAUDIO
            || this->mediaType == FRIEND_REQUEST_VIDEO || this->mediaType == FRIEND_REQUEST_VIDEO_NOAUDIO;
}

bool Snap::isFriendRequest() const {
    return this->mediaType >= FRIEND_REQUEST;
}

bool Snap::isDownloadable() const {
    return (!isViewed() && !isFriendRequest() && isIncoming());
}
