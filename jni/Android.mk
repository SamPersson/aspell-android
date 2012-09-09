LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_LDLIBS := -llog
#LOCAL_CFLAGS := -std=gnu99
LOCAL_MODULE := aspell
LOCAL_C_INCLUDES := $(NDK_APP_PROJECT_PATH)/jni/common
LOCAL_SRC_FILES := native.cpp\
  common/cache.cpp\
  common/string.cpp\
  common/getdata.cpp\
  common/itemize.cpp\
  common/file_util.cpp\
  common/string_map.cpp\
  common/string_list.cpp\
  common/config.cpp\
  common/posib_err.cpp\
  common/errors.cpp\
  common/error.cpp\
  common/fstream.cpp\
  common/iostream.cpp\
  common/info.cpp\
  common/can_have_error.cpp\
  common/convert.cpp\
  common/tokenizer.cpp\
  common/speller.cpp\
  common/document_checker.cpp\
  common/filter.cpp\
  common/objstack.cpp \
  common/strtonum.cpp\
  common/gettext_init.cpp\
  common/file_data_util.cpp\
  modules/speller/default/readonly_ws.cpp\
  modules/speller/default/suggest.cpp\
  modules/speller/default/data.cpp\
  modules/speller/default/multi_ws.cpp\
  modules/speller/default/phonetic.cpp\
  modules/speller/default/writable.cpp\
  modules/speller/default/speller_impl.cpp\
  modules/speller/default/phonet.cpp\
  modules/speller/default/typo_editdist.cpp\
  modules/speller/default/editdist.cpp\
  modules/speller/default/primes.cpp\
  modules/speller/default/language.cpp\
  modules/speller/default/leditdist.cpp\
  modules/speller/default/affix.cpp\
  modules/tokenizer/basic.cpp\
  lib/filter-c.cpp\
  lib/word_list-c.cpp\
  lib/info-c.cpp\
  lib/mutable_container-c.cpp\
  lib/error-c.cpp\
  lib/document_checker-c.cpp\
  lib/string_map-c.cpp\
  lib/new_config.cpp\
  lib/config-c.cpp\
  lib/string_enumeration-c.cpp\
  lib/can_have_error-c.cpp\
  lib/dummy.cpp\
  lib/new_filter.cpp\
  lib/new_fmode.cpp\
  lib/string_list-c.cpp\
  lib/find_speller.cpp\
  lib/speller-c.cpp\
  lib/string_pair_enumeration-c.cpp\
  lib/new_checker.cpp

include $(BUILD_SHARED_LIBRARY)
