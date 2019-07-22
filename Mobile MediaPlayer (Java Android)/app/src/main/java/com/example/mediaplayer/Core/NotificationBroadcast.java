package com.example.mediaplayer.Core;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import com.example.mediaplayer.MainActivity;

public class NotificationBroadcast extends BroadcastReceiver {
    public enum Actions { shuffleAction, previousAction, playPauseAction, nextAction }

    com.example.mediaplayer.MainActivity MainActivity;

    public NotificationBroadcast() {}

    public NotificationBroadcast(MainActivity activity)
    {
        MainActivity = activity;
    }

    @Override
    public void onReceive(Context context, Intent intent)
    {
        if(intent.getAction().equals(Actions.shuffleAction.toString()))
        {
            MainActivity.ChangePlayingMode();
        }
        else if (intent.getAction().equals(Actions.previousAction.toString()))
        {
            MainActivity.ChangeToPreviousSong();
        }
        else if (intent.getAction().equals(Actions.playPauseAction.toString()))
        {
            MainActivity.PlayPauseSong();
        }
        else if (intent.getAction().equals(Actions.nextAction.toString()))
        {
            MainActivity.ChangeToNextSong();
        }
        else if(intent.getAction().equals(Intent.ACTION_HEADSET_PLUG))
        {
            switch(intent.getIntExtra("state", -1)) {
                case(0):
                    MainActivity.PauseSong();
                    break;
                case(1):
                    MainActivity.PlaySong();
                    break;
            }
        }
    }
}
