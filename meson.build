project('cutils', 'c')

WARNINGS = ['-Wall', '-Wpedantic', '-Wextra', '-Wnull-dereference', '-Wshadow', '-Wconversion', '-Wstrict-prototypes', '-Wmissing-prototypes', '-Wcast-qual', '-Wstrict-overflow=5', '-Wunreachable-code', '-Wno-unused-parameter' ]
CFLAGS = ['-std=c11', '-fstrict-aliasing', '-fPIC'] + WARNINGS

subdir('include')
subdir('src')
