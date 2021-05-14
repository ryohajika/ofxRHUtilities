meta:
	ADDON_NAME = ofxRHUtilities
	ADDON_DESCRIPTION = utility pack for my openframeworks based projects
	ADDON_AUTHOR = Ryo Hajika
	ADDON_TAGS = "openframeworks" "utility"
	ADDON_URL = https://github.com/ryohajika/ofxRHUtilities.git

common:
	ADDON_DEPENDENCIES = ofxOpenCv

	ADDON_INCLUDES += src
	ADDON_INCLUDES += libs/easing-functions/src

	ADDON_SOURCES += src
	ADDON_SOURCES += libs/easing-functions/src

osx:
