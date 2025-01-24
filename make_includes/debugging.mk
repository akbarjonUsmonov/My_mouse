gdb_flags      := -ggdb -O0
asan_flags     := -g3 -fsanitize=address

gdb: gdb_concatenate all

gdb-re: gdb_concatenate re

gdb_concatenate:
	$(eval warning_flags += $(gdb_flags))

asan: asan_concatenate all

asan-re: asan_concatenate re

asan_concatenate:
	$(eval warning_flags += $(asan_flags))

debug_phony := gdb_concatenate gdb-re gdb asan_concatenate asan-re asan
