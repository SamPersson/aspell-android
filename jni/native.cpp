#include <jni.h>
#include <string.h>
#include <android/log.h>
#include "aspell.h"

#include <stdio.h>

#define DEBUG_TAG "NDK_ASpell"

extern "C"
{

void log_word_list(AspellSpeller * speller, const AspellWordList *wl)
{
	if (wl == 0)
	{
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,
		                    "NDK:LC: Failed to get suggested world list [%s]",
		                    aspell_speller_error_message(speller));
	}
	else
	{
		AspellStringEnumeration * els = aspell_word_list_elements(wl);
		const char * word;
		while ((word = aspell_string_enumeration_next(els)) != 0)
		{
			__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,
			                    "NDK:LC: Suggested: [%s]", word);
		}
		delete_aspell_string_enumeration(els);
	}
}

void Java_se_randomdev_aspellchecker_ASpell_destruct(JNIEnv * env, jobject _this)
{
	jclass cls = env->GetObjectClass(_this);
	jfieldID fid = env->GetFieldID(cls, "nativePtr", "J");
	AspellSpeller *speller = (AspellSpeller *) env->GetLongField(_this, fid);
	delete_aspell_speller(speller);
	env->SetLongField(_this, fid, 0);
}

void Java_se_randomdev_aspellchecker_ASpell_setUserDictionary(JNIEnv * env, jobject _this, jobjectArray strings)
{
	jclass cls = env->GetObjectClass(_this);
	jfieldID fid = env->GetFieldID(cls, "nativePtr", "J");
	AspellSpeller *speller = (AspellSpeller *) env->GetLongField(_this, fid);
	
	if (speller == NULL)
	{
		env->ThrowNew(env->FindClass("java/lang/Exception"), "Speller Not initialized");
		return;
	}
	
	aspell_speller_clear_session(speller);
	
	jboolean isCopy;	
	int numWords = env->GetArrayLength(strings);
	for (int i = 0; i < numWords; i++)
	{
		jstring jword = (jstring) env->GetObjectArrayElement(strings, i);
		const char * word = env->GetStringUTFChars(jword, &isCopy);
		int stringLength = env->GetStringUTFLength(jword);
		aspell_speller_add_to_session(speller, word, stringLength);
		env->ReleaseStringUTFChars(jword, word);
	}
	
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,
		                    "NDK:ASpell User dictionary updated");
}

jboolean Java_se_randomdev_aspellchecker_ASpell_initialize(JNIEnv * env,
                                                         jobject _this,
                                                         jstring dataDirStr,
                                                         jstring localeStr)
{
	jclass cls = env->GetObjectClass(_this);
	jfieldID fid = env->GetFieldID(cls, "nativePtr", "J");

	if (env->GetLongField(_this, fid) != 0)
	{
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,
		                    "NDK:ASpell Already initialized!");
		return JNI_FALSE;
	}

	AspellSpeller *speller = NULL;
	AspellConfig * config = NULL;
	AspellCanHaveError * ret;

	config = new_aspell_config();

	jboolean isCopy;
	const char * locale = env->GetStringUTFChars(localeStr, &isCopy);
	const char * dataDir = env->GetStringUTFChars(dataDirStr, &isCopy);
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,
	                    "NDK:ASpell Creating Speller [%s] [%s]", locale,
	                    dataDir);

	aspell_config_replace(config, "lang", locale);
	aspell_config_replace(config, "data-dir", dataDir);
	aspell_config_replace(config, "dict-dir", dataDir);
	aspell_config_replace(config, "rem-filter", "url");
	aspell_config_replace(config, "encoding", "UTF-8");

	ret = new_aspell_speller(config);
	delete_aspell_config(config);

	env->ReleaseStringUTFChars(localeStr, locale);
	env->ReleaseStringUTFChars(dataDirStr, dataDir);

	if (aspell_error(ret) != 0)
	{
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,
		                    "NDK:ASpell Failed to create speller [%s]",
		                    aspell_error_message(ret));
		delete_aspell_can_have_error(ret);
		return JNI_FALSE;
	}

	speller = to_aspell_speller(ret);
	config = aspell_speller_config(speller);

	env->SetLongField(_this, fid, (jlong) speller);

	return JNI_TRUE;
}

jobjectArray Java_se_randomdev_aspellchecker_ASpell_check(JNIEnv * env,
                                                        jobject _this,
                                                        jstring wordStr)
{
	jobjectArray res;

	jclass cls = env->GetObjectClass(_this);
	jfieldID fid = env->GetFieldID(cls, "nativePtr", "J");
	AspellSpeller *speller = (AspellSpeller *) env->GetLongField(_this, fid);

	if (speller == NULL)
	{
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,
		                    "NDK:ASpell Speller Not initialized.");
		res = (jobjectArray) env->NewObjectArray(
		    1, env->FindClass("java/lang/String"), env->NewStringUTF(""));

		env->SetObjectArrayElement(res, 0, env->NewStringUTF("-100"));
		return res;
	}

	jboolean isCopy;
	const char * word = env->GetStringUTFChars(wordStr, &isCopy);
	//__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,
	//                    "NDK:ASpell Checking word [%s]", word);

	int have = aspell_speller_check(speller, word, -1);
	char code[5];
	sprintf(code, "%d", have);

	if (have != 0 && have != 1)
	{ // error. Keep the code in the result and log the event.
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,
		                    "NDK:ASpell Error %s\n",
		                    aspell_speller_error_message(speller));
		res = (jobjectArray) env->NewObjectArray(
		    1, env->FindClass("java/lang/String"), env->NewStringUTF(""));
		env->SetObjectArrayElement(res, 0, env->NewStringUTF(code));
	}
	else
	{ // i have results, store them to the result array.
		const AspellWordList *wl = aspell_speller_suggest(speller, word, -1);
		int len = aspell_word_list_size(wl) + 1;
		res = (jobjectArray) env->NewObjectArray(
		    len, env->FindClass("java/lang/String"), env->NewStringUTF(""));

		AspellStringEnumeration * els = aspell_word_list_elements(wl);

		// store res code to first element of the list.
		env->SetObjectArrayElement(res, 0, env->NewStringUTF(code));

		const char * suggestion;
		int i;
		for (i = 1; i < len; ++i)
		{
			suggestion = aspell_string_enumeration_next(els);
			env->SetObjectArrayElement(res, i, env->NewStringUTF(suggestion));
		}
		delete_aspell_string_enumeration(els);
	}
	env->ReleaseStringUTFChars(wordStr, word);
	return res;
}

}
