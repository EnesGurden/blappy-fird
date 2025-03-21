project(
  'blappy-fird',
  'cpp',
  version: '0.1',
  default_options: ['default_library=shared', 'warning_level=3'],
)

cc = meson.get_compiler('cpp')
m_dep = cc.find_library('m', required: false)
gdi32_dep = cc.find_library('gdi32', required: false)
winmm_dep = cc.find_library('winmm', required: false)

raylib_dep = cc.find_library('raylib')
wt_dep = cc.find_library('wt')
wthttp_dep = cc.find_library('wthttp')

bf_sources = [
  'src/main.cpp',
  'src/game.cpp',
]

exe = executable(
  'blappy-fird',
  bf_sources,
  dependencies: [wt_dep, wthttp_dep, m_dep, gdi32_dep, winmm_dep, raylib_dep],
  install: true,
)

test('basic', exe)

install_data(sources: 'bird.png', install_dir: '/resources')