# -*- coding: UTF-8 -*-

import os
import platform
import logging

if __name__ == "__main__":
    #logging.basicConfig(level = logging.DEBUG)

    directory_solution = r'build/'
    build = 1
    if build == 0:
        build = "Debug"
    else:
        build = "Release"

    name_system = platform.system()
    source_directory = os.getcwd()
    generate_project = r' '
    build_project = r''

    if name_system == 'Windows':
        generate_project += r'cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=' + build + ' ' + source_directory
        build_project = r'mingw32-make'
    elif name_system == 'Linux' or name_system == 'Darwin':
        generate_project += r'cmake -G "Unix Makefiles" ' + source_directory
        build_project = r'make'


    logging.debug(generate_project)
    logging.debug(build_project)

    if not os.path.isdir(directory_solution):
        os.makedirs(directory_solution)

    os.chdir(directory_solution)
    os.system(generate_project)
    os.system(build_project)
