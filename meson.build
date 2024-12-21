project('blappy-fird', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

raylib_dep = dependency('raylib')

exe = executable('blappy-fird', 'src/main.c',
dependencies: raylib_dep,
  install : true)

test('basic', exe)
