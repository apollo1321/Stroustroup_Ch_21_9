import qbs

CppApplication {
    consoleApplication: true
    files: [
        "common.cpp",
        "common.h",
        "main.cpp",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
