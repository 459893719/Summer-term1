#ifndef BGM_H
#define BGM_H
#include <qmediaplayer.h>
#include <qmediaplaylist.h>

class Bgm
{
public:
    Bgm();
    ~Bgm();
    void clickBgm();
private:
    QMediaPlayer* bgmplayer;
    QMediaPlaylist* bgmplaylist;
    int flag;
};

#endif // BGM_H
