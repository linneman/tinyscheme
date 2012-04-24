# Standard things

sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

include		$(dir)/Rules.mk


# Local variables

TGTS_$(d)	:= $(d)/tinyscheme_$(PLATFORM).a

TGT_LIB		:= $(TGT_LIB) $(TGTS_$(d))

OBJS_$(d)	:= $(OBJS_tinyscheme)

DEPS_$(d)	:= $(OBJS_$(d):%=%.d)

CLEAN		:= $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d))  $(TGTS_$(d))


# Local rules

$(OBJS_$(d)):	CF_TGT := -std=gnu99 -Wno-switch-enum -Wno-switch -Wno-char-subscripts \
	-DSUN_DL=0 -DUSE_DL=0 -DUSE_COLON_HOOK=1\
	-DUSE_MATH=0 -DUSE_ASCII_NAMES=0 -DSTANDALONE=0 -I$(d)/src

$(TGTS_$(d)):  $(OBJS_$(d))
		$(ARCH)


# Standard things

-include	$(DEPS_$(d))

d		:= $(dirstack_$(sp))
sp	:= $(basename $(sp))

