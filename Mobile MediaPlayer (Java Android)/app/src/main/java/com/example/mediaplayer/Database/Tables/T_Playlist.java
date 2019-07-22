package com.example.mediaplayer.Database.Tables;

public class T_Playlist {
    public enum Fields { ID, Name }

    public static final String CREATE = "CREATE TABLE IF NOT EXISTS Playlist " +
            "(" +
            "   ID         INTEGER          PRIMARY KEY AUTOINCREMENT," +
            "   Name       VARCHAR(50)      NOT NULL " +
            ")";

    public static final String GET_ALL_PLAYLIST = "SELECT ID, NAME FROM Playlist;";

    public static final String GET_PLAYLIST_BY_NAME = "SELECT ID, NAME FROM Playlist " +
            "WHERE NAME =  ?";

    public static final String INSERT_PLAYLIST = "INSERT INTO Playlist(Name) VALUES(?)";

    public int Id;
    public String Name;

    public T_Playlist(int id, String name)
    {
        this.Id = id;
        this.Name = name;
    }
}
