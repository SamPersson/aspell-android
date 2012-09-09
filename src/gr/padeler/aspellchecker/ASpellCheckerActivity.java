package gr.padeler.aspellchecker;


import android.os.Bundle;
import android.preference.PreferenceActivity;


public class ASpellCheckerActivity extends PreferenceActivity{
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        addPreferencesFromResource(R.xml.prefs);
    }
}