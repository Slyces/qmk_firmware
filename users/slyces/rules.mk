SRC += slyces.c

#ifdef TAP_DANCE_ENABLE
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tap_dances.c
endif

#ifdef COMBO_ENABLE
ifeq ($(strip $(COMBO_ENABLE)), yes)
    SRC += combos.c
endif

#ifdef RGBLIGHT_ENABLE
ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += rgb_stuff.c
    #ifeq ($(strip $(RGBLIGHT_STARTUP_ANIMATION)), yes)
        #OPT_DEFS += -DRGBLIGHT_STARTUP_ANIMATION
    #endif
endif
