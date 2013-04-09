LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_ARM_MODE := arm
LOCAL_MODULE := openal
SRC_FILES := $(wildcard $(LOCAL_PATH)/../../../gfx/openal/*.c)
SRC_FILES := $(SRC_FILES:$(LOCAL_PATH)/%=%) 
LOCAL_SRC_FILES = $(SRC_FILES)
LOCAL_LDLIBS = -llog
LOCAL_CFLAGS := -O3
#LOCAL_CPPFLAGS := -O3
#LOCAL_CFLAGS := -O3 -mno-thumb
LOCAL_CPPFLAGS := -O3 -mno-thumb
include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_ARM_MODE := arm
LOCAL_MODULE   := gfxApp
LOCAL_CFLAGS   := -O3 -mno-thumb 
LOCAL_CPPFLAGS := $(LOCAL_CFLAGS)
LOCAL_C_INCLUDES = $(LOCAL_PATH)/../../../gfx/openal/ $(LOCAL_PATH)/../../../gfx/ $(LOCAL_PATH)/../../../gfxe/  $(LOCAL_PATH)/../../../ragtime/
SRC_FILES := $(wildcard $(LOCAL_PATH)/../../*.cpp)
SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../gfx/*.cpp)
SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../gfx/bullet/*.cpp)
SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../gfx/ttf/*.cpp)
SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../gfx/nvtristrip/*.cpp)
SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../gfx/png/*.c)
SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../gfx/zlib/*.c)
SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../gfx/detour/*.cpp)
SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../gfx/recast/*.cpp)
SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../gfx/vorbis/*.c)
SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../gfxe/*.cpp)
SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../ragtime/*.cpp)
SRC_FILES := $(SRC_FILES:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES := $(SRC_FILES)
LOCAL_SHARED_LIBRARIES := libopenal
LOCAL_LDLIBS := -L$(LOCAL_PATH)/../libs/armeabi 
LOCAL_LDLIBS += -lz -lm -ldl -lGLESv2 -lEGL -llog
# -lpthread -lopenal
LOCAL_CFLAGS := -O3 -Wno-write-strings
LOCAL_CPPFLAGS := -O3 -Wno-write-strings -std=c++11 -pthread -frtti -fexceptions
#LOCAL_CFLAGS := -O3 -mno-thumb -Wno-write-strings
#LOCAL_CPPFLAGS := -O3 -mno-thumb -Wno-write-strings -std=c++11 -pthread -frtti -fexceptions
include $(BUILD_SHARED_LIBRARY)
