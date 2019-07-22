package com.example.mediaplayer.Core;

import java.util.List;

public class CurrentInfo {
    public enum States { SongPlaying, PlaylistCreation }
    public enum PlayingModes { NormalMode, ShuffleMode }

    public States State;
    public Playlist Playlist;
    public int SongIndex;
    public PlayingModes PlayingMode;
    public List<Boolean> PlayedSongs;
    public int LastSong;
}
