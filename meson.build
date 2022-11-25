project(
	'profgrep',
	'c',
	version: '0.0.0',
	license: 'GPL-3.0',
	default_options: [
		'c_std=c99',
        'warning_level=3'
	],
)

cc = meson.get_compiler('c')

add_project_arguments(cc.get_supported_arguments([
    '-Wno-unused-parameter',
    '-pedantic',
    '-D_POSIX_C_SOURCE=200809L',
    '-Wno-missing-field-initializers',
]), language: 'c')


# buildtype
if get_option('buildtype') == 'debug'
    add_project_arguments(
        '-g3',
        '-Wno-unused-variable',
        '-Wno-unused-function',
        '-UNDEBUG',
        language : 'c'
    )
elif get_option('buildtype') == 'release'
    add_project_arguments(
        '-Ofast',
        '-Wunused-variable',
        '-Wunused-function',
        '-DNDEBUG',
        language : 'c'
    )
endif

# dependencies
assert(cc.has_header('tbs/types.h'))
incdir = include_directories('inc')
argp_dep = dependency('libargp')


# this is just for me :)
install_symlink(
    'profgrep',
    install_dir : meson.source_root(),
    pointing_to : join_paths(meson.project_build_root(), 'profgrep')
)

# compile without the main() file to link with tests
profgrep_src = files(
    'src/profgrep.c',
    'src/buffer.c',
    'src/search.c',
    'src/censor.c',
    'src/dictionary.c',
    'src/readln.c',
)

# MAIN EXECUTABLE
executable(
    'profgrep',
    profgrep_src,
    include_directories : incdir,
    dependencies : argp_dep,
)

# DOCS
# subdir('doc')
subdir('tst')

