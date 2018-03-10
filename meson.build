project('cutils', 'c')

WARNINGS = ['-Wall', '-Wpedantic', '-Wextra', '-Wnull-dereference', '-Wshadow', '-Wconversion', '-Wstrict-prototypes', '-Wmissing-prototypes', '-Wcast-qual', '-Wstrict-overflow=5', '-Wunreachable-code', '-Wno-unused-parameter', '-Wno-unused-function']
CFLAGS = ['-std=c89', '-fstrict-aliasing', '-fPIC'] + WARNINGS

subdir('include')
subdir('src')


pkg = import('pkgconfig')
libs = 'cutils'
headers = 'include'

pkg.generate(libraries : cutils_lib, subdirs : headers, version : '1.0', name : 'libcutils', filebase : 'cutils', description : 'Collection of some portable helper function and data structures in C89.')
