# Standard things

sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)


# Local variables

OBJS_$(d)	:= $(shell ./build/loop_obj.sh $(dir)/src)

DEPS_$(d)	:= $(OBJS_$(d):%=%.d)

CLEAN		:= $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d))


# Local rules

$(OBJS_$(d)):	CF_TGT := -I$(d)



# Standard things

-include	$(DEPS_$(d))

d		:= $(dirstack_$(sp))
sp	:= $(basename $(sp))

