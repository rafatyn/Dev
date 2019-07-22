package com.example.mediaplayer.Database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteStatement;

import com.example.mediaplayer.Core.CurrentInfo;
import com.example.mediaplayer.Core.Playlist;
import com.example.mediaplayer.Database.Tables.T_Playlist;
import com.example.mediaplayer.Database.Tables.T_Setup;
import com.example.mediaplayer.Database.Tables.T_Song;

import java.util.ArrayList;
import java.util.List;

public class Database extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "sqlite.db3";
    private SQLiteDatabase Database;

    public Database(Context context) {
        super(context, DATABASE_NAME, null, 1);
        Database = getWritableDatabase();
    }

    @Override
    public void onCreate(SQLiteDatabase db)
    {
        db.execSQL(T_Playlist.CREATE);
        db.execSQL(T_Setup.CREATE);
        db.execSQL(T_Song.CREATE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        onCreate(db);
    }

    @Override
    public void onDowngrade(SQLiteDatabase db, int oldVersion, int newVersion)
    {
        onUpgrade(db, oldVersion, newVersion);
    }

    public List<T_Playlist> GetPlaylists()
    {
        Database.beginTransaction();
        Cursor cursor = Database.rawQuery(T_Playlist.GET_ALL_PLAYLIST, null);

        if(cursor != null){
            List<T_Playlist> playlist = new ArrayList<>();

            cursor.moveToFirst();
            while(!cursor.isAfterLast()){
                playlist.add(new T_Playlist(cursor.getInt(cursor.getColumnIndex(T_Playlist.Fields.ID.name())),
                            cursor.getString(cursor.getColumnIndex(T_Playlist.Fields.Name.name()))));
                cursor.moveToNext();
            }

            Database.setTransactionSuccessful();
            Database.endTransaction();
            cursor.close();
            return playlist;
        }

        Database.endTransaction();
        return null;
    }

    public boolean InsertNewPlaylist(Playlist playlist)
    {
        Database.beginTransaction();
        SQLiteStatement query = Database.compileStatement(T_Playlist.INSERT_PLAYLIST);
        query.bindString(1, playlist.GetName());
        long result = query.executeInsert();

        if (result > 0)
        {
            int playlistID = (int)result;
            long countInserted = 0;

            for(String songPath : playlist.GetSongPaths())
            {
                SQLiteStatement subQuery = Database.compileStatement(T_Song.INSERT_SONGS);
                subQuery.bindString(1, songPath);
                subQuery.bindDouble(2, playlistID);
                countInserted += subQuery.executeInsert() > 0 ? 1 : 0;
            }

            if (countInserted == playlist.GetSongPaths().size())
            {
                Database.setTransactionSuccessful();
                Database.endTransaction();
                return true;
            }
            else
            {
                Database.endTransaction();
                return false;
            }
        }
        else
        {
            Database.endTransaction();
            return false;
        }
    }

    public List<T_Song> GetSongsByPlaylistID(int id)
    {
        Database.beginTransaction();
        Cursor cursor = Database.rawQuery(T_Song.GET_SONGS_BY_PLAYLIST, new String[] { Integer.toString(id) } );

        if(cursor != null){
            List<T_Song> songs = new ArrayList<>();

            cursor.moveToFirst();
            while(!cursor.isAfterLast()){
                songs.add(new T_Song(cursor.getString(cursor.getColumnIndex(T_Song.Fields.Path.name())),
                        cursor.getInt(cursor.getColumnIndex(T_Song.Fields.Playlist.name()))));
                cursor.moveToNext();
            }

            Database.setTransactionSuccessful();
            Database.endTransaction();
            cursor.close();
            return songs;
        }

        Database.endTransaction();
        return null;
    }

    public T_Setup GetCurrentInfo()
    {
        Database.beginTransaction();
        Cursor cursor = Database.rawQuery(T_Setup.GET_CURRENT_INFO, null);

        if(cursor != null){
            T_Setup setup = null;

            cursor.moveToFirst();
            if(!cursor.isAfterLast())
                setup = new T_Setup(cursor.getString(cursor.getColumnIndex(T_Setup.Fields.Playlist.name())),
                        cursor.getInt(cursor.getColumnIndex(T_Setup.Fields.SongIndex.name())),
                        cursor.getInt(cursor.getColumnIndex(T_Setup.Fields.PlayingMode.name())));

            Database.setTransactionSuccessful();
            Database.endTransaction();
            cursor.close();
            return setup;
        }

        Database.endTransaction();
        return null;
    }

    public boolean InsertCurrentInfo(CurrentInfo currentInfo)
    {
        Database.beginTransaction();

        Database.delete("Setup", "1", null);

        ContentValues values = new ContentValues();
        values.put(T_Setup.Fields.Playlist.name(), currentInfo.Playlist.GetName());
        values.put(T_Setup.Fields.SongIndex.name(), currentInfo.SongIndex);
        values.put(T_Setup.Fields.PlayingMode.name(), currentInfo.PlayingMode.ordinal());

        long result = Database.insert("Setup", null, values);

        if(result > 0){
            Database.setTransactionSuccessful();
            Database.endTransaction();
            return true;
        } else {
            Database.endTransaction();
            return false;
        }
    }
}
