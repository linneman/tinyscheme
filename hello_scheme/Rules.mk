# Standard things

sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)


# Local variables

OBJS_$(d)	:= $(shell ./build/loop_obj.sh $(dir)/src)

DEPS_$(d)	:= $(OBJS_$(d):%=%.d)

CLEAN		:= $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d))


# Local rules


# _POSIX_C_SOURCE=2 actives functions according "The Single Unix Specification, Version 2"
# in GNU/Linux system headers ( controlled by features.h macro ). This is currently
# required exclusively for getopt command line parsing.

# _GNU_SOURCE is required for the declaration of strdup in header file <string.h> for
# GNU platforms. strdup is used in json parser

$(OBJS_$(d)):	CF_TGT := -D_POSIX_C_SOURCE=2 -D_GNU_SOURCE \
	-I$(d)/src \
	-Itinyscheme/src


# Standard things

-include	$(DEPS_$(d))

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))

