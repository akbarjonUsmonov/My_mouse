lib_c_folder := $(lib_folder)c/
lib_h_folder := $(lib_folder)h/

lib_c := $(wildcard $(lib_c_folder)*.c)
lib_h := $(wildcard $(lib_h_folder)*.h)
lib_o := $(patsubst $(lib_c_folder)%.c, $(lib_o_folder)%.o,\
         $(lib_c))

$(lib_o_folder):
	if [ ! -d $@ ]; then mkdir -p $@; fi

$(lib_o): $(lib_o_folder)%.o: $(lib_c_folder)%.c $(lib_h)
	$(compiler) $(warning_flags) -I$(lib_h_folder) -c $< -o $@

lib_objects := $(lib_o_folder) $(lib_o)
