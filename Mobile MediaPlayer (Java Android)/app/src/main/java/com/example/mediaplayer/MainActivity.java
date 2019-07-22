package com.example.mediaplayer;

import android.Manifest;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.AudioManager;
import android.media.MediaMetadataRetriever;
import android.media.MediaPlayer;
import android.os.Build;
import android.os.IBinder;
import android.support.annotation.NonNull;
import android.support.v4.app.NotificationCompat;
import android.support.v4.app.TaskStackBuilder;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.RemoteViews;
import android.widget.TextView;
import android.widget.Toast;

import com.example.mediaplayer.Core.CurrentInfo;
import com.example.mediaplayer.Core.DirectoryNavigation;
import com.example.mediaplayer.Core.NotificationBroadcast;
import com.example.mediaplayer.Core.NotificationKillerService;
import com.example.mediaplayer.Core.Playlist;
import com.example.mediaplayer.Database.Database;
import com.example.mediaplayer.Database.Tables.T_Setup;
import com.example.mediaplayer.Database.Tables.T_Song;
import com.example.mediaplayer.Database.Tables.T_Playlist;

import java.io.IOException;
import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private enum Permissions { ReadExternalStorage }

    private Menu ToolbarMenu;
    private List<RelativeLayout> Pages;
    private CurrentInfo CurrentInfo;
    private Database Database;

    private DirectoryNavigation DirectoryTree;
    private MediaPlayer Player;
    private MediaMetadataRetriever Meta;
    private List<Playlist> Playlists;

    private List<AbstractMap.SimpleEntry> PlaylistMenuID;

    private boolean LongPress;
    private boolean AudioLock;
    private AudioManager AudioVolumeManager;


    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = findViewById(R.id.AppToolbar);
        setSupportActionBar(toolbar);

        Pages = new ArrayList<>();
        Pages.add(0, (RelativeLayout)findViewById(R.id.Page1_Layout));
        Pages.add(1, (RelativeLayout)findViewById(R.id.Page2_Layout));

        Database = new Database(this);

        CurrentInfo = new CurrentInfo();
        CurrentInfo.State = com.example.mediaplayer.Core.CurrentInfo.States.SongPlaying;
        CurrentInfo.PlayingMode = com.example.mediaplayer.Core.CurrentInfo.PlayingModes.NormalMode;
        ChangeToWindow();

        Playlists = new ArrayList<>();
        PlaylistMenuID = new ArrayList<>();
        LoadPlaylistsFromDB();

        Player = new MediaPlayer();
        AudioLock = false;
        LongPress = false;
        AudioVolumeManager = (AudioManager)getSystemService(Context.AUDIO_SERVICE);

        Player.setOnCompletionListener(new MediaPlayer.OnCompletionListener(){
            @Override
            public void onCompletion(MediaPlayer mp){
                ChangeToNextSong();
            }
        });

        Meta = new MediaMetadataRetriever();

        LoadCurrentInfoFromDB();

        ImageButton previousSongButton = findViewById(R.id.Page1_PreviousSongButton);

        previousSongButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ChangeToPreviousSong();
            }
        });

        ImageButton nextSongButton = findViewById(R.id.Page1_NextSongButton);

        nextSongButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ChangeToNextSong();
            }
        });

        ImageButton playPauseSongButton = findViewById(R.id.Page1_PlayPauseButton);

        playPauseSongButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                PlayPauseSong();
            }
        });

        ImageButton shuffleSongButton = findViewById(R.id.Page1_ShuffleSongButton);

        shuffleSongButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ChangePlayingMode();
            }
        });

        Button cancelFolderButton = findViewById(R.id.Page2_ToolbarCancelButton);

        cancelFolderButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                CurrentInfo.State = com.example.mediaplayer.Core.CurrentInfo.States.SongPlaying;
                ChangeToWindow();
            }
        });

        Button selectFolderButton = findViewById(R.id.Page2_ToolbarSelectButton);

        selectFolderButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (DirectoryTree.FolderHasSupportedAudioFiles())
                {
                    DirectoryTree.NewPlaylistFromFolder();
                    CurrentInfo.State = com.example.mediaplayer.Core.CurrentInfo.States.SongPlaying;
                    ChangeToWindow();
                }
                else
                    Toast.makeText(getApplicationContext(), "This folder doesn't have supported music files", Toast.LENGTH_LONG).show();
            }
        });

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O)
        {
            NotificationChannel channel = new NotificationChannel("Notification_Channel", "Notification_Channel_Name", NotificationManager.IMPORTANCE_DEFAULT);
            channel.setDescription("Notification_Channel_Description");
            NotificationManager notificationManager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
            notificationManager.createNotificationChannel(channel);
        }

        NotificationBroadcast receiver = new NotificationBroadcast(this);
        this.registerReceiver(receiver, new IntentFilter(NotificationBroadcast.Actions.shuffleAction.toString()));
        this.registerReceiver(receiver, new IntentFilter(NotificationBroadcast.Actions.previousAction.toString()));
        this.registerReceiver(receiver, new IntentFilter(NotificationBroadcast.Actions.playPauseAction.toString()));
        this.registerReceiver(receiver, new IntentFilter(NotificationBroadcast.Actions.nextAction.toString()));
        this.registerReceiver(receiver, new IntentFilter(Intent.ACTION_HEADSET_PLUG));
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        getMenuInflater().inflate(R.menu.home, menu);
        ToolbarMenu = menu;
        LoadMenuPlaylists();
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public void onBackPressed()
    {
        if (CurrentInfo.State == com.example.mediaplayer.Core.CurrentInfo.States.PlaylistCreation)
        {
            DirectoryTree.BackOneStep();
        }
        else if (CurrentInfo.State == com.example.mediaplayer.Core.CurrentInfo.States.SongPlaying)
        {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle("Exit");
            builder.setMessage("Do you want to exit?");
            builder.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                        ((NotificationManager) getSystemService(NOTIFICATION_SERVICE)).cancel(10);
                    }
                    android.os.Process.killProcess(android.os.Process.myPid());
                }
            });
            builder.setNegativeButton("No", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {

                }
            });
            builder.show();
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        switch (item.getItemId())
        {
            case R.id.menu_playlist:
                break;
            case R.id.new_playlist:
                if(checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED)
                {
                    if (shouldShowRequestPermissionRationale(Manifest.permission.READ_EXTERNAL_STORAGE))
                        Toast.makeText(this, "Cannot create a playlist without Read SdCard permission", Toast.LENGTH_SHORT).show();
                    else
                        requestPermissions(new String[] { Manifest.permission.READ_EXTERNAL_STORAGE }, Permissions.ReadExternalStorage.ordinal());
                }
                else
                {
                    CurrentInfo.State = com.example.mediaplayer.Core.CurrentInfo.States.PlaylistCreation;
                    DirectoryTree = new DirectoryNavigation(this, ((ListView)findViewById(R.id.Page2_FolderStructure)));
                    DirectoryTree.OpenFolder();
                    ChangeToWindow();
                }
                break;
            default:
                for(AbstractMap.SimpleEntry MenuID : PlaylistMenuID)
            {
                if(((int)MenuID.getKey()) == item.getItemId())
                {
                    CurrentInfo.Playlist = Playlists.get((int)MenuID.getValue());
                    CurrentInfo.SongIndex = 0;
                    CurrentInfo.PlayedSongs = Collections.nCopies(Playlists.get((int)MenuID.getValue()).GetSongPaths().size(), false);
                    CurrentInfo.LastSong = -1;
                    SaveCurrentInfo();
                    ChangePlayingSong(false);
                    break;
                }
            }
            break;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults)
    {
        switch (Permissions.values()[requestCode])
        {
            case ReadExternalStorage:
                if(grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED)
                {
                    CurrentInfo.State = com.example.mediaplayer.Core.CurrentInfo.States.PlaylistCreation;
                    DirectoryTree = new DirectoryNavigation(this, ((ListView)findViewById(R.id.Page2_FolderStructure)));
                    DirectoryTree.OpenFolder();
                    ChangeToWindow();
                }
                else
                    Toast.makeText(this, "Cannot create a playlist without Read SdCard permission", Toast.LENGTH_SHORT).show();

                break;
        }
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event)
    {
        if (event.getKeyCode() == KeyEvent.KEYCODE_VOLUME_DOWN) {
            if(event.getAction() == KeyEvent.ACTION_DOWN && event.isLongPress()){
                LongPress = true;
                ChangeToPreviousSong();
                return true;
            }else if(event.getAction() == KeyEvent.ACTION_DOWN){
                if(AudioLock)
                    return true;
                else{
                    AudioLock = true;
                    return true;
                }
            }else if(event.getAction() == KeyEvent.ACTION_UP) {
                if(AudioLock)
                    AudioLock = false;
                if(!LongPress)
                    AudioVolumeManager.adjustVolume(AudioManager.ADJUST_LOWER, AudioManager.FLAG_PLAY_SOUND
                            | AudioManager.FLAG_SHOW_UI);
                LongPress = false;
            }
        }else if(event.getKeyCode() == KeyEvent.KEYCODE_VOLUME_UP){
            if(event.getAction() == KeyEvent.ACTION_DOWN && event.isLongPress()){
                LongPress = true;
                ChangeToNextSong();
                return true;
            }else if(event.getAction() == KeyEvent.ACTION_DOWN){
                if(AudioLock)
                    return true;
                else{
                    AudioLock = true;
                    return true;
                }
            }else if(event.getAction() == KeyEvent.ACTION_UP) {
                if(AudioLock)
                    AudioLock = false;
                if(!LongPress)
                    AudioVolumeManager.adjustVolume(AudioManager.ADJUST_RAISE, AudioManager.FLAG_PLAY_SOUND
                            | AudioManager.FLAG_SHOW_UI);
                LongPress = false;
            }
        }
        return super.dispatchKeyEvent(event);
    }

    private void ChangeToWindow()
    {
        int index = CurrentInfo.State.ordinal();
        for(int i=0; i<Pages.size(); i++)
        {
            if (i == index)
                Pages.get(i).setVisibility(View.VISIBLE);
            else
                Pages.get(i).setVisibility(View.INVISIBLE);
        }
    }

    private void OpenNotification()
    {
        ServiceConnection mConnection = new ServiceConnection() {
            public void onServiceConnected(ComponentName className,
                                           IBinder binder) {
                ((NotificationKillerService.KillBinder) binder).service.startService(new Intent(
                        MainActivity.this, NotificationKillerService.class));

                Intent intent = new Intent(MainActivity.this, MainActivity.class);
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
                TaskStackBuilder taskBuilder = TaskStackBuilder.create(MainActivity.this);
                taskBuilder.addNextIntent(intent);

                NotificationCompat.Builder notificationBuilder = new NotificationCompat.Builder(MainActivity.this, "Notification_Channel")
                        .setSmallIcon(R.drawable.ic_play_song_button)
                        .setAutoCancel(false)
                        .setOnlyAlertOnce(true)
                        .setOngoing(true)
                        .setContentIntent(taskBuilder.getPendingIntent(0, PendingIntent.FLAG_UPDATE_CURRENT))
                        .setCustomContentView(new RemoteViews(getPackageName(), R.layout.notification))
                        .setPriority(NotificationCompat.PRIORITY_LOW)
                        .setVisibility(NotificationCompat.VISIBILITY_PUBLIC);

                Notification notification = notificationBuilder.build();

                if (Player.isPlaying())
                    notification.contentView.setImageViewResource(R.id.Notification_PlayPauseButton, R.drawable.ic_pause_song_button);
                else
                    notification.contentView.setImageViewResource(R.id.Notification_PlayPauseButton, R.drawable.ic_play_song_button);

                if (CurrentInfo.PlayingMode == com.example.mediaplayer.Core.CurrentInfo.PlayingModes.ShuffleMode)
                    notification.contentView.setImageViewResource(R.id.Notification_ShuffleSongButton, R.drawable.ic_shuffle_song_button);
                else
                    notification.contentView.setImageViewResource(R.id.Notification_ShuffleSongButton, R.drawable.ic_shuffle_disabled_song_button);

                if (CurrentInfo.Playlist != null)
                {
                    notification.contentView.setTextViewText(R.id.Notification_SongName, ((TextView)findViewById(R.id.Page1_SongName)).getText());
                    notification.contentView.setTextViewText(R.id.Notification_SongAuthor, ((TextView)findViewById(R.id.Page1_SongAuthor)).getText());

                    Meta.setDataSource(CurrentInfo.Playlist.GetSongPaths().get(CurrentInfo.SongIndex));
                    byte[] cover = Meta.getEmbeddedPicture();
                    if (cover != null)
                    {
                        Bitmap coverBitmap = BitmapFactory.decodeByteArray(cover, 0, cover.length);
                        notification.contentView.setImageViewBitmap(R.id.Notification_SongImage, coverBitmap);
                    }
                }
                else
                {
                    notification.contentView.setTextViewText(R.id.Notification_SongName, "No song playing");
                }

                Intent shuffleIntent = new Intent(NotificationBroadcast.Actions.shuffleAction.toString());
                PendingIntent shufflePreviousIntent = PendingIntent.getBroadcast(getApplicationContext(), 0, shuffleIntent, PendingIntent.FLAG_UPDATE_CURRENT);

                Intent previousIntent = new Intent(NotificationBroadcast.Actions.previousAction.toString());
                PendingIntent previousPreviousIntent = PendingIntent.getBroadcast(getApplicationContext(), 0, previousIntent, PendingIntent.FLAG_UPDATE_CURRENT);

                Intent playPauseIntent = new Intent(NotificationBroadcast.Actions.playPauseAction.toString());
                PendingIntent playPausePreviousIntent = PendingIntent.getBroadcast(getApplicationContext(), 0, playPauseIntent, PendingIntent.FLAG_UPDATE_CURRENT);

                Intent nextIntent = new Intent(NotificationBroadcast.Actions.nextAction.toString());
                PendingIntent nextPreviousIntent = PendingIntent.getBroadcast(getApplicationContext(), 0, nextIntent, PendingIntent.FLAG_UPDATE_CURRENT);

                notification.contentView.setOnClickPendingIntent(R.id.Notification_ShuffleSongButton, shufflePreviousIntent);
                notification.contentView.setOnClickPendingIntent(R.id.Notification_PreviousSongButton, previousPreviousIntent);
                notification.contentView.setOnClickPendingIntent(R.id.Notification_PlayPauseButton, playPausePreviousIntent);
                notification.contentView.setOnClickPendingIntent(R.id.Notification_NextSongButton, nextPreviousIntent);

                ((NotificationManager) getSystemService(NOTIFICATION_SERVICE)).notify(10, notification);
            }

            public void onServiceDisconnected(ComponentName className) { }
        };

        bindService(new Intent(MainActivity.this,
                        NotificationKillerService.class), mConnection,
                Context.BIND_AUTO_CREATE);
    }

    private void LoadCurrentInfoFromDB()
    {
        T_Setup info = Database.GetCurrentInfo();

        if (info != null)
        {
            CurrentInfo.PlayingMode = com.example.mediaplayer.Core.CurrentInfo.PlayingModes.values()[info.PlayingMode];

            if (CurrentInfo.PlayingMode == com.example.mediaplayer.Core.CurrentInfo.PlayingModes.NormalMode)
                ((ImageButton)findViewById(R.id.Page1_ShuffleSongButton)).setImageResource(R.drawable.ic_shuffle_disabled_song_button);
            else if (CurrentInfo.PlayingMode == com.example.mediaplayer.Core.CurrentInfo.PlayingModes.ShuffleMode)
                ((ImageButton)findViewById(R.id.Page1_ShuffleSongButton)).setImageResource(R.drawable.ic_shuffle_song_button);

            for (Playlist playlist : Playlists)
            {
                if (playlist.GetName().equals(info.Playlist))
                {
                    CurrentInfo.Playlist = playlist;
                    CurrentInfo.SongIndex = info.SongIndex;
                    CurrentInfo.PlayedSongs = new ArrayList<>(Collections.nCopies(playlist.GetSongPaths().size(), false));
                }
            }

            CurrentInfo.LastSong = -1;

            ChangePlayingSong(false);
        }

        OpenNotification();
    }

    private boolean SaveCurrentInfo()
    {
        return Database.InsertCurrentInfo(CurrentInfo);
    }

    private void LoadPlaylistsFromDB()
    {
        List<T_Playlist> dbPlaylists = Database.GetPlaylists();
        if(dbPlaylists != null) {
            for(T_Playlist dbPlaylist : dbPlaylists)
            {
                Playlist pl = new Playlist(dbPlaylist.Name);

                List<T_Song> dbSongs = Database.GetSongsByPlaylistID(dbPlaylist.Id);

                if(dbSongs != null){
                    for(T_Song dbSong : dbSongs)
                    {
                        pl.AddSong(dbSong.Path);
                    }
                }

                Playlists.add(pl);
            }
        }
    }

    private void LoadMenuPlaylists()
    {
        for(Playlist playlist : Playlists)
        {
            int itemId = R.id.new_playlist - 1000000000 + PlaylistMenuID.size();

            ToolbarMenu.findItem(R.id.menu_playlist).getSubMenu().add(0, itemId, 0, playlist.GetName());
            PlaylistMenuID.add(new AbstractMap.SimpleEntry<>(itemId, Playlists.indexOf(playlist)));
        }
    }

    public void AddPlaylist(Playlist playlist)
    {
        Playlists.add(playlist);
        boolean result = Database.InsertNewPlaylist(playlist);

        if (result)
        {
            int itemId = R.id.new_playlist - 1000000000 + PlaylistMenuID.size();

            ToolbarMenu.findItem(R.id.menu_playlist).getSubMenu().add(0, itemId, 0, playlist.GetName());
            PlaylistMenuID.add(new AbstractMap.SimpleEntry<>(itemId, Playlists.indexOf(playlist)));

            CurrentInfo.Playlist = playlist;
            CurrentInfo.SongIndex = 0;
            CurrentInfo.PlayedSongs = Collections.nCopies(playlist.GetSongPaths().size(), false);
            CurrentInfo.LastSong = -1;
            result = SaveCurrentInfo();

            if(result)
                ChangePlayingSong(false);
            else
                Toast.makeText(this, "Playlist added, a problem has occurred during playlist change", Toast.LENGTH_SHORT).show();
        }
        else
            Toast.makeText(this, "A problem has occurred, cannot add the playlist", Toast.LENGTH_SHORT).show();
    }

    private void ChangePlayingSong(){
        ChangePlayingSong(true);
    }

    private void ChangePlayingSong(boolean start)
    {
        if (CurrentInfo.Playlist != null)
        {
            Player.reset();
            try {
                Player.setDataSource(CurrentInfo.Playlist.GetSongPaths().get(CurrentInfo.SongIndex));
                Player.prepare();
            } catch (IOException e) {
                e.printStackTrace();
            }

            Meta.setDataSource(CurrentInfo.Playlist.GetSongPaths().get(CurrentInfo.SongIndex));
            byte[] cover = Meta.getEmbeddedPicture();
            ((TextView)findViewById(R.id.Page1_SongName)).setText(Meta.extractMetadata(MediaMetadataRetriever.METADATA_KEY_TITLE));
            ((TextView)findViewById(R.id.Page1_SongAuthor)).setText(String.format("%s - %s",
                    Meta.extractMetadata(MediaMetadataRetriever.METADATA_KEY_ARTIST),
                    Meta.extractMetadata(MediaMetadataRetriever.METADATA_KEY_ALBUM)));

            if (((TextView) findViewById(R.id.Page1_SongName)).getText() == "")
            {
                String songName = CurrentInfo.Playlist.GetSongPaths().get(CurrentInfo.SongIndex);
                songName = songName.replace('\\', '/');
                songName = songName.substring(songName.lastIndexOf('/') + 1,
                        songName.lastIndexOf('.') - (songName.lastIndexOf('/') + 1));
                ((TextView) findViewById(R.id.Page1_SongName)).setText(songName);
            }

            if (cover != null)
            {
                Bitmap coverBitmap = BitmapFactory.decodeByteArray(cover, 0, cover.length);
                ((ImageView)findViewById(R.id.Page1_SongImage)).setImageBitmap(coverBitmap);
            }

            if (start)
            {
                ((ImageButton)findViewById(R.id.Page1_PlayPauseButton)).setImageResource(R.drawable.ic_pause_song_button);
                Player.start();
            }
        }
    }

    public void PlayPauseSong()
    {
        if (CurrentInfo.Playlist != null && CurrentInfo.State == com.example.mediaplayer.Core.CurrentInfo.States.SongPlaying)
        {
            if (!Player.isPlaying())
            {
                int pos = Player.getCurrentPosition();

                if (pos < 0)
                    ChangePlayingSong();
                else
                {
                    Player.start();
                    ((ImageButton)findViewById(R.id.Page1_PlayPauseButton)).setImageResource(R.drawable.ic_pause_song_button);
                }
            }
            else
            {
                Player.pause();

                ((ImageButton)findViewById(R.id.Page1_PlayPauseButton)).setImageResource(R.drawable.ic_play_song_button);
            }
        }

        OpenNotification();
    }

    public void PlaySong()
    {
        if (CurrentInfo.Playlist != null && CurrentInfo.State == com.example.mediaplayer.Core.CurrentInfo.States.SongPlaying)
        {
            if (!Player.isPlaying())
            {
                int pos = Player.getCurrentPosition();

                if (pos < 0)
                    ChangePlayingSong();
                else
                {
                    Player.start();
                    ((ImageButton)findViewById(R.id.Page1_PlayPauseButton)).setImageResource(R.drawable.ic_pause_song_button);
                }
            }
        }

        OpenNotification();
    }

    public void PauseSong()
    {
        if (CurrentInfo.Playlist != null && CurrentInfo.State == com.example.mediaplayer.Core.CurrentInfo.States.SongPlaying)
        {
            if (Player.isPlaying())
            {
                Player.pause();

                ((ImageButton)findViewById(R.id.Page1_PlayPauseButton)).setImageResource(R.drawable.ic_play_song_button);
            }
        }

        OpenNotification();
    }

    public void ChangeToNextSong()
    {
        if (CurrentInfo.Playlist != null && CurrentInfo.State == com.example.mediaplayer.Core.CurrentInfo.States.SongPlaying)
        {
            boolean result = false;
            if (CurrentInfo.PlayingMode == com.example.mediaplayer.Core.CurrentInfo.PlayingModes.NormalMode)
            {
                if (CurrentInfo.SongIndex < CurrentInfo.Playlist.GetSongPaths().size() - 1)
                {
                    CurrentInfo.SongIndex += 1;
                    result = SaveCurrentInfo();
                }
            }
            else if (CurrentInfo.PlayingMode == com.example.mediaplayer.Core.CurrentInfo.PlayingModes.ShuffleMode)
            {
                Random rand = new Random();
                int nextSong = rand.nextInt(CurrentInfo.Playlist.GetSongPaths().size());

                for (int i = 0; CurrentInfo.PlayedSongs.get(nextSong); i++)
                {
                    nextSong = rand.nextInt(CurrentInfo.Playlist.GetSongPaths().size());

                    if (i > CurrentInfo.Playlist.GetSongPaths().size() / 8)
                    {
                        CurrentInfo.PlayedSongs = new ArrayList<>(Collections.nCopies(CurrentInfo.Playlist.GetSongPaths().size(), false));
                    }
                }

                CurrentInfo.PlayedSongs.set(nextSong, true);
                CurrentInfo.LastSong = CurrentInfo.SongIndex;
                CurrentInfo.SongIndex = nextSong;
                result = SaveCurrentInfo();
            }

            if(result){
                ChangePlayingSong(Player.isPlaying());
                OpenNotification();
            }else
                Toast.makeText(this, "A problem has occurred during song change", Toast.LENGTH_SHORT).show();
        }
    }

    public void ChangeToPreviousSong()
    {
        if (CurrentInfo.Playlist != null && CurrentInfo.State == com.example.mediaplayer.Core.CurrentInfo.States.SongPlaying)
        {
            boolean result = true;
            if (Player.getCurrentPosition() <= 10000)
            {
                if (CurrentInfo.PlayingMode == com.example.mediaplayer.Core.CurrentInfo.PlayingModes.NormalMode)
                {
                    if (CurrentInfo.SongIndex > 0)
                    {
                        CurrentInfo.SongIndex -= 1;
                        result = SaveCurrentInfo();
                    }
                }
                else if (CurrentInfo.PlayingMode == com.example.mediaplayer.Core.CurrentInfo.PlayingModes.ShuffleMode)
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

                    result = SaveCurrentInfo();
                }

                if(result)
                    ChangePlayingSong(Player.isPlaying());
                else
                    Toast.makeText(this, "A problem has occurred during song change", Toast.LENGTH_SHORT).show();
            }
            else
                Player.seekTo(0);

            if(result)
                OpenNotification();
        }
    }

    public void ChangePlayingMode()
    {
        if (CurrentInfo.PlayingMode == com.example.mediaplayer.Core.CurrentInfo.PlayingModes.NormalMode)
        {
            CurrentInfo.PlayingMode = com.example.mediaplayer.Core.CurrentInfo.PlayingModes.ShuffleMode;

            ((ImageButton)findViewById(R.id.Page1_ShuffleSongButton)).setImageResource(R.drawable.ic_shuffle_song_button);
        }
        else if (CurrentInfo.PlayingMode == com.example.mediaplayer.Core.CurrentInfo.PlayingModes.ShuffleMode)
        {
            CurrentInfo.PlayingMode = com.example.mediaplayer.Core.CurrentInfo.PlayingModes.NormalMode;

            ((ImageButton)findViewById(R.id.Page1_ShuffleSongButton)).setImageResource(R.drawable.ic_shuffle_disabled_song_button);
        }

        OpenNotification();
    }

    public void ShowFolderEmpty()
    {
        if(CurrentInfo.State == com.example.mediaplayer.Core.CurrentInfo.States.PlaylistCreation)
            findViewById(R.id.Page2_FolderEmpty).setVisibility(View.VISIBLE);
    }

    public void HideFolderEmpty()
    {
        if (CurrentInfo.State == com.example.mediaplayer.Core.CurrentInfo.States.PlaylistCreation)
            findViewById(R.id.Page2_FolderEmpty).setVisibility(View.INVISIBLE);
    }
}
