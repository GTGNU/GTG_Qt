include(src/build.pri)

assets.path = $$DESTDIR/assets
assets.files = $$PWD/assets/*

menu.path = $$DESTDIR/menu
menu.files = $$PWD/menu/*

INSTALLS += assets menu
