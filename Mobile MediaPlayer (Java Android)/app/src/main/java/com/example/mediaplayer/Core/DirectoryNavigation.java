package com.example.mediaplayer.Core;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;

import com.example.mediaplayer.MainActivity;
import com.example.mediaplayer.R;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class DirectoryNavigation {
    private String CurrentFolder;
    private ListView ListView;
    private MainActivity Handler;

    public DirectoryNavigation(MainActivity handler, ListView list){
        this(handler, list, null);
    }

    public DirectoryNavigation(MainActivity handler, ListView list, String uri)
    {
        if (uri != null && !uri.isEmpty())
            CurrentFolder = uri;
        else
            //CurrentFolder = Environment.RootDirectory.Path;
            CurrentFolder = "/mnt";

        ListView = list;
        Handler = handler;

        ListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                String previousFolder = CurrentFolder;
                CurrentFolder = CurrentFolder + '/' + parent.getItemAtPosition(position);
                if (!OpenFolder())
                {
                    CurrentFolder = previousFolder;
                }
            }
        });
    }

    public boolean OpenFolder()
    {
        List<String> items = new ArrayList<>();
        File rootDirectory;
        rootDirectory = new File(CurrentFolder);

        if (rootDirectory.exists())
        {
            File[] files = rootDirectory.listFiles();

            if (files != null)
            {
                for(File file : files)
                {
                    if (file.isDirectory())
                    {
                        items.add(file.getName());
                    }
                }

                if (items.size() > 0)
                {
                    Handler.HideFolderEmpty();
                    ListView.setVisibility(View.VISIBLE);

                    ListView.setAdapter(new ArrayAdapter<>(Handler, android.R.layout.simple_list_item_1, items));
                }
                else
                {
                    // TODO: Mostrar archivos y directorios
                    Handler.ShowFolderEmpty();
                    ListView.setVisibility(View.INVISIBLE);
                }

                return true;
            }
        }

        return false;
    }

    public void BackOneStep()
    {
        if (CurrentFolder.lastIndexOf('/') > 1)
        {
            CurrentFolder = CurrentFolder.substring(0, CurrentFolder.lastIndexOf('/'));
            OpenFolder();
        }
    }

    public List<String> FilesIntoFolder(String folderPath)
    {
        return FilesIntoFolder(folderPath, false);
    }

    public List<String> FilesIntoFolder(String folderPath, boolean absolutePath)
    {
        List<String> items = new ArrayList<>();
        File rootDirectory = new File(folderPath);

        if (rootDirectory.exists())
        {
            File[] files = rootDirectory.listFiles();

            if (files != null)
            {
                for(File file : files)
                {
                    if (file.isFile())
                    {
                        if (!absolutePath)
                            items.add(file.getName());
                        else
                            items.add(folderPath + '/' + file.getName());
                    }
                }

                return items;
            }
            else
            {
                return null;
            }
        }
        else
        {
            return null;
        }
    }

    public boolean FolderHasSupportedAudioFiles(){
        return FolderHasSupportedAudioFiles(null);
    }

    public boolean FolderHasSupportedAudioFiles(String path)
    {
        File rootFolder;
        if (path == null)
            rootFolder = new File(CurrentFolder);
        else
            rootFolder = new File(path);

        File[] files = rootFolder.listFiles();

        if (files != null)
        {
            for(File file : files)
            {
                if (file.isFile())
                {
                    if (file.getName().toLowerCase().endsWith(".mp3") || file.getName().toLowerCase().endsWith(".m4a") ||
                            file.getName().toLowerCase().endsWith(".wav") || file.getName().toLowerCase().endsWith(".ogg") ||
                            file.getName().toLowerCase().endsWith(".aac"))
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    public void NewPlaylistFromFolder(){
        NewPlaylistFromFolder(null);
    }

    public void NewPlaylistFromFolder(String path)
    {
        List<String> filesFolder;
        if (path == null)
            filesFolder = FilesIntoFolder(CurrentFolder, true);
        else
            filesFolder = FilesIntoFolder(path, true);

        final List<String> musicFiles = new ArrayList<>();
        for(String fileName : filesFolder)
        {
            if (fileName.toLowerCase().endsWith(".mp3") || fileName.toLowerCase().endsWith(".m4a") ||
                    fileName.toLowerCase().endsWith(".wav") || fileName.toLowerCase().endsWith(".ogg") ||
                    fileName.toLowerCase().endsWith(".aac"))
            {
                musicFiles.add(fileName);
            }
        }

        AlertDialog.Builder nameBuilder = new AlertDialog.Builder(Handler);
        EditText playlistNameInput = new EditText(Handler);
        nameBuilder.setTitle("Playlist name");
        nameBuilder.setView(playlistNameInput);
        nameBuilder.setMessage("Introduce the desired name for the playlist");
        nameBuilder.setPositiveButton("Submit", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                Playlist pl = new Playlist(((EditText)((AlertDialog)dialog).getCurrentFocus()).getText().toString());
                pl.AddListSong(musicFiles);
                Handler.AddPlaylist(pl);
            }
        });
        nameBuilder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {

            }
        });
        nameBuilder.show();
    }
}
