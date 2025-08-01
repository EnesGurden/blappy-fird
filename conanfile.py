from conan import ConanFile


class BlappyFird(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "PkgConfigDeps", "MesonToolchain"
    tool_requires = "pkgconf/2.2.0"

    def requirements(self):
        self.requires("raylib/5.5")
        self.requires("wt/4.11.2")
