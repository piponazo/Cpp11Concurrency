from conans import ConanFile

class ConanDependencies(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'cmake'

    def requirements(self):
        self.requires('catch2/2.13.9')
        self.requires('trompeloeil/42')
