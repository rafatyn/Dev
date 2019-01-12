using System.Collections.Generic;

namespace Riot_API
{
    // Realm Data Structs

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

    // Summoner Data Structs

    public class SummonerObject
    {
        public uint id { get; set; }
        public uint accountId { get; set; }
        public string name { get; set; }
        public ushort profileIconId { get; set; }
        public long revisionDate { get; set; }
        public ushort summonerLevel { get; set; }
    }

    // Current Game Data Structs

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

    public class ObserversObject
    {
        public string encryptionKey { get; set; }
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

    // Limbo

    public class PerksObject
    {
        public int perkStyle { get; set; }
        public List<int> perkIds { get; set; }
        public int perkSubStyle { get; set; }
    }

    // General Image Data Struct

    public class ImageObject
    {
        public string full { get; set; }
        public string sprite { get; set; }
        public string group { get; set; }
        public int x { get; set; }
        public int y { get; set; }
        public int w { get; set; }
        public int h { get; set; }
    }

    // Champions Data Structs

    public partial class ChampionsObject
    {
        public string Type { get; set; }
        public string Format { get; set; }
        public string Version { get; set; }
        public Dictionary<string, ChampionDataObject> Data { get; set; }
    }

    public partial class ChampionDataObject
    {
        public string Version { get; set; }
        public string Id { get; set; }
        public long Key { get; set; }
        public string Name { get; set; }
        public string Title { get; set; }
        public string Blurb { get; set; }
        public InfoObject Info { get; set; }
        public ImageObject Image { get; set; }
        public string[] Tags { get; set; }
        public string Partype { get; set; }
        public ChampionStatsObject Stats { get; set; }
    }

    public partial class InfoObject
    {
        public long Attack { get; set; }
        public long Defense { get; set; }
        public long Magic { get; set; }
        public long Difficulty { get; set; }
    }

    public class ChampionStatsObject
    {
        public float HP { get; set; }
        public float HpPerLevel { get; set; }
        public float MP { get; set; }
        public float MpPerLevel { get; set; }
        public float MoveSpeed { get; set; }
        public float Armor { get; set; }
        public float ArmorPerLevel { get; set; }
        public float SellBlock { get; set; }
        public float SellBlockPerLevel { get; set; }
        public float AttackRange { get; set; }
        public float HpRegen { get; set; }
        public float HpRegenPerLevel { get; set; }
        public float MpRegen { get; set; }
        public float MpRegenPerLevel { get; set; }
        public float Crit { get; set; }
        public float CritPerLevel { get; set; }
        public float AttackDamage { get; set; }
        public float AttackDamagePerLevel { get; set; }
        public float AttackSpeedOffset { get; set; }
        public float AttackSpeedPerLevel { get; set; }
    }

    // Summoner Spell Data Structs

    public partial class SummonerSpellsObject
    {
        public string Type { get; set; }
        public string Version { get; set; }
        public Dictionary<string, SummonerSpellDataObject> Data { get; set; }
    }

    public partial class SummonerSpellDataObject
    {
        public string Id { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public string Tooltip { get; set; }
        public long Maxrank { get; set; }
        public double[] Cooldown { get; set; }
        public string CooldownBurn { get; set; }
        public long[] Cost { get; set; }
        public long CostBurn { get; set; }
        public Dictionary<string, string> Datavalues { get; set; }
        public double[][] Effect { get; set; }
        public string[] EffectBurn { get; set; }
        public Var[] Vars { get; set; }
        public long Key { get; set; }
        public long SummonerLevel { get; set; }
        public string[] Modes { get; set; }
        public string CostType { get; set; }
        public long Maxammo { get; set; }
        public long[] Range { get; set; }
        public long RangeBurn { get; set; }
        public ImageObject Image { get; set; }
        public string Resource { get; set; }
    }

    public partial class Var
    {
        public string Link { get; set; }        
        public long[] Coeff { get; set; }        
        public string Key { get; set; }
    }

    // Champion Specific Data Structs

    public partial class ChampionSpecificDataObject
    {
        public string Type { get; set; }
        public string Format { get; set; }
        public string Version { get; set; }
        public Dictionary<string, ChampionSpecificDataObject> Data { get; set; }
    }

    public partial class ChampionSpecificDataObject
    {
        public string Id { get; set; }
        public long Key { get; set; }
        public string Name { get; set; }
        public string Title { get; set; }
        public ImageObject Image { get; set; }
        public SkinObject[] Skins { get; set; }
        public string Lore { get; set; }
        public string Blurb { get; set; }
        public string[] Allytips { get; set; }
        public string[] Enemytips { get; set; }
        public string[] Tags { get; set; }
        public string Partype { get; set; }
        public InfoObject Info { get; set; }
        public ChampionStatsObject Stats { get; set; }
        public SpellObject[] Spells { get; set; }
        public PassiveObject Passive { get; set; }
        public RecommendedItemsObject[] Recommended { get; set; }
    }

    public partial class SkinObject
    {
        public long Id { get; set; }
        public long Num { get; set; }
        public string Name { get; set; }
        public bool Chromas { get; set; }
    }

    public partial class PassiveObject
    {
        public string Name { get; set; }
        public string Description { get; set; }
        public ImageObject Image { get; set; }
    }

    public partial class SpellObject
    {
        public string Id { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public string Tooltip { get; set; }
        public LeveltipObject Leveltip { get; set; }
        public long Maxrank { get; set; }
        public double[] Cooldown { get; set; }
        public string CooldownBurn { get; set; }
        public long[] Cost { get; set; }
        public string CostBurn { get; set; }
        public Dictionary<string, string> Datavalues { get; set; }
        public double[][] Effect { get; set; }
        public string[] EffectBurn { get; set; }
        public object[] Vars { get; set; }
        public string CostType { get; set; }
        public long Maxammo { get; set; }
        public long[] Range { get; set; }
        public string RangeBurn { get; set; }
        public ImageObject Image { get; set; }
        public string Resource { get; set; }
    }

    public partial class LeveltipObject
    {
        public string[] Label { get; set; }
        public string[] Effect { get; set; }
    }

    public partial class RecommendedItemsObject
    {
        public string Champion { get; set; }
        public string Title { get; set; }
        public string Map { get; set; }
        public string Mode { get; set; }
        public string Type { get; set; }
        public string CustomTag { get; set; }
        public long? Sortrank { get; set; }
        public bool ExtensionPage { get; set; }
        public bool? UseObviousCheckmark { get; set; }
        public object CustomPanel { get; set; }
        public BlockObject[] Blocks { get; set; }
    }

    public partial class BlockObject
    {
        public string Type { get; set; }
        public bool RecMath { get; set; }
        public bool RecSteps { get; set; }
        public long MinSummonerLevel { get; set; }
        public long MaxSummonerLevel { get; set; }
        public string ShowIfSummonerSpell { get; set; }
        public string HideIfSummonerSpell { get; set; }
        public string AppendAfterSection { get; set; }
        public string[] VisibleWithAllOf { get; set; }
        public string[] HiddenWithAnyOf { get; set; }
        public ItemObject[] Items { get; set; }
    }

    public partial class ItemObject
    {
        public long Id { get; set; }
        public long Count { get; set; }
        public bool HideCount { get; set; }
    }   
}
