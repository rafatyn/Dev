package com.example.mediaplayer.Database.Tables;

public class T_Setup {
    public enum Fields { Playlist, SongIndex, PlayingMode }

    public static final String CREATE = "CREATE TABLE IF NOT EXISTS Setup " +
            "(" +
            "   Playlist        VARCHAR(50)         ," +
            "   SongIndex       INTEGER             ," +
            "   PlayingMode     INTEGER             NOT NULL," +
            "   FOREIGN KEY(Playlist) REFERENCES Playlist(ID)" +
            ")";

    public static final String GET_CURRENT_INFO = "SELECT PLAYLIST, SONGINDEX, PLAYINGMODE FROM Setup";

    public static final String SAVE_CURRENT_INFO = "INSERT INTO Setup VALUES(?, ?, ?)";

    public String Playlist;
    public int SongIndex;
    public int PlayingMode;

    public T_Setup(String playlist, int songIndex, int playingMode)
    {
        this.Playlist = playlist;
        this.SongIndex = songIndex;
        this.PlayingMode = playingMode;
    }
}
