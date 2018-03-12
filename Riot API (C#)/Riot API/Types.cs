using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Riot_API
{
    public class SummonerObject
    {
        public uint id { get; set; }
        public uint accountId { get; set; }
        public string name { get; set; }
        public ushort profileIconId { get; set; }
        public long revisionDate { get; set; }
        public ushort summonerLevel { get; set; }
    }

    public class ObserversObject
    {
        public string encryptionKey { get; set; }
    }

    public class PerksObject
    {
        public int perkStyle { get; set; }
        public List<int> perkIds { get; set; }
        public int perkSubStyle { get; set; }
    }

    public class ParticipantObject
    {
        public int profileIconId { get; set; }
        public int championId { get; set; }
        public string summonerName { get; set; }
        public List<object> gameCustomizationObjects { get; set; }
        public bool bot { get; set; }
        public PerksObject perks { get; set; }
        public int spell2Id { get; set; }
        public int teamId { get; set; }
        public int spell1Id { get; set; }
        public int summonerId { get; set; }
    }

    public class BannedChampionObject
    {
        public int teamId { get; set; }
        public int championId { get; set; }
        public int pickTurn { get; set; }
    }

    public class CurrentGameObject
    {
        public long gameId { get; set; }
        public long gameStartTime { get; set; }
        public string platformId { get; set; }
        public string gameMode { get; set; }
        public int mapId { get; set; }
        public string gameType { get; set; }
        public int gameQueueConfigId { get; set; }
        public ObserversObject observers { get; set; }
        public List<ParticipantObject> participants { get; set; }
        public int gameLength { get; set; }
        public List<BannedChampionObject> bannedChampions { get; set; }
    }

    public class ImageObject
    {
        public string full { get; set; }
        public string group { get; set; }
        public string sprite { get; set; }
        public int h { get; set; }
        public int w { get; set; }
        public int y { get; set; }
        public int x { get; set; }
    }    

    public class ChampionImageObject
    {
        public ImageObject image { get; set; }
        public string name { get; set; }
        public int id { get; set; }
        public string title { get; set; }
        public string key { get; set; }
    }
    public class SpellImageObject
    {
        public string name { get; set; }
        public ImageObject image { get; set; }
        public string key { get; set; }
        public int summonerLevel { get; set; }
        public int id { get; set; }
        public string description { get; set; }
    }

    public class RealmDifferentsVersionsObject
    {
        public string summoner { get; set; }
        public string map { get; set; }
        public string champion { get; set; }
        public string language { get; set; }
        public string mastery { get; set; }
        public string sticker { get; set; }
        public string item { get; set; }
        public string rune { get; set; }
        public string profileicon { get; set; }
    }

    public class RealmObject
    {
        public string lg { get; set; }
        public string dd { get; set; }
        public string l { get; set; }
        public RealmDifferentsVersionsObject n { get; set; }
        public int profileiconmax { get; set; }
        public string v { get; set; }
        public string cdn { get; set; }
        public string css { get; set; }
    }

    public class SpellCooldownObject
    {
        public string cooldownBurn { get; set; }
        public string name { get; set; }
        public string key { get; set; }
        public int summonerLevel { get; set; }
        public int id { get; set; }
        public string description { get; set; }
    }
}
