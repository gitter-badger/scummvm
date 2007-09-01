MODULE := engines/agi

MODULE_OBJS = \
	agi.o \
	agi_v2.o \
	agi_v3.o \
	agi_preagi.o \
	checks.o \
	console.o \
	cycle.o \
	detection.o \
	global.o \
	graphics.o \
	id.o \
	inv.o \
	keyboard.o \
	logic.o \
	lzw.o \
	menu.o \
	motion.o \
	objects.o \
	op_cmd.o \
	op_dbg.o \
	op_test.o \
	picture.o \
	preagi.o \
	preagi_keyboard.o \
	preagi_mickey.o \
	predictive.o \
	saveload.o \
	sound.o \
	sprite.o \
	text.o \
	view.o \
	wagparser.o \
	words.o


# This module can be built as a plugin
ifdef BUILD_PLUGINS
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
