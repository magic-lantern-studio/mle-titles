bin_PROGRAMS = null

null_SOURCES = \
    main.cpp \
    callback.cpp \
    title.cpp \
    gen/mlchunk.cxx \
    gen/mltables.cxx

#null_HEADERS = \
#    callback.h

null_CPPFLAGS = \
    -DMLE_DIGITAL_PLAYPRINT \
    -DMLE_NOT_DLL \
    -Igen \
    -I$(MLE_ROOT)/include \
    -I/usr/local/include

null_LDADD = \
    $(MLE_ROOT)/lib/mle/runtime/MleIvStage.so \
    $(MLE_ROOT)/lib/mle/runtime/Mle2dSet.so \
    -L$(MLE_ROOT)/lib/mle/runtime -lmlert -lmlloaders \
    -L$(MLE_ROOT)/lib -lplayprint -lmlmath -lmlutil \
    -L/usr/local/lib -lCoin -lSoXt -lXt
    
#null_LDADD = \
#    $(MLE_ROOT)/lib/mle/runtime/Mle2dSet.so \
#    -L$(MLE_ROOT)/lib/mle/runtime -l:MleIvStage.a -lmlert -lmlloaders \
#    -L$(MLE_ROOT)/lib -lplayprint -lmlmath -lmlutil \
#    -L/usr/local/lib -lCoin -lSoXt -lXt