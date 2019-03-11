using System.Collections.Generic;

namespace MediaPlayer.Core
{
    public class Playlist
    {
        public string Name { get; private set; }
        public List<string> SongPaths { get; private set; }

        public Playlist(string name)
        {
            Name = name;
            SongPaths = new List<string>();
        }

        public void AddSong(string path)
        {
            SongPaths.Add(path);
        }

        public void AddListSong(List<string> paths)
        {
            SongPaths.AddRange(paths);
        }

        public void RemoveSong(string path)
        {
            while (SongPaths.Remove(path)) { };
        }
    }
}