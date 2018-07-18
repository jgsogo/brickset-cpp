import os
from conans import ConanFile, CMake, tools, RunEnvironment


class BricksetConan(ConanFile):
    name = "brickset"
    version = "0.0"
    license = "<Put the package license here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of Brickset here>"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False],
               "with_openssl": [True, False]}
    default_options = "shared=False", "with_openssl=True"
    generators = "cmake"
    exports_sources = "src/*"

    def requirements(self):
        self.requires("gsoap/2.8.68@jgsogo/stable")
        if self.options.with_openssl:
            self.requires("OpenSSL/1.0.2o@conan/stable")

    def source(self):
        # TODO: Move this logic to CMake
        # Consume WSDL from Brickset
        brickset_api_v2_path = os.path.join(self.source_folder, "src", "brickset")
        if not os.path.exists(brickset_api_v2_path):
            os.makedirs(brickset_api_v2_path)

        api_v2 = "https://brickset.com/api/v2.asmx?WSDL"
        with tools.environment_append(RunEnvironment(self).vars):
            brickset_filepath = os.path.join(brickset_api_v2_path, "brickset_v2.h")
            self.run("wsdl2h -o {} {}".format(brickset_filepath, api_v2))  # May use proxy -rlocalhost:3128  ==> Document an honour env variable like HTTPS_PROXY?
            self.run("soapcpp2 -j -x -C -d{} {} -I{}".format(brickset_api_v2_path, brickset_filepath, os.path.join(self.deps_cpp_info["gsoap"].rootpath, "import")))

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="src")
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["hello"]
