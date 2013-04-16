


include $(LOCAL_PATH)/../../libpng/Android.mk
include $(LOCAL_PATH)/../../libjpeg/Android.mk
include $(LOCAL_PATH)/../../freetype/Android.mk

include $(CLEAR_VARS)
LOCAL_CFLAGS += -D_GLIBCXX_PERMIT_BACKWARD_HASH
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../libutils \
					$(LOCAL_PATH)/../../freetype/include \
					$(LOCAL_PATH)/../../libjpeg \
					$(LOCAL_PATH)/../../libpng \
					$(LOCAL_PATH)/../../Graphic
LOCAL_MODULE := Graphic
LOCAL_SRC_FILES := $(call all-cpp-files-under,../../Graphic) \
	test.cpp
LOCAL_STATIC_LIBRARIES := png jpeg ft2 
LOCAL_LDLIBS := -lz -lm -llog -ljnigraphics
	
include $(BUILD_SHARED_LIBRARY)
