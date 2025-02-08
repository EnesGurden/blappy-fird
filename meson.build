project(
  'blappy-fird',
  'c',
  version: '0.1',
  default_options: ['default_library=shared', 'warning_level=3'],
)

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: false)
gdi32_dep = cc.find_library('gdi32', required: false)
winmm_dep = cc.find_library('winmm', required: false)

raylib_dep = dependency('raylib')

exe = executable(
  'blappy-fird',
  'src/main.c',
  dependencies: [raylib_dep, m_dep, gdi32_dep, winmm_dep],
  install: true,
)

test('basic', exe)

install_data(sources: 'bird.png', install_dir: '/resources')