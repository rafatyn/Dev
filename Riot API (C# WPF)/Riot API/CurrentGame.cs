using System;
using System.Linq;
using System.Net;

namespace Riot_API
{
    class CurrentGame
    {
        private CurrentGameObject Game;

        public CurrentGame()
        {
            try
            {
                Game = Request.RequestCurrentGameInfo(Request.SummonerName);

                if (Game == null) return;
            }
            catch (WebException exeption)
            {
                throw exeption;
            }

            int Players = Game.participants.Count;

            for (int i = 0; i < Players / 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    string img = Convert.ToBase64String(Request.RequestChampiomImage(Game.participants.ElementAt(i + (j * (Players / 2))).championId).ToArray());
                    string element = "var element = document.createElement('img');"
                                   + "element.src = 'data:image/png;base64, " + img + "';"
                                   + "element.classList.add('rounded-circle');"
                                   + "element.classList.add('champion-img');";
                    UIHandler.AddChild(element, "current-game-img-" + ((i * 2) + j).ToString());

                    img = Convert.ToBase64String(Request.RequestSummonerSpellImage(Game.participants.ElementAt(i + (j * (Players / 2))).spell1Id).ToArray());
                    element = "var element = document.createElement('img');"
                            + "element.src = 'data:image/png;base64, " + img + "';"
                            + "element.classList.add('rounded-circle');"
                            + "element.classList.add('spell1-img');";
                    UIHandler.AddChild(element, "current-game-img-" + ((i * 2) + j).ToString());

                    element = "var element = document.createElement('img');"
                            + "element.src = 'data:image/png;base64, " + img + "';"
                            + "element.classList.add('rounded-circle');"
                            + "element.classList.add('status-first');";
                    UIHandler.AddChild(element, "current-game-cd-" + ((i * 2) + j).ToString());

                    int cooldown = Request.RequestSummonerSpellCooldown(Game.participants.ElementAt(i + (j * (Players / 2))).spell1Id);
                    if (cooldown != -1)
                    {
                        element = "var element = document.createElement('canvas');"
                                + "element.width = \"150\";"
                                + "element.height = \"150\";"
                                + "element.setAttribute(\"attr-timeLeft\", \"" + cooldown + "\");"
                                + "element.setAttribute(\"attr-totalTime\", \"" + cooldown + "\");"
                                + "element.classList.add('timer-canvas');"
                                + "element.classList.add('status-first');";
                        UIHandler.AddChild(element, "current-game-cd-" + ((i * 2) + j).ToString());
                    }

                    img = Convert.ToBase64String(Request.RequestSummonerSpellImage(Game.participants.ElementAt(i + (j * (Players / 2))).spell2Id).ToArray());
                    element = "var element = document.createElement('img');"
                            + "element.src = 'data:image/png;base64, " + img + "';"
                            + "element.classList.add('rounded-circle');"
                            + "element.classList.add('spell2-img');";
                    UIHandler.AddChild(element, "current-game-img-" + ((i * 2) + j).ToString());

                    element = "var element = document.createElement('img');"
                            + "element.src = 'data:image/png;base64, " + img + "';"
                            + "element.classList.add('rounded-circle');"
                            + "element.classList.add('status-second');";
                    UIHandler.AddChild(element, "current-game-cd-" + ((i * 2) + j).ToString());

                    cooldown = Request.RequestSummonerSpellCooldown(Game.participants.ElementAt(i + (j * (Players / 2))).spell2Id);
                    if (cooldown != -1)
                    {
                        element = "var element = document.createElement('canvas');"
                                + "element.width = \"150\";"
                                + "element.height = \"150\";"
                                + "element.setAttribute(\"attr-timeLeft\", \"" + cooldown + "\");"
                                + "element.setAttribute(\"attr-totalTime\", \"" + cooldown + "\");"
                                + "element.classList.add('timer-canvas');"
                                + "element.classList.add('status-second');";
                        UIHandler.AddChild(element, "current-game-cd-" + ((i * 2) + j).ToString());
                    }

                    img = Convert.ToBase64String(Request.RequestSummonerMaestryImage(Game.participants.ElementAt(i + (j * (Players / 2))).perks.perkIds[0]).ToArray());
                    element = "var element = document.createElement('img');"
                            + "element.src = 'data:image/png;base64, " + img + "';"
                            + "element.classList.add('rounded-circle');"
                            + "element.classList.add('maestry1-img');";
                    UIHandler.AddChild(element, "current-game-img-" + ((i * 2) + j).ToString());

                    img = Convert.ToBase64String(Request.RequestSummonerMaestryImage(Game.participants.ElementAt(i + (j * (Players / 2))).perks.perkSubStyle).ToArray());
                    element = "var element = document.createElement('img');"
                            + "element.src = 'data:image/png;base64, " + img + "';"
                            + "element.classList.add('rounded-circle');"
                            + "element.classList.add('maestry2-img');";
                    UIHandler.AddChild(element, "current-game-img-" + ((i * 2) + j).ToString());

                    img = Convert.ToBase64String(Request.RequestUltimateImageByChampion(Game.participants.ElementAt(i + (j * (Players / 2))).championId).ToArray());
                    element = "var element = document.createElement('img');"
                            + "element.src = 'data:image/png;base64, " + img + "';"
                            + "element.classList.add('rounded-circle');"
                            + "element.classList.add('status-third');";
                    UIHandler.AddChild(element, "current-game-cd-" + ((i * 2) + j).ToString());

                    cooldown = Request.RequestUltimateCooldownByChampion(Game.participants.ElementAt(i + (j * (Players / 2))).championId);
                    if (cooldown != -1)
                    {
                        element = "var element = document.createElement('canvas');"
                                + "element.width = \"150\";"
                                + "element.height = \"150\";"
                                + "element.setAttribute(\"attr-timeLeft\", \"" + cooldown + "\");"
                                + "element.setAttribute(\"attr-totalTime\", \"" + cooldown + "\");"
                                + "element.classList.add('timer-canvas');"
                                + "element.classList.add('status-third');";
                        UIHandler.AddChild(element, "current-game-cd-" + ((i * 2) + j).ToString());
                    }
                }
            }
        }
    }
}
