environ = environment()

environ.append('PATH', meson.project_build_root(), separator : ':')

test('biglist', find_program('./biglist.sh'), env : environ)

