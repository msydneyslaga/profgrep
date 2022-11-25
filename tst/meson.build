environ = environment()

environ.append('PATH', meson.project_build_root(), separator : ':')

test('censor', find_program('./censor.sh'), env : environ)

if find_program('lua', required : false).found()
    test('bytes', find_program('./bytes.sh'), env : environ)
endif

