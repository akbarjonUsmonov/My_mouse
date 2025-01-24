make_includes := ./make_includes/

include $(make_includes)folders.mk
include $(make_includes)variables.mk

.DELETE_ON_ERROR:

all: $(target)

include $(lib_folder)lib.mk
include $(mouse_folder)mouse.mk

objects := $(mouse_objects) $(lib_objects)

$(target): $(objects)
	$(compiler) $(warning_flags) -o $(target) $(mouse_o) $(lib_o)

include $(make_includes)debugging.mk

clean:
	rm -rf $(mouse_o)

fclean: clean
	rm -rf $(target) $(objects_folder)

re: fclean all

.PHONY: all clean fclean re $(debug_phony)
