from conans import ConanFile

class ConanDependencies(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'cmake'

    def requirements(self):
        self.requires('Catch2/2.9.1@catchorg/stable')
        self.requires('trompeloeil/v34@rollbear/stable')
