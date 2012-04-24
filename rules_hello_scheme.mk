# Standard things

# Local rules and targets

TGTS_$(d)	:= hello-scheme
DEPS_$(d)	:= $(TGTS_$(d):%=%.d)

TGT_BIN		:= $(TGT_BIN) $(TGTS_$(d))
#TGT_MAN1	:= $(TGT_MAN1) doc/man/man1/paenc.1
CLEAN		:= $(CLEAN) $(TGTS_$(d)) $(DEPS_$(d)) $(TGTS_$(d)).exe

$(TGTS_$(d)):	CF_TGT :=
$(TGTS_$(d)):	LL_TGT :=

$(TGTS_$(d)): $(OBJS_hello_scheme) tinyscheme/tinyscheme_$(PLATFORM).a
	$(LINK)



# Standard things

-include	$(DEPS_$(d))

