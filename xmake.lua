add_rules("mode.debug","mode.release")

target("maze-routing-algorithm")
    add_rules("qt.application")
    add_files("src/*.cpp")
    add_files("src/*.ui")
    add_files("src/*.h")
    add_frameworks("QtWidgets")
