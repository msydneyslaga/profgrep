environ = environment()

environ.append('PATH', meson.project_build_root(), separator : ':')

test('censor', find_program('./censor.sh'), env : environ)

