/**
 * 
 */
package gr.padeler.aspellchecker;


import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;

import android.content.ContentResolver;
import android.content.SharedPreferences;
import android.content.res.AssetManager;
import android.database.ContentObserver;
import android.database.Cursor;
import android.os.Handler;
import android.preference.PreferenceManager;
import android.provider.ContactsContract.Contacts;
import android.provider.UserDictionary.Words;
import android.service.textservice.SpellCheckerService;
import android.util.Log;
import android.view.textservice.SuggestionsInfo;
import android.view.textservice.TextInfo;

/**
 * @author padeler
 *
 */
public class ASpellCheckerService extends SpellCheckerService
{

	private static final String DATA = "data";
	private static final String TAG = ASpellCheckerService.class.getSimpleName();
	private static final boolean DBG = true;
	
	private static final String[] PROJECTION = {
	                                            Words._ID,
	                                            Words.WORD,
	                                            Words.FREQUENCY,
	                                            Words.LOCALE,
	                                            Words.APP_ID
	                                        };
	

	@Override
	public Session createSession()
	{
		// check if the data files are correctly copied from the assets.
		try{
			String dataDir = checkAndUpdateDataFiles();
			SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
			String lang = prefs.getString("available_dicts", "sv");
			
			return new ASpellCheckerSession(dataDir,getContentResolver());
			
		}catch(IOException e)
		{
			Log.e(TAG,"Failed to initialize ASpellCheckerService", e);
		}
		return new ASpellCheckerSession("",getContentResolver()); // TODO Find a good way to gracefully fail. This will fail on ASpell initialization.
	}
	
	private String checkAndUpdateDataFiles() throws IOException
	{
		String []files = getFilesDir().list();
		if(files.length==0)
		{
			Log.d(TAG, "Data dir is not available. Creating.");
			
			File dataDir = new File(getFilesDir()+File.separator+DATA);
			dataDir.mkdir();
			AssetManager assets = getAssets();
			files = assets.list(DATA);
			for(String file:files)
			{
				String dst = dataDir+File.separator+file;
				try{
					Log.d(TAG, "Copying "+file+" from assets to "+dst);
					
					FileOutputStream fout = new FileOutputStream(dst);
					InputStream in = assets.open(DATA+File.separator+file);
					
					byte buf[] = new byte[1024];
					int count=0;
					while((count=in.read(buf))!=-1)
					{
						fout.write(buf,0,count);
					}
					in.close();
					fout.close();
				}catch(IOException e){
					throw new IOException("Failed to copy "+file+" to "+dst, e);
				}
			}
		}
		
		String res = getFilesDir()+File.separator+DATA;
		return res;
	}
	
	private static class ASpellCheckerSession extends Session
	{
		private String mLocale;
		private ASpell bridge;
		private String dataDir;
		private ContentResolver contentResolver;
		
		public ASpellCheckerSession(String dataDir, final ContentResolver contentResolver)
		{
			this.dataDir = dataDir;
			this.contentResolver = contentResolver;
		}
		
		protected synchronized void UserDictionaryUpdated()
		{
			Cursor cursor = contentResolver.query(Words.CONTENT_URI, PROJECTION,
	            Words.LOCALE + " = ?", new String[] {mLocale}, null);

			int index = cursor.getColumnIndex(Words.WORD);
	    	ArrayList<String> words = new ArrayList<String>();
			while (cursor.moveToNext())
			{
				words.add(cursor.getString(index));
			}
			
			cursor = contentResolver.query( Contacts.CONTENT_URI, 
			            new String[]{Contacts.DISPLAY_NAME}, null, null, null);
			index = cursor.getColumnIndex(Contacts.DISPLAY_NAME);
			while(cursor.moveToNext())
			{
				for(String name : cursor.getString(index).split("\\s+"))
				{
					if(name.matches("(\\p{L}\\p{M}*)+"))
						words.add(name);
				}
			}
			
			Log.d(TAG,"Loaded user dictionary+contacts with " + words.size() + " words.");
			
			//Log.d(TAG, "User dictionary: "+ Arrays.toString(words.toArray(new String[]{})));
			
			bridge.setUserDictionary(words.toArray(new String[]{}));
		}

		@Override
		public synchronized void onCreate()
		{
			
			mLocale = getLocale();
			Log.d(TAG, "Creating ASpell Speller. DataDir: "+dataDir+" Lang: "+mLocale);
			
			bridge = new ASpell(dataDir,mLocale);
			
			contentResolver.registerContentObserver(Words.CONTENT_URI, true, new ContentObserver(null) {
			    @Override
			    public void onChange(boolean selfChange) {
			    	UserDictionaryUpdated();
			    }
			});
			UserDictionaryUpdated();
		}

		@Override
		public synchronized SuggestionsInfo onGetSuggestions(TextInfo textInfo, int suggestionsLimit)
		{
			mLocale = getLocale();
			String text = textInfo.getText();
			long start = System.currentTimeMillis();
			String []suggestions = bridge.check(text);
			long end = System.currentTimeMillis();
			String code = suggestions[0];
			Log.d(TAG, "===Suggestion code ==> "+code);

			if(suggestions.length>1) // we have some suggestions
			{
				if(suggestions.length>suggestionsLimit+1)
				{
					String []tmp = new String[suggestionsLimit];
					System.arraycopy(suggestions, 1, tmp, 0, suggestionsLimit);
					suggestions = tmp;
				}
				else  // just keep all suggestions
				{
					String []tmp = new String[suggestions.length-1];
					System.arraycopy(suggestions, 1, tmp, 0, tmp.length);
					suggestions = tmp;
				}
			}
			else{
				suggestions = new String[]{};
			}
			
			if (DBG)
			{
				Log.d(TAG, "["+mLocale+"].onGetSuggestions ("+textInfo.getText()+","+suggestionsLimit+"): " + " Code : "+code+". Time to ASPELL: "+(end-start)+" ms.");
			}
			int flags;
			if("1".equals(code) || suggestions.length > 0 && suggestions[0].equals(text))// Aspell bug?
			{
				flags = SuggestionsInfo.RESULT_ATTR_IN_THE_DICTIONARY;
			}
			else
			{
				flags = SuggestionsInfo.RESULT_ATTR_LOOKS_LIKE_TYPO;
			}
			
			if(suggestions.length>0) flags |= SuggestionsInfo.RESULT_ATTR_HAS_RECOMMENDED_SUGGESTIONS;
			
			return new SuggestionsInfo(flags, suggestions);
		}
	}
}