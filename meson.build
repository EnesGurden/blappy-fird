project(
  'blappy-fird',
  ['c', 'cpp'],
  version: '0.1',
  default_options: ['cpp_std=c++17', 'default_library=shared', 'warning_level=3'],
)

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: false)
gdi32_dep = cc.find_library('gdi32', required: false)
winmm_dep = cc.find_library('winmm', required: false)
raylib_dep = dependency('raylib')

cppc = meson.get_compiler('cpp')

wt_include_dir = include_directories('C:/msys64/mingw64/include/Wt')
wt_lib_dir = 'C:/msys64/mingw64/lib'
wt_lib = cppc.find_library('wt', dirs: wt_lib_dir)

exe = executable(
  'blappy-fird',
  'src/main.c',
  dependencies: [raylib_dep, m_dep, gdi32_dep, winmm_dep],
  install: true,
)

executable(
  'blappy-web',
  'src/server.cpp',
  include_directories: wt_include_dir,
  dependencies: [wt_lib],
  install: false,
)

test('basic', exe)

install_data(sources: 'bird.png', install_dir: 'resources')