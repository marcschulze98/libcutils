src = ['vector.c', 'dyn_string.c', 'misc.c']
srctest = src + ['test.c']

lib = shared_library('cutils', src, include_directories : inc)
cutils_dep = declare_dependency(link_with : lib, include_directories : inc)

executable('test_cutils', srctest, include_directories : inc, c_args: CFLAGS )