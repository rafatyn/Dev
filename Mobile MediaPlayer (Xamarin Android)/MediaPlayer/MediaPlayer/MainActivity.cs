using Android.App;
using Android.Media;
using Android.Net;
using Android.OS;
using Android.Runtime;
using Android.Support.V7.App;
using Android.Views;
using Android.Widget;
using Java.IO;
using System.Collections.Generic;

namespace MediaPlayer
{
    [Activity(Label = "@string/app_name", Theme = "@style/AppTheme", MainLauncher = true)]
    public class MainActivity : AppCompatActivity
    {
        private IMenu ToolbarMenu;
        private List<RelativeLayout> Pages;
        private Database.Database DB;

        private Core.DirectoryNavigation DirectoryTree;
        //private Android.Media.MediaPlayer Player;
        private AudioTrack Player;
        private List<Core.Playlist> Playlists;

        private List<KeyValuePair<int, int>> PlaylistMenuID;

        private Core.CurrentInfo CurrentInfo;

        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
            // Set our view from the "main" layout resource
            SetContentView(Resource.Layout.activity_main);

            Android.Support.V7.Widget.Toolbar toolbar = FindViewById<Android.Support.V7.Widget.Toolbar>(Resource.Id.AppToolbar);
            SetSupportActionBar(FindViewById<Android.Support.V7.Widget.Toolbar>(Resource.Id.AppToolbar));
            toolbar.Title = "Media Player";

            Pages = new List<RelativeLayout>();
            Pages.Insert(0, FindViewById<RelativeLayout>(Resource.Id.Page1_Layout));
            Pages.Insert(1, FindViewById<RelativeLayout>(Resource.Id.Page2_Layout));

            DB = new Database.Database(System.Environment.GetFolderPath(System.Environment.SpecialFolder.Personal) + "/sqlite.db3");

            CurrentInfo = new Core.CurrentInfo
            {
                State = Core.CurrentInfo.States.SongPlaying
            };
            ChangeToWindow();

            Playlists = new List<Core.Playlist>();
            PlaylistMenuID = new List<KeyValuePair<int, int>>();
            LoadPlaylistsFromDB();

            //Player = new Android.Media.MediaPlayer();
            Player = new AudioTrack.Builder().Build();

            LoadCurrentInfoFromDB();

            // TODO: Asignar canciones por ruta, buscar si se puede directamente asignar un grupo de canciones
            ImageButton previousSongButton = FindViewById<ImageButton>(Resource.Id.Page1_PreviousSongButton);

            previousSongButton.Click += (sender, e) =>
            {
                if (CurrentInfo.Playlist != null && CurrentInfo.State == Core.CurrentInfo.States.SongPlaying)
                {
                    if(CurrentInfo.SongIndex > 0)
                    {
                        CurrentInfo.SongIndex -= 1;
                        SaveCurrentInfo();
                    }

                    Toast.MakeText(this, CurrentInfo.Playlist.SongPaths[CurrentInfo.SongIndex], ToastLength.Short).Show();
                    //if (Player.CurrentPosition <= Player.Duration / 10)
                    //    Player.SetDataSource(this, Uri.Parse(""));
                    //else
                    //    Player.SeekTo(0);
                }
            };

            ImageButton nextSongButton = FindViewById<ImageButton>(Resource.Id.Page1_NextSongButton);

            nextSongButton.Click += (sender, e) =>
            {
                if (CurrentInfo.Playlist != null && CurrentInfo.State == Core.CurrentInfo.States.SongPlaying)
                {
                    if (CurrentInfo.SongIndex < CurrentInfo.Playlist.SongPaths.Count - 1)
                    {
                        CurrentInfo.SongIndex += 1;
                        SaveCurrentInfo();
                    }

                    Toast.MakeText(this, CurrentInfo.Playlist.SongPaths[CurrentInfo.SongIndex], ToastLength.Short).Show();
                    //Player.SetDataSource(this, Uri.Parse(""));
                }
            };
            //**************************************************************

            // TODO: Implementar opcion de reproducción en mono
            //AudioFormat.Builder monoAudioFormatBuilder = new AudioFormat.Builder();
            //monoAudioFormatBuilder.SetChannelMask(ChannelOut.Mono);
            //monoAudioFormatBuilder.SetEncoding(Encoding.Pcm16bit);
            //AudioFormat monoAudioFormat = monoAudioFormatBuilder.Build();

            //AudioTrack.Builder audioTrackBuilder = new AudioTrack.Builder();
            //audioTrackBuilder.SetAudioFormat(monoAudioFormat);            
            //AudioTrack audioTrack = audioTrackBuilder.Build();

            //File audio = new File("/system/media/sounds/sound.mp3"); // Use file into playlist
            //audioTrack.Write(audio.ToArray<byte>(), 0, audio.ToArray<byte>().Length);
            //**************************************************************

            ImageButton playPauseSongButton = FindViewById<ImageButton>(Resource.Id.Page1_PlayPauseButton);

            playPauseSongButton.Click += (sender, e) =>
            {
                if (CurrentInfo.Playlist != null && CurrentInfo.State == Core.CurrentInfo.States.SongPlaying)
                {
                    Toast.MakeText(this, CurrentInfo.Playlist.SongPaths[CurrentInfo.SongIndex], ToastLength.Short).Show();

                    if (Player.PlayState == PlayState.Stopped)
                    {
                        byte[] audio = System.IO.File.ReadAllBytes(CurrentInfo.Playlist.SongPaths[CurrentInfo.SongIndex]);
                        
                        Player = new AudioTrack.Builder()
                            .SetAudioFormat(new AudioFormat.Builder()
                                    .SetEncoding(Encoding.Pcm16bit)
                                    .SetSampleRate(44100)
                                    .SetChannelMask(ChannelOut.Stereo)
                                    .Build())
                            .SetBufferSizeInBytes(AudioTrack.GetMinBufferSize(44100, ChannelOut.Stereo, Encoding.Pcm16bit))
                            .Build();

                        Player.Write(audio, 0, audio.Length);
                        Player.Play();

                        FindViewById<ImageButton>(Resource.Id.Page1_PlayPauseButton).SetImageResource(Resource.Drawable.ic_pause_song_button);
                    }
                    else if (Player.PlayState == PlayState.Paused)
                    {
                        Player.Play();

                        FindViewById<ImageButton>(Resource.Id.Page1_PlayPauseButton).SetImageResource(Resource.Drawable.ic_pause_song_button);
                    }                        
                    else if (Player.PlayState == PlayState.Playing)
                    {
                        Player.Pause();

                        FindViewById<ImageButton>(Resource.Id.Page1_PlayPauseButton).SetImageResource(Resource.Drawable.ic_play_song_button);
                    }                        
                }
            };

            Button cancelFolderButton = FindViewById<Button>(Resource.Id.Page2_ToolbarCancelButton);

            cancelFolderButton.Click += (sender, e) =>
            {
                CurrentInfo.State = Core.CurrentInfo.States.SongPlaying;
                ChangeToWindow();
            };

            Button selectFolderButton = FindViewById<Button>(Resource.Id.Page2_ToolbarSelectButton);

            selectFolderButton.Click += (sender, e) =>
            {
                if (DirectoryTree.FolderHasSupportedAudioFiles())
                {
                    DirectoryTree.NewPlaylistFromFolder();
                    CurrentInfo.State = Core.CurrentInfo.States.SongPlaying;
                    ChangeToWindow();
                }
                else
                    Toast.MakeText(this, "This folder doesn't have supported music files", ToastLength.Long).Show();
            };
        }

        public override bool OnCreateOptionsMenu(IMenu menu)
        {
            MenuInflater.Inflate(Resource.Menu.home, menu);
            ToolbarMenu = menu;
            LoadMenuPlaylists();
            return base.OnCreateOptionsMenu(menu);
        }

        // TODO: Terminar menu
        public override bool OnOptionsItemSelected(IMenuItem item)
        {
            switch (item.ItemId)
            {
                case Resource.Id.menu_playlist:                    
                    break;
                case Resource.Id.new_playlist:
                    CurrentInfo.State = Core.CurrentInfo.States.PlaylistCreation;
                    DirectoryTree = new Core.DirectoryNavigation(this, FindViewById<ListView>(Resource.Id.Page2_FolderStructure));
                    DirectoryTree.OpenFolder();
                    ChangeToWindow();
                    break;
                case Resource.Id.aux_menu_playlist:                    
                    break;
                default:
                    foreach(KeyValuePair<int, int> MenuID in PlaylistMenuID)
                    {
                        if(MenuID.Key == item.ItemId)
                        {
                            CurrentInfo.Playlist = Playlists[MenuID.Value];
                            CurrentInfo.SongIndex = 0;
                            SaveCurrentInfo();
                            break;
                        }
                    }
                    break;
            }
            return base.OnOptionsItemSelected(item);
        }
        //***********************************************

        public override void OnBackPressed()
        {
            if(CurrentInfo.State == Core.CurrentInfo.States.PlaylistCreation)
            {
                DirectoryTree.BackOneStep();
            }                
            else if (CurrentInfo.State == Core.CurrentInfo.States.SongPlaying)
            {
                Android.App.AlertDialog.Builder builder = new Android.App.AlertDialog.Builder(this);
                builder.SetTitle("Exit");
                builder.SetMessage("Do you want to exit?");
                builder.SetPositiveButton("Yes", (sender, e) =>
                {
                    Process.KillProcess(Process.MyPid());
                });
                builder.SetNegativeButton("No", (sender, e) => { });
                builder.Show();
            }
        }

        private void LoadCurrentInfoFromDB()
        {
            Database.Tables.Setup info = DB.GetCurrentInfo();

            if (info != null)
            {
                foreach (Core.Playlist playlist in Playlists)
                {
                    if (playlist.Name == info.PlaylistName)
                    {
                        CurrentInfo.Playlist = playlist;
                        CurrentInfo.SongIndex = info.SongIndex;
                    }
                }
            }
        }

        private void LoadPlaylistsFromDB()
        {
            List<Database.Tables.Playlist> dbPlaylists = DB.GetPlaylists();
            foreach (Database.Tables.Playlist dbPlaylist in dbPlaylists)
            {
                Core.Playlist pl = new Core.Playlist(dbPlaylist.Name);

                List<Database.Tables.Song> dbSongs = DB.GetSongsByPlaylistID(dbPlaylist.ID);
                foreach (Database.Tables.Song dbSong in dbSongs)
                {
                    pl.AddSong(dbSong.Path);
                }

                Playlists.Add(pl);
            }
        }

        private void LoadMenuPlaylists()
        {
            foreach (Core.Playlist playlist in Playlists)
            {
                int itemId = Resource.Id.new_playlist - 1000000000 + PlaylistMenuID.Count;

                ToolbarMenu.FindItem(Resource.Id.menu_playlist).SubMenu.Add(0, itemId, 0, playlist.Name);
                PlaylistMenuID.Add(new KeyValuePair<int, int>(itemId, Playlists.IndexOf(playlist)));
            }
        }

        private bool SaveCurrentInfo()
        {
            return DB.InsertCurrentInfo(CurrentInfo);
        }

        private void ChangeToWindow()
        {
            int index = (int)CurrentInfo.State;
            for(int i=0; i<Pages.Count; i++)
            {
                if (i == index)
                    Pages[i].Visibility = ViewStates.Visible;
                else
                    Pages[i].Visibility = ViewStates.Invisible;
            }
        }

        public void AddPlaylist(Core.Playlist playlist)
        {
            Playlists.Add(playlist);
            bool result = DB.InsertNewPlaylist(playlist);

            if (result)
            {
                int itemId = Resource.Id.new_playlist - 1000000000 + PlaylistMenuID.Count;

                ToolbarMenu.FindItem(Resource.Id.menu_playlist).SubMenu.Add(0, itemId, 0, playlist.Name);
                PlaylistMenuID.Add(new KeyValuePair<int, int>(itemId, Playlists.IndexOf(playlist)));

                CurrentInfo.Playlist = playlist;
                CurrentInfo.SongIndex = 0;
                SaveCurrentInfo();
            }
            else
                Toast.MakeText(this, "A problem has ocurred, cannot add the playlist", ToastLength.Short).Show();
        }

        public void ShowFolderEmpty()
        {
            if(CurrentInfo.State == Core.CurrentInfo.States.PlaylistCreation)
                FindViewById<TextView>(Resource.Id.Page2_FolderEmpty).Visibility = ViewStates.Visible;
        }

        public void HideFolderEmpty()
        {
            if (CurrentInfo.State == Core.CurrentInfo.States.PlaylistCreation)
                FindViewById<TextView>(Resource.Id.Page2_FolderEmpty).Visibility = ViewStates.Invisible;
        }
    }
}