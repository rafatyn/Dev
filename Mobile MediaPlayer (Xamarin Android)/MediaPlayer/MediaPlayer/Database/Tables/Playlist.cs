using SQLite;

namespace MediaPlayer.Database.Tables
{
    class Playlist
    {
        [PrimaryKey, AutoIncrement]
        public int ID { get; set; }
        public string Name { get; set; }
    }
}