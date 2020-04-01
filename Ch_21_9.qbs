import qbs

CppApplication {

    consoleApplication: true

    property path graph_lib_dir: "../Graph_lib"

    files: [
        "common.cpp",
        "common.h",
        "databaseGUI.h",
        "main.cpp",
        graph_lib_dir +"/Graph.cpp",
        graph_lib_dir +"/GUI.cpp",
        graph_lib_dir +"/Window.cpp",
    ]

    cpp.includePaths: "/home/apollo/opt/fltk/include"
    cpp.libraryPaths: "/home/apollo/opt/fltk/lib"
    cpp.cxxFlags: "-Wno-unused-parameter"
    cpp.staticLibraries: [
                "fltk_images",
                "fltk",
                "png",
                "z",
                "jpeg",
                "Xrender",
                "Xfixes",
                "Xext",
                "Xft",
                "fontconfig",
                "pthread",
                "dl",
                "X11",
            ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
