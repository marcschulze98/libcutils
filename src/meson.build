src = ['vector.c', 'dyn_string.c', 'misc.c']
srctest = src + ['test.c']

cutils_lib = library('cutils', src, include_directories : inc, install: true)

cutils_dep = declare_dependency(link_with : cutils_lib, include_directories : inc)

executable('test_cutils', srctest, include_directories : inc, c_args: CFLAGS )
