#include "bgm.h"

Bgm::Bgm()
{
    flag = 1;//默认为播放状态

    bgmplaylist = new QMediaPlaylist;
    bgmplaylist->setCurrentIndex(1);
    bgmplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    bgmplaylist->addMedia(QUrl("./bgm/bgm.mp3"));
    bgmplayer = new QMediaPlayer;
    bgmplayer->setPlaylist(bgmplaylist);
    bgmplayer->setVolume(30);
    bgmplayer->play();
}

void Bgm::clickBgm()
{
    if (flag == 1)
    {
        flag = 0;
        bgmplayer->pause();
    }
    else if (flag == 0)
    {
        flag = 1;
        bgmplayer->play();
    }
}
