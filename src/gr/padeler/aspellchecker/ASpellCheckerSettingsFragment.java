/**
 * 
 */
package gr.padeler.aspellchecker;


import android.os.Bundle;
import android.preference.PreferenceFragment;

/**
 * @author padeler
 *
 */
public class ASpellCheckerSettingsFragment extends PreferenceFragment
{
    /**
     * Empty constructor for fragment generation.
     */
    public ASpellCheckerSettingsFragment() {
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        addPreferencesFromResource(R.xml.prefs);
    }
}
