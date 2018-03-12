using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace Riot_API
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            foreach (string region in Request.RegionNames)
            {
                RegionBox.Items.Add(region);
            }
            RegionBox.Text = Request.RegionNames[2];

            // Initialize watermark
            SummonerNameText.Text = "Summoner name";
            SummonerNameText.Foreground = Brushes.Silver;

            Request.Init();
        }

        public void RequestCurrentGameInfo()
        {
            CurrentGame currentGameWindow;
            try
            {
                currentGameWindow = new CurrentGame();
            }
            catch (WebException exeption)
            {
                MessageBox.Show(exeption.Message + '\n' + Request.LastError, exeption.Status.ToString(), MessageBoxButton.OK, MessageBoxImage.Warning, MessageBoxResult.OK, MessageBoxOptions.DefaultDesktopOnly);
                return;
            }
            currentGameWindow.HorizontalAlignment = HorizontalAlignment.Stretch;
            currentGameWindow.VerticalAlignment = VerticalAlignment.Stretch;
            Grid.SetRow(currentGameWindow, 1);
            ParentGrid.Children.Add(currentGameWindow);
        }

        private void GoButton_Click(object sender, RoutedEventArgs e)
        {
            if (Request.SummonerName != null)
            {
                RequestCurrentGameInfo();
            }
        }

        private void SummonerNameText_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (SummonerNameText.Text != "Summoner name" || Request.SummonerName != "")
            {
                Request.SummonerName = SummonerNameText.Text;
            }
        }

        private void RegionBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Request.SelectedRegion = Request.RegionServer[RegionBox.SelectedIndex];
        }

        private void SummonerNameText_PreviewGotKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            if (SummonerNameText.Text == "Summoner name")
            {
                SummonerNameText.Text = "";
                SummonerNameText.Foreground = Brushes.Black;
            }
        }

        private void SummonerNameText_PreviewLostKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            if (SummonerNameText.Text == "")
            {
                SummonerNameText.Text = "Summoner name";
                SummonerNameText.Foreground = Brushes.Silver;
            }
        }

        private void SummonerNameText_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
            {
                GoButton_Click(sender, e);
            }
        }
    }
}
