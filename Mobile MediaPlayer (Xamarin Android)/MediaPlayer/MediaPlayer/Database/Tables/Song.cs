using SQLite;

namespace MediaPlayer.Database.Tables
{
    class Song
    {        
        public string Path { get; set; }
        public int PlaylistID { get; set; }
    }
}