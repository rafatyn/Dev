using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.IO;
using Newtonsoft.Json;
using System.Windows;
using System.Windows.Media.Imaging;
using System.Windows.Controls;

namespace Riot_API
{
    static class Request
    {
        private const string BeginRequest = "https://";
        private const string RiotAPIUrl = ".api.riotgames.com";
        private const string PreKey = "api_key=";
        private const string Key = "RGAPI-8fad2468-b5ff-4dbc-b28f-1abfd887fa55";
        private const string RequestSummonerByName = "/lol/summoner/v3/summoners/by-name/";
        private const string RequestCurrentGame = "/lol/spectator/v3/active-games/by-summoner/";
        private const string RequestChampionById = "/lol/static-data/v3/champions/";
        private const string RequestSummonerSpellById = "/lol/static-data/v3/summoner-spells/";
        private const string RequestRealm = "/lol/static-data/v3/realms";
        public static readonly string[] RegionNames = { "BR", "EUN", "EUW", "JP", "KR", "LAN", "LAS", "NA", "OCE", "TR", "RU", "PBE" };
        public static readonly string[] RegionServer = { "br1", "eun1", "euw1", "jp1", "kr", "la1", "la2", "na1", "oc1", "tr1", "ru", "pbe1" };
        private const string ChampionImageFile = "Resources\\data_ic_";
        private const string SpellImageFile = "Resources\\data_is_";
        private const string MaestryImageFile = "Resources\\data_im_";

        public static string LastError { get; private set; }
        public static string ExecutionPath { get; private set; }
        public static string SelectedRegion { get; set; }
        public static string SummonerName { get; set; }
        public static RealmObject CurrentRealm { get; private set; }

        public static void Init()
        {
            string path = System.Reflection.Assembly.GetEntryAssembly().Location;
            path = path.Substring(0, path.LastIndexOf('\\') + 1);
            ExecutionPath = path;
            RequestRealmVersion();
        }

        public static void RequestRealmVersion()
        {
            HttpWebRequest request = WebRequest.Create(BeginRequest + SelectedRegion + RiotAPIUrl + RequestRealm + '?' + PreKey + Key) as HttpWebRequest;
            string result = MakeRequest(request);
            if (result != null)
            {
                CurrentRealm = JsonConvert.DeserializeObject<RealmObject>(result);
            }
        }

        public static SummonerObject RequestSummonerInfoByName(string name)
        {
            HttpWebRequest request = WebRequest.Create(BeginRequest + SelectedRegion + RiotAPIUrl + RequestSummonerByName + name + '?' + PreKey + Key) as HttpWebRequest;
            string result = MakeRequest(request);
            if (result != null) {
                return JsonConvert.DeserializeObject<SummonerObject>(result);
            }
            return null;
        }

        public static CurrentGameObject RequestCurrentGameInfo(string name)
        {
            SummonerObject summoner = RequestSummonerInfoByName(name);
            if (summoner != null)
            {
                HttpWebRequest request = WebRequest.Create(BeginRequest + SelectedRegion + RiotAPIUrl + RequestCurrentGame + summoner.id + '?' + PreKey + Key) as HttpWebRequest;
                string result = MakeRequest(request);
                if (result != null)
                {
                    return JsonConvert.DeserializeObject<CurrentGameObject>(result);
                }
                return null;
            }
            return null;
        }

        public static BitmapImage RequestChampiomImage(int id)
        {
            string path = ExecutionPath + ChampionImageFile + id;
            try
            {
                FileStream file = File.Open(path, FileMode.Open);
                file.Close();
            }
            catch(FileNotFoundException)
            {
                string championImage = null;
                HttpWebRequest request = WebRequest.Create(BeginRequest + SelectedRegion + RiotAPIUrl + RequestChampionById + id + "?locale=en_US&champData=image" + '&' + PreKey + Key) as HttpWebRequest;
                string result = MakeRequest(request);
                if (result != null)
                {
                    ChampionImageObject champion = JsonConvert.DeserializeObject<ChampionImageObject>(result);
                    championImage = champion.image.full;             
                }

                try
                {
                    using (WebClient client = new WebClient())
                    {
                        client.DownloadFile(CurrentRealm.cdn + "/" + CurrentRealm.n.champion + "/img/champion/" + championImage, ChampionImageFile + id);
                        client.Dispose();
                    }
                }
                catch (Exception exeption)
                {
                    MessageBox.Show(exeption.InnerException.Message, exeption.Source, MessageBoxButton.OK, MessageBoxImage.Warning, MessageBoxResult.OK, MessageBoxOptions.DefaultDesktopOnly);
                }
            }
            MemoryStream memoryStream = new MemoryStream();
            using (FileStream fileStream = File.OpenRead(path))
            {
                memoryStream.SetLength(fileStream.Length);
                fileStream.Read(memoryStream.GetBuffer(), 0, (int)fileStream.Length);
            }

            BitmapImage image = new BitmapImage();
            image.BeginInit();
            image.CacheOption = BitmapCacheOption.OnLoad;
            image.StreamSource = memoryStream;
            image.EndInit();
            return image;
        }

        public static BitmapImage RequestSummonerSpellImage(int id)
        {
            string path = ExecutionPath + SpellImageFile + id;
            try
            {
                FileStream file = File.Open(path, FileMode.Open);
                file.Close();
            }
            catch (FileNotFoundException)
            {
                string spellImage = null;
                HttpWebRequest request = WebRequest.Create(BeginRequest + SelectedRegion + RiotAPIUrl + RequestSummonerSpellById + id + "?locale=en_US&spellData=image" + '&' + PreKey + Key) as HttpWebRequest;
                string result = MakeRequest(request);
                if (result != null)
                {
                    SpellImageObject spell = JsonConvert.DeserializeObject<SpellImageObject>(result);
                    spellImage = spell.image.full;
                }

                try
                {
                    using (WebClient client = new WebClient())
                    {
                        client.DownloadFile(CurrentRealm.cdn + "/" + CurrentRealm.n.summoner + "/img/spell/" + spellImage, SpellImageFile + id);
                        client.Dispose();
                    }
                }
                catch (Exception exeption)
                {
                    MessageBox.Show(exeption.InnerException.Message, exeption.Source, MessageBoxButton.OK, MessageBoxImage.Warning, MessageBoxResult.OK, MessageBoxOptions.DefaultDesktopOnly);
                }
            }
            MemoryStream memoryStream = new MemoryStream();
            using (FileStream fileStream = File.OpenRead(path))
            {
                memoryStream.SetLength(fileStream.Length);
                fileStream.Read(memoryStream.GetBuffer(), 0, (int)fileStream.Length);
            }

            BitmapImage image = new BitmapImage();
            image.BeginInit();
            image.CacheOption = BitmapCacheOption.OnLoad;
            image.StreamSource = memoryStream;
            image.EndInit();
            return image;
        }

        public static BitmapImage RequestSummonerMaestryImage(int id)
        {
            string path = ExecutionPath + MaestryImageFile + id;
            MemoryStream memoryStream = new MemoryStream();
            using (FileStream fileStream = File.OpenRead(path))
            {
                memoryStream.SetLength(fileStream.Length);
                fileStream.Read(memoryStream.GetBuffer(), 0, (int)fileStream.Length);
            }

            BitmapImage image = new BitmapImage();
            image.BeginInit();
            image.CacheOption = BitmapCacheOption.OnLoad;
            image.StreamSource = memoryStream;
            image.EndInit();
            return image;
        }

        public static int RequestSummonerSpellCooldown(int id)
        {
            HttpWebRequest request = WebRequest.Create(BeginRequest + SelectedRegion + RiotAPIUrl + RequestSummonerSpellById + id + "?locale=en_US&spellData=cooldownBurn" + '&' + PreKey + Key) as HttpWebRequest;
            string result = MakeRequest(request);
            if (result != null)
            {
                SpellCooldownObject spell = JsonConvert.DeserializeObject<SpellCooldownObject>(result);
                return Int32.Parse(spell.cooldownBurn);
            }
            return -1;
        }

        public static string MakeRequest(HttpWebRequest request)
        {
            string result = null;
            try
            {
                using (HttpWebResponse response = request.GetResponse() as HttpWebResponse)
                {
                    StreamReader reader = new StreamReader(response.GetResponseStream());
                    result = reader.ReadToEnd();
                }
            }
            catch(WebException exeption)
            {
                LastError = request.Address.ToString();
                throw exeption;
            }
            return result;
        }
    }
}
