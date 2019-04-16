using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows;

namespace Riot_API
{
    static class Request
    {
        private const string BeginRequest = "https://";
        private const string RiotAPIUrl = ".api.riotgames.com";
        private const string DDragonAPIUrl = "ddragon.leagueoflegends.com";
        private const string PreKey = "api_key=";
        private const string Key = "RGAPI-f50adc70-bc7d-4fce-a4e0-98aa58ef2edf";
        private const string RequestSummonerByName = "/lol/summoner/v3/summoners/by-name/";
        private const string RequestCurrentGame = "/lol/spectator/v3/active-games/by-summoner/";
        private const string RequestChampions = "/data/en_US/champion.json";
        private const string RequestChampionByName = "/data/en_US/champion/{0}.json";
        private const string RequestSummonerSpells = "/data/en_US/summoner.json";
        private const string RequestRealm = "/realms/";
        public static readonly string[] RegionNames = { "BR", "EUN", "EUW", "JP", "KR", "LAN", "LAS", "NA", "OCE", "TR", "RU", "PBE" };
        public static readonly string[] RegionServer = { "br1", "eun1", "euw1", "jp1", "kr", "la1", "la2", "na1", "oc1", "tr1", "ru", "pbe1" };

        private const string ImageFileFolder = "Resources\\";
        private const string ChampionImageFile = "data_ic_";
        private const string SpellImageFile = "data_is_";
        private const string MaestryImageFile = "data_im_";
        private const string UltimateImageFile = "data_iu_";
        private const string SpellCooldownFile = "data_sc";
        private const string UltimateCooldownFile = "data_uc";

        public static string LastError { get; private set; }
        public static string ExecutionPath { get; private set; }
        public static string SelectedRegionServer { get; set; }
        public static string SelectedRegionName { get; set; }
        public static string SummonerName { get; set; }

        public static RealmObject CurrentRealm { get; private set; }
        private static ChampionsObject savedChampionData { get; set; }
        private static SummonerSpellsObject savedSummonerSpellData { get; set; }

        public static uint NumberRequest { get; private set; }

        public static void Init()
        {
            string path = System.Reflection.Assembly.GetEntryAssembly().Location;
            path = path.Substring(0, path.LastIndexOf('\\') + 1);
            ExecutionPath = path;

            NumberRequest = 0;

            RequestRealmVersion();
        }

        public static void RequestRealmVersion()
        {
            HttpWebRequest request = WebRequest.Create(BeginRequest + DDragonAPIUrl + RequestRealm + SelectedRegionName.ToLower() + ".json") as HttpWebRequest;
            string result = MakeRequest(request);
            if (result != null)
            {
                CurrentRealm = JsonConvert.DeserializeObject<RealmObject>(result);

                string ChampionPath = ExecutionPath + ImageFileFolder + CurrentRealm.n.champion.Replace('.', '_');
                if (!Directory.Exists(ChampionPath))
                {
                    Directory.CreateDirectory(ChampionPath);
                }
                string SummonerPath = ExecutionPath + ImageFileFolder + CurrentRealm.n.summoner.Replace('.', '_');
                if (!Directory.Exists(SummonerPath))
                {
                    Directory.CreateDirectory(SummonerPath);
                }
            }
        }

        public static SummonerObject RequestSummonerInfoByName(string name)
        {
            HttpWebRequest request = WebRequest.Create(BeginRequest + SelectedRegionServer + RiotAPIUrl + RequestSummonerByName + name + '?' + PreKey + Key) as HttpWebRequest;
            string result = MakeRequest(request);
            if (result != null)
            {
                return JsonConvert.DeserializeObject<SummonerObject>(result);
            }
            return null;
        }

        public static CurrentGameObject RequestCurrentGameInfo(string name)
        {
            SummonerObject summoner = RequestSummonerInfoByName(name);
            if (summoner != null)
            {
                HttpWebRequest request = WebRequest.Create(BeginRequest + SelectedRegionServer + RiotAPIUrl + RequestCurrentGame + summoner.id + '?' + PreKey + Key) as HttpWebRequest;
                string result = MakeRequest(request);
                if (result != null)
                {
                    return JsonConvert.DeserializeObject<CurrentGameObject>(result);
                }
                return null;
            }
            return null;
        }

        public static MemoryStream RequestChampiomImage(int id)
        {
            string path = ExecutionPath + ImageFileFolder + CurrentRealm.n.champion.Replace('.','_') + "\\" + ChampionImageFile + id;
            try
            {
                FileStream file = File.Open(path, FileMode.Open);
                file.Close();
            }
            catch (FileNotFoundException)
            {
                string championImage = null;
                if (savedChampionData == null)
                {
                    HttpWebRequest request = WebRequest.Create(BeginRequest + DDragonAPIUrl + "/cdn/" + CurrentRealm.n.champion + RequestChampions) as HttpWebRequest;
                    string result = MakeRequest(request);
                    if (result != null)
                    {
                        savedChampionData = JsonConvert.DeserializeObject<ChampionsObject>(result);
                    }
                }

                if (savedChampionData != null)
                {
                    foreach (KeyValuePair<string, ChampionDataObject> champ in savedChampionData.Data)
                    {
                        if (champ.Value.Key == id)
                        {
                            championImage = champ.Value.Image.full;
                            break;
                        }
                    }

                    if (championImage != null)
                    {
                        try
                        {
                            using (WebClient client = new WebClient())
                            {
                                client.DownloadFile(BeginRequest + DDragonAPIUrl + "/cdn/" + CurrentRealm.n.champion + "/img/champion/" + championImage,
                                                    ImageFileFolder + CurrentRealm.n.champion.Replace('.', '_') + "\\" + ChampionImageFile + id);
                                client.Dispose();
                            }
                        }
                        catch (Exception exeption)
                        {
                            MessageBox.Show(exeption.InnerException.Message, exeption.Source, MessageBoxButton.OK, MessageBoxImage.Warning, MessageBoxResult.OK, MessageBoxOptions.DefaultDesktopOnly);
                        }
                    }
                }
            }
            MemoryStream memoryStream = new MemoryStream();
            using (FileStream fileStream = File.OpenRead(path))
            {
                memoryStream.SetLength(fileStream.Length);
                fileStream.Read(memoryStream.GetBuffer(), 0, (int)fileStream.Length);
            }

            return memoryStream;
        }

        public static MemoryStream RequestSummonerSpellImage(int id)
        {
            string path = ExecutionPath + ImageFileFolder + CurrentRealm.n.summoner.Replace('.', '_') + "\\" + SpellImageFile + id;
            try
            {
                FileStream file = File.Open(path, FileMode.Open);
                file.Close();
            }
            catch (FileNotFoundException)
            {
                string spellImage = null;
                if (savedSummonerSpellData == null)
                {
                    HttpWebRequest request = WebRequest.Create(BeginRequest + DDragonAPIUrl + "/cdn/" + CurrentRealm.n.summoner + RequestSummonerSpells) as HttpWebRequest;
                    string result = MakeRequest(request);
                    if (result != null)
                    {
                        Regex re = new Regex("(\"coeff\":)[1-9]{1,10}");
                        MatchCollection matches = re.Matches(result);
                        for(int i = matches.Count - 1; i>=0; i--)
                        {
                            result = result.Insert(result.IndexOf(":", matches[i].Index) + 1, "[");
                            result = result.Insert(result.IndexOf(",", matches[i].Index), "]");
                        }                        
                        savedSummonerSpellData = JsonConvert.DeserializeObject<SummonerSpellsObject>(result);
                    }
                }

                if (savedSummonerSpellData != null)
                {
                    foreach (KeyValuePair<string, SummonerSpellDataObject> spell in savedSummonerSpellData.Data)
                    {
                        if (spell.Value.Key == id)
                        {
                            spellImage = spell.Value.Image.full;
                            break;
                        }
                    }

                    if (spellImage != null)
                    {
                        try
                        {
                            using (WebClient client = new WebClient())
                            {
                                client.DownloadFile(BeginRequest + DDragonAPIUrl + "/cdn/" + CurrentRealm.n.summoner + "/img/spell/" + spellImage,
                                                    ImageFileFolder + CurrentRealm.n.summoner.Replace('.', '_') + "\\" + SpellImageFile + id);
                                client.Dispose();
                            }
                        }
                        catch (Exception exeption)
                        {
                            MessageBox.Show(exeption.InnerException.Message, exeption.Source, MessageBoxButton.OK, MessageBoxImage.Warning, MessageBoxResult.OK, MessageBoxOptions.DefaultDesktopOnly);
                        }
                    }
                }
            }
            MemoryStream memoryStream = new MemoryStream();
            using (FileStream fileStream = File.OpenRead(path))
            {
                memoryStream.SetLength(fileStream.Length);
                fileStream.Read(memoryStream.GetBuffer(), 0, (int)fileStream.Length);
            }

            return memoryStream;
        }

        public static int RequestSummonerSpellCooldown(int id)
        {
            string path = ExecutionPath + ImageFileFolder + CurrentRealm.n.summoner.Replace('.', '_') + "\\" + SpellCooldownFile;
            try
            {
                FileStream file = File.Open(path, FileMode.Open);
                file.Close();
            }
            catch (FileNotFoundException)
            {
                FileStream file = File.Create(path);
                file.Close();
            }

            string json = File.ReadAllText(path, Encoding.UTF8);
            Dictionary<string, string> jsonObject = JsonConvert.DeserializeObject<Dictionary<string, string>>(json);

            if (jsonObject != null)
            {
                if (jsonObject.ContainsKey(id.ToString()))
                {
                    return Int32.Parse(jsonObject[id.ToString()]);
                }
            }
            else
            {
                jsonObject = new Dictionary<string, string>();
            }
            
            if(savedSummonerSpellData == null)
            {
                HttpWebRequest request = WebRequest.Create(BeginRequest + DDragonAPIUrl + "/cdn/" + CurrentRealm.n.summoner + RequestSummonerSpells) as HttpWebRequest;
                string result = MakeRequest(request);
                if (result != null)
                {
                    Regex re = new Regex("(\"coeff\":)[1-9]{1,10}");
                    MatchCollection matches = re.Matches(result);
                    for (int i = matches.Count - 1; i >= 0; i--)
                    {
                        result = result.Insert(result.IndexOf(":", matches[i].Index) + 1, "[");
                        result = result.Insert(result.IndexOf(",", matches[i].Index), "]");
                    }
                    savedSummonerSpellData = JsonConvert.DeserializeObject<SummonerSpellsObject>(result);
                }
            }

            foreach(KeyValuePair<string, SummonerSpellDataObject> spell in savedSummonerSpellData.Data)
            {
                if (spell.Value.Key == id)
                {
                    int cooldown = Int32.Parse(spell.Value.CooldownBurn);
                    jsonObject.Add(id.ToString(), cooldown.ToString());
                    json = JsonConvert.SerializeObject(jsonObject);
                    File.WriteAllText(path, json, Encoding.UTF8);

                    return cooldown;
                }
            }          
            return -1;
        }

        public static MemoryStream RequestUltimateImageByChampion(int id)
        {
            string path = ExecutionPath + ImageFileFolder + CurrentRealm.n.champion.Replace('.', '_') + "\\" + UltimateImageFile + id;
            try
            {
                FileStream file = File.Open(path, FileMode.Open);
                file.Close();
            }
            catch (FileNotFoundException)
            {
                string ultimateImage = null;
                if (savedChampionData == null)
                {
                    HttpWebRequest request = WebRequest.Create(BeginRequest + DDragonAPIUrl + "/cdn/" + CurrentRealm.n.champion + RequestChampions) as HttpWebRequest;
                    string result = MakeRequest(request);
                    if (result != null)
                    {
                        savedChampionData = JsonConvert.DeserializeObject<ChampionsObject>(result);
                    }
                }

                if (savedChampionData != null)
                {
                    string championName = null;
                    foreach (KeyValuePair<string, ChampionDataObject> champ in savedChampionData.Data)
                    {
                        if (champ.Value.Key == id)
                        {
                            championName = champ.Value.Id;
                            break;
                        }
                    }

                    HttpWebRequest request = WebRequest.Create(BeginRequest + DDragonAPIUrl + "/cdn/" + CurrentRealm.n.champion + String.Format(RequestChampionByName, championName)) as HttpWebRequest;
                    string result = MakeRequest(request);
                    if (result != null)
                    {
                        Regex re = new Regex("(\"rangeBurn\":)[1-9]{1,10}");
                        MatchCollection matches = re.Matches(result);
                        for (int i = matches.Count - 1; i >= 0; i--)
                        {
                            result = result.Insert(result.IndexOf(":", matches[i].Index) + 1, "[");
                            result = result.Insert(result.IndexOf(",", matches[i].Index), "]");
                        }
                        ChampionSpecificDataObject championData = JsonConvert.DeserializeObject<ChampionSpecificDataObject>(result);
                        ultimateImage = championData.Data[championName].Spells[3].Image.full;
                    }

                    if(ultimateImage != null)
                    {
                        try
                        {
                            using (WebClient client = new WebClient())
                            {
                                client.DownloadFile(BeginRequest + DDragonAPIUrl + "/cdn/" + CurrentRealm.n.champion + "/img/spell/" + ultimateImage,
                                                    ImageFileFolder + CurrentRealm.n.champion.Replace('.', '_') + "\\" + UltimateImageFile + id);
                                client.Dispose();
                            }
                        }
                        catch (Exception exeption)
                        {
                            MessageBox.Show(exeption.InnerException.Message, exeption.Source, MessageBoxButton.OK, MessageBoxImage.Warning, MessageBoxResult.OK, MessageBoxOptions.DefaultDesktopOnly);
                        }
                    }
                }
            }
            MemoryStream memoryStream = new MemoryStream();
            using (FileStream fileStream = File.OpenRead(path))
            {
                memoryStream.SetLength(fileStream.Length);
                fileStream.Read(memoryStream.GetBuffer(), 0, (int)fileStream.Length);
            }

            return memoryStream;
        }

        public static int RequestUltimateCooldownByChampion(int id)
        {
            string path = ExecutionPath + ImageFileFolder + CurrentRealm.n.summoner.Replace('.', '_') + "\\" + UltimateImageFile;
            try
            {
                FileStream file = File.Open(path, FileMode.Open);
                file.Close();
            }
            catch (FileNotFoundException)
            {
                FileStream file = File.Create(path);
                file.Close();
            }

            string json = File.ReadAllText(path, Encoding.UTF8);
            Dictionary<string, string> jsonObject = JsonConvert.DeserializeObject<Dictionary<string, string>>(json);

            if (jsonObject != null)
            {
                if (jsonObject.ContainsKey(id.ToString()))
                {
                    string cooldown = jsonObject[id.ToString()];
                    return Int32.Parse(cooldown);
                }
            }
            else
            {
                jsonObject = new Dictionary<string, string>();
            }


            if (savedChampionData == null)
            {
                HttpWebRequest request = WebRequest.Create(BeginRequest + DDragonAPIUrl + "/cdn/" + CurrentRealm.n.champion + RequestChampions) as HttpWebRequest;
                string result = MakeRequest(request);
                if (result != null)
                {
                    savedChampionData = JsonConvert.DeserializeObject<ChampionsObject>(result);
                }
            }

            if (savedChampionData != null)
            {
                string cooldown = null;
                string championName = null;
                foreach (KeyValuePair<string, ChampionDataObject> champ in savedChampionData.Data)
                {
                    if (champ.Value.Key == id)
                    {
                        championName = champ.Value.Id;
                        break;
                    }
                }

                HttpWebRequest request = WebRequest.Create(BeginRequest + DDragonAPIUrl + "/cdn/" + CurrentRealm.n.champion + String.Format(RequestChampionByName, championName)) as HttpWebRequest;
                string result = MakeRequest(request);
                if (result != null)
                {
                    ChampionSpecificDataObject championData = JsonConvert.DeserializeObject<ChampionSpecificDataObject>(result);
                    cooldown = championData.Data[championName].Spells[3].CooldownBurn;
                }
            
                if(cooldown != null)
                {
                    string[] cooldownBurn = cooldown.Split('/');
                    jsonObject.Add(id.ToString(), cooldownBurn[0].ToString());
                    json = JsonConvert.SerializeObject(jsonObject);
                    File.WriteAllText(path, json, Encoding.UTF8);

                    return Int32.Parse(cooldownBurn[0]);
                }                
            }
            return -1;
        }

        public static string MakeRequest(HttpWebRequest request)
        {
            NumberRequest++;
            string result = null;
            try
            {
                using (HttpWebResponse response = request.GetResponse() as HttpWebResponse)
                {
                    StreamReader reader = new StreamReader(response.GetResponseStream());
                    result = reader.ReadToEnd();
                }
            }
            catch (WebException exeption)
            {
                LastError = request.Address.ToString();
                throw exeption;
            }
            return result;
        }
    }
}