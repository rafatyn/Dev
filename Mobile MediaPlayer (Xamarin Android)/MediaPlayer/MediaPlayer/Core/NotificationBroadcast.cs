using Android.Content;
using Android.Support.V7.App;
using Android.Widget;

namespace MediaPlayer.Core
{
    public class NotificationBroadcast : BroadcastReceiver
    {
        public enum Actions { shuffleAction, previousAction, playPauseAction, nextAction }

        MainActivity MainActivity;

        public NotificationBroadcast(MainActivity activity)
        {
            MainActivity = activity;
        }

        public override void OnReceive(Context context, Intent intent)
        {
            if(intent.Action == Actions.shuffleAction.ToString())
            {
                MainActivity.ChangePlayingMode();
            }
            else if (intent.Action == Actions.previousAction.ToString())
            {
                MainActivity.ChangeToPreviousSong();
            }
            else if (intent.Action == Actions.playPauseAction.ToString())
            {
                MainActivity.PlayPauseSong();
            }
            else if (intent.Action == Actions.nextAction.ToString())
            {
                MainActivity.ChangeToNextSong();
            }
        }
    }
}