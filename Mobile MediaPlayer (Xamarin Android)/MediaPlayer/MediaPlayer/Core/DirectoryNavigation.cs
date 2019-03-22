using System.Collections.Generic;
using Android.App;
using Android.OS;
using Android.Views;
using Android.Widget;
using Java.IO;

namespace MediaPlayer.Core
{
    internal class DirectoryNavigation
    {
        private string CurrentFolder;
        private ListView ListView;
        private MainActivity Handler;

        public DirectoryNavigation(MainActivity handler, ListView list, string uri = null)
        {
            if (uri != null && uri != "")
                CurrentFolder = uri;
            else
                //CurrentFolder = Environment.RootDirectory.Path;
                CurrentFolder = "/mnt";

            ListView = list;
            Handler = handler;

            ListView.ItemClick += (sender, e) =>
            {
                string previousFolder = CurrentFolder;
                CurrentFolder = CurrentFolder + '/' + ((ArrayAdapter)((ListView)sender).Adapter).GetItem(e.Position);
                if (!OpenFolder())
                {
                    CurrentFolder = previousFolder;
                }
            };
        }

        public bool OpenFolder()
        {
            List<string> items = new List<string>();
            File rootDirectory;
            rootDirectory = new File(CurrentFolder);

            if (rootDirectory != null)
            {
                File[] files = rootDirectory.ListFiles();

                if (files != null)
                {
                    foreach (File file in files)
                    {
                        if (file.IsDirectory)
                        {
                            items.Add(file.Name);
                        }
                    }

                    if (items.Count > 0)
                    {
                        Handler.HideFolderEmpty();
                        ListView.Visibility = ViewStates.Visible;

                        ListView.Adapter = new ArrayAdapter<string>(Handler, Android.Resource.Layout.SimpleListItem1, items);
                    }
                    else
                    {
                        // TODO: Mostrar archivos y directorios
                        Handler.ShowFolderEmpty();
                        ListView.Visibility = ViewStates.Invisible;
                    }

                    return true;
                }
            }

            return false;
        }

        public void BackOneStep()
        {
            if (CurrentFolder.LastIndexOf('/') > 1)
            {
                CurrentFolder = CurrentFolder.Substring(0, CurrentFolder.LastIndexOf('/'));
                OpenFolder();
            }
        }

        public List<string> FilesIntoFolder(string folderPath, bool absolutePath = false)
        {
            List<string> items = new List<string>();
            File rootDirectory = new File(folderPath);

            if (rootDirectory != null)
            {
                File[] files = rootDirectory.ListFiles();

                if (files != null)
                {
                    foreach (File file in files)
                    {
                        if (file.IsFile)
                        {
                            if (!absolutePath)
                                items.Add(file.Name);
                            else
                                items.Add(folderPath + '/' + file.Name);
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

        public bool FolderHasSupportedAudioFiles(string path = null)
        {
            File rootFolder;
            if (path == null)
                rootFolder = new File(CurrentFolder);
            else
                rootFolder = new File(path);

            File[] files = rootFolder.ListFiles();

            if (files != null)
            {
                foreach (File file in files)
                {
                    if (file.IsFile)
                    {
                        if (file.Name.ToLower().EndsWith(".mp3") || file.Name.ToLower().EndsWith(".m4a") || file.Name.ToLower().EndsWith(".wav") ||
                            file.Name.ToLower().EndsWith(".ogg") || file.Name.ToLower().EndsWith(".aac"))
                        {
                            return true;
                        }
                    }
                }
            }

            return false;
        }

        public void NewPlaylistFromFolder(string path = null)
        {
            List<string> filesFolder;
            if (path == null)
                filesFolder = FilesIntoFolder(CurrentFolder, true);
            else
                filesFolder = FilesIntoFolder(path, true);

            List<string> musicFiles = new List<string>();
            foreach (string fileName in filesFolder)
            {
                if (fileName.ToLower().EndsWith(".mp3") || fileName.ToLower().EndsWith(".m4a") || fileName.ToLower().EndsWith(".wav") ||
                    fileName.ToLower().EndsWith(".ogg") || fileName.ToLower().EndsWith(".aac"))
                {
                    musicFiles.Add(fileName);
                }
            }

            AlertDialog.Builder nameBuilder = new AlertDialog.Builder(Handler);
            EditText playlistNameInput = new EditText(Handler);
            nameBuilder.SetTitle("Playlist name");
            nameBuilder.SetView(playlistNameInput);
            nameBuilder.SetMessage("Introduce the desired name for the playlist");
            nameBuilder.SetPositiveButton("Submit", (nameSender, nameE) =>
            {
                Playlist pl = new Playlist(((EditText)((AlertDialog)nameSender).Window.CurrentFocus).Text);
                pl.AddListSong(musicFiles);
                Handler.AddPlaylist(pl);
            });
            nameBuilder.SetNegativeButton("Cancel", (nameSender, nameE) => { });
            nameBuilder.Show();
        }
    }
}