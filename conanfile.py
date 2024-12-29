from conan import ConanFile
from conan.tools.cmake import cmake_layout


class BlappyFird(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "PkgConfigDeps", "MesonToolchain"
    tool_requires = "pkgconf/2.2.0"

    def requirements(self):
        self.requires("raylib/5.5")

    def layout(self):
        cmake_layout(self)