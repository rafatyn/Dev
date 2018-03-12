using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Drawing;
using System.IO;

namespace Riot_API
{
    public partial class CurrentGame : UserControl
    {
        private Ellipse[] SummonerIcons;
        private Ellipse[] Spell1Icons;
        private Ellipse[] Spell2Icons;
        private Ellipse[] Maestry1Icons;
        private Ellipse[] Maestry2Icons;
        private Border[] Names;
        private Button[] Buttons;
        private bool[] State;
        private int Players;
        private CurrentGameObject Game;
        private Grid IconsAndNames;

        public CurrentGame()
        {
            InitializeComponent();

            try
            {
                Game = Request.RequestCurrentGameInfo(Request.SummonerName);
            }
            catch(WebException exeption)
            {
                throw exeption;
            }
                        
            Players = Game.participants.Count;            
            SummonerIcons = new Ellipse[Players];
            Spell1Icons = new Ellipse[Players];
            Spell2Icons = new Ellipse[Players];
            Maestry1Icons = new Ellipse[Players];
            Maestry2Icons = new Ellipse[Players];
            Names = new Border[Players];
            Buttons = new Button[Players];
            State = new bool[Players];

            IconsAndNames = new Grid();
            IconsAndNames.SizeChanged += new SizeChangedEventHandler(IconsAndNames_SizeChanged);
            AddChild(IconsAndNames);
            
            ColumnDefinition column1 = new ColumnDefinition();
            column1.Width = new GridLength(1, GridUnitType.Star);
            IconsAndNames.ColumnDefinitions.Add(column1);
            ColumnDefinition column2 = new ColumnDefinition();
            column2.Width = new GridLength(2, GridUnitType.Star);
            IconsAndNames.ColumnDefinitions.Add(column2);
            ColumnDefinition column3 = new ColumnDefinition();
            column3.Width = new GridLength(0.2, GridUnitType.Star);
            IconsAndNames.ColumnDefinitions.Add(column3);
            ColumnDefinition column4 = new ColumnDefinition();
            column4.Width = new GridLength(0.2, GridUnitType.Star);
            IconsAndNames.ColumnDefinitions.Add(column4);
            ColumnDefinition column5 = new ColumnDefinition();
            column5.Width = new GridLength(2, GridUnitType.Star);
            IconsAndNames.ColumnDefinitions.Add(column5);
            ColumnDefinition column6 = new ColumnDefinition();
            column6.Width = new GridLength(1, GridUnitType.Star);
            IconsAndNames.ColumnDefinitions.Add(column6);
            
            for (int i=0; i<Players/2; i++) {
                RowDefinition row = new RowDefinition();
                row.Height = new GridLength(1, GridUnitType.Star);
                IconsAndNames.RowDefinitions.Add(row);
                for (int j = 0; j < 2; j++)
                {
                    Grid iconGrid = new Grid();
                    ColumnDefinition columnIcon1 = new ColumnDefinition();
                    columnIcon1.Width = new GridLength(1, GridUnitType.Star);
                    iconGrid.ColumnDefinitions.Add(columnIcon1);
                    ColumnDefinition columnIcon2 = new ColumnDefinition();
                    columnIcon2.Width = new GridLength(1, GridUnitType.Star);
                    iconGrid.ColumnDefinitions.Add(columnIcon2);
                    ColumnDefinition columnIcon3 = new ColumnDefinition();
                    columnIcon3.Width = new GridLength(1, GridUnitType.Star);
                    iconGrid.ColumnDefinitions.Add(columnIcon3);
                    RowDefinition iconRow1 = new RowDefinition();
                    iconRow1.Height = new GridLength(1, GridUnitType.Star);
                    iconGrid.RowDefinitions.Add(iconRow1);
                    RowDefinition iconRow2 = new RowDefinition();
                    iconRow2.Height = new GridLength(1, GridUnitType.Star);
                    iconGrid.RowDefinitions.Add(iconRow2);
                    RowDefinition iconRow3 = new RowDefinition();
                    iconRow3.Height = new GridLength(1, GridUnitType.Star);
                    iconGrid.RowDefinitions.Add(iconRow3);

                    SummonerIcons[i * 2 + j] = new Ellipse();
                    ImageBrush championIcon = new ImageBrush();
                    championIcon.ImageSource = Request.RequestChampiomImage(Game.participants.ElementAt(i + (j * (Players / 2))).championId);
                    SummonerIcons[i * 2 + j].Fill = championIcon;
                    SummonerIcons[i * 2 + j].VerticalAlignment = VerticalAlignment.Stretch;
                    SummonerIcons[i * 2 + j].HorizontalAlignment = HorizontalAlignment.Center;
                    SummonerIcons[i * 2 + j].MinHeight = 20;
                    Grid.SetColumn(SummonerIcons[i * 2 + j], 0);
                    Grid.SetRow(SummonerIcons[i * 2 + j], 0);
                    Grid.SetColumnSpan(SummonerIcons[i * 2 + j], 3);
                    Grid.SetRowSpan(SummonerIcons[i * 2 + j], 3);
                    iconGrid.Children.Add(SummonerIcons[i * 2 + j]);

                    Spell1Icons[i * 2 + j] = new Ellipse();
                    ImageBrush spell1Icon = new ImageBrush();                    
                    spell1Icon.ImageSource = Request.RequestSummonerSpellImage(Game.participants.ElementAt(i + (j * (Players / 2))).spell1Id);
                    Spell1Icons[i * 2 + j].Fill = spell1Icon;
                    Spell1Icons[i * 2 + j].VerticalAlignment = VerticalAlignment.Stretch;
                    Spell1Icons[i * 2 + j].HorizontalAlignment = HorizontalAlignment.Right;
                    Spell1Icons[i * 2 + j].MinHeight = 20;
                    Grid.SetColumn(Spell1Icons[i * 2 + j], 0);
                    Grid.SetRow(Spell1Icons[i * 2 + j], 0);
                    iconGrid.Children.Add(Spell1Icons[i * 2 + j]);

                    Spell2Icons[i * 2 + j] = new Ellipse();
                    ImageBrush spell2Icon = new ImageBrush();
                    spell2Icon.ImageSource = Request.RequestSummonerSpellImage(Game.participants.ElementAt(i + (j * (Players / 2))).spell2Id);
                    Spell2Icons[i * 2 + j].Fill = spell2Icon;
                    Spell2Icons[i * 2 + j].VerticalAlignment = VerticalAlignment.Stretch;
                    Spell2Icons[i * 2 + j].HorizontalAlignment = HorizontalAlignment.Right;
                    Spell2Icons[i * 2 + j].MinHeight = 20;
                    Grid.SetColumn(Spell2Icons[i * 2 + j], 0);
                    Grid.SetRow(Spell2Icons[i * 2 + j], 2);
                    iconGrid.Children.Add(Spell2Icons[i * 2 + j]);

                    Maestry1Icons[i * 2 + j] = new Ellipse();
                    ImageBrush maestry1Icon = new ImageBrush();
                    maestry1Icon.ImageSource = Request.RequestSummonerMaestryImage(Game.participants.ElementAt(i + (j * (Players / 2))).perks.perkIds[0]);
                    Maestry1Icons[i * 2 + j].Fill = maestry1Icon;
                    Maestry1Icons[i * 2 + j].VerticalAlignment = VerticalAlignment.Stretch;
                    Maestry1Icons[i * 2 + j].HorizontalAlignment = HorizontalAlignment.Left;
                    Maestry1Icons[i * 2 + j].MinHeight = 20;
                    Grid.SetColumn(Maestry1Icons[i * 2 + j], 2);
                    Grid.SetRow(Maestry1Icons[i * 2 + j], 0);
                    iconGrid.Children.Add(Maestry1Icons[i * 2 + j]);

                    Maestry2Icons[i * 2 + j] = new Ellipse();
                    ImageBrush maestry2Icon = new ImageBrush();
                    maestry2Icon.ImageSource = Request.RequestSummonerMaestryImage(Game.participants.ElementAt(i + (j * (Players / 2))).perks.perkSubStyle);                    
                    Maestry2Icons[i * 2 + j].Fill = maestry2Icon;
                    Maestry2Icons[i * 2 + j].VerticalAlignment = VerticalAlignment.Stretch;
                    Maestry2Icons[i * 2 + j].HorizontalAlignment = HorizontalAlignment.Left;
                    Maestry2Icons[i * 2 + j].MinHeight = 20;
                    Grid.SetColumn(Maestry2Icons[i * 2 + j], 2);
                    Grid.SetRow(Maestry2Icons[i * 2 + j], 2);
                    iconGrid.Children.Add(Maestry2Icons[i * 2 + j]);
                                        
                    Border gridBorder = new Border();
                    gridBorder.Padding = new Thickness(20, 10, 20, 10);
                    gridBorder.Child = iconGrid;

                    Grid.SetColumn(gridBorder, j == 0 ? 0 : 5);
                    Grid.SetRow(gridBorder, i);

                    Names[i * 2 + j] = new Border();
                    Names[i * 2 + j].Padding = new Thickness(30, 0, 0, 0);
                    Label name = new Label();
                    name.FontSize = 26;
                    name.Content = Game.participants.ElementAt(i + (j * (Players/2))).summonerName;
                    name.VerticalAlignment = VerticalAlignment.Center;
                    name.HorizontalAlignment = j == 0 ? HorizontalAlignment.Left : HorizontalAlignment.Right;
                    Names[i * 2 + j].Child = name;
                    Grid.SetColumn(Names[i * 2 + j], j == 0 ? 1 : 4);
                    Grid.SetRow(Names[i * 2 + j], i);

                    Buttons[i * 2 + j] = new Button();
                    Buttons[i * 2 + j].HorizontalAlignment = HorizontalAlignment.Stretch;
                    Buttons[i * 2 + j].VerticalAlignment = VerticalAlignment.Stretch;
                    string path = Request.ExecutionPath;                    
                    if (j == 0)
                    {
                        path += "Resources\\left arrow.png";
                        Grid.SetColumn(Buttons[i * 2 + j], 2);
                    }
                    else
                    {
                        path += "Resources\\right arrow.png";
                        Grid.SetColumn(Buttons[i * 2 + j], 3);
                    }
                    MemoryStream memoryStream = new MemoryStream();
                    using (FileStream fileStream = File.OpenRead(path))
                    {
                        memoryStream.SetLength(fileStream.Length);
                        fileStream.Read(memoryStream.GetBuffer(), 0, (int)fileStream.Length);
                    }
                    BitmapImage bitmapImage = new BitmapImage();
                    bitmapImage.BeginInit();
                    bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                    bitmapImage.StreamSource = memoryStream;
                    bitmapImage.EndInit();
                    System.Windows.Controls.Image image = new System.Windows.Controls.Image();
                    image.Source = bitmapImage;
                    Buttons[i * 2 + j].Content = image;
                    Buttons[i * 2 + j].Click += ExpandButton_Click;
                    Grid.SetRow(Buttons[i * 2 + j], i);                    

                    if(j == 0)
                    {
                        IconsAndNames.Children.Add(gridBorder);
                        IconsAndNames.Children.Add(Names[i * 2 + j]);
                        IconsAndNames.Children.Add(Buttons[i * 2 + j]);
                    }
                    else
                    {
                        IconsAndNames.Children.Add(Buttons[i * 2 + j]);
                        IconsAndNames.Children.Add(Names[i * 2 + j]);
                        IconsAndNames.Children.Add(gridBorder);
                    }
                }
            }            
        }

        private void IconsAndNames_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            if (SummonerIcons.Length > 0)
            {
                for (int i = 0; i < Players; i++)
                {
                    SummonerIcons[i].Width = SummonerIcons[i].ActualHeight;
                }
            }
            if (Spell1Icons.Length > 0)
            {
                for (int i = 0; i < Players; i++)
                {
                    Spell1Icons[i].Width = Spell1Icons[i].ActualHeight;
                }
            }
            if (Spell2Icons.Length > 0)
            {
                for (int i = 0; i < Players; i++)
                {
                    Spell2Icons[i].Width = Spell2Icons[i].ActualHeight;
                }
            }
            if (Maestry1Icons.Length > 0)
            {
                for (int i = 0; i < Players; i++)
                {
                    Maestry1Icons[i].Width = Maestry1Icons[i].ActualHeight;
                }
            }
            if (Maestry2Icons.Length > 0)
            {
                for (int i = 0; i < Players; i++)
                {
                    Maestry2Icons[i].Width = Maestry2Icons[i].ActualHeight;
                }
            }
        }

        private void ExpandButton_Click(object sender, RoutedEventArgs e)
        {
            int index = -1;
            for (int i = 0; i < Players; i++)
            {
                if (sender.Equals(Buttons[i]))
                {
                    index = i;
                    break;
                }
            }
            if (index >= 0)
            {
                if (!State[index])
                {
                    State[index] = true;
                    IconsAndNames.Children.RemoveAt(index * 3 + 1);

                    Grid iconGrid = new Grid();
                    ColumnDefinition columnIcon1 = new ColumnDefinition();
                    columnIcon1.Width = new GridLength(1, GridUnitType.Star);
                    iconGrid.ColumnDefinitions.Add(columnIcon1);
                    ColumnDefinition columnIcon2 = new ColumnDefinition();
                    columnIcon2.Width = new GridLength(1, GridUnitType.Star);
                    iconGrid.ColumnDefinitions.Add(columnIcon2);
                    ColumnDefinition columnIcon3 = new ColumnDefinition();
                    columnIcon3.Width = new GridLength(1, GridUnitType.Star);
                    iconGrid.ColumnDefinitions.Add(columnIcon3);

                    Border spell1Border = new Border();
                    spell1Border.Padding = new Thickness(20);
                    Ellipse spell1 = new Ellipse();
                    spell1.Fill = Spell1Icons[index].Fill;
                    spell1.VerticalAlignment = VerticalAlignment.Stretch;
                    spell1.HorizontalAlignment = HorizontalAlignment.Stretch;
                    spell1.MinHeight = 20;
                    spell1Border.Child = spell1;
                    Grid.SetColumn(spell1Border, index % 2 == 0 ? 0 : 2);
                    Label spell1Timer = new Label();
                    spell1Timer.Content = Request.RequestSummonerSpellCooldown(Game.participants
                        .ElementAt(index % 2 == 0 ? (index / 2) : (index / 2 + (Players / 2))).spell1Id).ToString();
                    spell1Timer.VerticalAlignment = VerticalAlignment.Center;
                    spell1Timer.HorizontalAlignment = HorizontalAlignment.Center;

                    Canvas spell1Canvas = new Canvas();
                    spell1Canvas.Children.Add(spell1Border);
                    //spell1Canvas.Children.Add(spell1Timer);

                    iconGrid.Children.Add(spell1Canvas);

                    Border spell2Border = new Border();
                    spell2Border.Padding = new Thickness(20);
                    Ellipse spell2 = new Ellipse();
                    spell2.Fill = Spell2Icons[index].Fill;
                    spell2.VerticalAlignment = VerticalAlignment.Stretch;
                    spell2.HorizontalAlignment = HorizontalAlignment.Stretch;
                    spell2.MinHeight = 20;
                    spell2Border.Child = spell2;
                    Grid.SetColumn(spell2Border, 1);
                    iconGrid.Children.Add(spell2Border);

                    Grid.SetColumn(iconGrid, index % 2 == 0 ? 1 : 4);
                    Grid.SetRow(iconGrid, index / 2);
                    IconsAndNames.Children.Insert(index * 3 + 1, iconGrid);
                }
                else
                {
                    State[index] = false;
                    IconsAndNames.Children.RemoveAt(index * 3 + 1);
                    IconsAndNames.Children.Insert(index * 3 + 1, Names[index]);
                }
            }
        }
    }
}
