BSG_TILE_GROUP_DIM_X     ?= $(call bsg-min-fn,2,$(BSG_MACHINE_GLOBAL_X))
BSG_TILE_GROUP_DIM_Y     ?= $(call bsg-min-fn,2,$(call bsg-minus-fn,$(BSG_MACHINE_GLOBAL_Y),1))
BSG_TILE_GROUP_NUM_TILES ?= $(call bsg-times-fn,$(BSG_TILE_GROUP_DIM_X),$(BSG_TILE_GROUP_DIM_Y))
BSG_TILE_GROUP_ABRV      ?= Y$(BSG_TILE_GROUP_DIM_Y)X$(BSG_TILE_GROUP_DIM_X)
