using PruebaAvisosLol;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Media;
using System.Net;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace Riot_API
{
    public partial class MainWindow : Window
    {
        private MediaPlayer player;
        private int ImgSize;
        private string summonerName;
        private int corner = 0;
        private DispatcherTimer everySecTimer;

        private List<Image> championImage;
        private List<Image> spell1Image;
        private List<Image> spell2Image;
        private List<Image> ultImage;
        private List<Image> monsterImage;

        private int[] spell1Cooldown;
        private int[] spell2Cooldown;
        private int[] ultCooldown;

        private int[] leftSpell1Cooldown;
        private int[] leftSpell2Cooldown;
        private int[] leftUltCooldown;
        private int[] leftMonsterCooldown;

        private List<Label> leftSpell1Label;
        private List<Label> leftSpell2Label;
        private List<Label> leftUltLabel;
        private List<Label> leftMonsterLabel;

        private bool[] spell1Active;
        private bool[] spell2Active;
        private bool[] ultActive;
        private bool[] monsterActive;

        private bool drawJungle;

        public MainWindow()
        {
            AppDomain.CurrentDomain.AssemblyResolve += (sender, args) =>
            {
                String resourceName = "AssemblyLoadingAndReflection." +
                   new AssemblyName(args.Name).Name + ".dll";
                using (var stream = Assembly.GetExecutingAssembly().GetManifestResourceStream(resourceName))
                {
                    Byte[] assemblyData = new Byte[stream.Length];
                    stream.Read(assemblyData, 0, assemblyData.Length);
                    return Assembly.Load(assemblyData);
                }
            };

            InitializeComponent();

            string[] options = File.ReadAllLines(Directory.GetParent(Assembly.GetExecutingAssembly().Location) + "\\Resources\\options.ini");
            string SoundPath = null;
            
            foreach(string option in options)
            {
                if (option.Contains("SummonerName"))
                {
                    summonerName = option.Substring(option.IndexOf("=")+1);
                }
                else if(option.Contains("ImageSize"))
                {
                    ImgSize = Int32.TryParse(option.Substring(option.IndexOf("=")+1), out ImgSize) == false ? 80 : Int32.Parse(option.Substring(option.IndexOf("=") + 1));
                }
                else if (option.Contains("CornerPosition"))
                {

                }
                else if (option.Contains("SoundPath"))
                {
                    SoundPath = option.Substring(option.IndexOf("=") + 1);
                }
            }

            System.Drawing.Icon icon = System.Drawing.Icon.ExtractAssociatedIcon(Directory.GetParent(Assembly.GetExecutingAssembly().Location) + "\\Resources\\LolIcon.ico");

            BitmapSource iconImage = System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap(icon.ToBitmap().GetHbitmap(), IntPtr.Zero,
                                          System.Windows.Int32Rect.Empty, BitmapSizeOptions.FromWidthAndHeight(icon.Width, icon.Height));

            this.Icon = iconImage;            
            TaskbarIcon.Icon = icon;

            ContextMenu CMenu = new ContextMenu();
            CMenu.Background = Brushes.White;

            MenuItem item1 = new MenuItem();
            item1.Header = "Cargar partida";
            item1.Click += new RoutedEventHandler(LoadGame);

            MenuItem item2 = new MenuItem();
            item2.Click += new RoutedEventHandler(ShowOptions);
            item2.Header = "Opciones";

            MenuItem item3 = new MenuItem();
            item3.Header = "Salir";
            item3.Click += new RoutedEventHandler(Quit);

            CMenu.Items.Add(item1);
            CMenu.Items.Add(item2);
            CMenu.Items.Add(item3);

            TaskbarIcon.ContextMenu = CMenu;
            TaskbarIcon.MenuActivation = Hardcodet.Wpf.TaskbarNotification.PopupActivationMode.RightClick;

            HotKey _hotKey = new HotKey(Key.Enter, KeyModifier.Ctrl, OnHotKeyHandler);

            player = new MediaPlayer();

            if (File.Exists(SoundPath))
                player.Open(new Uri(SoundPath));
            else
                player.Open(new Uri(Directory.GetParent(Assembly.GetExecutingAssembly().Location) + "\\Resources\\Alert.wav"));

            player.Volume = 0.15;

            Request.SelectedRegionServer = "euw1";
            Request.SelectedRegionName = "EUW";
            Request.Init();
            
            championImage = new List<Image>();
            spell1Image = new List<Image>();
            spell2Image = new List<Image>();
            ultImage = new List<Image>();

            everySecTimer = new DispatcherTimer();
            everySecTimer.Tick += new EventHandler(EverySec);
            everySecTimer.Interval = new TimeSpan(0, 0, 1);
        }

        private void OnHotKeyHandler(HotKey hotKey)
        {
            this.Activate();
            this.Topmost = true;
            //this.Focus();

            Debug.WriteLine("GetCheck");

            CurrentGame();
        }

        private DispatcherTimer createTimer(int seconds)
        {
            DispatcherTimer dispatcherTimer = new DispatcherTimer();            

            if (seconds < 60)
            {
                dispatcherTimer.Interval = new TimeSpan(0, 0, seconds);
                dispatcherTimer.Tick += new EventHandler(CCFinished);
            }
            else if(seconds < 90)
            {
                dispatcherTimer.Interval = new TimeSpan(0, 0, seconds - 30);
                dispatcherTimer.Tick += new EventHandler(Only30secLeft);
            }
            else
            {
                dispatcherTimer.Interval = new TimeSpan(0, 0, seconds - 60);
                dispatcherTimer.Tick += new EventHandler(Only1minLeft);
            }

            dispatcherTimer.Start();
            
            return dispatcherTimer;            
        }

        private void Only1minLeft(object sender, EventArgs e)
        {
            DispatcherTimer timer = (DispatcherTimer)sender;
            timer.Tick += new EventHandler(Only30secLeft);
            timer.Interval = new TimeSpan(0, 0, 60);
            timer.Start();

            player.Position = new TimeSpan(0);
            player.Play();
        }

        private void Only30secLeft(object sender, EventArgs e)
        {
            DispatcherTimer timer = (DispatcherTimer)sender;
            timer.Tick += new EventHandler(CCFinished);
            timer.Interval = new TimeSpan(0, 0, 30);
            timer.Start();

            player.Position = new TimeSpan(0);
            player.Play();
        }

        private void CCFinished(object sender, EventArgs e)
        {
            DispatcherTimer timer = (DispatcherTimer)sender;
            timer.Stop();

            player.Position = new TimeSpan(0);
            player.Play();
        }

        private void EverySec(object sender, EventArgs e)
        {
            for(int i = 0; i < spell1Cooldown.Length; i++)
            {
                if (spell1Active[i] == true)
                {
                    leftSpell1Cooldown[i] -= 1;
                    leftSpell1Label[i].Content = leftSpell1Cooldown[i];

                    if (leftSpell1Cooldown[i] < 0)
                    {
                        leftSpell1Label[i].Background = Brushes.Black;
                        spell1Active[i] = false;
                    }
                    else if (leftSpell1Cooldown[i] <= 30)
                    {
                        leftSpell1Label[i].Background = Brushes.Red;
                    }                        
                    else if (leftSpell1Cooldown[i] <= 60)
                    {
                        leftSpell1Label[i].Background = Brushes.Yellow;
                    }                        
                }
                if (spell2Active[i] == true)
                {
                    leftSpell2Cooldown[i] -= 1;
                    leftSpell2Label[i].Content = leftSpell2Cooldown[i];

                    if (leftSpell2Cooldown[i] < 0)
                    {
                        leftSpell2Label[i].Background = Brushes.Black;
                        spell2Active[i] = false;
                    }
                    else if (leftSpell2Cooldown[i] <= 30)
                    {
                        leftSpell2Label[i].Background = Brushes.Red;
                    }
                    else if (leftSpell2Cooldown[i] <= 60)
                    {
                        leftSpell2Label[i].Background = Brushes.Yellow;
                    }
                }
                if (ultActive[i] == true)
                {
                    leftUltCooldown[i] -= 1;
                    leftUltLabel[i].Content = leftUltCooldown[i];

                    if (leftUltCooldown[i] < 0)
                    {
                        leftUltLabel[i].Background = Brushes.Black;
                        ultActive[i] = false;
                    }
                    else if (leftUltCooldown[i] <= 30)
                    {
                        leftUltLabel[i].Background = Brushes.Red;
                    }
                    else if (leftUltCooldown[i] <= 60)
                    {
                        leftUltLabel[i].Background = Brushes.Yellow;
                    }
                }
            }

            if (drawJungle)
            {
                for (int i = 0; i < 7; i++)
                {
                    if (monsterActive[i] == true)
                    {
                        leftMonsterCooldown[i] -= 1;
                        leftMonsterLabel[i].Content = leftMonsterCooldown[i];

                        if (leftMonsterCooldown[i] < 0)
                        {
                            leftMonsterLabel[i].Background = Brushes.Black;
                            monsterActive[i] = false;
                        }
                        else if (leftMonsterCooldown[i] <= 30)
                        {
                            leftMonsterLabel[i].Background = Brushes.Red;
                        }
                        else if (leftMonsterCooldown[i] <= 60)
                        {
                            leftMonsterLabel[i].Background = Brushes.Yellow;
                        }
                    }
                }
            }
        }

        public void CurrentGame()
        {
            CurrentGameObject Game;
            try
            {
                Game = Request.RequestCurrentGameInfo(summonerName);

                if (Game == null) return;

                int teamID = 0;

                foreach (ParticipantObject participant in Game.participants)
                {
                    if (participant.summonerName.ToLower() == summonerName.ToLower())
                    {
                        teamID = participant.teamId;
                        break;
                    }
                }

                int Players = Game.participants.Count;

                championImage = new List<Image>();
                spell1Image = new List<Image>();
                spell2Image = new List<Image>();
                ultImage = new List<Image>();

                spell1Cooldown = new int[Players / 2];
                spell2Cooldown = new int[Players / 2];
                ultCooldown = new int[Players / 2];

                leftSpell1Cooldown = new int[Players / 2];
                leftSpell2Cooldown = new int[Players / 2];
                leftUltCooldown = new int[Players / 2];

                leftSpell1Label = new List<Label>();
                leftSpell2Label = new List<Label>();
                leftUltLabel = new List<Label>();

                spell1Active = new bool[Players / 2];
                spell2Active = new bool[Players / 2];
                ultActive = new bool[Players / 2];

                everySecTimer.Stop();

                MainGrid.Children.Clear();

                for (int i = 0; i < Players / 2; i++)
                {
                    Image auxImg = new Image();
                    auxImg.Height = ImgSize * 9 / 12;
                    auxImg.Width = ImgSize * 9 / 12;
                    auxImg.Margin = new Thickness((i * ImgSize) + i == 0 ? 0 : (10 + (i * ImgSize) + ((i - 1) * ImgSize / 5)), 10, 0, 0);
                    auxImg.Name = "Sum" + (i + 1) + "Img";
                    auxImg.VerticalAlignment = VerticalAlignment.Top;
                    auxImg.HorizontalAlignment = HorizontalAlignment.Left;

                    switch (i)
                    {
                        case 0: auxImg.MouseDown += Sum1Img_MouseDown; break;
                        case 1: auxImg.MouseDown += Sum2Img_MouseDown; break;
                        case 2: auxImg.MouseDown += Sum3Img_MouseDown; break;
                        case 3: auxImg.MouseDown += Sum4Img_MouseDown; break;
                        case 4: auxImg.MouseDown += Sum5Img_MouseDown; break;
                    }

                    MainGrid.Children.Add(auxImg);
                    championImage.Add(auxImg);

                    auxImg = new Image();
                    auxImg.Height = ImgSize / 2;
                    auxImg.Width = ImgSize / 2;
                    auxImg.Margin = new Thickness(10 + (i * ImgSize) + (i * ImgSize / 5) + (ImgSize / 2), 10, 0, 0);
                    auxImg.Name = "Sum" + (i + 1) + "Sp1";
                    auxImg.VerticalAlignment = VerticalAlignment.Top;
                    auxImg.HorizontalAlignment = HorizontalAlignment.Left;

                    switch (i)
                    {
                        case 0: auxImg.MouseDown += Sum1Sp1_MouseDown; break;
                        case 1: auxImg.MouseDown += Sum2Sp1_MouseDown; break;
                        case 2: auxImg.MouseDown += Sum3Sp1_MouseDown; break;
                        case 3: auxImg.MouseDown += Sum4Sp1_MouseDown; break;
                        case 4: auxImg.MouseDown += Sum5Sp1_MouseDown; break;
                    }                    

                    MainGrid.Children.Add(auxImg);
                    spell1Image.Add(auxImg);

                    Label timerLabel = new Label();
                    timerLabel.Height = ImgSize * 3 / 12;
                    timerLabel.Width = ImgSize / 2;
                    timerLabel.Margin = new Thickness(10 + (i * ImgSize) + (i * ImgSize / 5) + (ImgSize / 2), 10 + (ImgSize / 2), 0, 0);
                    timerLabel.Background = Brushes.Black;
                    timerLabel.Foreground = Brushes.Black;
                    timerLabel.FontWeight = FontWeights.Bold;
                    timerLabel.FontSize = ImgSize / 7;
                    timerLabel.Padding = new Thickness(0, 0, 0, 0);
                    timerLabel.Content = leftSpell1Cooldown[i];
                    timerLabel.VerticalAlignment = VerticalAlignment.Top;
                    timerLabel.HorizontalAlignment = HorizontalAlignment.Left;
                    timerLabel.HorizontalContentAlignment = HorizontalAlignment.Center;

                    switch (i)
                    {
                        case 0: timerLabel.MouseDown += Sum1Sp1_MouseDown; break;
                        case 1: timerLabel.MouseDown += Sum2Sp1_MouseDown; break;
                        case 2: timerLabel.MouseDown += Sum3Sp1_MouseDown; break;
                        case 3: timerLabel.MouseDown += Sum4Sp1_MouseDown; break;
                        case 4: timerLabel.MouseDown += Sum5Sp1_MouseDown; break;
                    }

                    MainGrid.Children.Add(timerLabel);
                    leftSpell1Label.Add(timerLabel);

                    auxImg = new Image();
                    auxImg.Height = ImgSize / 2;
                    auxImg.Width = ImgSize / 2;
                    auxImg.Margin = new Thickness(10 + (i * ImgSize) + (i * ImgSize / 5), 10 + (ImgSize / 2) + (ImgSize * 3 / 12), 0, 0);
                    auxImg.Name = "Sum" + (i + 1) + "Sp2";
                    auxImg.VerticalAlignment = VerticalAlignment.Top;
                    auxImg.HorizontalAlignment = HorizontalAlignment.Left;

                    switch (i)
                    {
                        case 0: auxImg.MouseDown += Sum1Sp2_MouseDown; break;
                        case 1: auxImg.MouseDown += Sum2Sp2_MouseDown; break;
                        case 2: auxImg.MouseDown += Sum3Sp2_MouseDown; break;
                        case 3: auxImg.MouseDown += Sum4Sp2_MouseDown; break;
                        case 4: auxImg.MouseDown += Sum5Sp2_MouseDown; break;
                    }

                    MainGrid.Children.Add(auxImg);
                    spell2Image.Add(auxImg);

                    timerLabel = new Label();
                    timerLabel.Height = ImgSize * 3 / 12;
                    timerLabel.Width = ImgSize / 2;
                    timerLabel.Margin = new Thickness(10 + (i * ImgSize) + (i * ImgSize / 5), 10 + ImgSize + (ImgSize * 3 / 12), 0, 0);
                    timerLabel.Background = Brushes.Black;
                    timerLabel.Foreground = Brushes.Black;
                    timerLabel.FontWeight = FontWeights.Bold;
                    timerLabel.FontSize = ImgSize / 7;
                    timerLabel.Padding = new Thickness(0, 0, 0, 0);
                    timerLabel.Content = leftSpell2Cooldown[i];
                    timerLabel.VerticalAlignment = VerticalAlignment.Top;
                    timerLabel.HorizontalAlignment = HorizontalAlignment.Left;
                    timerLabel.HorizontalContentAlignment = HorizontalAlignment.Center;

                    switch (i)
                    {
                        case 0: timerLabel.MouseDown += Sum1Sp2_MouseDown; break;
                        case 1: timerLabel.MouseDown += Sum2Sp2_MouseDown; break;
                        case 2: timerLabel.MouseDown += Sum3Sp2_MouseDown; break;
                        case 3: timerLabel.MouseDown += Sum4Sp2_MouseDown; break;
                        case 4: timerLabel.MouseDown += Sum5Sp2_MouseDown; break;
                    }

                    MainGrid.Children.Add(timerLabel);
                    leftSpell2Label.Add(timerLabel);

                    auxImg = new Image();
                    auxImg.Height = ImgSize / 2;
                    auxImg.Width = ImgSize / 2;
                    auxImg.Margin = new Thickness(10 + (i * ImgSize) + (i * ImgSize / 5) + (ImgSize / 2), 10 + (ImgSize / 2) + (ImgSize * 3 / 12), 0, 0);
                    auxImg.Name = "Sum" + (i + 1) + "Ult";
                    auxImg.VerticalAlignment = VerticalAlignment.Top;
                    auxImg.HorizontalAlignment = HorizontalAlignment.Left;

                    switch (i)
                    {
                        case 0: auxImg.MouseDown += Sum1Ult_MouseDown; break;
                        case 1: auxImg.MouseDown += Sum2Ult_MouseDown; break;
                        case 2: auxImg.MouseDown += Sum3Ult_MouseDown; break;
                        case 3: auxImg.MouseDown += Sum4Ult_MouseDown; break;
                        case 4: auxImg.MouseDown += Sum5Ult_MouseDown; break;
                    }

                    MainGrid.Children.Add(auxImg);
                    ultImage.Add(auxImg);

                    timerLabel = new Label();
                    timerLabel.Height = ImgSize * 3 / 12;
                    timerLabel.Width = ImgSize / 2;
                    timerLabel.Margin = new Thickness(10 + (i * ImgSize) + (i * ImgSize / 5) + (ImgSize / 2), 10 + ImgSize + (ImgSize * 3 / 12), 0, 0);
                    timerLabel.Background = Brushes.Black;
                    timerLabel.Foreground = Brushes.Black;
                    timerLabel.FontWeight = FontWeights.Bold;
                    timerLabel.FontSize = ImgSize / 7;
                    timerLabel.Padding = new Thickness(0,0,0,0);
                    timerLabel.Content = leftUltCooldown[i];
                    timerLabel.VerticalAlignment = VerticalAlignment.Top;
                    timerLabel.HorizontalAlignment = HorizontalAlignment.Left;
                    timerLabel.HorizontalContentAlignment = HorizontalAlignment.Center;

                    switch (i)
                    {
                        case 0: timerLabel.MouseDown += Sum1Ult_MouseDown; break;
                        case 1: timerLabel.MouseDown += Sum2Ult_MouseDown; break;
                        case 2: timerLabel.MouseDown += Sum3Ult_MouseDown; break;
                        case 3: timerLabel.MouseDown += Sum4Ult_MouseDown; break;
                        case 4: timerLabel.MouseDown += Sum5Ult_MouseDown; break;
                    }

                    MainGrid.Children.Add(timerLabel);
                    leftUltLabel.Add(timerLabel);

                    MainGrid.UpdateLayout();                    
                }                                

                int count = 0;

                for (int i = 0; i < Players; i++)
                {
                    if (Game.participants[i].teamId != teamID)
                    {
                        BitmapImage image = new BitmapImage();
                        image.BeginInit();
                        image.StreamSource = Request.RequestChampiomImage(Game.participants[i].championId);
                        image.EndInit();

                        championImage[count].Source = image;

                        image = new BitmapImage();
                        image.BeginInit();
                        image.StreamSource = Request.RequestSummonerSpellImage(Game.participants[i].spell1Id);
                        image.EndInit();

                        spell1Image[count].Source = image;

                        spell1Cooldown[count] = Request.RequestSummonerSpellCooldown(Game.participants[i].spell1Id);

                        image = new BitmapImage();
                        image.BeginInit();
                        image.StreamSource = Request.RequestSummonerSpellImage(Game.participants[i].spell2Id);
                        image.EndInit();

                        spell2Image[count].Source = image;

                        spell2Cooldown[count] = Request.RequestSummonerSpellCooldown(Game.participants[i].spell2Id);

                        image = new BitmapImage();
                        image.BeginInit();
                        image.StreamSource = Request.RequestUltimateImageByChampion(Game.participants[i].championId);
                        image.EndInit();

                        ultImage[count].Source = image;

                        ultCooldown[count] = Request.RequestUltimateCooldownByChampion(Game.participants[i].championId);

                        count++;
                    }
                }

                if(drawJungle == true)
                {
                    monsterImage = new List<Image>();
                    leftMonsterCooldown = new int[7];
                    leftMonsterLabel = new List<Label>();
                    monsterActive = new bool[7];

                    Image auxImg = new Image();
                    auxImg.Height = ImgSize / 2;
                    auxImg.Width = ImgSize / 2;
                    auxImg.Margin = new Thickness(10 + (ImgSize * 32.5 / 5), 10, 0, 0);
                    auxImg.Name = "BlueMonster";
                    auxImg.VerticalAlignment = VerticalAlignment.Top;
                    auxImg.HorizontalAlignment = HorizontalAlignment.Left;
                    auxImg.MouseDown += BlueMonster_MouseDown;
                    auxImg.Source = new BitmapImage(new Uri(Directory.GetParent(Assembly.GetExecutingAssembly().Location) + "\\Resources\\Blue.png"));
                    
                    MainGrid.Children.Add(auxImg);
                    monsterImage.Add(auxImg);

                    Label timerLabel = new Label();
                    timerLabel.Height = ImgSize * 3 / 12;
                    timerLabel.Width = ImgSize / 2;
                    timerLabel.Margin = new Thickness(10 + (ImgSize * 32.5 / 5), 10 + (ImgSize / 2), 0, 0);
                    timerLabel.Background = Brushes.Black;
                    timerLabel.Foreground = Brushes.Black;
                    timerLabel.FontWeight = FontWeights.Bold;
                    timerLabel.FontSize = ImgSize / 7;
                    timerLabel.Padding = new Thickness(0, 0, 0, 0);
                    timerLabel.Content = leftMonsterCooldown[0];
                    timerLabel.VerticalAlignment = VerticalAlignment.Top;
                    timerLabel.HorizontalAlignment = HorizontalAlignment.Left;
                    timerLabel.HorizontalContentAlignment = HorizontalAlignment.Center;
                    timerLabel.MouseDown += BlueMonster_MouseDown;

                    MainGrid.Children.Add(timerLabel);
                    leftMonsterLabel.Add(timerLabel);

                    auxImg = new Image();
                    auxImg.Height = ImgSize / 2;
                    auxImg.Width = ImgSize / 2;
                    auxImg.Margin = new Thickness(10 + (ImgSize * 37.5 / 5), 10, 0, 0);
                    auxImg.Name = "GrompMonster";
                    auxImg.VerticalAlignment = VerticalAlignment.Top;
                    auxImg.HorizontalAlignment = HorizontalAlignment.Left;
                    auxImg.MouseDown += GrompMonster_MouseDown;
                    auxImg.Source = new BitmapImage(new Uri(Directory.GetParent(Assembly.GetExecutingAssembly().Location) + "\\Resources\\Gromp.png"));

                    MainGrid.Children.Add(auxImg);
                    monsterImage.Add(auxImg);

                    timerLabel = new Label();
                    timerLabel.Height = ImgSize * 3 / 12;
                    timerLabel.Width = ImgSize / 2;
                    timerLabel.Margin = new Thickness(10 + (ImgSize * 37.5 / 5), 10 + (ImgSize / 2), 0, 0);
                    timerLabel.Background = Brushes.Black;
                    timerLabel.Foreground = Brushes.Black;
                    timerLabel.FontWeight = FontWeights.Bold;
                    timerLabel.FontSize = ImgSize / 7;
                    timerLabel.Padding = new Thickness(0, 0, 0, 0);
                    timerLabel.Content = leftMonsterCooldown[1];
                    timerLabel.VerticalAlignment = VerticalAlignment.Top;
                    timerLabel.HorizontalAlignment = HorizontalAlignment.Left;
                    timerLabel.HorizontalContentAlignment = HorizontalAlignment.Center;
                    timerLabel.MouseDown += GrompMonster_MouseDown;

                    MainGrid.Children.Add(timerLabel);
                    leftMonsterLabel.Add(timerLabel);

                    auxImg = new Image();
                    auxImg.Height = ImgSize / 2;
                    auxImg.Width = ImgSize / 2;
                    auxImg.Margin = new Thickness(10 + (ImgSize * 40 / 5), 10, 0, 0);
                    auxImg.Name = "KrugMonster";
                    auxImg.VerticalAlignment = VerticalAlignment.Top;
                    auxImg.HorizontalAlignment = HorizontalAlignment.Left;
                    auxImg.MouseDown += KrugMonster_MouseDown;
                    auxImg.Source = new BitmapImage(new Uri(Directory.GetParent(Assembly.GetExecutingAssembly().Location) + "\\Resources\\Krug.png"));

                    MainGrid.Children.Add(auxImg);
                    monsterImage.Add(auxImg);

                    timerLabel = new Label();
                    timerLabel.Height = ImgSize * 3 / 12;
                    timerLabel.Width = ImgSize / 2;
                    timerLabel.Margin = new Thickness(10 + (ImgSize * 40 / 5), 10 + (ImgSize / 2), 0, 0);
                    timerLabel.Background = Brushes.Black;
                    timerLabel.Foreground = Brushes.Black;
                    timerLabel.FontWeight = FontWeights.Bold;
                    timerLabel.FontSize = ImgSize / 7;
                    timerLabel.Padding = new Thickness(0, 0, 0, 0);
                    timerLabel.Content = leftMonsterCooldown[2];
                    timerLabel.VerticalAlignment = VerticalAlignment.Top;
                    timerLabel.HorizontalAlignment = HorizontalAlignment.Left;
                    timerLabel.HorizontalContentAlignment = HorizontalAlignment.Center;
                    timerLabel.MouseDown += KrugMonster_MouseDown;

                    MainGrid.Children.Add(timerLabel);
                    leftMonsterLabel.Add(timerLabel);

                    auxImg = new Image();
                    auxImg.Height = ImgSize / 2;
                    auxImg.Width = ImgSize / 2;
                    auxImg.Margin = new Thickness(10 + (ImgSize * 42.5 / 5), 10, 0, 0);
                    auxImg.Name = "RaptorMonster";
                    auxImg.VerticalAlignment = VerticalAlignment.Top;
                    auxImg.HorizontalAlignment = HorizontalAlignment.Left;
                    auxImg.MouseDown += RaptorMonster_MouseDown;
                    auxImg.Source = new BitmapImage(new Uri(Directory.GetParent(Assembly.GetExecutingAssembly().Location) + "\\Resources\\Raptor.png"));

                    MainGrid.Children.Add(auxImg);
                    monsterImage.Add(auxImg);

                    timerLabel = new Label();
                    timerLabel.Height = ImgSize * 3 / 12;
                    timerLabel.Width = ImgSize / 2;
                    timerLabel.Margin = new Thickness(10 + (ImgSize * 42.5 / 5), 10 + (ImgSize / 2), 0, 0);
                    timerLabel.Background = Brushes.Black;
                    timerLabel.Foreground = Brushes.Black;
                    timerLabel.FontWeight = FontWeights.Bold;
                    timerLabel.FontSize = ImgSize / 7;
                    timerLabel.Padding = new Thickness(0, 0, 0, 0);
                    timerLabel.Content = leftMonsterCooldown[3];
                    timerLabel.VerticalAlignment = VerticalAlignment.Top;
                    timerLabel.HorizontalAlignment = HorizontalAlignment.Left;
                    timerLabel.HorizontalContentAlignment = HorizontalAlignment.Center;
                    timerLabel.MouseDown += RaptorMonster_MouseDown;

                    MainGrid.Children.Add(timerLabel);
                    leftMonsterLabel.Add(timerLabel);

                    auxImg = new Image();
                    auxImg.Height = ImgSize / 2;
                    auxImg.Width = ImgSize / 2;
                    auxImg.Margin = new Thickness(10 + (ImgSize * 35 / 5), 10, 0, 0);
                    auxImg.Name = "RedMonster";
                    auxImg.VerticalAlignment = VerticalAlignment.Top;
                    auxImg.HorizontalAlignment = HorizontalAlignment.Left;
                    auxImg.MouseDown += RedMonster_MouseDown;
                    auxImg.Source = new BitmapImage(new Uri(Directory.GetParent(Assembly.GetExecutingAssembly().Location) + "\\Resources\\Red.png"));

                    MainGrid.Children.Add(auxImg);
                    monsterImage.Add(auxImg);

                    timerLabel = new Label();
                    timerLabel.Height = ImgSize * 3 / 12;
                    timerLabel.Width = ImgSize / 2;
                    timerLabel.Margin = new Thickness(10 + (ImgSize * 35 / 5), 10 + (ImgSize / 2), 0, 0);
                    timerLabel.Background = Brushes.Black;
                    timerLabel.Foreground = Brushes.Black;
                    timerLabel.FontWeight = FontWeights.Bold;
                    timerLabel.FontSize = ImgSize / 7;
                    timerLabel.Padding = new Thickness(0, 0, 0, 0);
                    timerLabel.Content = leftMonsterCooldown[4];
                    timerLabel.VerticalAlignment = VerticalAlignment.Top;
                    timerLabel.HorizontalAlignment = HorizontalAlignment.Left;
                    timerLabel.HorizontalContentAlignment = HorizontalAlignment.Center;
                    timerLabel.MouseDown += RedMonster_MouseDown;

                    MainGrid.Children.Add(timerLabel);
                    leftMonsterLabel.Add(timerLabel);

                    auxImg = new Image();
                    auxImg.Height = ImgSize / 2;
                    auxImg.Width = ImgSize / 2;
                    auxImg.Margin = new Thickness(10 + (ImgSize * 45 / 5), 10, 0, 0);
                    auxImg.Name = "ScuttlerMonster";
                    auxImg.VerticalAlignment = VerticalAlignment.Top;
                    auxImg.HorizontalAlignment = HorizontalAlignment.Left;
                    auxImg.MouseDown += ScuttlerMonster_MouseDown;
                    auxImg.Source = new BitmapImage(new Uri(Directory.GetParent(Assembly.GetExecutingAssembly().Location) + "\\Resources\\Scuttler.png"));

                    MainGrid.Children.Add(auxImg);
                    monsterImage.Add(auxImg);

                    timerLabel = new Label();
                    timerLabel.Height = ImgSize * 3 / 12;
                    timerLabel.Width = ImgSize / 2;
                    timerLabel.Margin = new Thickness(10 + (ImgSize * 45 / 5), 10 + (ImgSize / 2), 0, 0);
                    timerLabel.Background = Brushes.Black;
                    timerLabel.Foreground = Brushes.Black;
                    timerLabel.FontWeight = FontWeights.Bold;
                    timerLabel.FontSize = ImgSize / 7;
                    timerLabel.Padding = new Thickness(0, 0, 0, 0);
                    timerLabel.Content = leftMonsterCooldown[5];
                    timerLabel.VerticalAlignment = VerticalAlignment.Top;
                    timerLabel.HorizontalAlignment = HorizontalAlignment.Left;
                    timerLabel.HorizontalContentAlignment = HorizontalAlignment.Center;
                    timerLabel.MouseDown += ScuttlerMonster_MouseDown;

                    MainGrid.Children.Add(timerLabel);
                    leftMonsterLabel.Add(timerLabel);

                    auxImg = new Image();
                    auxImg.Height = ImgSize / 2;
                    auxImg.Width = ImgSize / 2;
                    auxImg.Margin = new Thickness(10 + (ImgSize * 47.5 / 5), 10, 0, 0);
                    auxImg.Name = "WolfMonster";
                    auxImg.VerticalAlignment = VerticalAlignment.Top;
                    auxImg.HorizontalAlignment = HorizontalAlignment.Left;
                    auxImg.MouseDown += WolfMonster_MouseDown;
                    auxImg.Source = new BitmapImage(new Uri(Directory.GetParent(Assembly.GetExecutingAssembly().Location) + "\\Resources\\Wolf.png"));

                    MainGrid.Children.Add(auxImg);
                    monsterImage.Add(auxImg);

                    timerLabel = new Label();
                    timerLabel.Height = ImgSize * 3 / 12;
                    timerLabel.Width = ImgSize / 2;
                    timerLabel.Margin = new Thickness(10 + (ImgSize * 47.5 / 5), 10 + (ImgSize / 2), 0, 0);
                    timerLabel.Background = Brushes.Black;
                    timerLabel.Foreground = Brushes.Black;
                    timerLabel.FontWeight = FontWeights.Bold;
                    timerLabel.FontSize = ImgSize / 7;
                    timerLabel.Padding = new Thickness(0, 0, 0, 0);
                    timerLabel.Content = leftMonsterCooldown[6];
                    timerLabel.VerticalAlignment = VerticalAlignment.Top;
                    timerLabel.HorizontalAlignment = HorizontalAlignment.Left;
                    timerLabel.HorizontalContentAlignment = HorizontalAlignment.Center;
                    timerLabel.MouseDown += WolfMonster_MouseDown;

                    MainGrid.Children.Add(timerLabel);
                    leftMonsterLabel.Add(timerLabel);
                }

                everySecTimer.Start();
            }
            catch (WebException e)
            {
                Debug.WriteLine(Request.LastError);

                if (e.Message.Contains("404"))
                    MessageBox.Show(summonerName + " is not in an active game", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }            
        }

        private void startCooldown(int summoner, int type)
        {
            switch (type)
            {
                case 1:
                    createTimer(spell1Cooldown[summoner]);
                    leftSpell1Cooldown[summoner] = spell1Cooldown[summoner];
                    spell1Active[summoner] = true;
                    leftSpell1Label[summoner].Content = leftSpell1Cooldown[summoner];
                    leftSpell1Label[summoner].Background = Brushes.Green;
                    break;
                case 2:
                    createTimer(spell2Cooldown[summoner]);
                    leftSpell2Cooldown[summoner] = spell2Cooldown[summoner];
                    spell2Active[summoner] = true;
                    leftSpell2Label[summoner].Content = leftSpell2Cooldown[summoner];
                    leftSpell2Label[summoner].Background = Brushes.Green;
                    break;
                case 3:
                    createTimer(ultCooldown[summoner]);
                    leftUltCooldown[summoner] = ultCooldown[summoner];
                    ultActive[summoner] = true;
                    leftUltLabel[summoner].Content = leftUltCooldown[summoner];
                    leftUltLabel[summoner].Background = Brushes.Green;
                    break;
                default:
                    break;
            }
        }

        private void Sum1Img_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(0, 0);
            }
        }

        private void Sum1Sp1_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(0, 1);
            }
        }

        private void Sum1Sp2_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(0, 2);
            }
        }

        private void Sum1Ult_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(0, 3);
            }
        }

        private void Sum2Img_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(1, 0);
            }
        }

        private void Sum2Sp1_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(1, 1);
            }
        }

        private void Sum2Sp2_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(1, 2);
            }
        }

        private void Sum2Ult_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(1, 3);
            }
        }

        private void Sum3Img_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(2, 0);
            }
        }

        private void Sum3Sp1_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(2, 1);
            }
        }

        private void Sum3Sp2_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(2, 2);
            }
        }

        private void Sum3Ult_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(2, 3);
            }
        }

        private void Sum4Img_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(3, 0);
            }
        }

        private void Sum4Sp1_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(3, 1);
            }
        }

        private void Sum4Sp2_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(3, 2);
            }
        }

        private void Sum4Ult_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(3, 3);
            }
        }

        private void Sum5Img_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(4, 0);
            }
        }

        private void Sum5Sp1_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(4, 1);
            }
        }

        private void Sum5Sp2_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(4, 2);
            }
        }

        private void Sum5Ult_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                startCooldown(4, 3);
            }
        }

        private void createJungleTimer(int seconds)
        {
            DispatcherTimer dispatcherTimer = new DispatcherTimer();
            dispatcherTimer.Interval = new TimeSpan(0, 0, seconds);
            dispatcherTimer.Tick += new EventHandler(CCFinished);
            dispatcherTimer.Start();
        }

        private void CCJungleFinished(object sender, EventArgs e)
        {
            DispatcherTimer timer = (DispatcherTimer)sender;
            timer.Stop();
        }

        private void BlueMonster_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                createJungleTimer(5 * 60);
                leftMonsterCooldown[0] = 5 * 60;
                monsterActive[0] = true;
                leftMonsterLabel[0].Content = 5 * 60;
                leftMonsterLabel[0].Background = Brushes.Green;
                Keyboard.ClearFocus();
            }
        }

        private void GrompMonster_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                createJungleTimer(2 * 60 + 30);
                leftMonsterCooldown[1] = 2 * 60 + 30;
                monsterActive[1] = true;
                leftMonsterLabel[1].Content = 2 * 60 + 30;
                leftMonsterLabel[1].Background = Brushes.Green;
            }
        }

        private void KrugMonster_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                createJungleTimer(2 * 60 + 30);
                leftMonsterCooldown[2] = 2 * 60 + 30;
                monsterActive[2] = true;
                leftMonsterLabel[2].Content = 2 * 60 + 30;
                leftMonsterLabel[2].Background = Brushes.Green;
            }
        }

        private void RaptorMonster_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                createJungleTimer(2 * 60 + 30);
                leftMonsterCooldown[3] = 2 * 60 + 30;
                monsterActive[3] = true;
                leftMonsterLabel[3].Content = 2 * 60 + 30;
                leftMonsterLabel[3].Background = Brushes.Green;
            }
        }

        private void RedMonster_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                createJungleTimer(5 * 60);
                leftMonsterCooldown[4] = 5 * 60;
                monsterActive[4] = true;
                leftMonsterLabel[4].Content = 5 * 60;
                leftMonsterLabel[4].Background = Brushes.Green;
            }
        }

        private void ScuttlerMonster_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                createJungleTimer(2 * 60 + 30);
                leftMonsterCooldown[5] = 2 * 60 + 30;
                monsterActive[5] = true;
                leftMonsterLabel[5].Content = 2 * 60 + 30;
                leftMonsterLabel[5].Background = Brushes.Green;
            }
        }

        private void WolfMonster_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftAlt))
            {
                createJungleTimer(2 * 60 + 30);
                leftMonsterCooldown[6] = 2 * 60 + 30;
                monsterActive[6] = true;
                leftMonsterLabel[6].Content = 2 * 60 + 30;
                leftMonsterLabel[6].Background = Brushes.Green;
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            TaskbarIcon.Visibility = Visibility.Collapsed;
            TaskbarIcon.Dispose();
        }

        private void Quit(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void ShowOptions(object sender, RoutedEventArgs e)
        {
            Window window = new OptionWindow(this, summonerName, ImgSize, corner, player.Source.AbsolutePath);

            window.Activate();
            window.Topmost = true;
            window.Focus();
            window.Show();
        }

        private void LoadGame(object sender, RoutedEventArgs e)
        {
            CurrentGame();
        }

        public void UpdateInfo(string name, int size, string soundPath)
        {
            summonerName = name;
            ImgSize = size;

            player = new MediaPlayer();
            player.Open(new Uri(soundPath));
            player.Volume = 0.25;
        }

        private void Window_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            this.Topmost = true;
            this.Show();
        }

        public void showJungleTimes(bool check)
        {
            drawJungle = check;
        }
    }
}