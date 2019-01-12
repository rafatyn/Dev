using Riot_API;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Microsoft.Win32;

namespace PruebaAvisosLol
{    
    public partial class OptionWindow : Window
    {
        MainWindow window;
        private int corner;

        public OptionWindow(MainWindow parent, string summonerName, int imgSize, int imgCorner, string soundPath)
        {
            InitializeComponent();

            window = parent;

            SummonerName.Text = summonerName;
            ImageSize.Text = imgSize.ToString();
            corner = imgCorner;
            SoundPath.Text = soundPath;
            SoundPath.IsReadOnly = true;
        }
        
        private void SummonerName_TextChanged(object sender, TextChangedEventArgs e)
        {
            if(SummonerName.Text != null && ImageSize.Value != null)
            {
                window.UpdateInfo(SummonerName.Text, (int)ImageSize.Value, SoundPath.Text);
            }
            else
            {
                MessageBox.Show("Summmoner name o Image size must have a value", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ImageSize_ValueChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            if (SummonerName.Text != null && ImageSize.Value != null)
            {
                window.UpdateInfo(SummonerName.Text, (int)ImageSize.Value, SoundPath.Text);
            }
            else
            {
                MessageBox.Show("Summmoner name o Image size must have a value", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void CornerTI_Click(object sender, RoutedEventArgs e)
        {
            corner = 0;
        }

        private void CornerTD_Click(object sender, RoutedEventArgs e)
        {
            corner = 1;
        }

        private void CornerBD_Click(object sender, RoutedEventArgs e)
        {
            corner = 2;
        }

        private void CornerBI_Click(object sender, RoutedEventArgs e)
        {
            corner = 3;
        }        

        private void LoadGame_Click(object sender, RoutedEventArgs e)
        {
            window.CurrentGame();
        }

        private void SaveOptions_Click(object sender, RoutedEventArgs e)
        {
            string[] options = new string[4];
            options[0] = "SummonerName=" + SummonerName.Text;
            options[1] = "ImageSize=" + ((int)ImageSize.Value).ToString();
            options[2] = "CornerPosition=" + corner.ToString();
            options[3] = "SoundPath=" + SoundPath.Text;

            File.WriteAllLines(Directory.GetParent(Assembly.GetExecutingAssembly().Location) + "\\Resources\\options.ini", options);
        }

        private void SoundPath_MouseUp(object sender, MouseButtonEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Sound files (*.mp3, *.wav)|*.mp3;*.wav";
            if (openFileDialog.ShowDialog() == true)
                SoundPath.Text = openFileDialog.FileName;

            if (SummonerName.Text != null && ImageSize.Value != null)
            {
                window.UpdateInfo(SummonerName.Text, (int)ImageSize.Value, SoundPath.Text);
            }
            else
            {
                MessageBox.Show("Summmoner name o Image size must have a value", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void Jungle_Click(object sender, RoutedEventArgs e)
        {
            window.showJungleTimes(Jungle.IsChecked == true);
        }
    }
}
