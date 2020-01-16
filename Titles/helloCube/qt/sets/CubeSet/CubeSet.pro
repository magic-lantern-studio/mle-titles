TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = \
    src \
    test

src.file = src/CubeSet.pro
test.file = test/unittest.pro

#app.depends = src
test.depends = src
