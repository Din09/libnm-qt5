project(createConnectionExample)
cmake_minimum_required(VERSION 2.6)

find_package(Qt4 REQUIRED)

include(FindPkgConfig)

pkg_check_modules(QTNETWORKMANAGER REQUIRED NetworkManagerQt)
if (NOT QTNETWORKMANAGER_FOUND)
    message(FATAL_ERROR "ERROR: NetworkManagerQt not found. http://projects.kde.org/search?q=networkmanager&scope=all&all_words=1&projects=1&submit=Submit")
endif (NOT QTNETWORKMANAGER_FOUND)

pkg_check_modules(QTNETWORK REQUIRED QtNetwork)
pkg_check_modules(NETWORKMANAGER REQUIRED NetworkManager)

include_directories(${QTNETWORK_INCLUDE_DIRS} ${QTNETWORKMANAGER_INCLUDE_DIRS})
link_directories(${QTNETWORK_LIBRARY_DIRS} ${QTNETWORKMANAGER_LIBRARY_DIRS})

set(createConnectionExample_SRCS
   main.cpp
)

add_executable(createConnectionExample ${createConnectionExample_SRCS})
target_link_libraries(createConnectionExample NetworkManagerQt ${QT_QTCORE_LIBRARY} ${QT_QTDBUS_LIBRARY} ${QT_QTNETWORK_LIBRARY})
