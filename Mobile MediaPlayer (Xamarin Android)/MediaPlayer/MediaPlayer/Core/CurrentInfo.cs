using System.Collections.Generic;

namespace MediaPlayer.Core
{
    class CurrentInfo
    {
        public enum States { SongPlaying, PlaylistCreation };
        public enum PlayingModes { NormalMode, ShuffleMode };

        public States State;
        public Playlist Playlist;
        public int SongIndex;
        public PlayingModes PlayingMode;
        public List<bool> PlayedSongs;
        public int LastSong;
    }
}