package com.example.mediaplayer.Database.Tables;

public class T_Song {
    public enum Fields { Path, Playlist }

    public static final String CREATE = "CREATE TABLE IF NOT EXISTS Song " +
            "(" +
            "   Path            VARCHAR(250)        NOT NULL," +
            "   Playlist        INTEGER             NOT NULL," +
            "   FOREIGN KEY(Playlist) REFERENCES Playlist(ID)" +
            ")";

    public static final String GET_SONGS_BY_PLAYLIST = "SELECT Path, Playlist FROM Song " +
            "WHERE Playlist = ?";

    public static final String INSERT_SONGS = "INSERT INTO Song VALUES(?, ?)";

    public String Path;
    public int Playlist;

    public T_Song(String path, int playlist)
    {
        this.Path = path;
        this.Playlist = playlist;
    }
}
