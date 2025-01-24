mouse_c_folder := $(mouse_folder)c/
mouse_h_folder := $(mouse_folder)h/

mouse_c := $(wildcard $(mouse_c_folder)*.c)
mouse_h := $(wildcard $(mouse_h_folder)*.h)
mouse_o := $(patsubst $(mouse_c_folder)%.c, $(mouse_o_folder)%.o,\
           $(mouse_c))

$(mouse_o_folder):
	if [ ! -d $@ ]; then mkdir -p $@; fi

mouse_compiler_includes := -I$(mouse_h_folder) -I$(lib_h_folder)

$(mouse_o): $(mouse_o_folder)%.o: $(mouse_c_folder)%.c
	$(compiler) $(warning_flags) $(mouse_compiler_includes) -c $< -o $@

## For future modules inclusion.
## mouse_o +=

mouse_o_folders := $(mouse_o_folder)

mouse_objects   := $(mouse_o_folders) $(mouse_o)
