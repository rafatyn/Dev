package com.example.mediaplayer.Core;

import java.util.ArrayList;
import java.util.List;

public class Playlist {
    private String Name;
    private List<String> SongPaths;

    public Playlist(String name)
    {
        Name = name;
        SongPaths = new ArrayList<>();
    }

    public String GetName()
    {
        return Name;
    }

    public List<String> GetSongPaths()
    {
        return SongPaths;
    }

    public void AddSong(String path)
    {
        SongPaths.add(path);
    }

    public void AddListSong(List<String> paths)
    {
        SongPaths.addAll(paths);
    }

    public void RemoveSong(String path)
    {
        while (SongPaths.remove(path)) { }
    }
}
