using SQLite;
using System.Collections.Generic;
using Java.IO;

namespace MediaPlayer.Database
{
    internal class Database
    {        
        public SQLiteConnection Connection { get; private set; }

        public Database(string dbPath, bool reset = false, bool hardReset = false)
        {
            Connection = new SQLiteConnection(dbPath);

            if (hardReset)
                new File(dbPath).Delete();
            else if (reset)
                ResetDatabase();
            
            Connection.CreateTable<Tables.Setup>();
            Connection.CreateTable<Tables.Playlist>();
            Connection.CreateTable<Tables.Song>();
        }

        public void ResetDatabase()
        {
            Connection.DropTable<Tables.Setup>();
            Connection.DropTable<Tables.Playlist>();
            Connection.DropTable<Tables.Song>();
        }

        public Tables.Setup GetCurrentInfo()
        {
            List<Tables.Setup> result = Connection.Table<Tables.Setup>().ToList();

            if (result.Count > 0)
                return result[0];
            else
                return null;
        }

        public bool InsertCurrentInfo(Core.CurrentInfo currentInfo)
        {
            Connection.BeginTransaction();

            Connection.DeleteAll<Tables.Setup>();

            Tables.Setup setup = new Tables.Setup
            {
                PlaylistName = currentInfo.Playlist.Name,
                SongIndex = currentInfo.SongIndex,
                PlayingMode = (int)currentInfo.PlayingMode
            };

            int result = Connection.Insert(setup);

            if(result == 1)
            {
                Connection.Commit();
                return true;
            }
            else
            {
                Connection.Rollback();
                return false;
            }
        }

        public List<Tables.Playlist> GetPlaylists()
        {
            return Connection.Table<Tables.Playlist>().ToList();
        }

        public Tables.Playlist GetPlaylistByName(string name)
        {
            List<Tables.Playlist> result = Connection.Table<Tables.Playlist>().Where(x => x.Name == name).ToList();

            if (result.Count > 0)
                return result[0];
            else
                return null;
        }

        public Tables.Playlist GetPlaylistById(int id)
        {
            List<Tables.Playlist> result = Connection.Table<Tables.Playlist>().Where(x => x.ID == id).ToList();

            if (result.Count > 0)
                return result[0];
            else
                return null;
        }

        public bool InsertNewPlaylist(Core.Playlist playlist)
        {
            Connection.BeginTransaction();

            Tables.Playlist obj = new Tables.Playlist
            {
                Name = playlist.Name
            };

            int result = Connection.Insert(obj);

            if (result == 1)
            {
                Tables.Playlist pl = GetPlaylistByName(playlist.Name);

                if (pl != null)
                {
                    int playlistID = pl.ID;
                    List<Tables.Song> songs = new List<Tables.Song>();

                    foreach (string songPath in playlist.SongPaths)
                    {
                        Tables.Song song = new Tables.Song
                        {
                            PlaylistID = playlistID,
                            Path = songPath
                        };
                        songs.Add(song);
                    }

                    result = Connection.InsertAll(songs);

                    if (result == songs.Count)
                    {
                        Connection.Commit();
                        return true;
                    }
                    else
                    {
                        Connection.Rollback();
                        return false;
                    }
                }
                else
                {
                    Connection.Rollback();
                    return false;
                }
            }
            else
            {
                Connection.Rollback();
                return false;
            }                
        }

        public List<Tables.Song> GetSongs()
        {
            return Connection.Table<Tables.Song>().ToList();
        }

        public List<Tables.Song> GetSongsByPlaylistID(int id)
        {
            return Connection.Table<Tables.Song>().Where(x => x.PlaylistID == id).ToList();
        }

        public List<Tables.Song> GetSongsByPlaylistName(string name)
        {
            Tables.Playlist playlist = GetPlaylistByName(name);
            return Connection.Table<Tables.Song>().Where(x => x.PlaylistID == playlist.ID).ToList();
        }
        /*
        public Task<List<TodoItem>> GetItemsNotDoneAsync()
        {
            return database.QueryAsync<TodoItem>("SELECT * FROM [TodoItem] WHERE [Done] = 0");
        }
        */
    }
}