meta:
	ADDON_NAME = ofxRHUtilities
	ADDON_DESCRIPTION = utility pack for my openframeworks based projects
	ADDON_AUTHOR = Ryo Hajika
	ADDON_TAGS = "openframeworks" "utility"
	ADDON_URL = https://github.com/ryohajika/ofxRHUtilities.git

common:
	#ADDON_DEPENDENCIES = ofxOpenCv

	ADDON_INCLUDES += src
	ADDON_INCLUDES += libs/easing-functions/src

	ADDON_INCLUDES += libs/CDT/CDT/extras
	ADDON_INCLUDES += libs/CDT/CDT/include

	ADDON_INCLUDES += libs/MemorySentinel/source

	ADDON_INCLUDES += libs/choc/audio
	ADDON_INCLUDES += libs/choc/containers
	ADDON_INCLUDES += libs/choc/gui
	ADDON_INCLUDES += libs/choc/javascript
	ADDON_INCLUDES += libs/choc/math
	ADDON_INCLUDES += libs/choc/memory
	ADDON_INCLUDES += libs/choc/platform
	ADDON_INCLUDES += libs/choc/text
	ADDON_INCLUDES += libs/choc/threading

	ADDON_SOURCES += src
	ADDON_SOURCES += libs/easing-functions/src
	ADDON_SOURCES += libs/MemorySentinel/source
	ADDON_SOURCES += libs/CDT/CDT/src

osx:
