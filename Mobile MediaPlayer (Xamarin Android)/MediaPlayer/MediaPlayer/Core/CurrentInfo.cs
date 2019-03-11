namespace MediaPlayer.Core
{
    class CurrentInfo
    {
        public enum States { SongPlaying, PlaylistCreation };

        public States State;
        public Playlist Playlist;
        public int SongIndex;
    }
}