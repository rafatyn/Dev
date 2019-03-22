using Android;
using Android.App;
using Android.Content;
using Android.Content.PM;
using Android.Graphics;
using Android.Graphics.Drawables;
using Android.Media;
using Android.Net;
using Android.OS;
using Android.Runtime;
using Android.Support.V4.App;
using Android.Support.V7.App;
using Android.Views;
using Android.Widget;
using Java.Util;
using System.Collections.Generic;
using System.Linq;
using TaskStackBuilder = Android.Support.V4.App.TaskStackBuilder;

namespace MediaPlayer
{
    [Activity(Label = "@string/app_name", Theme = "@style/AppTheme", MainLauncher = true)]
    public class MainActivity : AppCompatActivity
    {
        private enum Permissions { ReadExternalStorage };

        private IMenu ToolbarMenu;
        private List<RelativeLayout> Pages;
        private Database.Database DB;

        private Core.DirectoryNavigation DirectoryTree;
        private Android.Media.MediaPlayer Player;
        private MediaMetadataRetriever Meta;
        private List<Core.Playlist> Playlists;

        private List<KeyValuePair<int, int>> PlaylistMenuID;

        private Core.CurrentInfo CurrentInfo;

        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
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

            Player = new Android.Media.MediaPlayer();

            Player.Completion += (sender, e) =>
            {
                ChangeToNextSong();
            };

            Meta = new MediaMetadataRetriever();

            LoadCurrentInfoFromDB();

            ImageButton previousSongButton = FindViewById<ImageButton>(Resource.Id.Page1_PreviousSongButton);

            previousSongButton.Click += (sender, e) =>
            {
                ChangeToPreviousSong();
            };

            ImageButton nextSongButton = FindViewById<ImageButton>(Resource.Id.Page1_NextSongButton);

            nextSongButton.Click += (sender, e) =>
            {
                ChangeToNextSong();
            };

            ImageButton playPauseSongButton = FindViewById<ImageButton>(Resource.Id.Page1_PlayPauseButton);

            playPauseSongButton.Click += (sender, e) =>
            {
                PlayPauseSong();   
            };

            ImageButton shuffleSongButton = FindViewById<ImageButton>(Resource.Id.Page1_ShuffleSongButton);

            shuffleSongButton.Click += (sender, e) =>
            {
                ChangePlayingMode();
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

            if (Build.VERSION.SdkInt >= BuildVersionCodes.O)
            {
                NotificationChannel channel = new NotificationChannel("Notification_Channel", "Notification_Channel_Name", NotificationImportance.Default)
                {
                    Description = "Notification_Channel_Description"
                };

                NotificationManager notificationManager = (NotificationManager)GetSystemService(NotificationService);
                notificationManager.CreateNotificationChannel(channel);
            }

            Core.NotificationBroadcast receiver = new Core.NotificationBroadcast(this);
            RegisterReceiver(receiver, new IntentFilter(Core.NotificationBroadcast.Actions.shuffleAction.ToString()));
            RegisterReceiver(receiver, new IntentFilter(Core.NotificationBroadcast.Actions.previousAction.ToString()));
            RegisterReceiver(receiver, new IntentFilter(Core.NotificationBroadcast.Actions.playPauseAction.ToString()));
            RegisterReceiver(receiver, new IntentFilter(Core.NotificationBroadcast.Actions.nextAction.ToString()));
        }

        public override bool OnCreateOptionsMenu(IMenu menu)
        {
            MenuInflater.Inflate(Resource.Menu.home, menu);
            ToolbarMenu = menu;
            LoadMenuPlaylists();
            return base.OnCreateOptionsMenu(menu);
        }

        public override void OnBackPressed()
        {
            if (CurrentInfo.State == Core.CurrentInfo.States.PlaylistCreation)
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
                    NotificationManagerCompat.From(this).Cancel(10);
                    Process.KillProcess(Process.MyPid());
                });
                builder.SetNegativeButton("No", (sender, e) => { });
                builder.Show();
            }
        }

        public override bool OnOptionsItemSelected(IMenuItem item)
        {
            switch (item.ItemId)
            {
                case Resource.Id.menu_playlist:                    
                    break;
                case Resource.Id.new_playlist:
                    if(CheckSelfPermission(Manifest.Permission.ReadExternalStorage) != Android.Content.PM.Permission.Granted)
                    {
                        if (ShouldShowRequestPermissionRationale(Manifest.Permission.ReadExternalStorage))
                        {
                            Toast.MakeText(this, "Cannot create a playlist without Read SdCard permission", ToastLength.Long).Show();
                            break;
                        }
                        else
                            RequestPermissions(new string[] { Manifest.Permission.ReadExternalStorage }, (int)Permissions.ReadExternalStorage);
                    }
                    else
                    {
                        CurrentInfo.State = Core.CurrentInfo.States.PlaylistCreation;
                        DirectoryTree = new Core.DirectoryNavigation(this, FindViewById<ListView>(Resource.Id.Page2_FolderStructure));
                        DirectoryTree.OpenFolder();
                        ChangeToWindow();
                    }
                    break;
                default:
                    foreach(KeyValuePair<int, int> MenuID in PlaylistMenuID)
                    {
                        if(MenuID.Key == item.ItemId)
                        {
                            CurrentInfo.Playlist = Playlists[MenuID.Value];
                            CurrentInfo.SongIndex = 0;
                            CurrentInfo.PlayedSongs = Enumerable.ToList<bool>(Enumerable.Repeat(false, Playlists[MenuID.Value].SongPaths.Count));
                            CurrentInfo.LastSong = -1;
                            SaveCurrentInfo();
                            break;
                        }
                    }
                    break;
            }
            return base.OnOptionsItemSelected(item);
        }

        public override void OnRequestPermissionsResult(int requestCode, string[] permissions, [GeneratedEnum] Permission[] grantResults)
        {
            switch (requestCode)
            {
                case (int)Permissions.ReadExternalStorage:
                    if(grantResults.Length > 0 && grantResults[0] == Permission.Granted)
                    {
                        CurrentInfo.State = Core.CurrentInfo.States.PlaylistCreation;
                        DirectoryTree = new Core.DirectoryNavigation(this, FindViewById<ListView>(Resource.Id.Page2_FolderStructure));
                        DirectoryTree.OpenFolder();
                        ChangeToWindow();
                    }
                    else
                        Toast.MakeText(this, "Cannot create a playlist without Read SdCard permission", ToastLength.Long).Show();

                    break;
            }

            base.OnRequestPermissionsResult(requestCode, permissions, grantResults);
        }
        
        private void LoadCurrentInfoFromDB()
        {
            Database.Tables.Setup info = DB.GetCurrentInfo();

            if (info != null)
            {
                CurrentInfo.PlayingMode = (Core.CurrentInfo.PlayingModes)info.PlayingMode;

                if (CurrentInfo.PlayingMode == Core.CurrentInfo.PlayingModes.NormalMode)
                    FindViewById<ImageButton>(Resource.Id.Page1_ShuffleSongButton).SetImageResource(Resource.Drawable.ic_shuffle_disabled_song_button);
                else if (CurrentInfo.PlayingMode == Core.CurrentInfo.PlayingModes.ShuffleMode)
                    FindViewById<ImageButton>(Resource.Id.Page1_ShuffleSongButton).SetImageResource(Resource.Drawable.ic_shuffle_song_button);

                foreach (Core.Playlist playlist in Playlists)
                {
                    if (playlist.Name == info.PlaylistName)
                    {
                        CurrentInfo.Playlist = playlist;
                        CurrentInfo.SongIndex = info.SongIndex;                        
                        CurrentInfo.PlayedSongs = Enumerable.ToList<bool>(Enumerable.Repeat(false, playlist.SongPaths.Count));
                    }
                }

                CurrentInfo.LastSong = -1;

                ChangePlayingSong(false);                
            }

            OpenNotification();
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
                CurrentInfo.PlayedSongs = Enumerable.ToList<bool>(Enumerable.Repeat(false, playlist.SongPaths.Count));
                CurrentInfo.LastSong = -1;
                SaveCurrentInfo();
            }
            else
                Toast.MakeText(this, "A problem has ocurred, cannot add the playlist", ToastLength.Short).Show();
        }

        public void ChangePlayingMode()
        {
            if (CurrentInfo.PlayingMode == Core.CurrentInfo.PlayingModes.NormalMode)
            {
                CurrentInfo.PlayingMode = Core.CurrentInfo.PlayingModes.ShuffleMode;

                FindViewById<ImageButton>(Resource.Id.Page1_ShuffleSongButton).SetImageResource(Resource.Drawable.ic_shuffle_song_button);
            }
            else if (CurrentInfo.PlayingMode == Core.CurrentInfo.PlayingModes.ShuffleMode)
            {
                CurrentInfo.PlayingMode = Core.CurrentInfo.PlayingModes.NormalMode;

                FindViewById<ImageButton>(Resource.Id.Page1_ShuffleSongButton).SetImageResource(Resource.Drawable.ic_shuffle_disabled_song_button);
            }

            OpenNotification();
        }

        public void ChangeToNextSong()
        {
            if (CurrentInfo.Playlist != null && CurrentInfo.State == Core.CurrentInfo.States.SongPlaying)
            {
                if (CurrentInfo.PlayingMode == Core.CurrentInfo.PlayingModes.NormalMode)
                {
                    if (CurrentInfo.SongIndex < CurrentInfo.Playlist.SongPaths.Count - 1)
                    {
                        CurrentInfo.SongIndex += 1;
                        SaveCurrentInfo();
                    }
                }
                else if (CurrentInfo.PlayingMode == Core.CurrentInfo.PlayingModes.ShuffleMode)
                {
                    Random rand = new Random();
                    int nextSong = rand.NextInt(CurrentInfo.Playlist.SongPaths.Count);

                    for (int i = 0; CurrentInfo.PlayedSongs[nextSong]; i++)
                    {
                        nextSong = rand.NextInt(CurrentInfo.Playlist.SongPaths.Count);

                        if (i > CurrentInfo.Playlist.SongPaths.Count / 8)
                        {
                            CurrentInfo.PlayedSongs = Enumerable.ToList<bool>(Enumerable.Repeat(false, CurrentInfo.Playlist.SongPaths.Count));
                        }
                    }

                    CurrentInfo.PlayedSongs[nextSong] = true;
                    CurrentInfo.LastSong = CurrentInfo.SongIndex;
                    CurrentInfo.SongIndex = nextSong;
                    SaveCurrentInfo();
                }
                ChangePlayingSong();

                OpenNotification();
            }
        }

        public void ChangeToPreviousSong()
        {
            if (CurrentInfo.Playlist != null && CurrentInfo.State == Core.CurrentInfo.States.SongPlaying)
            {                
                if (Player.CurrentPosition <= 10000)
                {
                    if (CurrentInfo.PlayingMode == Core.CurrentInfo.PlayingModes.NormalMode)
                    {
                        if (CurrentInfo.SongIndex > 0)
                        {
                            CurrentInfo.SongIndex -= 1;
                            SaveCurrentInfo();
                        }
                    }
                    else if (CurrentInfo.PlayingMode == Core.CurrentInfo.PlayingModes.ShuffleMode)
                    {
                        if(CurrentInfo.LastSong != -1 && CurrentInfo.SongIndex != CurrentInfo.LastSong)
                        {
                            CurrentInfo.SongIndex = CurrentInfo.LastSong;
                        }
                        else
                        {
                            if (CurrentInfo.SongIndex > 0)
                            {
                                CurrentInfo.SongIndex -= 1;
                            }
                        }
                        
                        SaveCurrentInfo();
                    }

                    ChangePlayingSong();
                }
                else
                    Player.SeekTo(0);

                OpenNotification();
            }
        }

        private void ChangePlayingSong(bool start = true)
        {
            if (CurrentInfo.Playlist != null)
            {
                Player.Reset();
                Player.SetDataSource(CurrentInfo.Playlist.SongPaths[CurrentInfo.SongIndex]);
                Player.Prepare();

                Meta.SetDataSource(CurrentInfo.Playlist.SongPaths[CurrentInfo.SongIndex]);
                byte[] cover = Meta.GetEmbeddedPicture();
                FindViewById<TextView>(Resource.Id.Page1_SongName).Text = Meta.ExtractMetadata(MetadataKey.Title);
                FindViewById<TextView>(Resource.Id.Page1_SongAuthor).Text = Meta.ExtractMetadata(MetadataKey.Artist)
                    + " - " + Meta.ExtractMetadata(MetadataKey.Album);

                if (FindViewById<TextView>(Resource.Id.Page1_SongName).Text == "")
                {
                    string songName = CurrentInfo.Playlist.SongPaths[CurrentInfo.SongIndex];
                    songName = songName.Substring(songName.LastIndexOfAny(new char[] { '/', '\\' }) + 1,
                        songName.LastIndexOf('.') - (songName.LastIndexOfAny(new char[] { '/', '\\' }) + 1));
                    FindViewById<TextView>(Resource.Id.Page1_SongName).Text = songName;
                }

                if (cover != null)
                {
                    Android.Graphics.Bitmap coverBitmap = Android.Graphics.BitmapFactory.DecodeByteArray(cover, 0, cover.Length);
                    FindViewById<ImageView>(Resource.Id.Page1_SongImage).SetImageBitmap(coverBitmap);
                }

                if (start)
                {
                    FindViewById<ImageButton>(Resource.Id.Page1_PlayPauseButton).SetImageResource(Resource.Drawable.ic_pause_song_button);
                    Player.Start();
                }
            }
        }

        public void PlayPauseSong()
        {
            if (CurrentInfo.Playlist != null && CurrentInfo.State == Core.CurrentInfo.States.SongPlaying)
            {
                if (!Player.IsPlaying)
                {
                    int pos = Player.CurrentPosition;

                    if (pos < 0)
                        ChangePlayingSong();
                    else
                    {
                        Player.Start();
                        FindViewById<ImageButton>(Resource.Id.Page1_PlayPauseButton).SetImageResource(Resource.Drawable.ic_pause_song_button);
                    }
                }
                else if (Player.IsPlaying)
                {
                    Player.Pause();

                    FindViewById<ImageButton>(Resource.Id.Page1_PlayPauseButton).SetImageResource(Resource.Drawable.ic_play_song_button);
                }
            }

            OpenNotification();
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

        private void OpenNotification()
        {
            Intent intent = new Intent(this, typeof(MainActivity));
            intent.SetFlags(ActivityFlags.NewTask | ActivityFlags.ClearTask);
            TaskStackBuilder taskBuilder = TaskStackBuilder.Create(this);
            taskBuilder.AddNextIntent(intent);

            NotificationCompat.Builder notificationBuilder = new NotificationCompat.Builder(this, "Notification_Channel")
                .SetSmallIcon(Resource.Drawable.ic_play_song_button)
                .SetAutoCancel(false)
                .SetOnlyAlertOnce(true)
                .SetOngoing(true)
                .SetContentIntent(taskBuilder.GetPendingIntent(0, (int)PendingIntentFlags.UpdateCurrent))
                .SetCustomContentView(new RemoteViews(PackageName, Resource.Layout.notification))
                .SetPriority(NotificationCompat.PriorityLow)
                .SetVisibility(NotificationCompat.VisibilityPublic);
            
            if (Player.IsPlaying)
                notificationBuilder.ContentView.SetImageViewResource(Resource.Id.Notification_PlayPauseButton, Resource.Drawable.ic_pause_song_button);
            else
                notificationBuilder.ContentView.SetImageViewResource(Resource.Id.Notification_PlayPauseButton, Resource.Drawable.ic_play_song_button);

            if (CurrentInfo.PlayingMode == Core.CurrentInfo.PlayingModes.ShuffleMode)
                notificationBuilder.ContentView.SetImageViewResource(Resource.Id.Notification_ShuffleSongButton, Resource.Drawable.ic_shuffle_song_button);
            else
                notificationBuilder.ContentView.SetImageViewResource(Resource.Id.Notification_ShuffleSongButton, Resource.Drawable.ic_shuffle_disabled_song_button);

            if (CurrentInfo.Playlist != null)
            {
                notificationBuilder.ContentView.SetTextViewText(Resource.Id.Notification_SongName, FindViewById<TextView>(Resource.Id.Page1_SongName).Text);
                notificationBuilder.ContentView.SetTextViewText(Resource.Id.Notification_SongAuthor, FindViewById<TextView>(Resource.Id.Page1_SongAuthor).Text);
                            
                Meta.SetDataSource(CurrentInfo.Playlist.SongPaths[CurrentInfo.SongIndex]);
                byte[] cover = Meta.GetEmbeddedPicture();
                if (cover != null)
                {
                    Android.Graphics.Bitmap coverBitmap = Android.Graphics.BitmapFactory.DecodeByteArray(cover, 0, cover.Length);
                    notificationBuilder.ContentView.SetImageViewBitmap(Resource.Id.Notification_SongImage, coverBitmap);
                }
            }
            else
            {
                notificationBuilder.ContentView.SetTextViewText(Resource.Id.Notification_SongName, "No song playing");
            }

            Notification notification = notificationBuilder.Build();

            Intent shuffleIntent = new Intent(Core.NotificationBroadcast.Actions.shuffleAction.ToString());
            PendingIntent shufflePreviousIntent = PendingIntent.GetBroadcast(ApplicationContext, 0, shuffleIntent, PendingIntentFlags.UpdateCurrent);

            Intent previousIntent = new Intent(Core.NotificationBroadcast.Actions.previousAction.ToString());
            PendingIntent previousPreviousIntent = PendingIntent.GetBroadcast(ApplicationContext, 0, previousIntent, PendingIntentFlags.UpdateCurrent);

            Intent playPauseIntent = new Intent(Core.NotificationBroadcast.Actions.playPauseAction.ToString());
            PendingIntent playPausePreviousIntent = PendingIntent.GetBroadcast(ApplicationContext, 0, playPauseIntent, PendingIntentFlags.UpdateCurrent);

            Intent nextIntent = new Intent(Core.NotificationBroadcast.Actions.nextAction.ToString());
            PendingIntent nextPreviousIntent = PendingIntent.GetBroadcast(ApplicationContext, 0, nextIntent, PendingIntentFlags.UpdateCurrent);

            notification.ContentView.SetOnClickPendingIntent(Resource.Id.Notification_ShuffleSongButton, shufflePreviousIntent);
            notification.ContentView.SetOnClickPendingIntent(Resource.Id.Notification_PreviousSongButton, previousPreviousIntent);
            notification.ContentView.SetOnClickPendingIntent(Resource.Id.Notification_PlayPauseButton, playPausePreviousIntent);
            notification.ContentView.SetOnClickPendingIntent(Resource.Id.Notification_NextSongButton, nextPreviousIntent);            

            NotificationManagerCompat.From(this).Notify(10, notification);
        }
    }
}